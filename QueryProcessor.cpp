//
// Created by Saaketh Koka on 4/16/21.
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor(std::string directoryName) : handler(directoryName) {
   runProcess();
}

std::vector<ResearchDocument*> QueryProcessor::inputQuery(std::string query) {
   if(query.length() == 0 || query.empty()){
       std::cout << "Not valid input" << std::endl;
       return std::vector<ResearchDocument*>();
   }
   std::vector<std::string> allWords = split(query);
   if(allWords.size() == 1){
       return this->handler.andQuery(allWords); //returns an all of a single word is returns all matches to the word
   }
   std::vector<std::string> firstSet;
   bool type = 0; //0 for OR and 1 for AND
   int loc = 0;
   if(allWords.at(0) == "AND"){
       type = 1;
       loc = 1;
       for(int i = 1; i < allWords.size(); i++){
           if(allWords.at(i) == "AUTHOR" || allWords.at(i) == "NOT"){
               break;
           }
           firstSet.push_back(allWords.at(i));
           loc++;
       }
   } else if(allWords.at(0) == "OR"){
       type = 0;
       loc = 1;
       for(int i = 1; i < allWords.size(); i++){
           if(allWords.at(i) == "AUTHOR" || allWords.at(i) == "NOT"){
               break;
           }
           firstSet.push_back(allWords.at(i));
           loc++;
       }
   } else if(allWords.at(0) != "NOT"  && allWords.at(0) != "AUTHOR"){ //look at this to see if it needs to be changed
       type = 1;
       loc = 1;
       firstSet.push_back(allWords.at(0));
   }

   if(loc == allWords.size()){
       if(type){
           return this->handler.andQuery(firstSet);
       } else {
           return this->handler.orQuery(firstSet);
       }
   }
   if(allWords.at(loc) == "NOT"){
       std::string notWord = allWords.at(loc+1);
       if(loc+2 == allWords.size()){ //Not only
           if(!type){ //OR
               return this->handler.orNotQuery(firstSet,notWord);
           } else { //AND
               return this->handler.andNotQuery(firstSet,notWord);
           }
       } else { //Not and Author
           std::string authWord = allWords.at(loc+3);
           if(!type){
               return this->handler.orNotAuthorQuery(firstSet,authWord,notWord);
           } else {
               return this->handler.andNotAuthorQuery(firstSet,authWord,notWord);
           }
       }
   }
   if(allWords.at(loc) == "AUTHOR"){
       std::string authWord = allWords.at(loc+1);
       if(loc == 0){
           return this->handler.authorQuery(authWord);
       }
       if(!type){
           return this->handler.orAuthorQuery(firstSet,authWord);
       } else {
           return this->handler.andAuthorQuery(firstSet,authWord);
       }
   }
   std::cout << "Not valid input" << std::endl;
   return std::vector<ResearchDocument*>();
}

void QueryProcessor::runProcess() {
    std::cout << "Good Day Doctor Fontenot," << std::endl;
    std::cout << "Welcome to the Rayburg Terminal" << std::endl;
    std::cout << "To search type: SEARCH" << std::endl;
    std::cout << "To get statistics type: STATS" << std::endl;
    std::cout << "To create a persistence file type: PERSIST" << std::endl;
    std::cout << "To populate the index type: POPULATE" << std::endl;
    std::cout << "To terminate the program type: TERMINATE" << std::endl;
    bool hasTerminated = false;
    do{
        std::cout << ">> ";
        std::string input;
        getline(std::cin,input);
        if(input == ""){
            std::cout << "Invald command. Please try again." << std::endl;
        } else if(input == "TERMINATE"){
            hasTerminated = true;
        } else if(input == "SEARCH") {
            search();
        } else if(input == "STATS"){
            stats();
        } else if(input == "PERSIST"){
            createPresistenceFile();
        } else if(input == "POPULATE"){
            repopulate();
        } else {
            std::cout << "Invald command. Please try again." << std::endl;
        }
    } while(!hasTerminated);
    std::cout << "Have a nice summer!" << std::endl;
}

std::vector<std::string> QueryProcessor::split(std::string &input) {
    std::vector<std::string> output;
    std::stringstream stream(input);
    std::string holder;
    while(getline(stream,holder,' ')){
        output.push_back(holder);
    }
    return output;
}

void QueryProcessor::generateOutput(std::vector<ResearchDocument *> inputDocs) {
    if(inputDocs.size() == 0){
        std::cout << "This search yields no results." << std::endl;
        return;
    }
    std::cout << "There are " <<  inputDocs.size() << " results to the search" << std::endl;
    int i = 0;
    while(i < 15 && i < inputDocs.size()){
        if(inputDocs.at(i)->title == ""){
            std::cout << "<" << i+1 << "> " << "Title: None" << std::endl;
        } else {
            std::cout << "<" << i+1 << "> " << "Title: " << inputDocs.at(i)->title << std::endl;
        }
        i++;
    }
    bool wantsToExit = false;
    do{
        std::cout << "Please enter the document that you would like to enter or enter NO if you would like to end this search: ";
        std::string input;
        getline(std::cin,input);
        if(input[0] == 'N' || input[0] == 'n'){
            wantsToExit = true;
        } else {
            try{
                int documentValue = stoi(input) - 1;
                if(documentValue < inputDocs.size() && documentValue >= 0 && documentValue < 15){
                    printArticle(inputDocs.at(documentValue));
                } else {
                    std::cout << "Invalid input value. Please try again" << std::endl;
                }
            } catch(std::invalid_argument){
                std::cout << "Invalid input value. Please try again" << std::endl;
            }
        }
    } while(!wantsToExit);
}

void QueryProcessor::printArticle(ResearchDocument *document) {
    if(document->title == ""){
        std::cout << "Title: None" << std::endl;
    } else {
        std::cout << "Title: " << document->title << std::endl;
    }
    std::cout << "ID: " << document->paper_id << std::endl;
    if(document->author_last.size() > 0){
        std::cout << "Author: " << document->author_last.at(0) << std::endl;
    } else {
        std::cout << "Author: None" << std::endl;
    }
    std::string shorterText;
    if(document->wordCount <= 300){
        shorterText = document->text;
    } else {
        std::vector<std::string> words = split(document->text);
        for(int i = 0; i < 300; i++){
            shorterText += words.at(i) + " ";
        }
    }
    std::string outText;
    for(int i = 0; i < shorterText.size(); i++){
        if(i > 0 && i % 90 == 0 ){
            if(shorterText.at(i+1) != ' ' || shorterText.at(i+1) == '.'){
                outText += "-";
            }
            outText += "\n";
            outText +=  "      ";
        }
        outText += shorterText.at(i);
    }
    std::cout << "Text: ";
    std::cout << outText << std::endl;
    std::cout << std::endl;
}

void QueryProcessor::search() {
    bool repeat = false;
    do{
        std::cout << "Search: ";
        std::string query;
        std::getline(std::cin,query);
        std::cout << "The results for " << query << " are: " << std::endl;
        std::vector<ResearchDocument*> documents = inputQuery(query);
        generateOutput(documents);
        std::string anotherSearch;
        std::cout << "Do you want to conduct another search?";
        std::getline(std::cin,anotherSearch);
        if(anotherSearch == "" || anotherSearch[0] == 'Y' || anotherSearch[0] == 'y'){
            repeat = true;
        } else {
            repeat = false;
        }
    } while(repeat);
}

void QueryProcessor::stats() {
    this->handler.printStats();
}

void QueryProcessor::repopulate() {
    std::string typeOfUse;
    bool fileIndex;
    std::cout << "Do you want to populate using a file index? ";
    getline(std::cin,typeOfUse);
    if(typeOfUse == ""){
        std::cout << "Invalid response" << std::endl;
        return;
    } else if(typeOfUse[0] == 'Y' || typeOfUse[0] == 'y'){
        fileIndex = true;
    } else {
        fileIndex = false;
        std::cout << "A directory will be used." << std::endl;
    }
    bool executed = false;
    if(fileIndex){
        std::string authorFile;
        std::string wordIdexFile;
        std::string documentDirectory;
        std::cout << "Please enter the name of the file in which the authors information is located. " << std::endl;
        getline(std::cin,authorFile);
        std::cout << "Please enter the name of the persistant word index file. " << std::endl;
        getline(std::cin,wordIdexFile);
        std::cout << "Please enter the directory of documents " << std::endl;
        getline(std::cin,documentDirectory);
        this->handler.createIndexFromFile(wordIdexFile,authorFile, documentDirectory);
    } else {
        std::string directoryName;
        std::cout << "Please enter the directory name. " << std::endl;
        getline(std::cin,directoryName);
        this->handler.~IndexHandler();
        new (&handler) IndexHandler(directoryName);
    }
}

void QueryProcessor::createPresistenceFile() {
    std::cout << "Creating Persistence File: " << std::endl;
    handler.createAVLPersistanceFile();
    handler.createHashPersistanceFile();
    std::cout << "Finished creating Persistence File." << std::endl;

}

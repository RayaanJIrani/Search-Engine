//
// Created by Saaketh Koka on 4/12/21.
//
#include <chrono>
#include "IndexHandler.h"

IndexHandler::IndexHandler(std::string directoryName) : parser(directoryName), wordIndex(), authorIndex() {
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Indexing words... " << std::endl;
    createWordIndex();
    auto end = std::chrono::high_resolution_clock::now();
    double time = (double) std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000000.00;
    std::cout << "Finished Indexing in " << time << " seconds." << std::endl;
}

void IndexHandler::createWordIndex() {
    createStopWords(); //This fills the stop words AVL Tree
    std::vector<ResearchDocument*>* vect;
    for(auto &document : parser.documents){
        std::stringstream ss(document.text);
        int wordCounter = 0;
        while(!ss.eof()){
            std::string word;
            getline(ss, word, ' ');
            cleanWord(word);
            if(stopWords.contains(word)){
                continue;
            }
            wordCounter++;
            vect = wordIndex.get(word);
            if(vect != nullptr){
                vect->push_back(&document);
            }
            else{
                std::vector<ResearchDocument*> vect;
                vect.push_back(&document);
                wordIndex.insert(word, vect);
            }

        }
        document.wordCount = wordCounter;
        for(auto &author : document.author_last){

            vect = authorIndex.getVal(author);
            if(vect != nullptr){
                vect->push_back(&document);
            }
            else{
                std::vector<ResearchDocument*> vect;
                vect.push_back(&document);
                authorIndex.insert(author, vect);
            }
        }
    }
}
void IndexHandler::printDocuments(std::string word) {
    cleanWord(word);
    if(!wordIndex.contains(word)){
        std::cout << "Word does not exist in documents." << std::endl;
        return;
    }
    std::vector<ResearchDocument*> *documents = wordIndex.get(word);
    std::vector<ResearchDocument*> uniqueDocuments;

    for(auto &c : *documents){
        bool isInUniqueDocuments = false;
        for(auto &d : uniqueDocuments){
            if(d == c){
                isInUniqueDocuments = true;
                break;
            }
        }
        if(!isInUniqueDocuments){
            uniqueDocuments.push_back(c);
        }
    }
    for(auto &c : uniqueDocuments){
        std::cout << c->paper_id << std::endl;
    }
    std::cout << "Word Searched For: " << word << std::endl;
}

void IndexHandler::cleanWord(std::string &word) {
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
}

void IndexHandler::createStopWords() {
    std::fstream inFS("words.txt");
    if(!inFS.is_open()){
        std::cout << "File not opened: " << std::endl;
        assert(false);
    }
    while(!inFS.eof()){
        std::string stopWord;
        getline(inFS,stopWord);
        cleanWord(stopWord);
        stopWords.insert(stopWord,1);
    }
    inFS.close();
}

bool IndexHandler::isInVector(ResearchDocument *doc, std::vector<ResearchDocument *> &vect) {
    for(const auto &c : vect){
        if(c == doc){
            return true;
        }
    }
    return false;
}

std::vector<ResearchDocument *> IndexHandler::uniquifyVect(std::vector<ResearchDocument *> a) {
    std::vector<ResearchDocument*> returnVect;
    for(auto &c: a){
        if(!isInVector(c,returnVect)){
            returnVect.push_back(c);
        }
    }
    return returnVect;
}

std::vector<ResearchDocument *>
IndexHandler::findIntersection(std::vector<ResearchDocument *> a, std::vector<ResearchDocument *> b) {
    std::vector<ResearchDocument*> returnVect;
    for(auto &c: a){
        if(isInVector(c,b) && !isInVector(c,returnVect)){
            returnVect.push_back(c);
        }
    }
    return returnVect;
}

std::vector<ResearchDocument *>
IndexHandler::findUnion(std::vector<ResearchDocument *> a, std::vector<ResearchDocument *> b) {
    std::vector<ResearchDocument*> returnVect;
    for(auto &c: a){
        if(!isInVector(c,returnVect)){
            returnVect.push_back(c);
        }
    }
    for(auto &c: b){
        if(!isInVector(c,returnVect)){
            returnVect.push_back(c);
        }
    }
    return returnVect;
}

std::vector<ResearchDocument *>
IndexHandler::findDifference(std::vector<ResearchDocument *> a, std::vector<ResearchDocument *> subtractVect) {
    std::vector<ResearchDocument*> returnVect;
    for(auto &c: a){
        if(!isInVector(c,subtractVect) && !isInVector(c,returnVect)){
            returnVect.push_back(c);
        }
    }
    return returnVect;
}



std::vector<ResearchDocument *> IndexHandler::andQuery(std::vector<std::string> andWordVect) {
    for(auto &c : andWordVect){
        cleanWord(c);
    }
    std::vector<ResearchDocument*> documentsToReturn;
    if(andWordVect.size() == 0){
        throw std::invalid_argument("No words passed in vector");
    }
    if(andWordVect.size() == 1){
        std::vector<ResearchDocument*> *vect = wordIndex.get(andWordVect[0]);
        if(vect == nullptr){
            return std::vector<ResearchDocument*>();
        }
        return uniquifyVect(*vect);
    }
    std::vector<ResearchDocument*> *vect = wordIndex.get(andWordVect[0]);
    if(vect == nullptr){
        return std::vector<ResearchDocument*>();
    }
    documentsToReturn = uniquifyVect(*wordIndex.get(andWordVect[0]));
    for(auto &c : andWordVect){
        vect = wordIndex.get(c);
        if(vect == nullptr){
            return std::vector<ResearchDocument*>();
        }
        documentsToReturn = findIntersection(documentsToReturn, *vect);
    }
    ranker(documentsToReturn, andWordVect);
    return documentsToReturn;
}

std::vector<ResearchDocument *> IndexHandler::orQuery(std::vector<std::string> orWordVect) {
    for(auto &c : orWordVect){
        cleanWord(c);
    }
    std::vector<ResearchDocument*> documentsToReturn;
    if(orWordVect.size() == 0){
        throw std::invalid_argument("No words passed in vector");
    }
    if(orWordVect.size() == 1){
        std::vector<ResearchDocument*> *vect = wordIndex.get(orWordVect[0]);
        if(vect == nullptr){
            return std::vector<ResearchDocument*>();
        }
        return uniquifyVect(*vect);
    }
    std::vector<ResearchDocument*> *vect = wordIndex.get(orWordVect[0]);
    if(vect == nullptr){
        return std::vector<ResearchDocument*>();
    }
    documentsToReturn = uniquifyVect(*wordIndex.get(orWordVect[0]));
    for(auto &c : orWordVect){
        vect = wordIndex.get(c);
        if(vect == nullptr){
            continue;
        }
        documentsToReturn = findUnion(documentsToReturn, *vect);
    }
    ranker(documentsToReturn, orWordVect);
    return documentsToReturn;
}

std::vector<ResearchDocument *> IndexHandler::andNotQuery(std::vector<std::string> andWordVect, std::string notWord) {
    std::vector<ResearchDocument*> returnVect = andQuery(andWordVect);
    cleanWord(notWord);
    std::vector<ResearchDocument*> *notWordVect = wordIndex.get(notWord);
    if(notWordVect == nullptr){
        return returnVect;
    }
    returnVect = findDifference(returnVect, *notWordVect);
    ranker(returnVect, andWordVect);
    return returnVect;
}

std::vector<ResearchDocument *> IndexHandler::orNotQuery(std::vector<std::string> orWordVect, std::string notWord) {
    std::vector<ResearchDocument*> returnVect = orQuery(orWordVect);
    cleanWord(notWord);
    std::vector<ResearchDocument*> *notWordVect = wordIndex.get(notWord);
    if(notWordVect == nullptr){
        return returnVect;
    }
    returnVect = findDifference(returnVect, *notWordVect);
    ranker(returnVect, orWordVect);
    return returnVect;
}

std::vector<ResearchDocument *> IndexHandler::authorQuery(std::string author) {
    std::vector<ResearchDocument*> *vect =  authorIndex.getVal(author);
    if(vect == nullptr){
        return std::vector<ResearchDocument*>();
    }
    std::vector<ResearchDocument*> returnVect;
    for(auto &c : *vect){
        if(!isInVector(c, returnVect)){
            returnVect.push_back(c);
        }
    }
    return returnVect;
}

std::vector<ResearchDocument *> IndexHandler::authorNotQuery(std::string author, std::string notWord) {
    cleanWord(notWord);
    std::vector<ResearchDocument*> *authorVect =  authorIndex.getVal(author);
    std::vector<ResearchDocument*> *notWordVect =  authorIndex.getVal(author);
    std::vector<ResearchDocument*> returnVect;
    if(authorVect == nullptr){
        return std::vector<ResearchDocument*>();
    }
    for(auto &c : *authorVect){
        if(!isInVector(c, *notWordVect) && !isInVector(c, returnVect)){
            returnVect.push_back(c);
        }
    }
    return returnVect;
}

std::vector<ResearchDocument *>
IndexHandler::orAuthorQuery(std::vector<std::string> orVect, std::string author) {
    std::vector<ResearchDocument*> *authorVect = authorIndex.getVal(author);
    if(authorVect == nullptr){
        return std::vector<ResearchDocument*>();
    }
    std::vector<ResearchDocument*> returnVect = orQuery(orVect);
    returnVect = findIntersection(returnVect, *authorVect);
    ranker(returnVect, orVect);
    return returnVect;
}

std::vector<ResearchDocument *> IndexHandler::andAuthorQuery(std::vector<std::string> andVect, std::string author) {
    std::vector<ResearchDocument*> *authorVect = authorIndex.getVal(author);
    if(authorVect == nullptr){
        return std::vector<ResearchDocument*>();
    }
    std::vector<ResearchDocument*> returnVect = andQuery(andVect);
    returnVect = findIntersection(returnVect, *authorVect);
    ranker(returnVect, andVect);
    return returnVect;
}

std::vector<ResearchDocument *>
IndexHandler::orNotAuthorQuery(std::vector<std::string> orVect, std::string author, std::string notWord) {
    std::vector<ResearchDocument*> orAuthorQueryVect = orAuthorQuery(orVect,author);
    std::vector<ResearchDocument*> orNotQueryVect = orNotQuery(orVect, notWord);
    std::vector<ResearchDocument*> returnVect = findIntersection(orAuthorQueryVect, orNotQueryVect);
    ranker(returnVect, orVect);
    return returnVect;
}

std::vector<ResearchDocument *>
IndexHandler::andNotAuthorQuery(std::vector<std::string> andVect, std::string author, std::string notWord) {
    std::vector<ResearchDocument*> andAuthorQueryVect = andAuthorQuery(andVect,author);
    std::vector<ResearchDocument*> andNotQueryVect = andNotQuery(andVect, notWord);
    std::vector<ResearchDocument*> returnVect = findIntersection(andAuthorQueryVect, andNotQueryVect);
    ranker(returnVect, andVect);
    return returnVect;
}



void IndexHandler::ranker(std::vector<ResearchDocument *> &vect, const std::vector<std::string>& wordVect) {
    std::vector<double> scores;
    for(auto &c : vect){
        scores.push_back(calcScore(c, wordVect));
    }
    quickSort(vect, scores, vect.size());
    std::reverse(vect.begin(), vect.end());


}
template<class A, class B>
void IndexHandler::quickSort(std::vector<A>& vect, std::vector<B> &scores, int size){
    quickSortRec(vect, scores, 0, size - 1);

}
template<class A, class B>
void IndexHandler::quickSortRec(std::vector<A>& vect, std::vector<B> &scores, int start, int end){
    if(start >= end){
        return;
    }
    B pivot = scores[end];
    int x = partition(vect, scores, start, end - 1, pivot);
    quickSortRec(vect, scores, start, x - 1);
    quickSortRec(vect, scores, x + 1, end);

}
template<class A, class B>
int IndexHandler::partition(std::vector<A>& vect, std::vector<B> &scores, int start, int end, B pivot){
    B temp;
    int i = start, j = end;
    A temp2;
    while(i < j){
        while(scores[i] < pivot){
            i++;
        }
        while(scores[j] > pivot){
            j--;
        }
        if(i > j){
            break;
        }
        temp = scores[i];
        scores[i] = scores[j];
        scores[j] = temp;

        temp2 = vect[i];
        vect[i] = vect[j];
        vect[j] = temp2;

        i++;
        j--;
    }
    if(scores[i] < scores[end + 1]){
        i++;
    }
    temp = scores[i];
    scores[i] = scores[end + 1];
    scores[end + 1] = temp;

    temp2 = vect[i];
    vect[i] = vect[end + 1];
    vect[end + 1] = temp2;
    return i;
}

double IndexHandler::calcScore(ResearchDocument *doc, const std::vector<std::string>& wordVect) {
    int counter = 0;
    std::vector<std::string> vect = wordVect;
    for(auto& c: vect){
        cleanWord(c);
    }
    for(auto & c : vect){
        std::vector<ResearchDocument*> *documentsFromWord = wordIndex.get(c);
        if(documentsFromWord == nullptr){
            continue;
        }
        for(auto &d : *documentsFromWord){
            if(d == doc){
                counter++;
            }
        }
    }
    return (double) counter / (double)doc->wordCount;
}

void IndexHandler::printStats() {
    std::vector<DSAVLTreeNode<std::string, std::vector<ResearchDocument *>>> vect = wordIndex.getVectOfElements();
    std::vector<double> vectDocumentCounter;
    for(auto &c : vect){
        vectDocumentCounter.push_back(c.get_value().size());
    }
    quickSort(vect, vectDocumentCounter, vect.size());
    std::cout << std::endl;
    std::cout << "Statistics:" << std::endl;
    int totalWords = 0;
    for(auto &c : parser.documents){
        totalWords += c.wordCount;
    }
    double avgWords = (double)totalWords / (double)parser.documents.size();
    std::cout << "Total Documents Parsed: " << parser.documents.size() << std::endl;
    std::cout << "Average Number Words in each Document: " << avgWords << std::endl;
    std::cout << "Number of unique words: " << vect.size() << std::endl;
    std::cout << "Number of unique author names: " << authorIndex.getNumElememts() << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Top 50 most frequent words: " << std::endl;
    std::reverse(vect.begin(), vect.end());
    for(int i = 0; i < 50; i++){
        std::cout << vect[i].get_key() << " " << vect[i].get_value().size() << std::endl;
    }


}


void IndexHandler::createIndexFromFile(std::string wordIndexFilename, std::string authorIndexFilename,
                                       std::string directoryName) {
    parser.reParseDocuments(directoryName);
    this->wordIndex.~DSAVLTree<std::string, std::vector<ResearchDocument*>>();
    new (&wordIndex) DSAVLTree<std::string, std::vector<ResearchDocument*>>();
    std::fstream infs(wordIndexFilename);
    if(!infs.is_open()){
        std::cout << "file failed to open: " << wordIndexFilename <<  std::endl;
        assert(false);
    }
    std::string buffer;
    std::string key;
    std::string valueBuffer;
    while(!infs.eof()){
        getline(infs, buffer);
        std::stringstream ss(buffer);
        std::vector<ResearchDocument*> vect;
        ss >> key;
        while(!ss.eof()){
            ss >> valueBuffer;
            vect.push_back(parser.findDocumentID(valueBuffer));
        }
        wordIndex.insert(key, vect);
    }
    infs.close();

    DSHashTable<std::string, std::vector<ResearchDocument*>> newTable;
    infs.open(authorIndexFilename);
    if(!infs.is_open()){
        std::cout << "file failed to open: " << authorIndexFilename <<  std::endl;
        assert(false);
    }
    while(!infs.eof()){
        getline(infs, buffer);
        std::stringstream ss(buffer);
        std::vector<ResearchDocument*> vect;
        ss >> key;
        while(!ss.eof()){
            ss >> valueBuffer;
            vect.push_back(parser.findDocumentID(valueBuffer));
        }
        newTable.insert(key, vect);
    }
    authorIndex = newTable;
    infs.close();
}

void IndexHandler::createAVLPersistanceFile() {
    wordIndex.printTreeToFile("PersistanceAVL.txt");
}

void IndexHandler::createHashPersistanceFile() {
    authorIndex.printTableToFile("PersistanceHash.txt");
}

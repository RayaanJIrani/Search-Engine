//
// Created by Saaketh Koka on 4/10/21.
//

#include "DocumentParser.h"
#include <filesystem>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include <string>


DocumentParser::DocumentParser(std::string directoryName) {
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Parsing Documents... " << std::endl;
    for (const auto & entry : std::experimental::filesystem::directory_iterator(directoryName)){
        if(entry.path().extension().string() != ".json"){
            continue;
        }

        FILE* fp = fopen(entry.path().c_str(), "r"); // non-Windows use "r"

        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        rapidjson::Document d;
        d.ParseStream(is);
        rapidjson::Value &id = d["paper_id"];
        rapidjson::Value &abstract = d["abstract"];
        rapidjson::Value &body = d["body_text"];
        rapidjson::Value &title = d["metadata"]["title"];
        rapidjson::Value &authors = d["metadata"]["authors"];
        std::string text;
        for(int i = 0; i < abstract.Size(); i++){
            if(abstract[i].HasMember("text")){
                text += abstract[i]["text"].GetString();
                text += " ";
            }
        }
        for(int i = 0; i < body.Size(); i++){
            if(body[i].HasMember("text")){
                text += body[i]["text"].GetString();
                text += " ";
            }
        }
        std::vector<std::string> author_last;
        for(int i = 0; i < authors.Size(); i++){
            if(authors[i].HasMember("last")){
                author_last.push_back(authors[i]["last"].GetString());
            }
        }
        ResearchDocument doc(id.GetString(), title.GetString(), text, author_last);
        documents.push_back(doc);
        fclose(fp);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double time = (double) std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000000.00;
    std::cout << "Finished Parsing in " << time << " seconds." << std::endl;
}

void DocumentParser::sortDocuments() {
    std::sort(documents.begin(), documents.end());
}

ResearchDocument *DocumentParser::findDocumentID(std::string ID) {
    int start = 0;
    int end  = documents.size() - 1;
    int middle = (end + start) / 2;
    while(end >= start){
        if(documents[middle].paper_id == ID){
            return &documents[middle];
        }
        if(ID < documents[middle].paper_id){
            end = middle - 1;
        }
        else {
            start = middle + 1;
        }
        middle = (end + start)/2;
    }
}

void DocumentParser::reParseDocuments(std::string directoryName) {
    documents.clear();
    for (const auto & entry : std::experimental::filesystem::directory_iterator(directoryName)){
        if(entry.path().extension().string() != ".json"){
            continue;
        }

        FILE* fp = fopen(entry.path().c_str(), "r"); // non-Windows use "r"

        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        rapidjson::Document d;
        d.ParseStream(is);
        rapidjson::Value &id = d["paper_id"];
        rapidjson::Value &abstract = d["abstract"];
        rapidjson::Value &body = d["body_text"];
        rapidjson::Value &title = d["metadata"]["title"];
        rapidjson::Value &authors = d["metadata"]["authors"];
        std::string text;
        for(int i = 0; i < abstract.Size(); i++){
            if(abstract[i].HasMember("text")){
                text += abstract[i]["text"].GetString();
                text += " ";
            }
        }
        for(int i = 0; i < body.Size(); i++){
            if(body[i].HasMember("text")){
                text += body[i]["text"].GetString();
                text += " ";
            }
        }
        std::vector<std::string> author_last;
        for(int i = 0; i < authors.Size(); i++){
            if(authors[i].HasMember("last")){
                author_last.push_back(authors[i]["last"].GetString());
            }
        }
        ResearchDocument doc(id.GetString(), title.GetString(), text, author_last);
        documents.push_back(doc);
        fclose(fp);
    }
    sortDocuments();
}
//
// Created by Saaketh Koka on 4/16/21.
//
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include "ResearchDocument.h"
#include "IndexHandler.h"

class QueryProcessor {
private:
    IndexHandler handler;
    void runProcess();
    std::vector<std::string> split(std::string& input);
    std::vector<ResearchDocument*> inputQuery(std::string query); //This takes in the Query and does everything which needs to be one on it
    void generateOutput(std::vector<ResearchDocument*> inputDocs);
    void printArticle(ResearchDocument* document);
    void search();
    void stats();
    void repopulate();
    void createPresistenceFile();

public:
    /**
     * Calls the Index Handler Constructor with input directoryName
     * Calls run process method which executes the user interface
     * @param directoryName - the name of the directory which is to be parsed in
     */
    QueryProcessor(std::string directoryName); //constructor
};



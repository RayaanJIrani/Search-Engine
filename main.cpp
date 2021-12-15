#include <iostream>
#include <string>
#include "porter2_stemmer.h"
#include "QueryProcessor.h"
#include <algorithm>
#include <sstream>

int main(int argc, char* argv[]) {
    if(argc == 1){
    } else {
//        IndexHandler h1(argv[1]);
//        std::vector<std::string> wordVector = {"virus", "research", "ebola"};
//        std::vector<ResearchDocument *> vect = h1.andQuery(wordVector);
//        for (auto &c : vect) {
//            std::cout << c->paper_id << " " << c->title << std::endl;
//        }
//        std::cout << "Num docs: " << vect.size() << std::endl;
        QueryProcessor qp(argv[1]);

    }

    return 0;
}

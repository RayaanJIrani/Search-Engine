//
// Created by Saaketh Koka on 4/10/21.
//

#pragma once
#include <string>
#include <vector>
#include "DSAVLTree.h"
#include "DSAVLTreeString.h"
#include "DSHashTable.h"
#include "ResearchDocument.h"
#include <experimental/filesystem>
class DocumentParser {
    friend class IndexHandler;
private:
    std::vector<ResearchDocument> documents;
public:

    /**
     * Constructor -- enters all json files into the vector of documents
     * @param directoryName - name of the directory being parsed
     */
    DocumentParser(std::string directoryName);

    /**
     * Sorts document vector based on Document IDs
     */
    void sortDocuments();

    /**
     * Returns the pointer to a document with a certain ID
     * @param ID - ID of the dcoument being searched for
     * @return ReaserchDocumet* - the pointer to the document being looked for
     */
    ResearchDocument* findDocumentID(std::string ID);

    /**
     * Empties the documents vector, parses the documents in directory path
     * @param directoryPath
     */
    void reParseDocuments(std::string directoryPath);
};



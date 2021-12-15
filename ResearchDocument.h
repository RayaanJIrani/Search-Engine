//
// Created by Saaketh Koka on 4/10/21.
//
#pragma once
#include <string>
#include <vector>


//MVP -- minimal viable product
struct ResearchDocument{
    std::string paper_id;
    std::string title;
    std::vector<std::string> author_last;
    std::string text;
    int wordCount;


    /**
     * Default constructor of Reaserch Document
     * @param paperId - the paperID of the document
     * @param title - the title of the document
     * @param text - the raw text of the document
     * @param author_last - a vector of the last names of the authors of the documents
     */
    ResearchDocument(const std::string &paperId, const std::string &title, const std::string &text, const std::vector<std::string> author_last);

    /**
     * Overloaded Comparison Operator - compares the Document ID's of the documents
     * @return bool - if the two Reaserh Documents are the same
     */
    bool operator== (const ResearchDocument& data) const;

    /**
     * Compares the two documents document ID's to see if the Document ID of *this is less than the ID of other
     * @param data - the other document being compared
     * @return bool - returns if *this is less than data
     */
    bool operator< (const ResearchDocument& data) const;



};


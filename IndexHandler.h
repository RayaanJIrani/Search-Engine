//
// Created by Rayaan Irani, OBE on 4/12/21.
//


#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include "porter2_stemmer.h"
#include "DocumentParser.h"
#include <algorithm>
class IndexHandler {
private:
    DocumentParser parser;
    DSAVLTree<std::string, std::vector<ResearchDocument*>> wordIndex;
    DSHashTable<std::string, std::vector<ResearchDocument*>> authorIndex;
    DSAVLTree<std::string, int> stopWords;


    void createWordIndex();
    void createStopWords();
    void cleanWord(std::string& word);
    bool isInVector(ResearchDocument* doc, std::vector<ResearchDocument*> &vect);

    std::vector<ResearchDocument*> uniquifyVect(std::vector<ResearchDocument*> a);
    std::vector<ResearchDocument*> findIntersection(std::vector<ResearchDocument*> a,
                                                    std::vector<ResearchDocument*> b);
    std::vector<ResearchDocument*> findUnion(std::vector<ResearchDocument*> a,
                                                    std::vector<ResearchDocument*> b);
    std::vector<ResearchDocument*> findDifference(std::vector<ResearchDocument*> a,
                                             std::vector<ResearchDocument*> subtractVect);

    template<class A, class B>
    void quickSort(std::vector<A>& vect, std::vector<B> &scores, int size);
    template<class A, class B>
    void quickSortRec(std::vector<A>& vect, std::vector<B> &scores, int start, int end);
    template<class A, class B>
    int partition(std::vector<A>& vect, std::vector<B> &scores, int start, int end, B pivot);

    double calcScore(ResearchDocument* doc, const std::vector<std::string>& wordVect);
    void ranker(std::vector<ResearchDocument*>& vect, const std::vector<std::string>& wordVect);



public:

    /**
     * IndexHandler constructor
     * Calls the Document Parser constructor with input directoryName
     * Converts the document vector to a DSAVL tree of unique words and hash map of unique authors
     * @param directoryName - the name of the directory being parsed
     */
    IndexHandler(std::string directoryName);

    /**
     * Prints all of the  IDs for documents associated with a given word
     * @param word - word being compared
     */
    void printDocuments(std::string word);

    /**
     * Returns a vector of pointers to documents containing both input words.
     * @param First Word Query
     * @param Second Word Query
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> andQuery(std::vector<std::string> andWordVect);
    /**
     * Returns a vector of pointers to documents containing at least one of the inputs.
     * @param First Word Query
     * @param Second Word Query
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> orQuery(std::vector<std::string> orWordVect);
    /**
     * Returns a vector of pointers to documents containing both input words which do not mention the Word to exclude.
     * @param First Word Query
     * @param Second Word Query
     * @param Word to exclude
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> andNotQuery(std::vector<std::string> andWordVect, std::string notWord);
    /**
     * Returns a vector of pointers to documents containing at least one of the two input words which do not mention the
     * Word to exclude.
     * @param First Word Query
     * @param Second Word Query
     * @param Word to exclude
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> orNotQuery(std::vector<std::string> orWordVect, std::string notWord);
    /**
     * Returns a vector of pointers to documents written by Author's with a certain last name.
     * @param author
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> authorQuery(std::string author);
    /**
     * Returns a vector of pointers to documents written by Authors with a certain last name that do not include the
     * not word.
     * @param Author Last Name: std::string
     * @param Not Word: std::string
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> authorNotQuery(std::string author, std::string notWord);
    /**
     * Returns a vector of pointers to documents written by Authors with a certain last name that include at least
     * one of the words passed in through a vector.
     * @param Vector of words: std::vector<std::string>
     * @param Author Last Name: std::string
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> orAuthorQuery(std::vector<std::string> orVect, std::string author);
    /**
     * Returns a vector of pointers to documents written by Authors with a certain last name that include all of the
     * words passed in through a vector.
     * @param Vector of Words: std::vector<std::string>
     * @param Author Last Name: std::string
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> andAuthorQuery(std::vector<std::string> andVect, std::string author);
    /**
     * Returns a vector of pointers to documents written by Authors with a certain last name that include at least one
     * of the words that are passed in through the OR vector and do not include the NOT word.
     * @param Vector of Words: std::vector<std::string>
     * @param Author Last Name: std::string
     * @param Word to Exclude: std::string
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> orNotAuthorQuery(std::vector<std::string> orVect, std::string author, std::string notWord);
    /**
     * Returns a vector of pointers to documents written by Authors with a certain last name that include all of the
     * words that are passed in through the AND vector and do not include the NOT word.
     * @param Vector of Words: std::vector<std::string>
     * @param Author Last Name: std::string
     * @param Word to Exclude: std::string
     * @return std::vector<ResearchDocument*>
     */
    std::vector<ResearchDocument*> andNotAuthorQuery(std::vector<std::string> andVect, std::string author, std::string notWord);

    /**
     * Prints the statsitics of wordIndex and author index: total words, average words, unique wo
     * total words, average words, unique words, unique authors, top words
     */
    void printStats();

    /**
     * generates wordIndex and authorIndex from a persistence file
     * @param wordIndexFilename - the filename of the word persistence file
     * @param authorIndexFilename - filename of the author persistence file
     * @param directoryName - the directory in which both files are located
     */
    void createIndexFromFile(std::string wordIndexFilename, std::string authorIndexFilename, std::string directoryName);


    /**
     * generates a persistence file using wordIndex
     */
    void createAVLPersistanceFile();

    /**
     * generates a persistence file using authorIndex
     */
    void createHashPersistanceFile();

};



//
// Created by Saaketh Koka on 4/12/21.
//

#include "ResearchDocument.h"

ResearchDocument::ResearchDocument(const std::string &paperId, const std::string &title, const std::string& text, const std::vector<std::string> author_last): paper_id(paperId), title(title), text(text), author_last(author_last){
    wordCount = 0;
}

bool ResearchDocument::operator==(const ResearchDocument &data) const {
    return this->paper_id.compare(data.paper_id) == 0;
}

bool ResearchDocument::operator<(const ResearchDocument &data) const {
    return (this->paper_id < data.paper_id);
}


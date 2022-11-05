/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#include <grammar.h>

#include <fstream>
#include <sstream>

#include <assertions.h>

Grammar::Grammar(const std::string file_path) {
    std::ifstream infile(file_path);

    std::string line;
    while (std::getline(infile, line)) {
        // Remove trailing whitespace.
        while(!line.empty() && std::isspace(line.back())) line.pop_back();
        // Split on the spaces.
        std::stringstream stream(line);
        std::string lhs, arrow, rhs_inst;
        std::vector<std::string> rhs;
        stream >> lhs >> arrow;
        ASSERT(arrow == "->");
        while (stream.rdbuf()->in_avail() != 0) {
            stream >> rhs_inst;
            rhs.push_back(rhs_inst);
        }
        productions.push_back(Production(lhs, rhs));
    }

    this->actions = SemanticActions(this->productions.size());
}

Grammar::~Grammar() {}

const Production &Grammar::getProduction(const unsigned int index) const {
    ASSERT(index < this->productions.size());
    return this->productions.at(index);
}

const ActionFunction Grammar::getAction(unsigned int index) const {
    return this->actions.getAction(index);
}

void Grammar::setAction(unsigned int index, ActionFunction action) {
    this->actions.putSemanticAction(action, index);
}

std::string Grammar::to_string() const {
    std::string result = "";
    for (
        auto i = this->productions.begin(); i != this->productions.end(); i++
    ) {
        result += (*i).to_string() + "\n";
    }
    return result;
}
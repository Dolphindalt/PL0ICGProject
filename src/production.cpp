/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#include <production.h>

Production::Production() {}

Production::Production(std::string lhs, std::vector<std::string> rhs) 
: lhs(lhs), rhs(rhs) {}

Production::~Production() {}

const std::vector<std::string> &Production::getRHS() const {
    return this->rhs;
}

const std::string &Production::getLHS() const {
    return this->lhs;
}

std::string Production::to_string() const {
    std::string result = "";
    result += this->lhs;
    result += " ->";
    for (auto i = this->rhs.begin(); i != this->rhs.end(); i++) {
        result += " " + *i;
    }
    return result;
}
/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#ifndef PRODUCTION_H__
#define PRODUCTION_H__

#include <string>
#include <vector>

class Production {
public:
    Production();
    Production(std::string lhs, std::vector<std::string> rhs);
    virtual ~Production();

    const std::vector<std::string> &getRHS() const;
    const std::string &getLHS() const;

    std::string to_string() const;
private:
    std::string lhs;
    std::vector<std::string> rhs;
};

#endif
/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#ifndef GRAMMAR_H__
#define GRAMMAR_H__

#include <string>
#include <vector>

#include <semantic_actions.h>
#include <production.h>

class Grammar {
public:
    Grammar(const std::string file_path);
    virtual ~Grammar();

    /**
     * Returns a production from the grammar. Productions are number from 
     * 0 to size - 1.
     * @param index The production number.
     * @return The production.
     */
    const Production &getProduction(const unsigned int index) const;

    /**
     * Returns a semantic action associated with the production numbered index.
     * @param index The index associated with the production and action.
     * @return The semantic action function.
     */
    const ActionFunction getAction(unsigned int index) const;

    /**
     * Sets the semantic action for the production numbered as index.
     * @param index The index of the production to set an action for.
     * @param action The semantic action to associate with the production.
     */
    void setAction(unsigned int index, ActionFunction action);

    std::string to_string() const;
private:
    std::vector<Production> productions;
    SemanticActions actions;
};

#endif
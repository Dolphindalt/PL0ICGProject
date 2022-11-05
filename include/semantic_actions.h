/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#ifndef SEMANTIC_ACTIONS_H__
#define SEMANTIC_ACTIONS_H__

#include <functional>
#include <stack>
#include <optional>
#include <vector>

#include <ast.h>
#include <production.h>

using Symbol = std::string;

// Huge dude here.
using ActionFunction = std::function<ASTNodePtr(std::stack<ASTNodePtr> *, const Production, std::vector<Symbol>)>;

class SemanticActions {
public:
    // Default constructor for zero initialization.
    SemanticActions();

    /**
     * Initializes the semantic actions storage. The amount should be equal to 
     * the number of productions in the grammar.
     * @param amount The amount of semantic actions.
     */
    SemanticActions(unsigned int amount);

    // Deconstructor deletes the actions memory.
    virtual ~SemanticActions();

    /**
     * Inserts a semantic action for the production index.
     * @param action The semantic action function.
     * @param index The production number to attach the action to.
     */
    void putSemanticAction(
        ActionFunction action, const unsigned int index
    );

    /**
     * Given a production number, returns the associated action.
     * @param index The production number.
     * @return The action associated with the production.
     */
    ActionFunction getAction(const unsigned int index) const;
private:
    unsigned int amount;
    std::vector<ActionFunction> actions;
};

#endif
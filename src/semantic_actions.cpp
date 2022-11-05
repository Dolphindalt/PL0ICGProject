/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#include <semantic_actions.h>

#include <assertions.h>

static ASTNodePtr defaultAction(
    std::stack<ASTNodePtr> *previousActions,
    const Production production,
    std::vector<Symbol> symbols
) {
    // For the default action, we simply do nothing.
    return nullptr;
}

SemanticActions::SemanticActions() {}

SemanticActions::SemanticActions(unsigned int amount) 
: amount(amount) {
    // All actions are initialized to the default action.
    for (unsigned int i = 0; i < amount; i++) {
        this->actions.push_back(defaultAction);
    }
}

SemanticActions::~SemanticActions() {}

void SemanticActions::putSemanticAction(
    ActionFunction action, const unsigned int index
) {
    ASSERT(index < this->amount);
    this->actions[index] = action;
}

ActionFunction SemanticActions::getAction(const unsigned int index) const {
    ASSERT(index < this->amount);
    return this->actions.at(index);
}
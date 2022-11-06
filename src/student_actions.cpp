/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#include <student_actions.h>

#include <logging.h>

/**
 * A semantic action is a function that has the following prototype:
 * ASTNodePtr fuction(std::stack<AStNodePtr> &, const Production, std::vector<std::string>);
 * Semantic actions should return nullptr if the result is unused, which is 
 * the case with "if statement" and "while loop" nodes. Otherwise, a result 
 * in the form of an ASTNodePtr is returned and will be pushed onto the 
 * stack automatically. The stack and production are utilized to perform the 
 * action, using the stack to fetch previous result and the production to 
 * get information, such as operations, from.
 * 
 * For a description of AST nodes, see ast.h.
 * 
 * For the semantic action calling mechanism, see the driver in parser.cpp.
 * 
 * By default, all semantic actions do nothing and return a nullptr. See
 * semantic_actions.h for more information.
 */
void addSemanticActions(Grammar &grammar) {
    // Add your semantic actions here.
    // Example:
    // When production 1 is reduced, the function called action1 is called.
    // You can reuse the same function in multiple semantic actions.
    // grammar.setAction(1, action1);
    // grammar.setAction(10, action1);
    WARNING_LOGV(
        "Implement your semantic actions here and remove this warning when done"
    );
}

/**
 * The rest of this file is for you to write your semantic action functions.
 */
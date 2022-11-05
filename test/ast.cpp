/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#include <catch2/catch.hpp>

#include <ast.h>

TEST_CASE("AST Smoke Test", "[AST]") {

    // Constructing an AST for a + b * c.
    const ASTNodePtr a_var = std::make_shared<ASTNode>(AST_VARIABLE, "a");
    const ASTNodePtr b_var = std::make_shared<ASTNode>(AST_VARIABLE, "b");
    const ASTNodePtr c_var = std::make_shared<ASTNode>(AST_VARIABLE, "c");

    ASTNodePtr add_expr = std::make_shared<ASTNode>(AST_BINARY_EXPRESSION, "+");
    ASTNodePtr mul_expr = std::make_shared<ASTNode>(AST_BINARY_EXPRESSION, "*");

    mul_expr->addChild(b_var);
    mul_expr->addChild(c_var);

    add_expr->addChild(a_var);
    add_expr->addChild(mul_expr);

    ASTNode::printTree(add_expr, 3);
}
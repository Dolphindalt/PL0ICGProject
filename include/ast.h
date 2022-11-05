/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#ifndef AST_H__
#define AST_H__

#include <memory>
#include <vector>
#include <string>

class ASTNode;

using ASTNodePtr = std::shared_ptr<ASTNode>;

typedef enum ast_node_type {
    /**
     * The value of the binary expression node is the operator.
     * The binary expression has two children, one for each operand.
     */
    AST_BINARY_EXPRESSION,
    /**
     * The value of the unary expression node is the operator.
     * The unary expression has one child, the operand.
     */
    AST_UNARY_EXPRESSION,
    /**
     * The call expression value is the name of the function.
     * The call expression has no children, but if this language had arguments 
     * and a return type, these would be the children.
     */
    AST_CALL_EXPRESSION,
    /**
     * The if statement value is "if".
     * The children of the if statement are the conditional expression and 
     * the body of the if statement.
     */
    AST_IF_STATEMENT,
    /**
     * The while loop statement value is "while".
     * The children of the while loop are the conditional expression and the 
     * body of the while loop. The body is a sequenece of expressions and 
     * statements.
     */
    AST_WHILE_LOOP_STATEMENT,
    /**
     * The procedure declaration value is the name of the procedure. The 
     * children of the procedure are the block statements. The body of is a
     * sequence of expressions and statements.
     */
    AST_PROCEDURE_DECLARATION,
    /**
     * The program node is the node at the root of the tree. The value of the 
     * program node is simply program. Its children are the first block that 
     * is parsed as shown in the grammar, i.e., a sequence of statements and 
     * expressions.
     */
    AST_PROGRAM,
    /**
     * The value of the varible is its name identifier and has no children.
     */
    AST_VARIABLE,
    /**
     * The value of the number literal is the number literal itself and has
     * no children.
     */
    AST_NUMBER_LITERAL
} ast_node_t;

class ASTNode {
public:
    /**
     * Prints a string representation of the AST.
     * @param root Node to start printing from.
     * @param treeSize The depth of the tree or an over-estimate.
     */ 
    static void printTree(ASTNodePtr root, int treeSize);

    // The following functions are helper functions provided to you for use
    // in the semantic actions. These functions properly instantiate the 
    // various types of ASTNodes; just provide the correct arguments and 
    // most of the work is done for you.
    static ASTNodePtr makeBinaryExpression(
        const std::string &operation, ASTNodePtr lhs, ASTNodePtr rhs
    );

    static ASTNodePtr makeBinaryExpression(
        const std::string &operation, ASTNodePtr rhs
    );

    static ASTNodePtr makeUnaryExpression(
        const std::string &operation, ASTNodePtr operand
    );

    static ASTNodePtr makeCallExpression(const std::string &callee);

    static ASTNodePtr makeIfStatement(ASTNodePtr condition);

    static ASTNodePtr makeWhileLoop(ASTNodePtr condition);

    static ASTNodePtr makeProcedure(const std::string &proc_name);

    static ASTNodePtr makeProgram();

    static ASTNodePtr makeVariable(std::string name);

    static ASTNodePtr makeNumberLiteral(std::string number);

    // This section is where the non-static functions begins.
    ASTNode();

    /**
     * Constructs an ASTNode, populating the type and value fields.
     * @param type The type of node.
     * @param value The value of the node.
     * Please read the specification if you use this function.
     */
    ASTNode(const ast_node_t type, const std::string &value);

    virtual ~ASTNode();

    /**
     * Adds a child to the current ASTNode from right to left.
     * @param node The node to append as a child.
     */
    void addChild(const ASTNodePtr node);

    const ast_node_t getType() const;
    const std::string &getValue() const;
    const std::vector<ASTNodePtr> &getChildren() const;

private:
    static void printNTree(
        ASTNodePtr node, 
        std::vector<bool> flag,
        int depth,
        bool isLast
    );

    ast_node_t type;
    std::string value;
    std::vector<ASTNodePtr> children;
};

#endif
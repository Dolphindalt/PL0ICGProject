/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#include <ast.h>

#include <iostream>

void ASTNode::printTree(ASTNodePtr root, int treeSize) {
    std::vector<bool> flag(treeSize, true);
    ASTNode::printNTree(root, flag, 0, false);
}

ASTNodePtr ASTNode::makeBinaryExpression(
    const std::string &operation, ASTNodePtr lhs, ASTNodePtr rhs
) {
    auto binaryExpr = std::make_shared<ASTNode>(
        AST_BINARY_EXPRESSION, operation
    );
    binaryExpr->addChild(rhs);
    binaryExpr->addChild(lhs);
    return binaryExpr;
}

ASTNodePtr ASTNode::makeBinaryExpression(
    const std::string &operation, ASTNodePtr rhs
) {
    auto binaryExpr = std::make_shared<ASTNode>(
        AST_BINARY_EXPRESSION, operation
    );
    binaryExpr->addChild(rhs);
    return binaryExpr;
}

ASTNodePtr makeUnaryExpression(
    const std::string &operation, ASTNodePtr operand
) {
    auto unaryExpr = std::make_shared<ASTNode>(AST_UNARY_EXPRESSION, operation);
    unaryExpr->addChild(operand);
    return unaryExpr;
}

ASTNodePtr ASTNode::makeCallExpression(const std::string &callee) {
    return std::make_shared<ASTNode>(AST_CALL_EXPRESSION, callee);
}

ASTNodePtr ASTNode::makeIfStatement(ASTNodePtr condition) {
    auto ifStmt = std::make_shared<ASTNode>(AST_IF_STATEMENT, "if");
    ifStmt->addChild(condition);
    return ifStmt;
}

ASTNodePtr ASTNode::makeWhileLoop(ASTNodePtr condition) {
    auto whileLoop = std::make_shared<ASTNode>(
        AST_WHILE_LOOP_STATEMENT, "while"
    );
    whileLoop->addChild(condition);
    return whileLoop;
}

ASTNodePtr ASTNode::makeProcedure(const std::string &proc_name) {
    return std::make_shared<ASTNode>(AST_PROCEDURE_DECLARATION, proc_name);
}

ASTNodePtr ASTNode::makeProgram() {
    return std::make_shared<ASTNode>(AST_PROGRAM, "program");
}

ASTNodePtr ASTNode::makeVariable(std::string name) {
    return std::make_shared<ASTNode>(AST_VARIABLE, name);
}

ASTNodePtr ASTNode::makeNumberLiteral(std::string number) {
    return std::make_shared<ASTNode>(AST_NUMBER_LITERAL, number);
}

ASTNode::ASTNode() {}

ASTNode::ASTNode(const ast_node_t type, const std::string &value)
: type(type), value(value) {}

ASTNode::~ASTNode() {}

void ASTNode::addChild(const ASTNodePtr node) {
    // Yes, this is super slow.
    this->children.insert(this->children.begin(), 1, node);
}

const ast_node_t ASTNode::getType() const {
    return this->type;
}

const std::string &ASTNode::getValue() const {
    return this->value;
}

const std::vector<ASTNodePtr> &ASTNode::getChildren() const {
    return this->children;
}

void ASTNode::printNTree(
    ASTNodePtr node, 
    std::vector<bool> flag, 
    int depth,
    bool isLast
) {
    if (node == nullptr) {
        return;
    }

    for (int i = 1; i < depth; i++) {
        if (flag[i] == true) {
            std::cout << "|    ";
        } else {
            std::cout << "    ";
        }
    }

    if (depth == 0) {
        std::cout << node->getValue() << std::endl;
    } else if (isLast) {
        std::cout << "+--- " << node->getValue() << std::endl;
        flag[depth] = false;
    } else {
        std::cout << "+--- " << node->getValue() << std::endl;
    }

    size_t it = 0;
    for (
        auto itr = node->getChildren().begin(); 
        itr != node->getChildren().end();
        itr++, it++
    ) {
        ASTNode::printNTree(
            *itr, 
            flag, 
            depth + 1, 
            it == (node->getChildren().size() - 1)
        );
    }

    flag[depth] = true;
}
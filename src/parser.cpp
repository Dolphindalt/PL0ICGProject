/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#include <parser.h>
#include <ast.h>
#include <student_actions.h>

#include <stack>

// Define this if you want to see additional parsing logging.
#undef PARSER_TABLE_LOGGING

Parser::Parser(const token_stream_t &tokens) 
: tokens(tokens), lrtable(LRTable(CsvReader(lr_table_path))), 
    grammar(Grammar(grammar_path)) {
        addSemanticActions(this->grammar);
    }

Parser::~Parser() {}

std::string Parser::mapTokenIntoTableEntry(const token_t token) const {
    switch (token.type) {
        case IDENTIFIER:
            return "ident";
        case NUMBER_LITERAL:
            return "number";
        case COMMA:
            return "comma";
        case END_OF_FILE:
            return "$";
        default:
            break;
    }
    return token.lexeme;
}

// This driver code looks oddly familiar...
ASTNodePtr Parser::parse() {

    const State startState = 0;
    std::stack<unsigned int> stateStack;
    std::stack<Symbol> symbolStack;
    std::stack<ASTNodePtr> semanticStack;

    // The $ symbol is not appended as the END_OF_FILE marker acts as the $.
    stateStack.push(startState);

    bool parseDone = false;
    while (!parseDone) {
        const State currentState = stateStack.top();
        const Symbol incomingInput = 
            this->mapTokenIntoTableEntry(this->peekNextToken());

        lr_cell_t x = this->lrtable.getCell(currentState, incomingInput);

        #ifdef PARSER_TABLE_LOGGING
        INFO_LOG(
            "x: table[%d, %s] = x{action: %s value: %d}",
            currentState,
            incomingInput.c_str(),
            lrActionToStringMap.at(x.action).c_str(),
            x.number
        );
        #endif

        switch (x.action) {
            case SHIFT: {
                // Since we are shifting, we consume the token from the input.
                token_t nextInput = this->getNextToken();
                symbolStack.push(nextInput.lexeme);
                stateStack.push(x.number);
                break;
            }
            case REDUCE: {
                // Pop the number of RHS symbols off the stack.
                const Production production = 
                    this->grammar.getProduction(x.number);

                unsigned int rulesToPopLen = production.getRHS().size();

                std::vector<Symbol> poppedSymbols;

                while (rulesToPopLen != 0) {
                    rulesToPopLen--;
                    ASSERT(!stateStack.empty());
                    ASSERT(!symbolStack.empty());

                    stateStack.pop();

                    poppedSymbols.push_back(symbolStack.top());
                    symbolStack.pop();
                }

                // The symbols are popped off and stored in backwards order,
                // so we reverse the vector to get the order to be as it 
                // would appear in the production rule.
                std::reverse(poppedSymbols.begin(), poppedSymbols.end());

                // The state on top of the stack after reducing is used.
                ASSERT(!stateStack.empty());
                unsigned int stateIndex = stateStack.top();
                const std::string lhs = production.getLHS();

                // Validate that the next state is in the goto section.
                lr_cell_t nextState = this->lrtable.getCell(stateIndex, lhs);

                #ifdef PARSER_TABLE_LOGGING
                INFO_LOG(
                    "GOTO: table[%d, %s] = x{action: %s value: %d}",
                    stateIndex,
                    lhs.c_str(),
                    lrActionToStringMap.at(nextState.action).c_str(),
                    nextState.number
                );
                #endif

                if (nextState.action != GOTO || nextState.number == 0) {
                    ERROR_LOG(
                        "got an invalid goto action, %s with state %d",
                        lrActionToStringMap.at(nextState.action).c_str(),
                        nextState.number
                    );
                    exit(EXIT_FAILURE);
                }

                // Push the lhs to the symbol stack.
                symbolStack.push(lhs);

                // GOTO the next state.
                stateStack.push(nextState.number);

                // Process the semantic actions.
                ActionFunction action = this->grammar.getAction(x.number);
                
                ASTNodePtr result = action(
                    &semanticStack, production, poppedSymbols
                );

                if (result != nullptr) {
                    semanticStack.push(result);
                }

                break;
            }
            case EMPTY:
                ERROR_LOG("Encountered an empty parsing table cell");
                // TODO: Better error handling. Print what was expected.
                exit(EXIT_FAILURE);
            case GOTO:
                ERROR_LOG("Encountered an unexpected goto parsing action")
                exit(EXIT_FAILURE);
            case ACCT:
                parseDone = true;
                break;
            default:
                ERROR_LOG(
                    "encountered an unexpected parsing action %d", 
                    x.action
                );
                exit(EXIT_FAILURE);
        }
    }

    // If you did not implement the semantic actions yet, this assertion will
    // fail. This assertion is included because an empty stack will trigger 
    // a segmentation fault.
    ASSERT(semanticStack.size() >= 1);

    // The element left on top of the stack is presumed to be the root
    // of the abstract syntax tree.
    return semanticStack.top();
}

token_t Parser::getNextToken() {
    // Assumes that the end of the token stream always has 
    // the end of file enumeration.
    if (this->current_token == this->tokens.size()) {
        return this->tokens[this->current_token - 1];
    }
    
    return this->tokens[this->current_token++];
}

token_t Parser::peekNextToken() const {
    if (this->current_token == this->tokens.size()) {
        return this->tokens[this->current_token - 1];
    }
    return this->tokens[this->current_token];
}

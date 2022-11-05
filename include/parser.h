/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#ifndef PARSER_H__
#define PARSER_H__

#include <lexer.h>
#include <stack>
#include <initializer_list>

#include <lrtable.h>
#include <grammar.h>

class Parser {
public:
    Parser(const token_stream_t &tokens);
    virtual ~Parser();

    /**
     * Converts a token into a valid lr table column entry.
     * 
     * This function has a really bad code smell. If the design was improved,
     * it is likely that this function could be eliminated. Do you see why?
     * 
     * @param token The token, in which the lexeme and class are of interest.
     * @return A valid column header for the lr parsing table.
     */
    std::string mapTokenIntoTableEntry(const token_t token) const;

    ASTNodePtr parse();
private:
    token_t getNextToken();
    token_t peekNextToken() const;

    const char *lr_table_path = "../tables/lrtable.csv";
    const char *grammar_path = "../tables/grammar.txt";

    const token_stream_t tokens;
    unsigned int current_token = 0;
    LRTable lrtable;
    Grammar grammar;
};

#endif
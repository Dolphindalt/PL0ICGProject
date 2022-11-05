/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#ifndef LRTABLE_H__
#define LRTABLE_H__

#include <string>
#include <map>

#include <utilities.h>

// Models the three types of non-empty cells in the LRTable.
typedef enum lr_action {
    SHIFT, REDUCE, GOTO, EMPTY, ACCT
} lr_action_t;

static std::map<lr_action_t, std::string> lrActionToStringMap = {
    {SHIFT, "SHIFT"},
    {REDUCE, "REDUCE"},
    {GOTO, "GOTO"},
    {EMPTY, "EMPTY"},
    {ACCT, "ACCT"}
};

// Models a cell in the LRTable.
typedef struct lr_cell {
    unsigned int number;
    lr_action_t action;
} lr_cell_t;

// A symbol is a string that is expected to be a terminal or non-terminal.
using Symbol = std::string;

// A state is represented as a positive integer number.
using State = unsigned int;

class LRTable {
public:
    LRTable(const CsvReader &table);
    virtual ~LRTable();

    /**
     * Given the current state and input symbols, returns true if the table 
     * cell is non-empty.
     * @param state The state from the top of the stack driver.
     * @param input The token at the front of the input.
     * @return True if the cell is non-empty, otherwise false.
     */
    bool hasCell(const State state, const Symbol input) const;

    /**
     * Given the current state and input symbol, returns a table cell.
     * @param state The state from the top of the stack driver.
     * @param input The token at the front of the input.
     * @return The contents of the cell, including an action and number. 
     */
    lr_cell_t getCell(const State state, const Symbol input) const;
private:
    std::map<std::pair<State, Symbol>, lr_cell_t> table;
};

#endif
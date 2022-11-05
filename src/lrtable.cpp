#include <lrtable.h>

LRTable::LRTable(const CsvReader &table) {

    const int rows = table.getRows();
    const int cols = table.getColumns();
    // Row 0 contains no useful information and is skipped.
    // Row 1 denotes the starts of the action and goto sections.
    // The start section is always the second row, but the goto column
    // will appear later. We must check if we have reached the goto section
    // using this row. Could be found in advanced, but lazy.
    const int typeRow = 1;
    // Row 2 lists the terminals (action) and then non-terminals (goto).
    const int symbolRow = 2;
    // The first column contains the states starting from after the symbol row.
    const int stateColumn = 0;
    const int firstStateRow = 3;

    bool inGoto = false;

    for (int col = stateColumn + 1; col < cols; col++) {
        // Check if we are in the goto section yet.
        if (!inGoto)
            inGoto = table.get(typeRow, col) == "GOTO";

        Symbol symbol = table.get(symbolRow, col); 

        // Loop through the rows of interest.
        for (int row = firstStateRow; row < rows; row++) {
            unsigned int state = atoi(table.get(row, stateColumn).c_str());

            const std::string entry = table.get(row, col);

            // Empty cells are inserted as an empty entry.
            if (entry == "") {
                lr_cell_t cell;
                cell.action = EMPTY;
                cell.number = 0; // Unused.
                this->table.insert({std::make_pair(state, symbol), cell});
                continue;
            }

            // Check for the special case acceptance cell.
            if (entry == "acct") {
                lr_cell_t cell;
                cell.action = ACCT;
                cell.number = 0; // Unused.
                this->table.insert({std::make_pair(state, symbol), cell});
                continue;
            }

            if (inGoto) {
                // Goto cells are just a single number.
                unsigned int gotoState = atoi(entry.c_str());
                lr_cell_t cell;
                cell.number = gotoState;
                cell.action = GOTO;
                this->table.insert({std::make_pair(state, symbol), cell});
            } else {
                // Action cells start with s or r and are followed by a number.
                char actionChar = entry.at(0);
                lr_action_t action = (actionChar == 's') ? SHIFT : REDUCE;
                unsigned int nextState = 
                    atoi(entry.substr(1, entry.size()-1).c_str());
                lr_cell_t cell;
                cell.number = nextState;
                cell.action = action;
                this->table.insert({std::make_pair(state, symbol), cell});
            }
        }
    }
 }

LRTable::~LRTable() {}

bool LRTable::hasCell(const unsigned int state, const Symbol input) const {
    return this->table.count(std::make_pair(state, input)) > 0;
}

lr_cell_t LRTable::getCell(const unsigned int state, const Symbol input) const {
    return this->table.at(std::make_pair(state, input));
}
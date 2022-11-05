/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#ifndef SYMBOL_TABLE_H__
#define SYMBOL_TABLE_H__

#include <lexer.h>
#include <string>
#include <memory>
#include <map>

typedef std::string address;

typedef enum st_entry_type {
    ST_VARIABLE,
    ST_LITERAL,
    ST_FUNCTION
} st_entry_type_t;

typedef enum type { 
    VOID,
    NUMBER
} type_t;

static std::map<type_t, std::string> typeToStringMap = {
    {VOID, "VOID"},
    {NUMBER, "NUMBER"}
};

inline std::string typeToString(const type_t t) { 
    return typeToStringMap.at(t); 
};

typedef struct symbol_table_entry {
    st_entry_type_t entry_type;
    token_t token;

    union {
        bool is_constant;
        bool is_assigned;
        type_t type;
    } variable;

    union {
        int64_t value;
        type_t type;
    } literal;

    union {
        // Argument types and a return type would go here if the language was
        // more advanced.
    } procedure;
} st_entry_t;

class SymbolTable {
public:
    SymbolTable();
    SymbolTable(std::shared_ptr<SymbolTable> enclosingScope);

    virtual ~SymbolTable();

    void insert(const address &name, const st_entry_t &object);

    bool lookup(
        const address &name, 
        unsigned int *out_level, 
        st_entry_t *out_entry
    ) const;

    bool isGlobalScope() const;

    unsigned int getLevel() const { return this->level; };
private:
    std::map<address, st_entry_t> symbolTable;
    std::shared_ptr<SymbolTable> enclosingScope = nullptr;
    unsigned int level = 0;
};

#endif
/**
 *  CPSC 323 Compilers and Languages
 * 
 *  Dalton Caron, Teaching Associate
 *  dcaron@fullerton.edu, +1 949-616-2699
 *  Department of Computer Science
 */
#ifndef STUDENT_ACTIONS_H__
#define STUDENT_ACTIONS_H__

#include <grammar.h>

/**
 * addSemanticActions populates the grammar with the appropriate semantic 
 * actions as defined by the programmer.
 * @param grammar The grammar to augment.
 */
void addSemanticActions(Grammar &grammar);

#endif
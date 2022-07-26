#ifndef LOGIC_H
#define LOGIC_H

/**
 * logical not
 */
#define NOT(A) (!(A))
/**
 * logical conjunction
 */
#define AND(A, B) ((A) && (B))
/**
 * logical disjunction
 */
#define OR(A, B) ((A) || (B))
/**
 * logical implication
 */
#define IMPLIES(A, B) (NOT(A) || (B))
/**
 * logical nor
 */
#define NOR(A, B) (NOT(A) && NOT(B))

#endif

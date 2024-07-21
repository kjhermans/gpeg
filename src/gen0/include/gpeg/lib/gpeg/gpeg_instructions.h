#ifndef _GPEG_INSTR_H_
#define _GPEG_INSTR_H_

#define OPCODE_ANY 996
#define OPCODE_BACKCOMMIT 263104
#define OPCODE_BITMASK 1049445
#define OPCODE_CALL 263042
#define OPCODE_CATCH 263059
#define OPCODE_CHAR 263127
#define OPCODE_CLOSECAPTURE 262912
#define OPCODE_COMMIT 262966
#define OPCODE_CONDJUMP 525089
#define OPCODE_COUNTER 525142
#define OPCODE_END 262360
#define OPCODE_EQ 262147
#define OPCODE_FAIL 843
#define OPCODE_FAILTWICE 912
#define OPCODE_GT 262149
#define OPCODE_GTEQ 262150
#define OPCODE_IMOVETO 9
#define OPCODE_INTRPCAPTURE 524303
#define OPCODE_IRMOVETO 10
#define OPCODE_JUMP 262963
#define OPCODE_LT 262156
#define OPCODE_LTEQ 262161
#define OPCODE_MOVETO 262162
#define OPCODE_NEQ 262164
#define OPCODE_NOOP 0
#define OPCODE_OPENCAPTURE 263068
#define OPCODE_PARTIALCOMMIT 263092
#define OPCODE_QUAD 263038
#define OPCODE_RANGE 525245
#define OPCODE_RET 928
#define OPCODE_RMOVETO 262168
#define OPCODE_SET 2098122
#define OPCODE_SKIP 262960
#define OPCODE_SPAN 2098145
#define OPCODE_TESTANY 262918
#define OPCODE_TESTCHAR 525210
#define OPCODE_TESTQUAD 525275
#define OPCODE_TESTSET 2360163
#define OPCODE_TRAP 4278255615
#define OPCODE_VAR 263150


#define OPCODE_STRINGS_DEF static char* opcode_strings[] = { \
  "ANY", \
  "BACKCOMMIT", \
  "BITMASK", \
  "CALL", \
  "CATCH", \
  "CHAR", \
  "CLOSECAPTURE", \
  "COMMIT", \
  "CONDJUMP", \
  "COUNTER", \
  "END", \
  "EQ", \
  "FAIL", \
  "FAILTWICE", \
  "GT", \
  "GTEQ", \
  "IMOVETO", \
  "INTRPCAPTURE", \
  "IRMOVETO", \
  "JUMP", \
  "LT", \
  "LTEQ", \
  "MOVETO", \
  "NEQ", \
  "NOOP", \
  "OPENCAPTURE", \
  "PARTIALCOMMIT", \
  "QUAD", \
  "RANGE", \
  "RET", \
  "RMOVETO", \
  "SET", \
  "SKIP", \
  "SPAN", \
  "TESTANY", \
  "TESTCHAR", \
  "TESTQUAD", \
  "TESTSET", \
  "TRAP", \
  "VAR", \
};


#define OPCODE_STRINGS_SWITCH switch (opcode) { \
  case OPCODE_ANY: return opcode_strings[ 0 ]; \
  case OPCODE_BACKCOMMIT: return opcode_strings[ 1 ]; \
  case OPCODE_BITMASK: return opcode_strings[ 2 ]; \
  case OPCODE_CALL: return opcode_strings[ 3 ]; \
  case OPCODE_CATCH: return opcode_strings[ 4 ]; \
  case OPCODE_CHAR: return opcode_strings[ 5 ]; \
  case OPCODE_CLOSECAPTURE: return opcode_strings[ 6 ]; \
  case OPCODE_COMMIT: return opcode_strings[ 7 ]; \
  case OPCODE_CONDJUMP: return opcode_strings[ 8 ]; \
  case OPCODE_COUNTER: return opcode_strings[ 9 ]; \
  case OPCODE_END: return opcode_strings[ 10 ]; \
  case OPCODE_EQ: return opcode_strings[ 11 ]; \
  case OPCODE_FAIL: return opcode_strings[ 12 ]; \
  case OPCODE_FAILTWICE: return opcode_strings[ 13 ]; \
  case OPCODE_GT: return opcode_strings[ 14 ]; \
  case OPCODE_GTEQ: return opcode_strings[ 15 ]; \
  case OPCODE_IMOVETO: return opcode_strings[ 16 ]; \
  case OPCODE_INTRPCAPTURE: return opcode_strings[ 17 ]; \
  case OPCODE_IRMOVETO: return opcode_strings[ 18 ]; \
  case OPCODE_JUMP: return opcode_strings[ 19 ]; \
  case OPCODE_LT: return opcode_strings[ 20 ]; \
  case OPCODE_LTEQ: return opcode_strings[ 21 ]; \
  case OPCODE_MOVETO: return opcode_strings[ 22 ]; \
  case OPCODE_NEQ: return opcode_strings[ 23 ]; \
  case OPCODE_NOOP: return opcode_strings[ 24 ]; \
  case OPCODE_OPENCAPTURE: return opcode_strings[ 25 ]; \
  case OPCODE_PARTIALCOMMIT: return opcode_strings[ 26 ]; \
  case OPCODE_QUAD: return opcode_strings[ 27 ]; \
  case OPCODE_RANGE: return opcode_strings[ 28 ]; \
  case OPCODE_RET: return opcode_strings[ 29 ]; \
  case OPCODE_RMOVETO: return opcode_strings[ 30 ]; \
  case OPCODE_SET: return opcode_strings[ 31 ]; \
  case OPCODE_SKIP: return opcode_strings[ 32 ]; \
  case OPCODE_SPAN: return opcode_strings[ 33 ]; \
  case OPCODE_TESTANY: return opcode_strings[ 34 ]; \
  case OPCODE_TESTCHAR: return opcode_strings[ 35 ]; \
  case OPCODE_TESTQUAD: return opcode_strings[ 36 ]; \
  case OPCODE_TESTSET: return opcode_strings[ 37 ]; \
  case OPCODE_TRAP: return opcode_strings[ 38 ]; \
  case OPCODE_VAR: return opcode_strings[ 39 ]; \
}

#endif

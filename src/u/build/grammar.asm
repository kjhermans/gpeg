GRAMMAR:
  opencapture 0
  opencapture 0
  ret

S:
  opencapture 1
  opencapture 1
  ret

MULTILINECOMMENT:
  opencapture 2
  opencapture 2
  ret

COMMENT:
  opencapture 3
  opencapture 3
  ret

__prefix:
  opencapture 4
  opencapture 4
  ret

END:
  call __prefix
  opencapture 5
  opencapture 5
  ret

DEFINITION:
  call __prefix
  opencapture 6
  opencapture 6
  ret

RULE:
  call __prefix
  opencapture 7
  opencapture 7
  ret

EXPRESSION:
  call __prefix
  opencapture 8
  opencapture 8
  ret

TERMS:
  call __prefix
  opencapture 9
  opencapture 9
  ret

TERM:
  call __prefix
  opencapture 10
  opencapture 10
  ret

SCANMATCHER:
  call __prefix
  opencapture 11
  opencapture 11
  ret

QUANTIFIEDMATCHER:
  call __prefix
  opencapture 12
  opencapture 12
  ret

QUANTIFIER:
  call __prefix
  opencapture 13
  opencapture 13
  ret

Q_ZEROORONE:
  call __prefix
  opencapture 14
  opencapture 14
  ret

Q_ONEORMORE:
  call __prefix
  opencapture 15
  opencapture 15
  ret

Q_ZEROORMORE:
  call __prefix
  opencapture 16
  opencapture 16
  ret

Q_FROMTO:
  call __prefix
  opencapture 17
  opencapture 17
  ret

Q_UNTIL:
  call __prefix
  opencapture 18
  opencapture 18
  ret

Q_FROM:
  call __prefix
  opencapture 19
  opencapture 19
  ret

Q_SPECIFIC:
  call __prefix
  opencapture 20
  opencapture 20
  ret

Q_VAR:
  call __prefix
  opencapture 21
  opencapture 21
  ret

MATCHER:
  call __prefix
  opencapture 22
  opencapture 22
  ret

BITMASK:
  call __prefix
  opencapture 23
  opencapture 23
  ret

VARCAPTURE:
  call __prefix
  opencapture 24
  opencapture 24
  ret

CAPTURETYPE:
  call __prefix
  opencapture 25
  opencapture 25
  ret

TYPE:
  call __prefix
  opencapture 26
  opencapture 26
  ret

CAPTURE:
  call __prefix
  opencapture 27
  opencapture 27
  ret

GROUP:
  call __prefix
  opencapture 28
  opencapture 28
  ret

SET:
  call __prefix
  opencapture 29
  opencapture 29
  ret

VARREFERENCE:
  call __prefix
  opencapture 30
  opencapture 30
  ret

REFERENCE:
  call __prefix
  opencapture 31
  opencapture 31
  ret

LIMITEDCALL:
  call __prefix
  opencapture 32
  opencapture 32
  ret

LCMODES:
  call __prefix
  opencapture 33
  opencapture 33
  ret

LCPARAM:
  call __prefix
  opencapture 34
  opencapture 34
  ret

LEFTARROW:
  call __prefix
  opencapture 35
  opencapture 35
  ret

NOT:
  call __prefix
  opencapture 36
  opencapture 36
  ret

AND:
  call __prefix
  opencapture 37
  opencapture 37
  ret

MACRO:
  call __prefix
  opencapture 38
  opencapture 38
  ret

ENDFORCE:
  call __prefix
  opencapture 39
  opencapture 39
  ret

HEXLITERAL:
  call __prefix
  opencapture 40
  opencapture 40
  ret

NUMBER:
  call __prefix
  opencapture 41
  opencapture 41
  ret

STRING:
  call __prefix
  opencapture 42
  opencapture 42
  ret

OR:
  call __prefix
  opencapture 43
  opencapture 43
  ret

ANY:
  call __prefix
  opencapture 44
  opencapture 44
  ret

IMPORTDECL:
  call __prefix
  opencapture 45
  opencapture 45
  ret

KW_IMPORT:
  call __prefix
  opencapture 46
  opencapture 46
  ret

OPTNAMESPACE:
  call __prefix
  opencapture 47
  opencapture 47
  ret

KW_AS:
  call __prefix
  opencapture 48
  opencapture 48
  ret

STRINGLITERAL:
  call __prefix
  opencapture 49
  opencapture 49
  ret

IDENT:
  call __prefix
  opencapture 50
  opencapture 50
  ret

BOPEN:
  call __prefix
  opencapture 51
  opencapture 51
  ret

BCLOSE:
  call __prefix
  opencapture 52
  opencapture 52
  ret

CBOPEN:
  call __prefix
  opencapture 53
  opencapture 53
  ret

CBCLOSE:
  call __prefix
  opencapture 54
  opencapture 54
  ret

ABOPEN:
  call __prefix
  opencapture 55
  opencapture 55
  ret

ABCLOSE:
  call __prefix
  opencapture 56
  opencapture 56
  ret

COLON:
  call __prefix
  opencapture 57
  opencapture 57
  ret

SEMICOLON:
  call __prefix
  opencapture 58
  opencapture 58
  ret


GRAMMAR:
  opencapture 0
  catch L2
  call DEFINITION
  commit L1
L2:
  call EXPRESSION
L1:
  call END
  closecapture 0
  ret

S:
  opencapture 1
  closecapture 1
  ret

MULTILINECOMMENT:
  opencapture 2
  range 2d
  range 2d
  range 5b
  range 5b
  range 5d
  range 5d
  range 5d
  range 5d
  closecapture 2
  ret

COMMENT:
  opencapture 3
  range 2d
  range 2d
  range 6e
  closecapture 3
  ret

__prefix:
  opencapture 4
  catch L5
  call MULTILINECOMMENT
  commit L4
L5:
  catch L6
  call COMMENT
  commit L4
L6:
  call S
L4:
  closecapture 4
  ret

END:
  call __prefix
  opencapture 5
  closecapture 5
  ret

DEFINITION:
  call __prefix
  opencapture 6
  catch L9
  call RULE
  commit L8
L9:
  call IMPORTDECL
L8:
  closecapture 6
  ret

RULE:
  call __prefix
  opencapture 7
  call IDENT
  call LEFTARROW
  call EXPRESSION
  closecapture 7
  ret

EXPRESSION:
  call __prefix
  opencapture 8
  call TERMS
  call OR
  call TERMS
  closecapture 8
  ret

TERMS:
  call __prefix
  opencapture 9
  call TERM
  closecapture 9
  ret

TERM:
  call __prefix
  opencapture 10
  catch L12
  call SCANMATCHER
  commit L11
L12:
  call QUANTIFIEDMATCHER
L11:
  closecapture 10
  ret

SCANMATCHER:
  call __prefix
  opencapture 11
  catch L15
  call NOT
  commit L14
L15:
  call AND
L14:
  call MATCHER
  closecapture 11
  ret

QUANTIFIEDMATCHER:
  call __prefix
  opencapture 12
  call MATCHER
  call QUANTIFIER
  closecapture 12
  ret

QUANTIFIER:
  call __prefix
  opencapture 13
  catch L18
  call Q_ZEROORONE
  commit L17
L18:
  catch L19
  call Q_ONEORMORE
  commit L17
L19:
  catch L20
  call Q_ZEROORMORE
  commit L17
L20:
  catch L21
  call Q_FROMTO
  commit L17
L21:
  catch L22
  call Q_UNTIL
  commit L17
L22:
  catch L23
  call Q_FROM
  commit L17
L23:
  catch L24
  call Q_SPECIFIC
  commit L17
L24:
  call Q_VAR
L17:
  closecapture 13
  ret

Q_ZEROORONE:
  call __prefix
  opencapture 14
  range 3f
  closecapture 14
  ret

Q_ONEORMORE:
  call __prefix
  opencapture 15
  range 2b
  closecapture 15
  ret

Q_ZEROORMORE:
  call __prefix
  opencapture 16
  range 2a
  closecapture 16
  ret

Q_FROMTO:
  call __prefix
  opencapture 17
  range 5e
  range 2d
  closecapture 17
  ret

Q_UNTIL:
  call __prefix
  opencapture 18
  range 5e
  range 2d
  closecapture 18
  ret

Q_FROM:
  call __prefix
  opencapture 19
  range 5e
  range 2d
  closecapture 19
  ret

Q_SPECIFIC:
  call __prefix
  opencapture 20
  range 5e
  closecapture 20
  ret

Q_VAR:
  call __prefix
  opencapture 21
  range 5e
  call BOPEN
  call VARREFERENCE
  call BCLOSE
  closecapture 21
  ret

MATCHER:
  call __prefix
  opencapture 22
  catch L27
  call ANY
  commit L26
L27:
  catch L28
  call SET
  commit L26
L28:
  catch L29
  call STRING
  commit L26
L29:
  catch L30
  call BITMASK
  commit L26
L30:
  catch L31
  call HEXLITERAL
  commit L26
L31:
  catch L32
  call VARCAPTURE
  commit L26
L32:
  catch L33
  call CAPTURE
  commit L26
L33:
  catch L34
  call GROUP
  commit L26
L34:
  catch L35
  call MACRO
  commit L26
L35:
  catch L36
  call ENDFORCE
  commit L26
L36:
  catch L37
  call VARREFERENCE
  commit L26
L37:
  catch L38
  call REFERENCE
  commit L26
L38:
  call LIMITEDCALL
L26:
  closecapture 22
  ret

BITMASK:
  call __prefix
  opencapture 23
  range 7c
  range 7c
  closecapture 23
  ret

VARCAPTURE:
  call __prefix
  opencapture 24
  call CBOPEN
  call COLON
  call IDENT
  call CAPTURETYPE
  call COLON
  call EXPRESSION
  call CBCLOSE
  closecapture 24
  ret

CAPTURETYPE:
  call __prefix
  opencapture 25
  call SEMICOLON
  call TYPE
  closecapture 25
  ret

TYPE:
  call __prefix
  opencapture 26
  catch L41
  range 75
  range 69
  range 6e
  range 74
  range 33
  range 32
  commit L40
L41:
  range 69
  range 6e
  range 74
  range 33
  range 32
L40:
  closecapture 26
  ret

CAPTURE:
  call __prefix
  opencapture 27
  call CBOPEN
  call EXPRESSION
  call CBCLOSE
  closecapture 27
  ret

GROUP:
  call __prefix
  opencapture 28
  call BOPEN
  call EXPRESSION
  call BCLOSE
  closecapture 28
  ret

SET:
  call __prefix
  opencapture 29
  call ABOPEN
  range 5e
  catch L44
  catch L46
  catch L48
  commit L47
L48:
  range 30
  range 78
L47:
  commit L45
L46:
L45:
  range 2d
  catch L52
  catch L54
  commit L53
L54:
  range 30
  range 78
L53:
  commit L51
L52:
L51:
  commit L43
L44:
  catch L59
  catch L61
  commit L60
L61:
  range 30
  range 78
L60:
  commit L58
L59:
L58:
L43:
  call ABCLOSE
  closecapture 29
  ret

VARREFERENCE:
  call __prefix
  opencapture 30
  range 24
  catch L65
  call IDENT
  commit L64
L65:
  call NUMBER
L64:
  range 2d
  call BITMASK
  closecapture 30
  ret

REFERENCE:
  call __prefix
  opencapture 31
  call KW_IMPORT
  call IDENT
  call LEFTARROW
  closecapture 31
  ret

LIMITEDCALL:
  call __prefix
  opencapture 32
  range 3c
  call LCMODES
  call COLON
  call LCPARAM
  call COLON
  call IDENT
  range 3e
  closecapture 32
  ret

LCMODES:
  call __prefix
  opencapture 33
  range 72
  range 75
  range 69
  range 6e
  range 74
  range 33
  range 32
  closecapture 33
  ret

LCPARAM:
  call __prefix
  opencapture 34
  closecapture 34
  ret

LEFTARROW:
  call __prefix
  opencapture 35
  range 3c
  range 2d
  closecapture 35
  ret

NOT:
  call __prefix
  opencapture 36
  range 21
  closecapture 36
  ret

AND:
  call __prefix
  opencapture 37
  range 26
  closecapture 37
  ret

MACRO:
  call __prefix
  opencapture 38
  range 25
  closecapture 38
  ret

ENDFORCE:
  call __prefix
  opencapture 39
  range 5f
  range 5f
  range 65
  range 6e
  range 64
  call S
  call NUMBER
  closecapture 39
  ret

HEXLITERAL:
  call __prefix
  opencapture 40
  range 30
  range 78
  closecapture 40
  ret

NUMBER:
  call __prefix
  opencapture 41
  closecapture 41
  ret

STRING:
  call __prefix
  opencapture 42
  call STRINGLITERAL
  range 69
  closecapture 42
  ret

OR:
  call __prefix
  opencapture 43
  range 2f
  closecapture 43
  ret

ANY:
  call __prefix
  opencapture 44
  range 2e
  closecapture 44
  ret

IMPORTDECL:
  call __prefix
  opencapture 45
  call KW_IMPORT
  call STRINGLITERAL
  call OPTNAMESPACE
  call SEMICOLON
  closecapture 45
  ret

KW_IMPORT:
  call __prefix
  opencapture 46
  range 69
  range 6d
  range 70
  range 6f
  range 72
  range 74
  closecapture 46
  ret

OPTNAMESPACE:
  call __prefix
  opencapture 47
  call KW_AS
  call IDENT
  closecapture 47
  ret

KW_AS:
  call __prefix
  opencapture 48
  range 61
  range 73
  closecapture 48
  ret

STRINGLITERAL:
  call __prefix
  opencapture 49
  range 27
  catch L68
  catch L70
  commit L69
L70:
  range 78
L69:
  commit L67
L68:
L67:
  range 27
  closecapture 49
  ret

IDENT:
  call __prefix
  opencapture 50
  closecapture 50
  ret

BOPEN:
  call __prefix
  opencapture 51
  range 28
  closecapture 51
  ret

BCLOSE:
  call __prefix
  opencapture 52
  range 29
  closecapture 52
  ret

CBOPEN:
  call __prefix
  opencapture 53
  range 7b
  closecapture 53
  ret

CBCLOSE:
  call __prefix
  opencapture 54
  range 7d
  closecapture 54
  ret

ABOPEN:
  call __prefix
  opencapture 55
  range 5b
  closecapture 55
  ret

ABCLOSE:
  call __prefix
  opencapture 56
  range 5d
  closecapture 56
  ret

COLON:
  call __prefix
  opencapture 57
  range 3a
  closecapture 57
  ret

SEMICOLON:
  call __prefix
  opencapture 58
  range 3b
  closecapture 58
  ret


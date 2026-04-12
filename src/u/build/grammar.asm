-- GPEG compiler, release 0.4.6

  call GRAMMAR
  end 0

GRAMMAR:
  opencapture 0
  catch L2
  call DEFINITION
  catch L3
LOOP3:
  call DEFINITION
  partialcommit LOOP3
L3:
  commit L1
L2:
  call EXPRESSION
L1:
  call END
  closecapture 0
  ret

S:
  opencapture 1
  catch L5
LOOP5:
  partialcommit LOOP5
L5:
  closecapture 1
  ret

MULTILINECOMMENT:
  opencapture 2
  range 2d
  range 2d
  range 5b
  range 5b
  catch L6
LOOP6:
  catch L7
  range 5d
  range 5d
  failtwice
L7:
  range 00 ff
  partialcommit LOOP6
L6:
  range 5d
  range 5d
  closecapture 2
  ret

COMMENT:
  opencapture 3
  range 2d
  range 2d
  catch L8
LOOP8:
  partialcommit LOOP8
L8:
  range 6e
  closecapture 3
  ret

__prefix:
  opencapture 4
  catch L9
LOOP9:
  catch L11
  call MULTILINECOMMENT
  commit L10
L11:
  catch L12
  call COMMENT
  commit L10
L12:
  call S
L10:
  partialcommit LOOP9
L9:
  closecapture 4
  ret

END:
  call __prefix
  opencapture 5
  catch L14
  range 00 ff
  failtwice
L14:
  closecapture 5
  ret

DEFINITION:
  call __prefix
  opencapture 6
  catch L16
  call RULE
  commit L15
L16:
  call IMPORTDECL
L15:
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
  catch L18
LOOP18:
  call OR
  call TERMS
  partialcommit LOOP18
L18:
  closecapture 8
  ret

TERMS:
  call __prefix
  opencapture 9
  call TERM
  catch L19
LOOP19:
  call TERM
  partialcommit LOOP19
L19:
  closecapture 9
  ret

TERM:
  call __prefix
  opencapture 10
  catch L21
  call SCANMATCHER
  commit L20
L21:
  call QUANTIFIEDMATCHER
L20:
  closecapture 10
  ret

SCANMATCHER:
  call __prefix
  opencapture 11
  catch L24
  call NOT
  commit L23
L24:
  call AND
L23:
  call MATCHER
  closecapture 11
  ret

QUANTIFIEDMATCHER:
  call __prefix
  opencapture 12
  call MATCHER
  catch L26
  call QUANTIFIER
  commit __NEXT__
L26:
  closecapture 12
  ret

QUANTIFIER:
  call __prefix
  opencapture 13
  catch L28
  call Q_ZEROORONE
  commit L27
L28:
  catch L29
  call Q_ONEORMORE
  commit L27
L29:
  catch L30
  call Q_ZEROORMORE
  commit L27
L30:
  catch L31
  call Q_FROMTO
  commit L27
L31:
  catch L32
  call Q_UNTIL
  commit L27
L32:
  catch L33
  call Q_FROM
  commit L27
L33:
  catch L34
  call Q_SPECIFIC
  commit L27
L34:
  call Q_VAR
L27:
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
  catch L36
LOOP36:
  partialcommit LOOP36
L36:
  range 2d
  catch L37
LOOP37:
  partialcommit LOOP37
L37:
  closecapture 17
  ret

Q_UNTIL:
  call __prefix
  opencapture 18
  range 5e
  range 2d
  catch L38
LOOP38:
  partialcommit LOOP38
L38:
  closecapture 18
  ret

Q_FROM:
  call __prefix
  opencapture 19
  range 5e
  catch L39
LOOP39:
  partialcommit LOOP39
L39:
  range 2d
  closecapture 19
  ret

Q_SPECIFIC:
  call __prefix
  opencapture 20
  range 5e
  catch L40
LOOP40:
  partialcommit LOOP40
L40:
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
  catch L42
  call ANY
  commit L41
L42:
  catch L43
  call SET
  commit L41
L43:
  catch L44
  call STRING
  commit L41
L44:
  catch L45
  call BITMASK
  commit L41
L45:
  catch L46
  call HEXLITERAL
  commit L41
L46:
  catch L47
  call VARCAPTURE
  commit L41
L47:
  catch L48
  call CAPTURE
  commit L41
L48:
  catch L49
  call GROUP
  commit L41
L49:
  catch L50
  call MACRO
  commit L41
L50:
  catch L51
  call ENDFORCE
  commit L41
L51:
  catch L52
  call VARREFERENCE
  commit L41
L52:
  catch L53
  call REFERENCE
  commit L41
L53:
  call LIMITEDCALL
L41:
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
  catch L55
  call CAPTURETYPE
  commit __NEXT__
L55:
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
  catch L57
  range 75
  range 69
  range 6e
  range 74
  range 33
  range 32
  commit L56
L57:
  range 69
  range 6e
  range 74
  range 33
  range 32
L56:
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
  catch L59
  range 5e
  commit __NEXT__
L59:
  catch L62
  catch L64
  catch L66
  commit L65
L66:
  range 30
  range 78
L65:
  commit L63
L64:
L63:
  range 2d
  catch L70
  catch L72
  commit L71
L72:
  range 30
  range 78
L71:
  commit L69
L70:
L69:
  commit L61
L62:
  catch L77
  catch L79
  commit L78
L79:
  range 30
  range 78
L78:
  commit L76
L77:
L76:
L61:
  catch L60
LOOP60:
  catch L62
  catch L64
  catch L66
  commit L65
L66:
  range 30
  range 78
L65:
  commit L63
L64:
L63:
  range 2d
  catch L70
  catch L72
  commit L71
L72:
  range 30
  range 78
L71:
  commit L69
L70:
L69:
  commit L61
L62:
  catch L77
  catch L79
  commit L78
L79:
  range 30
  range 78
L78:
  commit L76
L77:
L76:
L61:
  partialcommit LOOP60
L60:
  call ABCLOSE
  closecapture 29
  ret

VARREFERENCE:
  call __prefix
  opencapture 30
  range 24
  catch L83
  call IDENT
  commit L82
L83:
  call NUMBER
L82:
  catch L85
  range 2d
  call BITMASK
  commit __NEXT__
L85:
  closecapture 30
  ret

REFERENCE:
  call __prefix
  opencapture 31
  catch L86
  call KW_IMPORT
  failtwice
L86:
  call IDENT
  catch L87
  call LEFTARROW
  failtwice
L87:
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
  catch L88
LOOP88:
  partialcommit LOOP88
L88:
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
  catch L89
LOOP89:
  partialcommit LOOP89
L89:
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
  catch L90
LOOP90:
  partialcommit LOOP90
L90:
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
  catch L91
LOOP91:
  partialcommit LOOP91
L91:
  closecapture 41
  ret

STRING:
  call __prefix
  opencapture 42
  call STRINGLITERAL
  catch L92
  range 69
  commit __NEXT__
L92:
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
  catch L93
  call KW_AS
  call IDENT
  commit __NEXT__
L93:
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
  catch L94
LOOP94:
  catch L96
  catch L98
  commit L97
L98:
  range 78
L97:
  commit L95
L96:
L95:
  partialcommit LOOP94
L94:
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


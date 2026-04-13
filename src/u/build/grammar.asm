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
  catch L10
LOOP10:
  catch L12
  call MULTILINECOMMENT
  commit L11
L12:
  catch L13
  call COMMENT
  commit L11
L13:
  call S
L11:
  partialcommit LOOP10
L10:
  closecapture 4
  ret

END:
  call __prefix
  opencapture 5
  catch L15
  range 00 ff
  failtwice
L15:
  closecapture 5
  ret

DEFINITION:
  call __prefix
  opencapture 6
  catch L17
  call RULE
  commit L16
L17:
  call IMPORTDECL
L16:
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
  catch L19
LOOP19:
  call OR
  call TERMS
  partialcommit LOOP19
L19:
  closecapture 8
  ret

TERMS:
  call __prefix
  opencapture 9
  call TERM
  catch L20
LOOP20:
  call TERM
  partialcommit LOOP20
L20:
  closecapture 9
  ret

TERM:
  call __prefix
  opencapture 10
  catch L22
  call SCANMATCHER
  commit L21
L22:
  call QUANTIFIEDMATCHER
L21:
  closecapture 10
  ret

SCANMATCHER:
  call __prefix
  opencapture 11
  catch L25
  call NOT
  commit L24
L25:
  call AND
L24:
  call MATCHER
  closecapture 11
  ret

QUANTIFIEDMATCHER:
  call __prefix
  opencapture 12
  call MATCHER
  catch L27
  call QUANTIFIER
  commit __NEXT__
L27:
  closecapture 12
  ret

QUANTIFIER:
  call __prefix
  opencapture 13
  catch L29
  call Q_ZEROORONE
  commit L28
L29:
  catch L30
  call Q_ONEORMORE
  commit L28
L30:
  catch L31
  call Q_ZEROORMORE
  commit L28
L31:
  catch L32
  call Q_FROMTO
  commit L28
L32:
  catch L33
  call Q_UNTIL
  commit L28
L33:
  catch L34
  call Q_FROM
  commit L28
L34:
  catch L35
  call Q_SPECIFIC
  commit L28
L35:
  call Q_VAR
L28:
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
SET38_1:
  catch L37
LOOP37:
SET39_1:
  partialcommit LOOP37
L37:
  range 2d
SET41_1:
  catch L40
LOOP40:
SET42_1:
  partialcommit LOOP40
L40:
  closecapture 17
  ret

Q_UNTIL:
  call __prefix
  opencapture 18
  range 5e
  range 2d
SET44_1:
  catch L43
LOOP43:
SET45_1:
  partialcommit LOOP43
L43:
  closecapture 18
  ret

Q_FROM:
  call __prefix
  opencapture 19
  range 5e
SET47_1:
  catch L46
LOOP46:
SET48_1:
  partialcommit LOOP46
L46:
  range 2d
  closecapture 19
  ret

Q_SPECIFIC:
  call __prefix
  opencapture 20
  range 5e
SET50_1:
  catch L49
LOOP49:
SET51_1:
  partialcommit LOOP49
L49:
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
  catch L53
  call ANY
  commit L52
L53:
  catch L54
  call SET
  commit L52
L54:
  catch L55
  call STRING
  commit L52
L55:
  catch L56
  call BITMASK
  commit L52
L56:
  catch L57
  call HEXLITERAL
  commit L52
L57:
  catch L58
  call VARCAPTURE
  commit L52
L58:
  catch L59
  call CAPTURE
  commit L52
L59:
  catch L60
  call GROUP
  commit L52
L60:
  catch L61
  call MACRO
  commit L52
L61:
  catch L62
  call ENDFORCE
  commit L52
L62:
  catch L63
  call VARREFERENCE
  commit L52
L63:
  catch L64
  call REFERENCE
  commit L52
L64:
  call LIMITEDCALL
L52:
  closecapture 22
  ret

BITMASK:
  call __prefix
  opencapture 23
  range 7c
  counter 0 1
CTR0:
  condjump 0 CTR0
  catch L66
  counter 1 31
CTR1:
  partialcommit __NEXT__
  condjump 1 CTR1
  commit __NEXT__
L66:
  range 7c
  closecapture 23
  ret

VARCAPTURE:
  call __prefix
  opencapture 24
  call CBOPEN
  call COLON
  call IDENT
  catch L69
  call CAPTURETYPE
  commit __NEXT__
L69:
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
  catch L71
  range 75
  range 69
  range 6e
  range 74
  range 33
  range 32
  commit L70
L71:
  range 69
  range 6e
  range 74
  range 33
  range 32
L70:
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
  catch L73
  range 5e
  commit __NEXT__
L73:
  catch L76
  catch L78
  catch L80
  commit L79
L80:
  range 30
  range 78
  counter 2 2
CTR2:
SET83_1:
SET83_3:
SET83_5:
  condjump 2 CTR2
L79:
  commit L77
L78:
L77:
  range 2d
  catch L87
  catch L89
  commit L88
L89:
  range 30
  range 78
  counter 3 2
CTR3:
SET92_1:
SET92_3:
SET92_5:
  condjump 3 CTR3
L88:
  commit L86
L87:
L86:
  commit L75
L76:
  catch L97
  catch L99
  commit L98
L99:
  range 30
  range 78
  counter 4 2
CTR4:
SET102_1:
SET102_3:
SET102_5:
  condjump 4 CTR4
L98:
  commit L96
L97:
L96:
L75:
  catch L74
LOOP74:
  catch L106
  catch L108
  catch L110
  commit L109
L110:
  range 30
  range 78
  counter 5 2
CTR5:
SET113_1:
SET113_3:
SET113_5:
  condjump 5 CTR5
L109:
  commit L107
L108:
L107:
  range 2d
  catch L117
  catch L119
  commit L118
L119:
  range 30
  range 78
  counter 6 2
CTR6:
SET122_1:
SET122_3:
SET122_5:
  condjump 6 CTR6
L118:
  commit L116
L117:
L116:
  commit L105
L106:
  catch L127
  catch L129
  commit L128
L129:
  range 30
  range 78
  counter 7 2
CTR7:
SET132_1:
SET132_3:
SET132_5:
  condjump 7 CTR7
L128:
  commit L126
L127:
L126:
L105:
  partialcommit LOOP74
L74:
  call ABCLOSE
  closecapture 29
  ret

VARREFERENCE:
  call __prefix
  opencapture 30
  range 24
  catch L136
  call IDENT
  commit L135
L136:
  call NUMBER
L135:
  catch L138
  range 2d
  call BITMASK
  commit __NEXT__
L138:
  closecapture 30
  ret

REFERENCE:
  call __prefix
  opencapture 31
  catch L139
  call KW_IMPORT
  failtwice
L139:
  call IDENT
  catch L140
  call LEFTARROW
  failtwice
L140:
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
  catch L141
LOOP141:
  partialcommit LOOP141
L141:
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
  catch L142
LOOP142:
  partialcommit LOOP142
L142:
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
SET144_1:
SET144_3:
  catch L145
LOOP145:
SET146_1:
SET146_3:
SET146_5:
  partialcommit LOOP145
L145:
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
  counter 8 2
CTR8:
SET147_1:
SET147_3:
SET147_5:
  condjump 8 CTR8
  closecapture 40
  ret

NUMBER:
  call __prefix
  opencapture 41
SET149_1:
  catch L148
LOOP148:
SET150_1:
  partialcommit LOOP148
L148:
  closecapture 41
  ret

STRING:
  call __prefix
  opencapture 42
  call STRINGLITERAL
  catch L151
  range 69
  commit __NEXT__
L151:
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
  catch L152
  call KW_AS
  call IDENT
  commit __NEXT__
L152:
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
  catch L153
LOOP153:
  catch L155
  catch L157
  commit L156
L157:
  range 78
  counter 9 2
CTR9:
SET160_1:
SET160_3:
SET160_5:
  condjump 9 CTR9
L156:
  commit L154
L155:
L154:
  partialcommit LOOP153
L153:
  range 27
  closecapture 49
  ret

IDENT:
  call __prefix
  opencapture 50
SET163_1:
SET163_3:
  counter 10 0
CTR10:
SET165_1:
SET165_3:
SET165_5:
  condjump 10 CTR10
  catch L164
  counter 11 63
CTR11:
SET166_1:
SET166_3:
SET166_5:
  partialcommit __NEXT__
  condjump 11 CTR11
  commit __NEXT__
L164:
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


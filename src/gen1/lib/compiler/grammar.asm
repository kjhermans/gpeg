  call GRAMMAR
  end 0

GRAMMAR:
  opencapture 0
  catch __L1
  call DEFINITION
  catch __L3
__L4:
  call DEFINITION
  partialcommit __L4
__L3:
  commit __L2
__L1:
  call EXPRESSION
__L2:
  call END
  closecapture 0
  ret

S:
  opencapture 1
  set 002e000001000000000000000000000000000000000000000000000000000000
  catch __L5
__L6:
  set 002e000001000000000000000000000000000000000000000000000000000000
  partialcommit __L6
__L5:
  closecapture 1
  ret

MULTILINECOMMENT:
  opencapture 2
  quad 2d2d5b5b
  catch __L7
__L8:
  catch __L9
  char 5d
  char 5d
  failtwice
__L9:
  any
  partialcommit __L8
__L7:
  char 5d
  char 5d
  closecapture 2
  ret

COMMENT:
  opencapture 3
  char 2d
  char 2d
  catch __L10
__L11:
  set fffbffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
  partialcommit __L11
__L10:
  char 0a
  closecapture 3
  ret

__prefix:
  catch __L12
__L13:
  catch __L14
  call MULTILINECOMMENT
  commit __L15
__L14:
  catch __L16
  call COMMENT
  commit __L17
__L16:
  call S
__L17:
__L15:
  partialcommit __L13
__L12:
  ret

END:
  call __prefix
  opencapture 4
  catch __L18
  any
  failtwice
__L18:
  closecapture 4
  ret

DEFINITION:
  call __prefix
  opencapture 5
  catch __L19
  call RULE
  commit __L20
__L19:
  call IMPORTDECL
__L20:
  closecapture 5
  ret

RULE:
  call __prefix
  opencapture 6
  call IDENT
  call LEFTARROW
  call EXPRESSION
  closecapture 6
  ret

EXPRESSION:
  call __prefix
  opencapture 7
  call TERMS
  catch __L21
__L22:
  opencapture 8
  call OR
  call TERMS
  closecapture 8
  partialcommit __L22
__L21:
  closecapture 7
  ret

TERMS:
  call __prefix
  opencapture 9
  call TERM
  catch __L23
__L24:
  call TERM
  partialcommit __L24
__L23:
  closecapture 9
  ret

TERM:
  call __prefix
  opencapture 10
  catch __L25
  call SCANMATCHER
  commit __L26
__L25:
  call QUANTIFIEDMATCHER
__L26:
  closecapture 10
  ret

SCANMATCHER:
  call __prefix
  opencapture 11
  catch __L27
  call NOT
  commit __L28
__L27:
  call AND
__L28:
  call MATCHER
  closecapture 11
  ret

QUANTIFIEDMATCHER:
  call __prefix
  opencapture 12
  call MATCHER
  catch __L29
  call QUANTIFIER
  commit __L29
__L29:
  closecapture 12
  ret

QUANTIFIER:
  call __prefix
  opencapture 13
  catch __L31
  call Q_ZEROORONE
  commit __L32
__L31:
  catch __L33
  call Q_ONEORMORE
  commit __L34
__L33:
  catch __L35
  call Q_ZEROORMORE
  commit __L36
__L35:
  catch __L37
  call Q_FROMTO
  commit __L38
__L37:
  catch __L39
  call Q_UNTIL
  commit __L40
__L39:
  catch __L41
  call Q_FROM
  commit __L42
__L41:
  catch __L43
  call Q_SPECIFIC
  commit __L44
__L43:
  call Q_VAR
__L44:
__L42:
__L40:
__L38:
__L36:
__L34:
__L32:
  closecapture 13
  ret

Q_ZEROORONE:
  call __prefix
  opencapture 14
  char 3f
  closecapture 14
  ret

Q_ONEORMORE:
  call __prefix
  opencapture 15
  char 2b
  closecapture 15
  ret

Q_ZEROORMORE:
  call __prefix
  opencapture 16
  char 2a
  closecapture 16
  ret

Q_FROMTO:
  call __prefix
  opencapture 17
  char 5e
  opencapture 18
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L45
__L46:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L46
__L45:
  closecapture 18
  char 2d
  opencapture 19
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L47
__L48:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L48
__L47:
  closecapture 19
  closecapture 17
  ret

Q_UNTIL:
  call __prefix
  opencapture 20
  char 5e
  char 2d
  opencapture 21
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L49
__L50:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L50
__L49:
  closecapture 21
  closecapture 20
  ret

Q_FROM:
  call __prefix
  opencapture 22
  char 5e
  opencapture 23
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L51
__L52:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L52
__L51:
  closecapture 23
  char 2d
  closecapture 22
  ret

Q_SPECIFIC:
  call __prefix
  opencapture 24
  char 5e
  opencapture 25
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L53
__L54:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L54
__L53:
  closecapture 25
  closecapture 24
  ret

Q_VAR:
  call __prefix
  opencapture 26
  char 5e
  call BOPEN
  call VARREFERENCE
  call BCLOSE
  closecapture 26
  ret

MATCHER:
  call __prefix
  opencapture 27
  catch __L55
  call ANY
  commit __L56
__L55:
  catch __L57
  call SET
  commit __L58
__L57:
  catch __L59
  call STRING
  commit __L60
__L59:
  catch __L61
  call BITMASK
  commit __L62
__L61:
  catch __L63
  call HEXLITERAL
  commit __L64
__L63:
  catch __L65
  call VARCAPTURE
  commit __L66
__L65:
  catch __L67
  call CAPTURE
  commit __L68
__L67:
  catch __L69
  call GROUP
  commit __L70
__L69:
  catch __L71
  call MACRO
  commit __L72
__L71:
  catch __L73
  call ENDFORCE
  commit __L74
__L73:
  catch __L75
  call VARREFERENCE
  commit __L76
__L75:
  catch __L77
  call REFERENCE
  commit __L78
__L77:
  call LIMITEDCALL
__L78:
__L76:
__L74:
__L72:
__L70:
__L68:
__L66:
__L64:
__L62:
__L60:
__L58:
__L56:
  closecapture 27
  ret

BITMASK:
  call __prefix
  opencapture 28
  char 7c
  set 0000000000000300000000800000000000000000000000000000000000000000
  catch __L79
  counter 1 31
__L80:
  set 0000000000000300000000800000000000000000000000000000000000000000
  partialcommit __NEXT__
  condjump 1 __L80
  commit __L79
__L79:
  char 7c
  closecapture 28
  ret

VARCAPTURE:
  call __prefix
  opencapture 29
  call CBOPEN
  call COLON
  call IDENT
  catch __L81
  call CAPTURETYPE
  commit __L81
__L81:
  call COLON
  call EXPRESSION
  call CBCLOSE
  call CAPTUREEND
  closecapture 29
  ret

CAPTURETYPE:
  call __prefix
  opencapture 30
  call SEMICOLON
  call TYPE
  closecapture 30
  ret

TYPE:
  call __prefix
  opencapture 31
  catch __L83
  quad 75696e74
  char 33
  char 32
  commit __L84
__L83:
  quad 696e7433
  char 32
__L84:
  closecapture 31
  ret

CAPTURE:
  call __prefix
  opencapture 32
  call CBOPEN
  call EXPRESSION
  call CBCLOSE
  call CAPTUREEND
  closecapture 32
  ret

GROUP:
  call __prefix
  opencapture 33
  call BOPEN
  call EXPRESSION
  call BCLOSE
  closecapture 33
  ret

CAPTUREEND:
  call __prefix
  opencapture 34
  catch __L85
  catch __L87
  call REPLACE
  commit __L88
__L87:
  call RECYCLE
__L88:
  commit __L85
__L85:
  closecapture 34
  ret

SET:
  call __prefix
  opencapture 35
  call ABOPEN
  catch __L89
  opencapture 36
  char 5e
  closecapture 36
  commit __L89
__L89:
  catch __L91
  opencapture 37
  catch __L93
  char 5c
  catch __L95
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L96
__L95:
  char 30
  char 78
  counter 5 2
__L97:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 5 __L97
__L96:
  commit __L94
__L93:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L94:
  closecapture 37
  char 2d
  opencapture 38
  catch __L98
  char 5c
  catch __L100
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L101
__L100:
  char 30
  char 78
  counter 6 2
__L102:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 6 __L102
__L101:
  commit __L99
__L98:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L99:
  closecapture 38
  commit __L92
__L91:
  opencapture 39
  catch __L103
  char 5c
  catch __L105
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L106
__L105:
  char 30
  char 78
  counter 7 2
__L107:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 7 __L107
__L106:
  commit __L104
__L103:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L104:
  closecapture 39
__L92:
  catch __L108
__L109:
  catch __L110
  opencapture 37
  catch __L112
  char 5c
  catch __L114
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L115
__L114:
  char 30
  char 78
  counter 8 2
__L116:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 8 __L116
__L115:
  commit __L113
__L112:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L113:
  closecapture 37
  char 2d
  opencapture 38
  catch __L117
  char 5c
  catch __L119
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L120
__L119:
  char 30
  char 78
  counter 9 2
__L121:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 9 __L121
__L120:
  commit __L118
__L117:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L118:
  closecapture 38
  commit __L111
__L110:
  opencapture 39
  catch __L122
  char 5c
  catch __L124
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L125
__L124:
  char 30
  char 78
  counter 10 2
__L126:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 10 __L126
__L125:
  commit __L123
__L122:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L123:
  closecapture 39
__L111:
  partialcommit __L109
__L108:
  call ABCLOSE
  closecapture 35
  ret

VARREFERENCE:
  call __prefix
  opencapture 40
  char 24
  catch __L127
  call IDENT
  commit __L128
__L127:
  call NUMBER
__L128:
  catch __L129
  char 2d
  call BITMASK
  commit __L129
__L129:
  closecapture 40
  ret

REFERENCE:
  call __prefix
  opencapture 41
  catch __L131
  call KW_IMPORT
  failtwice
__L131:
  call IDENT
  catch __L132
  call LEFTARROW
  failtwice
__L132:
  closecapture 41
  ret

LIMITEDCALL:
  call __prefix
  opencapture 42
  char 3c
  call LCMODES
  call COLON
  call LCPARAM
  call COLON
  call IDENT
  catch __L133
__L134:
  set 002e000001000000000000000000000000000000000000000000000000000000
  partialcommit __L134
__L133:
  char 3e
  closecapture 42
  ret

LCMODES:
  call __prefix
  opencapture 43
  quad 7275696e
  char 74
  char 33
  char 32
  closecapture 43
  ret

LCPARAM:
  call __prefix
  opencapture 44
  catch __L135
__L136:
  set ffd1fffffefffffbffffffffffffffffffffffffffffffffffffffffffffffff
  partialcommit __L136
__L135:
  closecapture 44
  ret

REPLACE:
  call __prefix
  opencapture 45
  call RIGHTARROW
  call REPLACETERMS
  closecapture 45
  ret

REPLACETERMS:
  call __prefix
  opencapture 46
  call REPLACETERM
  catch __L137
__L138:
  call REPLACETERM
  partialcommit __L138
__L137:
  closecapture 46
  ret

REPLACETERM:
  call __prefix
  opencapture 47
  catch __L139
  call STRINGLITERAL
  commit __L140
__L139:
  catch __L141
  call HEXLITERAL
  commit __L142
__L141:
  call VARREFERENCE
__L142:
__L140:
  closecapture 47
  ret

RECYCLE:
  call __prefix
  opencapture 48
  call FATARROW
  call IDENT
  closecapture 48
  ret

LEFTARROW:
  call __prefix
  opencapture 49
  char 3c
  char 2d
  closecapture 49
  ret

RIGHTARROW:
  call __prefix
  opencapture 50
  char 2d
  char 3e
  closecapture 50
  ret

FATARROW:
  call __prefix
  opencapture 51
  char 3d
  char 3e
  closecapture 51
  ret

NOT:
  call __prefix
  opencapture 52
  char 21
  closecapture 52
  ret

AND:
  call __prefix
  opencapture 53
  char 26
  closecapture 53
  ret

MACRO:
  call __prefix
  opencapture 54
  char 25
  set 0000000000000000feffff07feffff0700000000000000000000000000000000
  catch __L143
__L144:
  set 000000000000ff03feffff07feffff0700000000000000000000000000000000
  partialcommit __L144
__L143:
  closecapture 54
  ret

ENDFORCE:
  call __prefix
  opencapture 55
  quad 5f5f656e
  char 64
  call S
  call NUMBER
  closecapture 55
  ret

HEXLITERAL:
  call __prefix
  opencapture 56
  char 30
  char 78
  counter 12 2
__L145:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 12 __L145
  closecapture 56
  ret

NUMBER:
  call __prefix
  opencapture 57
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L146
__L147:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L147
__L146:
  closecapture 57
  ret

STRING:
  call __prefix
  opencapture 58
  call STRINGLITERAL
  catch __L148
  char 69
  commit __L148
__L148:
  closecapture 58
  ret

OR:
  call __prefix
  opencapture 59
  char 2f
  closecapture 59
  ret

ANY:
  call __prefix
  opencapture 60
  char 2e
  closecapture 60
  ret

IMPORTDECL:
  call __prefix
  opencapture 61
  call KW_IMPORT
  call STRINGLITERAL
  call OPTNAMESPACE
  call SEMICOLON
  closecapture 61
  ret

KW_IMPORT:
  call __prefix
  opencapture 62
  quad 696d706f
  char 72
  char 74
  closecapture 62
  ret

OPTNAMESPACE:
  call __prefix
  opencapture 63
  catch __L150
  call KW_AS
  call IDENT
  commit __L150
__L150:
  closecapture 63
  ret

KW_AS:
  call __prefix
  opencapture 64
  char 61
  char 73
  closecapture 64
  ret

STRINGLITERAL:
  call __prefix
  opencapture 65
  char 27
  opencapture 66
  catch __L152
__L153:
  catch __L154
  char 5c
  catch __L156
  set 0000000080000000000000100040540000000000000000000000000000000000
  commit __L157
__L156:
  char 78
  counter 15 2
__L158:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 15 __L158
__L157:
  commit __L155
__L154:
  set ffffffff7fffffffffffffefffffffffffffffffffffffffffffffffffffffff
__L155:
  partialcommit __L153
__L152:
  closecapture 66
  char 27
  closecapture 65
  ret

IDENT:
  call __prefix
  opencapture 67
  set 0000000000000000feffff87feffff0700000000000000000000000000000000
  catch __L159
  counter 16 63
__L160:
  set 000000000000ff03feffff87feffff0700000000000000000000000000000000
  partialcommit __NEXT__
  condjump 16 __L160
  commit __L159
__L159:
  closecapture 67
  ret

BOPEN:
  call __prefix
  opencapture 68
  char 28
  closecapture 68
  ret

BCLOSE:
  call __prefix
  opencapture 69
  char 29
  closecapture 69
  ret

CBOPEN:
  call __prefix
  opencapture 70
  char 7b
  closecapture 70
  ret

CBCLOSE:
  call __prefix
  opencapture 71
  char 7d
  closecapture 71
  ret

ABOPEN:
  call __prefix
  opencapture 72
  char 5b
  closecapture 72
  ret

ABCLOSE:
  call __prefix
  opencapture 73
  char 5d
  closecapture 73
  ret

COLON:
  call __prefix
  opencapture 74
  char 3a
  closecapture 74
  ret

SEMICOLON:
  call __prefix
  opencapture 75
  char 3b
  closecapture 75
  ret


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
  catch __L11
__L12:
  set fffbffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
  partialcommit __L12
__L11:
  char 0a
  closecapture 3
  ret

__prefix:
  catch __L13
__L14:
  catch __L15
  catch __L17
  call MULTILINECOMMENT
  commit __L18
__L17:
  call COMMENT
__L18:
  commit __L16
__L15:
  call S
__L16:
  partialcommit __L14
__L13:
  ret

END:
  call __prefix
  opencapture 4
  catch __L19
  any
  failtwice
__L19:
  closecapture 4
  ret

DEFINITION:
  call __prefix
  opencapture 5
  catch __L21
  call RULE
  commit __L22
__L21:
  call IMPORTDECL
__L22:
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
  catch __L23
__L24:
  opencapture 8
  call OR
  call TERMS
  closecapture 8
  partialcommit __L24
__L23:
  closecapture 7
  ret

TERMS:
  call __prefix
  opencapture 9
  call TERM
  catch __L25
__L26:
  call TERM
  partialcommit __L26
__L25:
  closecapture 9
  ret

TERM:
  call __prefix
  opencapture 10
  catch __L27
  call SCANMATCHER
  commit __L28
__L27:
  call QUANTIFIEDMATCHER
__L28:
  closecapture 10
  ret

SCANMATCHER:
  call __prefix
  opencapture 11
  catch __L29
  call NOT
  commit __L30
__L29:
  call AND
__L30:
  call MATCHER
  closecapture 11
  ret

QUANTIFIEDMATCHER:
  call __prefix
  opencapture 12
  call MATCHER
  catch __L31
  call QUANTIFIER
  commit __NEXT__
__L31:
  closecapture 12
  ret

QUANTIFIER:
  call __prefix
  opencapture 13
  catch __L32
  catch __L34
  catch __L36
  catch __L38
  catch __L40
  catch __L42
  catch __L44
  call Q_ZEROORONE
  commit __L45
__L44:
  call Q_ONEORMORE
__L45:
  commit __L43
__L42:
  call Q_ZEROORMORE
__L43:
  commit __L41
__L40:
  call Q_FROMTO
__L41:
  commit __L39
__L38:
  call Q_UNTIL
__L39:
  commit __L37
__L36:
  call Q_FROM
__L37:
  commit __L35
__L34:
  call Q_SPECIFIC
__L35:
  commit __L33
__L32:
  call Q_VAR
__L33:
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
  catch __L46
__L47:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L47
__L46:
  closecapture 18
  char 2d
  opencapture 19
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L48
__L49:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L49
__L48:
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
  catch __L50
__L51:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L51
__L50:
  closecapture 21
  closecapture 20
  ret

Q_FROM:
  call __prefix
  opencapture 22
  char 5e
  opencapture 23
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L52
__L53:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L53
__L52:
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
  catch __L54
__L55:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L55
__L54:
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
  catch __L56
  catch __L58
  catch __L60
  catch __L62
  catch __L64
  catch __L66
  catch __L68
  catch __L70
  catch __L72
  catch __L74
  catch __L76
  catch __L78
  call ANY
  commit __L79
__L78:
  call SET
__L79:
  commit __L77
__L76:
  call STRING
__L77:
  commit __L75
__L74:
  call BITMASK
__L75:
  commit __L73
__L72:
  call HEXLITERAL
__L73:
  commit __L71
__L70:
  call VARCAPTURE
__L71:
  commit __L69
__L68:
  call CAPTURE
__L69:
  commit __L67
__L66:
  call GROUP
__L67:
  commit __L65
__L64:
  call MACRO
__L65:
  commit __L63
__L62:
  call ENDFORCE
__L63:
  commit __L61
__L60:
  call VARREFERENCE
__L61:
  commit __L59
__L58:
  call REFERENCE
__L59:
  commit __L57
__L56:
  call LIMITEDCALL
__L57:
  closecapture 27
  ret

BITMASK:
  call __prefix
  opencapture 28
  char 7c
  set 0000000000000300000000800000000000000000000000000000000000000000
  catch __L80
  counter 1 31
__L81:
  set 0000000000000300000000800000000000000000000000000000000000000000
  partialcommit __NEXT__
  condjump 1 __L81
  commit __NEXT__
__L80:
  char 7c
  closecapture 28
  ret

VARCAPTURE:
  call __prefix
  opencapture 29
  call CBOPEN
  call COLON
  call IDENT
  catch __L82
  call CAPTURETYPE
  commit __NEXT__
__L82:
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
  catch __L86
  call REPLACE
  commit __L87
__L86:
  call RECYCLE
__L87:
  commit __NEXT__
__L85:
  closecapture 34
  ret

SET:
  call __prefix
  opencapture 35
  call ABOPEN
  catch __L88
  opencapture 36
  char 5e
  closecapture 36
  commit __NEXT__
__L88:
  catch __L89
  opencapture 37
  catch __L91
  char 5c
  catch __L93
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L94
__L93:
  char 30
  char 78
  counter 2 2
__L95:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 2 __L95
__L94:
  commit __L92
__L91:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L92:
  closecapture 37
  char 2d
  opencapture 38
  catch __L96
  char 5c
  catch __L98
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L99
__L98:
  char 30
  char 78
  counter 3 2
__L100:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 3 __L100
__L99:
  commit __L97
__L96:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L97:
  closecapture 38
  commit __L90
__L89:
  opencapture 39
  catch __L101
  char 5c
  catch __L103
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L104
__L103:
  char 30
  char 78
  counter 4 2
__L105:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 4 __L105
__L104:
  commit __L102
__L101:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L102:
  closecapture 39
__L90:
  catch __L106
__L107:
  catch __L108
  opencapture 37
  catch __L110
  char 5c
  catch __L112
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L113
__L112:
  char 30
  char 78
  counter 5 2
__L114:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 5 __L114
__L113:
  commit __L111
__L110:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L111:
  closecapture 37
  char 2d
  opencapture 38
  catch __L115
  char 5c
  catch __L117
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L118
__L117:
  char 30
  char 78
  counter 6 2
__L119:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 6 __L119
__L118:
  commit __L116
__L115:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L116:
  closecapture 38
  commit __L109
__L108:
  opencapture 39
  catch __L120
  char 5c
  catch __L122
  set 0000000000200000000000300040540000000000000000000000000000000000
  commit __L123
__L122:
  char 30
  char 78
  counter 7 2
__L124:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 7 __L124
__L123:
  commit __L121
__L120:
  set ffffffffffffffffffffffcfffffffffffffffffffffffffffffffffffffffff
__L121:
  closecapture 39
__L109:
  partialcommit __L107
__L106:
  call ABCLOSE
  closecapture 35
  ret

VARREFERENCE:
  call __prefix
  opencapture 40
  char 24
  catch __L125
  call IDENT
  commit __L126
__L125:
  call NUMBER
__L126:
  catch __L127
  char 2d
  call BITMASK
  commit __NEXT__
__L127:
  closecapture 40
  ret

REFERENCE:
  call __prefix
  opencapture 41
  catch __L128
  call KW_IMPORT
  failtwice
__L128:
  call IDENT
  catch __L130
  call LEFTARROW
  failtwice
__L130:
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
  catch __L132
__L133:
  set 002e000001000000000000000000000000000000000000000000000000000000
  partialcommit __L133
__L132:
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
  catch __L134
__L135:
  set ffd1fffffefffffbffffffffffffffffffffffffffffffffffffffffffffffff
  partialcommit __L135
__L134:
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
  catch __L136
__L137:
  call REPLACETERM
  partialcommit __L137
__L136:
  closecapture 46
  ret

REPLACETERM:
  call __prefix
  opencapture 47
  catch __L138
  catch __L140
  call STRINGLITERAL
  commit __L141
__L140:
  call HEXLITERAL
__L141:
  commit __L139
__L138:
  call VARREFERENCE
__L139:
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
  catch __L142
__L143:
  set 000000000000ff03feffff07feffff0700000000000000000000000000000000
  partialcommit __L143
__L142:
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
  counter 8 2
__L144:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 8 __L144
  closecapture 56
  ret

NUMBER:
  call __prefix
  opencapture 57
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L145
__L146:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L146
__L145:
  closecapture 57
  ret

STRING:
  call __prefix
  opencapture 58
  call STRINGLITERAL
  catch __L147
  char 69
  commit __NEXT__
__L147:
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
  catch __L148
  call KW_AS
  call IDENT
  commit __NEXT__
__L148:
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
  catch __L149
__L150:
  catch __L151
  char 5c
  catch __L153
  set 0000000080000000000000100040540000000000000000000000000000000000
  commit __L154
__L153:
  char 78
  counter 9 2
__L155:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 9 __L155
__L154:
  commit __L152
__L151:
  set ffffffff7fffffffffffffefffffffffffffffffffffffffffffffffffffffff
__L152:
  partialcommit __L150
__L149:
  closecapture 66
  char 27
  closecapture 65
  ret

IDENT:
  call __prefix
  opencapture 67
  set 0000000000000000feffff87feffff0700000000000000000000000000000000
  catch __L156
  counter 10 63
__L157:
  set 000000000000ff03feffff87feffff0700000000000000000000000000000000
  partialcommit __NEXT__
  condjump 10 __L157
  commit __NEXT__
__L156:
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


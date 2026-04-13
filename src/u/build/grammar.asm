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
  catch MACRO6_1
  range 20
  commit L6
MACRO6_1:
  range 07 0d
L6:
  catch L5
LOOP5:
  catch MACRO7_1
  range 20
  commit L7
MACRO7_1:
  range 07 0d
L7:
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
  catch L8
LOOP8:
  catch L9
  range 5d
  range 5d
  failtwice
L9:
  range 00 ff
  partialcommit LOOP8
L8:
  range 5d
  range 5d
  closecapture 2
  ret

COMMENT:
  opencapture 3
  range 2d
  range 2d
  catch L10
LOOP10:
  range 5c
L11:
  partialcommit LOOP10
L10:
  range 6e
  closecapture 3
  ret

__prefix:
  opencapture 4
  catch L12
LOOP12:
  catch L14
  call MULTILINECOMMENT
  commit L13
L14:
  catch L15
  call COMMENT
  commit L13
L15:
  call S
L13:
  partialcommit LOOP12
L12:
  closecapture 4
  ret

END:
  call __prefix
  opencapture 5
  catch L17
  range 00 ff
  failtwice
L17:
  closecapture 5
  ret

DEFINITION:
  call __prefix
  opencapture 6
  catch L19
  call RULE
  commit L18
L19:
  call IMPORTDECL
L18:
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
  catch L21
LOOP21:
  call OR
  call TERMS
  partialcommit LOOP21
L21:
  closecapture 8
  ret

TERMS:
  call __prefix
  opencapture 9
  call TERM
  catch L22
LOOP22:
  call TERM
  partialcommit LOOP22
L22:
  closecapture 9
  ret

TERM:
  call __prefix
  opencapture 10
  catch L24
  call SCANMATCHER
  commit L23
L24:
  call QUANTIFIEDMATCHER
L23:
  closecapture 10
  ret

SCANMATCHER:
  call __prefix
  opencapture 11
  catch L27
  call NOT
  commit L26
L27:
  call AND
L26:
  call MATCHER
  closecapture 11
  ret

QUANTIFIEDMATCHER:
  call __prefix
  opencapture 12
  call MATCHER
  catch L29
  call QUANTIFIER
  commit __NEXT__
L29:
  closecapture 12
  ret

QUANTIFIER:
  call __prefix
  opencapture 13
  catch L31
  call Q_ZEROORONE
  commit L30
L31:
  catch L32
  call Q_ONEORMORE
  commit L30
L32:
  catch L33
  call Q_ZEROORMORE
  commit L30
L33:
  catch L34
  call Q_FROMTO
  commit L30
L34:
  catch L35
  call Q_UNTIL
  commit L30
L35:
  catch L36
  call Q_FROM
  commit L30
L36:
  catch L37
  call Q_SPECIFIC
  commit L30
L37:
  call Q_VAR
L30:
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
  range 30 39
L40:
  catch L39
LOOP39:
  range 30 39
L41:
  partialcommit LOOP39
L39:
  range 2d
  range 30 39
L43:
  catch L42
LOOP42:
  range 30 39
L44:
  partialcommit LOOP42
L42:
  closecapture 17
  ret

Q_UNTIL:
  call __prefix
  opencapture 18
  range 5e
  range 2d
  range 30 39
L46:
  catch L45
LOOP45:
  range 30 39
L47:
  partialcommit LOOP45
L45:
  closecapture 18
  ret

Q_FROM:
  call __prefix
  opencapture 19
  range 5e
  range 30 39
L49:
  catch L48
LOOP48:
  range 30 39
L50:
  partialcommit LOOP48
L48:
  range 2d
  closecapture 19
  ret

Q_SPECIFIC:
  call __prefix
  opencapture 20
  range 5e
  range 30 39
L52:
  catch L51
LOOP51:
  range 30 39
L53:
  partialcommit LOOP51
L51:
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
  catch L55
  call ANY
  commit L54
L55:
  catch L56
  call SET
  commit L54
L56:
  catch L57
  call STRING
  commit L54
L57:
  catch L58
  call BITMASK
  commit L54
L58:
  catch L59
  call HEXLITERAL
  commit L54
L59:
  catch L60
  call VARCAPTURE
  commit L54
L60:
  catch L61
  call CAPTURE
  commit L54
L61:
  catch L62
  call GROUP
  commit L54
L62:
  catch L63
  call MACRO
  commit L54
L63:
  catch L64
  call ENDFORCE
  commit L54
L64:
  catch L65
  call VARREFERENCE
  commit L54
L65:
  catch L66
  call REFERENCE
  commit L54
L66:
  call LIMITEDCALL
L54:
  closecapture 22
  ret

BITMASK:
  call __prefix
  opencapture 23
  range 7c
  counter 0 1
CTR0:
  catch SET69_1
  range 30
  commit L69
SET69_1:
  catch SET69_2
  range 31
  commit L69
SET69_2:
  range 5f
L69:
  condjump 0 CTR0
  catch L68
  counter 1 31
CTR1:
  catch SET70_1
  range 30
  commit L70
SET70_1:
  catch SET70_2
  range 31
  commit L70
SET70_2:
  range 5f
L70:
  partialcommit __NEXT__
  condjump 1 CTR1
  commit __NEXT__
L68:
  range 7c
  closecapture 23
  ret

VARCAPTURE:
  call __prefix
  opencapture 24
  call CBOPEN
  call COLON
  call IDENT
  catch L71
  call CAPTURETYPE
  commit __NEXT__
L71:
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
  catch L73
  range 75
  range 69
  range 6e
  range 74
  range 33
  range 32
  commit L72
L73:
  range 69
  range 6e
  range 74
  range 33
  range 32
L72:
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
  catch L75
  range 5e
  commit __NEXT__
L75:
  catch L78
  catch L80
  catch L82
  catch SET83_1
  range 6e
  commit L83
SET83_1:
  catch SET83_2
  range 72
  commit L83
SET83_2:
  catch SET83_3
  range 74
  commit L83
SET83_3:
  catch SET83_4
  range 76
  commit L83
SET83_4:
  catch SET83_5
  range 5c
  commit L83
SET83_5:
  catch SET83_6
  range 5c
  commit L83
SET83_6:
  range 5c
L83:
  commit L81
L82:
  range 30
  range 78
  counter 2 2
CTR2:
  catch SET85_2
  range 30 39
  commit L85
SET85_2:
  catch SET85_4
  range 61 66
  commit L85
SET85_4:
  range 41 46
L85:
  condjump 2 CTR2
L81:
  commit L79
L80:
  catch SET87_2
  range 5c
  commit L87
SET87_2:
  range 5c
L87:
L79:
  range 2d
  catch L89
  catch L91
  catch SET92_1
  range 6e
  commit L92
SET92_1:
  catch SET92_2
  range 72
  commit L92
SET92_2:
  catch SET92_3
  range 74
  commit L92
SET92_3:
  catch SET92_4
  range 76
  commit L92
SET92_4:
  catch SET92_5
  range 5c
  commit L92
SET92_5:
  catch SET92_6
  range 5c
  commit L92
SET92_6:
  range 5c
L92:
  commit L90
L91:
  range 30
  range 78
  counter 3 2
CTR3:
  catch SET94_2
  range 30 39
  commit L94
SET94_2:
  catch SET94_4
  range 61 66
  commit L94
SET94_4:
  range 41 46
L94:
  condjump 3 CTR3
L90:
  commit L88
L89:
  catch SET96_2
  range 5c
  commit L96
SET96_2:
  range 5c
L96:
L88:
  commit L77
L78:
  catch L99
  catch L101
  catch SET102_1
  range 6e
  commit L102
SET102_1:
  catch SET102_2
  range 72
  commit L102
SET102_2:
  catch SET102_3
  range 74
  commit L102
SET102_3:
  catch SET102_4
  range 76
  commit L102
SET102_4:
  catch SET102_5
  range 5c
  commit L102
SET102_5:
  catch SET102_6
  range 5c
  commit L102
SET102_6:
  range 5c
L102:
  commit L100
L101:
  range 30
  range 78
  counter 4 2
CTR4:
  catch SET104_2
  range 30 39
  commit L104
SET104_2:
  catch SET104_4
  range 61 66
  commit L104
SET104_4:
  range 41 46
L104:
  condjump 4 CTR4
L100:
  commit L98
L99:
  catch SET106_2
  range 5c
  commit L106
SET106_2:
  range 5c
L106:
L98:
L77:
  catch L76
LOOP76:
  catch L108
  catch L110
  catch L112
  catch SET113_1
  range 6e
  commit L113
SET113_1:
  catch SET113_2
  range 72
  commit L113
SET113_2:
  catch SET113_3
  range 74
  commit L113
SET113_3:
  catch SET113_4
  range 76
  commit L113
SET113_4:
  catch SET113_5
  range 5c
  commit L113
SET113_5:
  catch SET113_6
  range 5c
  commit L113
SET113_6:
  range 5c
L113:
  commit L111
L112:
  range 30
  range 78
  counter 5 2
CTR5:
  catch SET115_2
  range 30 39
  commit L115
SET115_2:
  catch SET115_4
  range 61 66
  commit L115
SET115_4:
  range 41 46
L115:
  condjump 5 CTR5
L111:
  commit L109
L110:
  catch SET117_2
  range 5c
  commit L117
SET117_2:
  range 5c
L117:
L109:
  range 2d
  catch L119
  catch L121
  catch SET122_1
  range 6e
  commit L122
SET122_1:
  catch SET122_2
  range 72
  commit L122
SET122_2:
  catch SET122_3
  range 74
  commit L122
SET122_3:
  catch SET122_4
  range 76
  commit L122
SET122_4:
  catch SET122_5
  range 5c
  commit L122
SET122_5:
  catch SET122_6
  range 5c
  commit L122
SET122_6:
  range 5c
L122:
  commit L120
L121:
  range 30
  range 78
  counter 6 2
CTR6:
  catch SET124_2
  range 30 39
  commit L124
SET124_2:
  catch SET124_4
  range 61 66
  commit L124
SET124_4:
  range 41 46
L124:
  condjump 6 CTR6
L120:
  commit L118
L119:
  catch SET126_2
  range 5c
  commit L126
SET126_2:
  range 5c
L126:
L118:
  commit L107
L108:
  catch L129
  catch L131
  catch SET132_1
  range 6e
  commit L132
SET132_1:
  catch SET132_2
  range 72
  commit L132
SET132_2:
  catch SET132_3
  range 74
  commit L132
SET132_3:
  catch SET132_4
  range 76
  commit L132
SET132_4:
  catch SET132_5
  range 5c
  commit L132
SET132_5:
  catch SET132_6
  range 5c
  commit L132
SET132_6:
  range 5c
L132:
  commit L130
L131:
  range 30
  range 78
  counter 7 2
CTR7:
  catch SET134_2
  range 30 39
  commit L134
SET134_2:
  catch SET134_4
  range 61 66
  commit L134
SET134_4:
  range 41 46
L134:
  condjump 7 CTR7
L130:
  commit L128
L129:
  catch SET136_2
  range 5c
  commit L136
SET136_2:
  range 5c
L136:
L128:
L107:
  partialcommit LOOP76
L76:
  call ABCLOSE
  closecapture 29
  ret

VARREFERENCE:
  call __prefix
  opencapture 30
  range 24
  catch L138
  call IDENT
  commit L137
L138:
  call NUMBER
L137:
  catch L140
  range 2d
  call BITMASK
  commit __NEXT__
L140:
  closecapture 30
  ret

REFERENCE:
  call __prefix
  opencapture 31
  catch L141
  call KW_IMPORT
  failtwice
L141:
  call IDENT
  catch L142
  call LEFTARROW
  failtwice
L142:
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
  catch L143
LOOP143:
  catch MACRO144_1
  range 20
  commit L144
MACRO144_1:
  range 07 0d
L144:
  partialcommit LOOP143
L143:
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
  catch L145
LOOP145:
  catch SET146_2
  range 3a
  commit L146
SET146_2:
  catch SET146_3
  range 20
  commit L146
SET146_3:
  catch SET146_4
  range 5c
  commit L146
SET146_4:
  catch SET146_5
  range 5c
  commit L146
SET146_5:
  catch SET146_6
  range 5c
  commit L146
SET146_6:
  range 5c
L146:
  partialcommit LOOP145
L145:
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
  catch SET147_2
  range 61 7a
  commit L147
SET147_2:
  range 41 5a
L147:
  catch L148
LOOP148:
  catch SET149_2
  range 61 7a
  commit L149
SET149_2:
  catch SET149_4
  range 41 5a
  commit L149
SET149_4:
  range 30 39
L149:
  partialcommit LOOP148
L148:
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
  catch SET150_2
  range 30 39
  commit L150
SET150_2:
  catch SET150_4
  range 61 66
  commit L150
SET150_4:
  range 41 46
L150:
  condjump 8 CTR8
  closecapture 40
  ret

NUMBER:
  call __prefix
  opencapture 41
  range 30 39
L152:
  catch L151
LOOP151:
  range 30 39
L153:
  partialcommit LOOP151
L151:
  closecapture 41
  ret

STRING:
  call __prefix
  opencapture 42
  call STRINGLITERAL
  catch L154
  range 69
  commit __NEXT__
L154:
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
  catch L155
  call KW_AS
  call IDENT
  commit __NEXT__
L155:
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
  catch L156
LOOP156:
  catch L158
  catch L160
  catch SET161_1
  range 6e
  commit L161
SET161_1:
  catch SET161_2
  range 72
  commit L161
SET161_2:
  catch SET161_3
  range 74
  commit L161
SET161_3:
  catch SET161_4
  range 76
  commit L161
SET161_4:
  catch SET161_5
  range 5c
  commit L161
SET161_5:
  range 27
L161:
  commit L159
L160:
  range 78
  counter 9 2
CTR9:
  catch SET163_2
  range 30 39
  commit L163
SET163_2:
  catch SET163_4
  range 61 66
  commit L163
SET163_4:
  range 41 46
L163:
  condjump 9 CTR9
L159:
  commit L157
L158:
  catch SET165_2
  range 27
  commit L165
SET165_2:
  range 5c
L165:
L157:
  partialcommit LOOP156
L156:
  range 27
  closecapture 49
  ret

IDENT:
  call __prefix
  opencapture 50
  catch SET166_2
  range 61 7a
  commit L166
SET166_2:
  catch SET166_4
  range 41 5a
  commit L166
SET166_4:
  range 5f
L166:
  counter 10 0
CTR10:
  catch SET168_2
  range 61 7a
  commit L168
SET168_2:
  catch SET168_4
  range 41 5a
  commit L168
SET168_4:
  catch SET168_6
  range 30 39
  commit L168
SET168_6:
  range 5f
L168:
  condjump 10 CTR10
  catch L167
  counter 11 63
CTR11:
  catch SET169_2
  range 61 7a
  commit L169
SET169_2:
  catch SET169_4
  range 41 5a
  commit L169
SET169_4:
  catch SET169_6
  range 30 39
  commit L169
SET169_6:
  range 5f
L169:
  partialcommit __NEXT__
  condjump 11 CTR11
  commit __NEXT__
L167:
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


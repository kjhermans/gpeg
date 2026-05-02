-- GPEG compiler, release 0.5.8

  call GRAMMAR
  end 0

GRAMMAR:
  opencapture 1
  catch L2
  call RULE
  catch L3
LOOP3:
  call RULE
  partialcommit LOOP3
L3:
  commit L1
L2:
  call EXPRESSION
L1:
  call END
  closecapture 1
  ret

S:
  opencapture 2
  catch MACRO6_1
  range 09 0b
  commit L6
MACRO6_1:
  catch MACRO6_2
  range 0d
  commit L6
MACRO6_2:
  range 20
L6:
  catch L5
LOOP5:
  catch MACRO7_1
  range 09 0b
  commit L7
MACRO7_1:
  catch MACRO7_2
  range 0d
  commit L7
MACRO7_2:
  range 20
L7:
  partialcommit LOOP5
L5:
  closecapture 2
  ret

MULTILINECOMMENT:
  opencapture 3
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
  closecapture 3
  ret

COMMENT:
  opencapture 4
  range 2d
  range 2d
  catch L10
LOOP10:
  catch SET11_0
  range 00 09
  commit L11
SET11_0:
  range 0b ff
L11:
  partialcommit LOOP10
L10:
  range 0a
  closecapture 4
  ret

__prefix:
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
  catch L18
LOOP18:
  opencapture 8
  call OR
  call TERMS
  closecapture 8
  partialcommit LOOP18
L18:
  closecapture 7
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
  opencapture 18
  range 30 39
L37:
  catch L36
LOOP36:
  range 30 39
L38:
  partialcommit LOOP36
L36:
  closecapture 18
  range 2d
  opencapture 19
  range 30 39
L40:
  catch L39
LOOP39:
  range 30 39
L41:
  partialcommit LOOP39
L39:
  closecapture 19
  closecapture 17
  ret

Q_UNTIL:
  call __prefix
  opencapture 20
  range 5e
  range 2d
  opencapture 21
  range 30 39
L43:
  catch L42
LOOP42:
  range 30 39
L44:
  partialcommit LOOP42
L42:
  closecapture 21
  closecapture 20
  ret

Q_FROM:
  call __prefix
  opencapture 22
  range 5e
  opencapture 23
  range 30 39
L46:
  catch L45
LOOP45:
  range 30 39
L47:
  partialcommit LOOP45
L45:
  closecapture 23
  range 2d
  closecapture 22
  ret

Q_SPECIFIC:
  call __prefix
  opencapture 24
  range 5e
  opencapture 25
  range 30 39
L49:
  catch L48
LOOP48:
  range 30 39
L50:
  partialcommit LOOP48
L48:
  closecapture 25
  closecapture 24
  ret

Q_VAR:
  call __prefix
  opencapture 26
  range 5e
  call BOPEN
  call VARREFERENCE
  call BCLOSE
  closecapture 26
  ret

MATCHER:
  call __prefix
  opencapture 27
  catch L52
  call ANY
  commit L51
L52:
  catch L53
  call SET
  commit L51
L53:
  catch L54
  call STRING
  commit L51
L54:
  catch L55
  call BITMASK
  commit L51
L55:
  catch L56
  call HEXLITERAL
  commit L51
L56:
  catch L57
  call VARCAPTURE
  commit L51
L57:
  catch L58
  call CAPTURE
  commit L51
L58:
  catch L59
  call GROUP
  commit L51
L59:
  catch L60
  call MACRO
  commit L51
L60:
  catch L61
  call ENDFORCE
  commit L51
L61:
  catch L62
  call VARREFERENCE
  commit L51
L62:
  catch L63
  call REFERENCE
  commit L51
L63:
  call LIMITEDCALL
L51:
  closecapture 27
  ret

BITMASK:
  call __prefix
  opencapture 28
  range 7c
  counter 0 8
CTR0:
  catch SET65_0
  range 30 31
  commit L65
SET65_0:
  range 5f 5f
L65:
  condjump 0 CTR0
  range 7c
  closecapture 28
  ret

VARCAPTURE:
  call __prefix
  opencapture 29
  call CBOPEN
  call COLON
  call IDENT
  call COLON
  call EXPRESSION
  call CBCLOSE
  closecapture 29
  ret

CAPTURE:
  call __prefix
  opencapture 30
  call CBOPEN
  call EXPRESSION
  call CBCLOSE
  closecapture 30
  ret

GROUP:
  call __prefix
  opencapture 31
  call BOPEN
  call EXPRESSION
  call BCLOSE
  closecapture 31
  ret

SET:
  call __prefix
  opencapture 32
  call ABOPEN
  catch L66
  opencapture 33
  range 5e
  closecapture 33
  commit __NEXT__
L66:
  catch L69
  opencapture 34
  catch L71
  range 5c
  catch L73
  catch SET74_0
  range 2d 2d
  commit L74
SET74_0:
  catch SET74_1
  range 5c 5d
  commit L74
SET74_1:
  catch SET74_2
  range 6e 6e
  commit L74
SET74_2:
  catch SET74_3
  range 72 72
  commit L74
SET74_3:
  catch SET74_4
  range 74 74
  commit L74
SET74_4:
  range 76 76
L74:
  commit L72
L73:
  range 78
  counter 1 2
CTR1:
  catch SET76_0
  range 30 39
  commit L76
SET76_0:
  catch SET76_1
  range 41 46
  commit L76
SET76_1:
  range 61 66
L76:
  condjump 1 CTR1
L72:
  commit L70
L71:
  catch SET78_0
  range 00 5b
  commit L78
SET78_0:
  range 5e ff
L78:
L70:
  closecapture 34
  range 2d
  opencapture 35
  catch L80
  range 5c
  catch L82
  catch SET83_0
  range 2d 2d
  commit L83
SET83_0:
  catch SET83_1
  range 5c 5d
  commit L83
SET83_1:
  catch SET83_2
  range 6e 6e
  commit L83
SET83_2:
  catch SET83_3
  range 72 72
  commit L83
SET83_3:
  catch SET83_4
  range 74 74
  commit L83
SET83_4:
  range 76 76
L83:
  commit L81
L82:
  range 78
  counter 2 2
CTR2:
  catch SET85_0
  range 30 39
  commit L85
SET85_0:
  catch SET85_1
  range 41 46
  commit L85
SET85_1:
  range 61 66
L85:
  condjump 2 CTR2
L81:
  commit L79
L80:
  catch SET87_0
  range 00 5b
  commit L87
SET87_0:
  range 5e ff
L87:
L79:
  closecapture 35
  commit L68
L69:
  opencapture 36
  catch L90
  range 5c
  catch L92
  catch SET93_0
  range 2d 2d
  commit L93
SET93_0:
  catch SET93_1
  range 5c 5d
  commit L93
SET93_1:
  catch SET93_2
  range 6e 6e
  commit L93
SET93_2:
  catch SET93_3
  range 72 72
  commit L93
SET93_3:
  catch SET93_4
  range 74 74
  commit L93
SET93_4:
  range 76 76
L93:
  commit L91
L92:
  range 78
  counter 3 2
CTR3:
  catch SET95_0
  range 30 39
  commit L95
SET95_0:
  catch SET95_1
  range 41 46
  commit L95
SET95_1:
  range 61 66
L95:
  condjump 3 CTR3
L91:
  commit L89
L90:
  catch SET97_0
  range 00 5b
  commit L97
SET97_0:
  range 5e ff
L97:
L89:
  closecapture 36
L68:
  catch L67
LOOP67:
  catch L99
  opencapture 34
  catch L101
  range 5c
  catch L103
  catch SET104_0
  range 2d 2d
  commit L104
SET104_0:
  catch SET104_1
  range 5c 5d
  commit L104
SET104_1:
  catch SET104_2
  range 6e 6e
  commit L104
SET104_2:
  catch SET104_3
  range 72 72
  commit L104
SET104_3:
  catch SET104_4
  range 74 74
  commit L104
SET104_4:
  range 76 76
L104:
  commit L102
L103:
  range 78
  counter 4 2
CTR4:
  catch SET106_0
  range 30 39
  commit L106
SET106_0:
  catch SET106_1
  range 41 46
  commit L106
SET106_1:
  range 61 66
L106:
  condjump 4 CTR4
L102:
  commit L100
L101:
  catch SET108_0
  range 00 5b
  commit L108
SET108_0:
  range 5e ff
L108:
L100:
  closecapture 34
  range 2d
  opencapture 35
  catch L110
  range 5c
  catch L112
  catch SET113_0
  range 2d 2d
  commit L113
SET113_0:
  catch SET113_1
  range 5c 5d
  commit L113
SET113_1:
  catch SET113_2
  range 6e 6e
  commit L113
SET113_2:
  catch SET113_3
  range 72 72
  commit L113
SET113_3:
  catch SET113_4
  range 74 74
  commit L113
SET113_4:
  range 76 76
L113:
  commit L111
L112:
  range 78
  counter 5 2
CTR5:
  catch SET115_0
  range 30 39
  commit L115
SET115_0:
  catch SET115_1
  range 41 46
  commit L115
SET115_1:
  range 61 66
L115:
  condjump 5 CTR5
L111:
  commit L109
L110:
  catch SET117_0
  range 00 5b
  commit L117
SET117_0:
  range 5e ff
L117:
L109:
  closecapture 35
  commit L98
L99:
  opencapture 36
  catch L120
  range 5c
  catch L122
  catch SET123_0
  range 2d 2d
  commit L123
SET123_0:
  catch SET123_1
  range 5c 5d
  commit L123
SET123_1:
  catch SET123_2
  range 6e 6e
  commit L123
SET123_2:
  catch SET123_3
  range 72 72
  commit L123
SET123_3:
  catch SET123_4
  range 74 74
  commit L123
SET123_4:
  range 76 76
L123:
  commit L121
L122:
  range 78
  counter 6 2
CTR6:
  catch SET125_0
  range 30 39
  commit L125
SET125_0:
  catch SET125_1
  range 41 46
  commit L125
SET125_1:
  range 61 66
L125:
  condjump 6 CTR6
L121:
  commit L119
L120:
  catch SET127_0
  range 00 5b
  commit L127
SET127_0:
  range 5e ff
L127:
L119:
  closecapture 36
L98:
  partialcommit LOOP67
L67:
  call ABCLOSE
  closecapture 32
  ret

VARREFERENCE:
  call __prefix
  opencapture 37
  range 24
  catch L129
  call IDENT
  commit L128
L129:
  call NUMBER
L128:
  closecapture 37
  ret

REFERENCE:
  call __prefix
  opencapture 38
  call IDENT
  catch L131
  call LEFTARROW
  failtwice
L131:
  closecapture 38
  ret

LIMITEDCALL:
  call __prefix
  opencapture 39
  range 3c
  range 3a
  range 24
  call IDENT
  call COLON
  call BIT
  call COLON
  call NUMBER
  call COLON
  call IDENT
  catch L132
LOOP132:
  catch MACRO133_1
  range 09 0b
  commit L133
MACRO133_1:
  catch MACRO133_2
  range 0d
  commit L133
MACRO133_2:
  range 20
L133:
  partialcommit LOOP132
L132:
  range 3e
  closecapture 39
  ret

LEFTARROW:
  call __prefix
  opencapture 40
  range 3c
  range 2d
  closecapture 40
  ret

NOT:
  call __prefix
  opencapture 41
  range 21
  closecapture 41
  ret

AND:
  call __prefix
  opencapture 42
  range 26
  closecapture 42
  ret

MACRO:
  call __prefix
  opencapture 43
  range 25
  catch SET134_0
  range 41 5a
  commit L134
SET134_0:
  range 61 7a
L134:
  catch L135
LOOP135:
  catch SET136_0
  range 30 39
  commit L136
SET136_0:
  catch SET136_1
  range 41 5a
  commit L136
SET136_1:
  range 61 7a
L136:
  partialcommit LOOP135
L135:
  closecapture 43
  ret

ENDFORCE:
  call __prefix
  opencapture 44
  range 5f
  range 5f
  range 65
  range 6e
  range 64
  call S
  call NUMBER
  closecapture 44
  ret

HEXLITERAL:
  call __prefix
  opencapture 45
  range 30
  range 78
  counter 7 2
CTR7:
  catch SET137_0
  range 30 39
  commit L137
SET137_0:
  catch SET137_1
  range 41 46
  commit L137
SET137_1:
  range 61 66
L137:
  condjump 7 CTR7
  closecapture 45
  ret

NUMBER:
  call __prefix
  opencapture 46
  range 30 39
L139:
  catch L138
LOOP138:
  range 30 39
L140:
  partialcommit LOOP138
L138:
  closecapture 46
  ret

STRING:
  call __prefix
  opencapture 47
  call STRINGLITERAL
  catch L141
  range 69
  commit __NEXT__
L141:
  closecapture 47
  ret

OR:
  call __prefix
  opencapture 48
  range 2f
  closecapture 48
  ret

ANY:
  call __prefix
  opencapture 49
  range 2e
  closecapture 49
  ret

STRINGLITERAL:
  call __prefix
  opencapture 50
  range 27
  opencapture 51
  catch L142
LOOP142:
  catch L144
  range 5c
  catch L146
  catch SET147_0
  range 27 27
  commit L147
SET147_0:
  catch SET147_1
  range 5c 5c
  commit L147
SET147_1:
  catch SET147_2
  range 6e 6e
  commit L147
SET147_2:
  catch SET147_3
  range 72 72
  commit L147
SET147_3:
  catch SET147_4
  range 74 74
  commit L147
SET147_4:
  range 76 76
L147:
  commit L145
L146:
  range 78
  counter 8 2
CTR8:
  catch SET149_0
  range 30 39
  commit L149
SET149_0:
  catch SET149_1
  range 41 46
  commit L149
SET149_1:
  range 61 66
L149:
  condjump 8 CTR8
L145:
  commit L143
L144:
  catch SET151_0
  range 00 26
  commit L151
SET151_0:
  catch SET151_1
  range 28 5b
  commit L151
SET151_1:
  range 5d ff
L151:
L143:
  partialcommit LOOP142
L142:
  closecapture 51
  range 27
  closecapture 50
  ret

BIT:
  call __prefix
  opencapture 52
  range 30 31
L152:
  closecapture 52
  ret

IDENT:
  call __prefix
  opencapture 53
  catch SET153_0
  range 41 5a
  commit L153
SET153_0:
  catch SET153_1
  range 5f 5f
  commit L153
SET153_1:
  range 61 7a
L153:
  catch L154
  counter 10 63
CTR10:
  catch SET155_0
  range 30 39
  commit L155
SET155_0:
  catch SET155_1
  range 41 5a
  commit L155
SET155_1:
  catch SET155_2
  range 5f 5f
  commit L155
SET155_2:
  range 61 7a
L155:
  partialcommit __NEXT__
  condjump 10 CTR10
  commit __NEXT__
L154:
  closecapture 53
  ret

BOPEN:
  call __prefix
  opencapture 54
  range 28
  closecapture 54
  ret

BCLOSE:
  call __prefix
  opencapture 55
  range 29
  closecapture 55
  ret

CBOPEN:
  call __prefix
  opencapture 56
  range 7b
  closecapture 56
  ret

CBCLOSE:
  call __prefix
  opencapture 57
  range 7d
  closecapture 57
  ret

ABOPEN:
  call __prefix
  opencapture 58
  range 5b
  closecapture 58
  ret

ABCLOSE:
  call __prefix
  opencapture 59
  range 5d
  closecapture 59
  ret

COLON:
  call __prefix
  opencapture 60
  range 3a
  closecapture 60
  ret

SEMICOLON:
  call __prefix
  opencapture 61
  range 3b
  closecapture 61
  ret


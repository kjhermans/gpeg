-- GPEG compiler, release 0.5.12

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
  catch SET66_0
  range 30 31
  commit L66
SET66_0:
  range 5f 5f
L66:
  catch L65
  counter 1 7
CTR1:
  catch SET67_0
  range 30 31
  commit L67
SET67_0:
  range 5f 5f
L67:
  partialcommit __NEXT__
  condjump 1 CTR1
  commit __NEXT__
L65:
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
  catch L68
  opencapture 33
  range 5e
  closecapture 33
  commit __NEXT__
L68:
  catch L71
  opencapture 34
  catch L73
  range 5c
  catch L75
  catch SET76_0
  range 2d 2d
  commit L76
SET76_0:
  catch SET76_1
  range 5c 5d
  commit L76
SET76_1:
  catch SET76_2
  range 6e 6e
  commit L76
SET76_2:
  catch SET76_3
  range 72 72
  commit L76
SET76_3:
  catch SET76_4
  range 74 74
  commit L76
SET76_4:
  range 76 76
L76:
  commit L74
L75:
  range 78
  counter 2 2
CTR2:
  catch SET78_0
  range 30 39
  commit L78
SET78_0:
  catch SET78_1
  range 41 46
  commit L78
SET78_1:
  range 61 66
L78:
  condjump 2 CTR2
L74:
  commit L72
L73:
  catch SET80_0
  range 00 5b
  commit L80
SET80_0:
  range 5e ff
L80:
L72:
  closecapture 34
  range 2d
  opencapture 35
  catch L82
  range 5c
  catch L84
  catch SET85_0
  range 2d 2d
  commit L85
SET85_0:
  catch SET85_1
  range 5c 5d
  commit L85
SET85_1:
  catch SET85_2
  range 6e 6e
  commit L85
SET85_2:
  catch SET85_3
  range 72 72
  commit L85
SET85_3:
  catch SET85_4
  range 74 74
  commit L85
SET85_4:
  range 76 76
L85:
  commit L83
L84:
  range 78
  counter 3 2
CTR3:
  catch SET87_0
  range 30 39
  commit L87
SET87_0:
  catch SET87_1
  range 41 46
  commit L87
SET87_1:
  range 61 66
L87:
  condjump 3 CTR3
L83:
  commit L81
L82:
  catch SET89_0
  range 00 5b
  commit L89
SET89_0:
  range 5e ff
L89:
L81:
  closecapture 35
  commit L70
L71:
  opencapture 36
  catch L92
  range 5c
  catch L94
  catch SET95_0
  range 2d 2d
  commit L95
SET95_0:
  catch SET95_1
  range 5c 5d
  commit L95
SET95_1:
  catch SET95_2
  range 6e 6e
  commit L95
SET95_2:
  catch SET95_3
  range 72 72
  commit L95
SET95_3:
  catch SET95_4
  range 74 74
  commit L95
SET95_4:
  range 76 76
L95:
  commit L93
L94:
  range 78
  counter 4 2
CTR4:
  catch SET97_0
  range 30 39
  commit L97
SET97_0:
  catch SET97_1
  range 41 46
  commit L97
SET97_1:
  range 61 66
L97:
  condjump 4 CTR4
L93:
  commit L91
L92:
  catch SET99_0
  range 00 5b
  commit L99
SET99_0:
  range 5e ff
L99:
L91:
  closecapture 36
L70:
  catch L69
LOOP69:
  catch L101
  opencapture 34
  catch L103
  range 5c
  catch L105
  catch SET106_0
  range 2d 2d
  commit L106
SET106_0:
  catch SET106_1
  range 5c 5d
  commit L106
SET106_1:
  catch SET106_2
  range 6e 6e
  commit L106
SET106_2:
  catch SET106_3
  range 72 72
  commit L106
SET106_3:
  catch SET106_4
  range 74 74
  commit L106
SET106_4:
  range 76 76
L106:
  commit L104
L105:
  range 78
  counter 5 2
CTR5:
  catch SET108_0
  range 30 39
  commit L108
SET108_0:
  catch SET108_1
  range 41 46
  commit L108
SET108_1:
  range 61 66
L108:
  condjump 5 CTR5
L104:
  commit L102
L103:
  catch SET110_0
  range 00 5b
  commit L110
SET110_0:
  range 5e ff
L110:
L102:
  closecapture 34
  range 2d
  opencapture 35
  catch L112
  range 5c
  catch L114
  catch SET115_0
  range 2d 2d
  commit L115
SET115_0:
  catch SET115_1
  range 5c 5d
  commit L115
SET115_1:
  catch SET115_2
  range 6e 6e
  commit L115
SET115_2:
  catch SET115_3
  range 72 72
  commit L115
SET115_3:
  catch SET115_4
  range 74 74
  commit L115
SET115_4:
  range 76 76
L115:
  commit L113
L114:
  range 78
  counter 6 2
CTR6:
  catch SET117_0
  range 30 39
  commit L117
SET117_0:
  catch SET117_1
  range 41 46
  commit L117
SET117_1:
  range 61 66
L117:
  condjump 6 CTR6
L113:
  commit L111
L112:
  catch SET119_0
  range 00 5b
  commit L119
SET119_0:
  range 5e ff
L119:
L111:
  closecapture 35
  commit L100
L101:
  opencapture 36
  catch L122
  range 5c
  catch L124
  catch SET125_0
  range 2d 2d
  commit L125
SET125_0:
  catch SET125_1
  range 5c 5d
  commit L125
SET125_1:
  catch SET125_2
  range 6e 6e
  commit L125
SET125_2:
  catch SET125_3
  range 72 72
  commit L125
SET125_3:
  catch SET125_4
  range 74 74
  commit L125
SET125_4:
  range 76 76
L125:
  commit L123
L124:
  range 78
  counter 7 2
CTR7:
  catch SET127_0
  range 30 39
  commit L127
SET127_0:
  catch SET127_1
  range 41 46
  commit L127
SET127_1:
  range 61 66
L127:
  condjump 7 CTR7
L123:
  commit L121
L122:
  catch SET129_0
  range 00 5b
  commit L129
SET129_0:
  range 5e ff
L129:
L121:
  closecapture 36
L100:
  partialcommit LOOP69
L69:
  call ABCLOSE
  closecapture 32
  ret

VARREFERENCE:
  call __prefix
  opencapture 37
  range 24
  catch L131
  call IDENT
  commit L130
L131:
  call NUMBER
L130:
  closecapture 37
  ret

REFERENCE:
  call __prefix
  opencapture 38
  call IDENT
  catch L133
  call LEFTARROW
  failtwice
L133:
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
  catch L134
LOOP134:
  catch MACRO135_1
  range 20
  commit L135
MACRO135_1:
  range 07 0d
L135:
  partialcommit LOOP134
L134:
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
  catch SET136_0
  range 41 5a
  commit L136
SET136_0:
  range 61 7a
L136:
  catch L137
LOOP137:
  catch SET138_0
  range 30 39
  commit L138
SET138_0:
  catch SET138_1
  range 41 5a
  commit L138
SET138_1:
  range 61 7a
L138:
  partialcommit LOOP137
L137:
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
  counter 8 2
CTR8:
  catch SET139_0
  range 30 39
  commit L139
SET139_0:
  catch SET139_1
  range 41 46
  commit L139
SET139_1:
  range 61 66
L139:
  condjump 8 CTR8
  closecapture 45
  ret

NUMBER:
  call __prefix
  opencapture 46
  range 30 39
L141:
  catch L140
LOOP140:
  range 30 39
L142:
  partialcommit LOOP140
L140:
  closecapture 46
  ret

STRING:
  call __prefix
  opencapture 47
  call STRINGLITERAL
  catch L143
  range 69
  commit __NEXT__
L143:
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
  catch L144
LOOP144:
  catch L146
  range 5c
  catch L148
  catch SET149_0
  range 27 27
  commit L149
SET149_0:
  catch SET149_1
  range 5c 5c
  commit L149
SET149_1:
  catch SET149_2
  range 6e 6e
  commit L149
SET149_2:
  catch SET149_3
  range 72 72
  commit L149
SET149_3:
  catch SET149_4
  range 74 74
  commit L149
SET149_4:
  range 76 76
L149:
  commit L147
L148:
  range 78
  counter 9 2
CTR9:
  catch SET151_0
  range 30 39
  commit L151
SET151_0:
  catch SET151_1
  range 41 46
  commit L151
SET151_1:
  range 61 66
L151:
  condjump 9 CTR9
L147:
  commit L145
L146:
  catch SET153_0
  range 00 26
  commit L153
SET153_0:
  catch SET153_1
  range 28 5b
  commit L153
SET153_1:
  range 5d ff
L153:
L145:
  partialcommit LOOP144
L144:
  closecapture 51
  range 27
  closecapture 50
  ret

BIT:
  call __prefix
  opencapture 52
  range 30 31
L154:
  closecapture 52
  ret

IDENT:
  call __prefix
  opencapture 53
  catch SET155_0
  range 41 5a
  commit L155
SET155_0:
  catch SET155_1
  range 5f 5f
  commit L155
SET155_1:
  range 61 7a
L155:
  catch L156
  counter 11 63
CTR11:
  catch SET157_0
  range 30 39
  commit L157
SET157_0:
  catch SET157_1
  range 41 5a
  commit L157
SET157_1:
  catch SET157_2
  range 5f 5f
  commit L157
SET157_2:
  range 61 7a
L157:
  partialcommit __NEXT__
  condjump 11 CTR11
  commit __NEXT__
L156:
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


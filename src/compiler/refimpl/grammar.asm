-- GPEG compiler, release 0.6.1

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
  char 20
  commit L6
MACRO6_1:
  range 07 0d
L6:
  catch L5
LOOP5:
  catch MACRO7_1
  char 20
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
  char 2d
  char 2d
  char 5b
  char 5b
  catch L8
LOOP8:
  catch L9
  char 5d
  char 5d
  failtwice
L9:
  any
  partialcommit LOOP8
L8:
  char 5d
  char 5d
  closecapture 3
  ret

COMMENT:
  opencapture 4
  char 2d
  char 2d
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
  char 0a
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
  any
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
  range 30 39
L37:
  catch L36
LOOP36:
  range 30 39
L38:
  partialcommit LOOP36
L36:
  closecapture 18
  char 2d
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
  char 5e
  char 2d
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
  char 5e
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
  char 2d
  closecapture 22
  ret

Q_SPECIFIC:
  call __prefix
  opencapture 24
  char 5e
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
  char 5e
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
  catch L64
  call LIMITEDCALL
  commit L51
L64:
  call ANNOTATION
L51:
  closecapture 27
  ret

BITMASK:
  call __prefix
  opencapture 28
  char 7c
  catch SET67_0
  range 30 31
  commit L67
SET67_0:
  range 5f 5f
L67:
  catch L66
  counter 1 7
CTR1:
  catch SET68_0
  range 30 31
  commit L68
SET68_0:
  range 5f 5f
L68:
  partialcommit __NEXT__
  condjump 1 CTR1
  commit __NEXT__
L66:
  char 7c
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
  catch L69
  opencapture 33
  char 5e
  closecapture 33
  commit __NEXT__
L69:
  catch L72
  opencapture 34
  catch L74
  char 5c
  catch L76
  catch SET77_0
  range 2d 2d
  commit L77
SET77_0:
  catch SET77_1
  range 5c 5d
  commit L77
SET77_1:
  catch SET77_2
  range 6e 6e
  commit L77
SET77_2:
  catch SET77_3
  range 72 72
  commit L77
SET77_3:
  catch SET77_4
  range 74 74
  commit L77
SET77_4:
  range 76 76
L77:
  commit L75
L76:
  char 78
  counter 2 2
CTR2:
  catch SET79_0
  range 30 39
  commit L79
SET79_0:
  catch SET79_1
  range 41 46
  commit L79
SET79_1:
  range 61 66
L79:
  condjump 2 CTR2
L75:
  commit L73
L74:
  catch SET81_0
  range 00 5b
  commit L81
SET81_0:
  range 5e ff
L81:
L73:
  closecapture 34
  char 2d
  opencapture 35
  catch L83
  char 5c
  catch L85
  catch SET86_0
  range 2d 2d
  commit L86
SET86_0:
  catch SET86_1
  range 5c 5d
  commit L86
SET86_1:
  catch SET86_2
  range 6e 6e
  commit L86
SET86_2:
  catch SET86_3
  range 72 72
  commit L86
SET86_3:
  catch SET86_4
  range 74 74
  commit L86
SET86_4:
  range 76 76
L86:
  commit L84
L85:
  char 78
  counter 3 2
CTR3:
  catch SET88_0
  range 30 39
  commit L88
SET88_0:
  catch SET88_1
  range 41 46
  commit L88
SET88_1:
  range 61 66
L88:
  condjump 3 CTR3
L84:
  commit L82
L83:
  catch SET90_0
  range 00 5b
  commit L90
SET90_0:
  range 5e ff
L90:
L82:
  closecapture 35
  commit L71
L72:
  opencapture 36
  catch L93
  char 5c
  catch L95
  catch SET96_0
  range 2d 2d
  commit L96
SET96_0:
  catch SET96_1
  range 5c 5d
  commit L96
SET96_1:
  catch SET96_2
  range 6e 6e
  commit L96
SET96_2:
  catch SET96_3
  range 72 72
  commit L96
SET96_3:
  catch SET96_4
  range 74 74
  commit L96
SET96_4:
  range 76 76
L96:
  commit L94
L95:
  char 78
  counter 4 2
CTR4:
  catch SET98_0
  range 30 39
  commit L98
SET98_0:
  catch SET98_1
  range 41 46
  commit L98
SET98_1:
  range 61 66
L98:
  condjump 4 CTR4
L94:
  commit L92
L93:
  catch SET100_0
  range 00 5b
  commit L100
SET100_0:
  range 5e ff
L100:
L92:
  closecapture 36
L71:
  catch L70
LOOP70:
  catch L102
  opencapture 34
  catch L104
  char 5c
  catch L106
  catch SET107_0
  range 2d 2d
  commit L107
SET107_0:
  catch SET107_1
  range 5c 5d
  commit L107
SET107_1:
  catch SET107_2
  range 6e 6e
  commit L107
SET107_2:
  catch SET107_3
  range 72 72
  commit L107
SET107_3:
  catch SET107_4
  range 74 74
  commit L107
SET107_4:
  range 76 76
L107:
  commit L105
L106:
  char 78
  counter 5 2
CTR5:
  catch SET109_0
  range 30 39
  commit L109
SET109_0:
  catch SET109_1
  range 41 46
  commit L109
SET109_1:
  range 61 66
L109:
  condjump 5 CTR5
L105:
  commit L103
L104:
  catch SET111_0
  range 00 5b
  commit L111
SET111_0:
  range 5e ff
L111:
L103:
  closecapture 34
  char 2d
  opencapture 35
  catch L113
  char 5c
  catch L115
  catch SET116_0
  range 2d 2d
  commit L116
SET116_0:
  catch SET116_1
  range 5c 5d
  commit L116
SET116_1:
  catch SET116_2
  range 6e 6e
  commit L116
SET116_2:
  catch SET116_3
  range 72 72
  commit L116
SET116_3:
  catch SET116_4
  range 74 74
  commit L116
SET116_4:
  range 76 76
L116:
  commit L114
L115:
  char 78
  counter 6 2
CTR6:
  catch SET118_0
  range 30 39
  commit L118
SET118_0:
  catch SET118_1
  range 41 46
  commit L118
SET118_1:
  range 61 66
L118:
  condjump 6 CTR6
L114:
  commit L112
L113:
  catch SET120_0
  range 00 5b
  commit L120
SET120_0:
  range 5e ff
L120:
L112:
  closecapture 35
  commit L101
L102:
  opencapture 36
  catch L123
  char 5c
  catch L125
  catch SET126_0
  range 2d 2d
  commit L126
SET126_0:
  catch SET126_1
  range 5c 5d
  commit L126
SET126_1:
  catch SET126_2
  range 6e 6e
  commit L126
SET126_2:
  catch SET126_3
  range 72 72
  commit L126
SET126_3:
  catch SET126_4
  range 74 74
  commit L126
SET126_4:
  range 76 76
L126:
  commit L124
L125:
  char 78
  counter 7 2
CTR7:
  catch SET128_0
  range 30 39
  commit L128
SET128_0:
  catch SET128_1
  range 41 46
  commit L128
SET128_1:
  range 61 66
L128:
  condjump 7 CTR7
L124:
  commit L122
L123:
  catch SET130_0
  range 00 5b
  commit L130
SET130_0:
  range 5e ff
L130:
L122:
  closecapture 36
L101:
  partialcommit LOOP70
L70:
  call ABCLOSE
  closecapture 32
  ret

VARREFERENCE:
  call __prefix
  opencapture 37
  char 24
  catch L132
  call IDENT
  commit L131
L132:
  call NUMBER
L131:
  closecapture 37
  ret

REFERENCE:
  call __prefix
  opencapture 38
  call IDENT
  catch L134
  call LEFTARROW
  failtwice
L134:
  closecapture 38
  ret

LIMITEDCALL:
  call __prefix
  opencapture 39
  char 3c
  char 3a
  char 24
  call IDENT
  call COLON
  call BIT
  call COLON
  call NUMBER
  call COLON
  call IDENT
  catch L135
LOOP135:
  catch MACRO136_1
  char 20
  commit L136
MACRO136_1:
  range 07 0d
L136:
  partialcommit LOOP135
L135:
  char 3e
  closecapture 39
  ret

LEFTARROW:
  call __prefix
  opencapture 40
  char 3c
  char 2d
  closecapture 40
  ret

NOT:
  call __prefix
  opencapture 41
  char 21
  closecapture 41
  ret

AND:
  call __prefix
  opencapture 42
  char 26
  closecapture 42
  ret

MACRO:
  call __prefix
  opencapture 43
  char 25
  catch SET137_0
  range 41 5a
  commit L137
SET137_0:
  range 61 7a
L137:
  catch L138
LOOP138:
  catch SET139_0
  range 30 39
  commit L139
SET139_0:
  catch SET139_1
  range 41 5a
  commit L139
SET139_1:
  range 61 7a
L139:
  partialcommit LOOP138
L138:
  closecapture 43
  ret

ENDFORCE:
  call __prefix
  opencapture 44
  char 5f
  char 5f
  char 65
  char 6e
  char 64
  call S
  call NUMBER
  closecapture 44
  ret

ANNOTATION:
  call __prefix
  opencapture 45
  char 40
  char 40
  call IDENT
  opencapture 46
  catch L140
LOOP140:
  catch SET141_0
  range 00 09
  commit L141
SET141_0:
  range 0b ff
L141:
  partialcommit LOOP140
L140:
  closecapture 46
  char 0a
  closecapture 45
  ret

HEXLITERAL:
  call __prefix
  opencapture 47
  char 30
  char 78
  counter 8 2
CTR8:
  catch SET142_0
  range 30 39
  commit L142
SET142_0:
  catch SET142_1
  range 41 46
  commit L142
SET142_1:
  range 61 66
L142:
  condjump 8 CTR8
  closecapture 47
  ret

NUMBER:
  call __prefix
  opencapture 48
  range 30 39
L144:
  catch L143
LOOP143:
  range 30 39
L145:
  partialcommit LOOP143
L143:
  closecapture 48
  ret

STRING:
  call __prefix
  opencapture 49
  call STRINGLITERAL
  catch L146
  char 69
  commit __NEXT__
L146:
  closecapture 49
  ret

OR:
  call __prefix
  opencapture 50
  char 2f
  closecapture 50
  ret

ANY:
  call __prefix
  opencapture 51
  char 2e
  closecapture 51
  ret

STRINGLITERAL:
  call __prefix
  opencapture 52
  char 27
  opencapture 53
  catch L147
LOOP147:
  catch L149
  char 5c
  catch L151
  catch SET152_0
  range 27 27
  commit L152
SET152_0:
  catch SET152_1
  range 5c 5c
  commit L152
SET152_1:
  catch SET152_2
  range 6e 6e
  commit L152
SET152_2:
  catch SET152_3
  range 72 72
  commit L152
SET152_3:
  catch SET152_4
  range 74 74
  commit L152
SET152_4:
  range 76 76
L152:
  commit L150
L151:
  char 78
  counter 9 2
CTR9:
  catch SET154_0
  range 30 39
  commit L154
SET154_0:
  catch SET154_1
  range 41 46
  commit L154
SET154_1:
  range 61 66
L154:
  condjump 9 CTR9
L150:
  commit L148
L149:
  catch SET156_0
  range 00 26
  commit L156
SET156_0:
  catch SET156_1
  range 28 5b
  commit L156
SET156_1:
  range 5d ff
L156:
L148:
  partialcommit LOOP147
L147:
  closecapture 53
  char 27
  closecapture 52
  ret

BIT:
  call __prefix
  opencapture 54
  range 30 31
L157:
  closecapture 54
  ret

IDENT:
  call __prefix
  opencapture 55
  catch SET158_0
  range 41 5a
  commit L158
SET158_0:
  catch SET158_1
  range 5f 5f
  commit L158
SET158_1:
  range 61 7a
L158:
  catch L159
  counter 11 63
CTR11:
  catch SET160_0
  range 30 39
  commit L160
SET160_0:
  catch SET160_1
  range 41 5a
  commit L160
SET160_1:
  catch SET160_2
  range 5f 5f
  commit L160
SET160_2:
  range 61 7a
L160:
  partialcommit __NEXT__
  condjump 11 CTR11
  commit __NEXT__
L159:
  closecapture 55
  ret

BOPEN:
  call __prefix
  opencapture 56
  char 28
  closecapture 56
  ret

BCLOSE:
  call __prefix
  opencapture 57
  char 29
  closecapture 57
  ret

CBOPEN:
  call __prefix
  opencapture 58
  char 7b
  closecapture 58
  ret

CBCLOSE:
  call __prefix
  opencapture 59
  char 7d
  closecapture 59
  ret

ABOPEN:
  call __prefix
  opencapture 60
  char 5b
  closecapture 60
  ret

ABCLOSE:
  call __prefix
  opencapture 61
  char 5d
  closecapture 61
  ret

COLON:
  call __prefix
  opencapture 62
  char 3a
  closecapture 62
  ret

SEMICOLON:
  call __prefix
  opencapture 63
  char 3b
  closecapture 63
  ret


  call TOP
  end 0

TOP:
  opencapture 0
  call INSTRUCTIONS
  closecapture 0
  ret

S:
  opencapture 1
  set 002e000001000000000000000000000000000000000000000000000000000000
  catch __L1
__L2:
  set 002e000001000000000000000000000000000000000000000000000000000000
  partialcommit __L2
__L1:
  closecapture 1
  ret

MULTILINECOMMENT:
  opencapture 2
  quad 2d2d5b5b
  catch __L3
__L4:
  catch __L5
  char 5d
  char 5d
  failtwice
__L5:
  any
  partialcommit __L4
__L3:
  char 5d
  char 5d
  closecapture 2
  ret

COMMENT:
  opencapture 3
  char 2d
  char 2d
  catch __L6
__L7:
  set fffbffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
  partialcommit __L7
__L6:
  char 0a
  closecapture 3
  ret

__prefix:
  catch __L8
__L9:
  catch __L10
  call MULTILINECOMMENT
  commit __L11
__L10:
  catch __L12
  call COMMENT
  commit __L13
__L12:
  call S
__L13:
__L11:
  partialcommit __L9
__L8:
  ret

INSTRUCTIONS:
  call __prefix
  opencapture 4
  call INSTRUCTION
  catch __L14
__L15:
  call INSTRUCTION
  partialcommit __L15
__L14:
  call END
  closecapture 4
  ret

INSTRUCTION:
  call __prefix
  opencapture 5
  catch __L16
  call RULEINSTR
  commit __L17
__L16:
  call LABELDEF
__L17:
  closecapture 5
  ret

RULEINSTR:
  call __prefix
  opencapture 6
  catch __L18
  call ANYINSTR
  commit __L19
__L18:
  catch __L20
  call BACKCOMMITINSTR
  commit __L21
__L20:
  catch __L22
  call CALLINSTR
  commit __L23
__L22:
  catch __L24
  call CATCHINSTR
  commit __L25
__L24:
  catch __L26
  call CHARINSTR
  commit __L27
__L26:
  catch __L28
  call BITMASKINSTR
  commit __L29
__L28:
  catch __L30
  call CLOSECAPTUREINSTR
  commit __L31
__L30:
  catch __L32
  call COMMITINSTR
  commit __L33
__L32:
  catch __L34
  call INTRPCAPTUREINSTR
  commit __L35
__L34:
  catch __L36
  call ENDINSTR
  commit __L37
__L36:
  catch __L38
  call FAILTWICEINSTR
  commit __L39
__L38:
  catch __L40
  call FAILINSTR
  commit __L41
__L40:
  catch __L42
  call JUMPINSTR
  commit __L43
__L42:
  catch __L44
  call NOOPINSTR
  commit __L45
__L44:
  catch __L46
  call TRAPINSTR
  commit __L47
__L46:
  catch __L48
  call OPENCAPTUREINSTR
  commit __L49
__L48:
  catch __L50
  call PARTIALCOMMITINSTR
  commit __L51
__L50:
  catch __L52
  call QUADINSTR
  commit __L53
__L52:
  catch __L54
  call RETINSTR
  commit __L55
__L54:
  catch __L56
  call SETINSTR
  commit __L57
__L56:
  catch __L58
  call RANGEINSTR
  commit __L59
__L58:
  catch __L60
  call SKIPINSTR
  commit __L61
__L60:
  catch __L62
  call SPANINSTR
  commit __L63
__L62:
  catch __L64
  call TESTANYINSTR
  commit __L65
__L64:
  catch __L66
  call TESTCHARINSTR
  commit __L67
__L66:
  catch __L68
  call TESTQUADINSTR
  commit __L69
__L68:
  catch __L70
  call TESTSETINSTR
  commit __L71
__L70:
  catch __L72
  call VARINSTR
  commit __L73
__L72:
  catch __L74
  call COUNTERINSTR
  commit __L75
__L74:
  call CONDJUMPINSTR
__L75:
__L73:
__L71:
__L69:
__L67:
__L65:
__L63:
__L61:
__L59:
__L57:
__L55:
__L53:
__L51:
__L49:
__L47:
__L45:
__L43:
__L41:
__L39:
__L37:
__L35:
__L33:
__L31:
__L29:
__L27:
__L25:
__L23:
__L21:
__L19:
  closecapture 6
  ret

END:
  call __prefix
  opencapture 7
  catch __L76
  any
  failtwice
__L76:
  closecapture 7
  ret

ANYINSTR:
  call __prefix
  opencapture 8
  char 61
  char 6e
  char 79
  closecapture 8
  ret

BACKCOMMITINSTR:
  call __prefix
  opencapture 9
  quad 6261636b
  quad 636f6d6d
  char 69
  char 74
  call S
  call LABEL
  closecapture 9
  ret

CALLINSTR:
  call __prefix
  opencapture 10
  quad 63616c6c
  call S
  call LABEL
  closecapture 10
  ret

CATCHINSTR:
  call __prefix
  opencapture 11
  catch __L77
  quad 63617463
  char 68
  commit __L78
__L77:
  quad 63686f69
  char 63
  char 65
__L78:
  call S
  call LABEL
  closecapture 11
  ret

CHARINSTR:
  call __prefix
  opencapture 12
  quad 63686172
  call S
  call HEXBYTE
  closecapture 12
  ret

BITMASKINSTR:
  call __prefix
  opencapture 13
  quad 6269746d
  char 61
  char 73
  char 6b
  call S
  call UNSIGNED
  call S
  call HEXQUAD
  call S
  call HEXQUAD
  call S
  call HEXQUAD
  closecapture 13
  ret

CLOSECAPTUREINSTR:
  call __prefix
  opencapture 14
  quad 636c6f73
  quad 65636170
  quad 74757265
  call S
  call SLOT
  closecapture 14
  ret

COMMITINSTR:
  call __prefix
  opencapture 15
  quad 636f6d6d
  char 69
  char 74
  call S
  call LABEL
  closecapture 15
  ret

ENDINSTR:
  call __prefix
  opencapture 16
  char 65
  char 6e
  char 64
  call S
  call CODE
  closecapture 16
  ret

FAILINSTR:
  call __prefix
  opencapture 17
  quad 6661696c
  closecapture 17
  ret

FAILTWICEINSTR:
  call __prefix
  opencapture 18
  quad 6661696c
  quad 74776963
  char 65
  closecapture 18
  ret

INTRPCAPTUREINSTR:
  call __prefix
  opencapture 19
  quad 696e7472
  quad 70636170
  quad 74757265
  call S
  call INTRPCAPTURETYPES
  call S
  catch __L79
  call SLOT
  commit __L80
__L79:
  quad 64656661
  char 75
  char 6c
  char 74
__L80:
  closecapture 19
  ret

JUMPINSTR:
  call __prefix
  opencapture 20
  quad 6a756d70
  call S
  call LABEL
  closecapture 20
  ret

NOOPINSTR:
  call __prefix
  opencapture 21
  quad 6e6f6f70
  closecapture 21
  ret

TRAPINSTR:
  call __prefix
  opencapture 22
  quad 74726170
  closecapture 22
  ret

OPENCAPTUREINSTR:
  call __prefix
  opencapture 23
  quad 6f70656e
  quad 63617074
  char 75
  char 72
  char 65
  call S
  call SLOT
  closecapture 23
  ret

PARTIALCOMMITINSTR:
  call __prefix
  opencapture 24
  quad 70617274
  quad 69616c63
  quad 6f6d6d69
  char 74
  call S
  call LABEL
  closecapture 24
  ret

QUADINSTR:
  call __prefix
  opencapture 25
  quad 71756164
  call S
  call QUAD
  closecapture 25
  ret

RETINSTR:
  call __prefix
  opencapture 26
  char 72
  char 65
  char 74
  closecapture 26
  ret

SETINSTR:
  call __prefix
  opencapture 27
  char 73
  char 65
  char 74
  call S
  call SET
  closecapture 27
  ret

RANGEINSTR:
  call __prefix
  opencapture 28
  quad 72616e67
  char 65
  call S
  call HEXBYTE
  call S
  call HEXBYTE
  closecapture 28
  ret

SKIPINSTR:
  call __prefix
  opencapture 29
  quad 736b6970
  call S
  call UNSIGNED
  closecapture 29
  ret

SPANINSTR:
  call __prefix
  opencapture 30
  quad 7370616e
  call S
  call SET
  closecapture 30
  ret

TESTANYINSTR:
  call __prefix
  opencapture 31
  quad 74657374
  char 61
  char 6e
  char 79
  call S
  call LABEL
  closecapture 31
  ret

TESTCHARINSTR:
  call __prefix
  opencapture 32
  quad 74657374
  quad 63686172
  call S
  call HEXBYTE
  call S
  call LABEL
  closecapture 32
  ret

TESTQUADINSTR:
  call __prefix
  opencapture 33
  quad 74657374
  quad 71756164
  call S
  call QUAD
  call S
  call LABEL
  closecapture 33
  ret

TESTSETINSTR:
  call __prefix
  opencapture 34
  quad 74657374
  char 73
  char 65
  char 74
  call S
  call SET
  call S
  call LABEL
  closecapture 34
  ret

VARINSTR:
  call __prefix
  opencapture 35
  char 76
  char 61
  char 72
  call S
  call SLOT
  closecapture 35
  ret

COUNTERINSTR:
  call __prefix
  opencapture 36
  quad 636f756e
  char 74
  char 65
  char 72
  call S
  call REGISTER
  call S
  call UNSIGNED
  closecapture 36
  ret

CONDJUMPINSTR:
  call __prefix
  opencapture 37
  quad 636f6e64
  quad 6a756d70
  call S
  call REGISTER
  call S
  call LABEL
  closecapture 37
  ret

LABELDEF:
  call __prefix
  opencapture 38
  call LABEL
  call COLON
  closecapture 38
  ret

CODE:
  call __prefix
  opencapture 39
  call UNSIGNED
  closecapture 39
  ret

HEXBYTE:
  call __prefix
  opencapture 40
  counter 0 2
__L81:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 0 __L81
  closecapture 40
  ret

HEXQUAD:
  call __prefix
  opencapture 41
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  catch __L82
  counter 1 7
__L83:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  partialcommit __NEXT__
  condjump 1 __L83
  commit __L82
__L82:
  closecapture 41
  ret

LABEL:
  call __prefix
  opencapture 42
  set 000000000000ff03feffff87feffff0700000000000000000000000000000000
  catch __L84
  counter 2 63
__L85:
  set 000000000000ff03feffff87feffff0700000000000000000000000000000000
  partialcommit __NEXT__
  condjump 2 __L85
  commit __L84
__L84:
  closecapture 42
  ret

UNSIGNED:
  call __prefix
  opencapture 43
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L86
__L87:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L87
__L86:
  closecapture 43
  ret

NUMBER:
  call __prefix
  opencapture 44
  catch __L88
  char 2d
  commit __L88
__L88:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L90
__L91:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L91
__L90:
  closecapture 44
  ret

QUAD:
  call __prefix
  opencapture 45
  counter 4 8
__L92:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 4 __L92
  closecapture 45
  ret

SET:
  call __prefix
  opencapture 46
  counter 5 64
__L93:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 5 __L93
  closecapture 46
  ret

SLOT:
  call __prefix
  opencapture 47
  call UNSIGNED
  closecapture 47
  ret

REGISTER:
  call __prefix
  opencapture 48
  call UNSIGNED
  closecapture 48
  ret

TYPE:
  call __prefix
  opencapture 49
  call UNSIGNED
  closecapture 49
  ret

COLON:
  call __prefix
  opencapture 50
  char 3a
  closecapture 50
  ret

AMPERSAND:
  call __prefix
  opencapture 51
  char 26
  closecapture 51
  ret

STRINGLITERAL:
  call __prefix
  opencapture 52
  char 27
  opencapture 53
  catch __L94
__L95:
  catch __L96
  char 5c
  catch __L98
  set 0000000080000000000000100040540000000000000000000000000000000000
  commit __L99
__L98:
  counter 6 3
__L100:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  condjump 6 __L100
__L99:
  commit __L97
__L96:
  set ffffffff7fffffffffffffefffffffffffffffffffffffffffffffffffffffff
__L97:
  partialcommit __L95
__L94:
  closecapture 53
  char 27
  closecapture 52
  ret

INTRPCAPTURETYPES:
  call __prefix
  opencapture 54
  opencapture 55
  quad 7275696e
  char 74
  char 33
  char 32
  closecapture 55
  closecapture 54
  ret


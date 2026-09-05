-- GPEG compiler, release 0.6.1

  call TOP
  end 0

TOP:
  opencapture 1
  call INSTRUCTIONS
  closecapture 1
  ret

S:
  opencapture 2
  catch MACRO2_1
  char 20
  commit L2
MACRO2_1:
  range 07 0d
L2:
  catch L1
LOOP1:
  catch MACRO3_1
  char 20
  commit L3
MACRO3_1:
  range 07 0d
L3:
  partialcommit LOOP1
L1:
  closecapture 2
  ret

MULTILINECOMMENT:
  opencapture 3
  char 2d
  char 2d
  char 5b
  char 5b
  catch L4
LOOP4:
  catch L5
  char 5d
  char 5d
  failtwice
L5:
  any
  partialcommit LOOP4
L4:
  char 5d
  char 5d
  closecapture 3
  ret

COMMENT:
  opencapture 4
  char 2d
  char 2d
  catch L6
LOOP6:
  catch SET7_0
  range 00 09
  commit L7
SET7_0:
  range 0b ff
L7:
  partialcommit LOOP6
L6:
  char 0a
  closecapture 4
  ret

__prefix:
  catch L8
LOOP8:
  catch L10
  call MULTILINECOMMENT
  commit L9
L10:
  catch L11
  call COMMENT
  commit L9
L11:
  call S
L9:
  partialcommit LOOP8
L8:
  ret

INSTRUCTIONS:
  call __prefix
  opencapture 5
  call INSTRUCTION
  catch L13
LOOP13:
  call INSTRUCTION
  partialcommit LOOP13
L13:
  call END
  closecapture 5
  ret

INSTRUCTION:
  call __prefix
  opencapture 6
  catch L15
  call RULEINSTR
  commit L14
L15:
  call LABELDEF
L14:
  closecapture 6
  ret

RULEINSTR:
  call __prefix
  opencapture 7
  catch L18
  call BACKCOMMITINSTR
  commit L17
L18:
  catch L19
  call CALLINSTR
  commit L17
L19:
  catch L20
  call CATCHINSTR
  commit L17
L20:
  catch L21
  call CLOSECAPTUREINSTR
  commit L17
L21:
  catch L22
  call COMMITINSTR
  commit L17
L22:
  catch L23
  call ENDINSTR
  commit L17
L23:
  catch L24
  call FAILTWICEINSTR
  commit L17
L24:
  catch L25
  call FAILINSTR
  commit L17
L25:
  catch L26
  call LIMITINSTR
  commit L17
L26:
  catch L27
  call OPENCAPTUREINSTR
  commit L17
L27:
  catch L28
  call PARTIALCOMMITINSTR
  commit L17
L28:
  catch L29
  call RETINSTR
  commit L17
L29:
  catch L30
  call RANGEINSTR
  commit L17
L30:
  catch L31
  call BITMASKINSTR
  commit L17
L31:
  catch L32
  call CHARINSTR
  commit L17
L32:
  catch L33
  call ANYINSTR
  commit L17
L33:
  catch L34
  call VARINSTR
  commit L17
L34:
  catch L35
  call COUNTERINSTR
  commit L17
L35:
  call CONDJUMPINSTR
L17:
  closecapture 7
  ret

END:
  call __prefix
  opencapture 8
  catch L37
  any
  failtwice
L37:
  closecapture 8
  ret

BACKCOMMITINSTR:
  call __prefix
  opencapture 9
  char 62
  char 61
  char 63
  char 6b
  char 63
  char 6f
  char 6d
  char 6d
  char 69
  char 74
  call S
  call LABEL
  closecapture 9
  ret

CALLINSTR:
  call __prefix
  opencapture 10
  char 63
  char 61
  char 6c
  char 6c
  call S
  call LABEL
  closecapture 10
  ret

CATCHINSTR:
  call __prefix
  opencapture 11
  char 63
  char 61
  char 74
  char 63
  char 68
  call S
  call LABEL
  closecapture 11
  ret

CLOSECAPTUREINSTR:
  call __prefix
  opencapture 12
  char 63
  char 6c
  char 6f
  char 73
  char 65
  char 63
  char 61
  char 70
  char 74
  char 75
  char 72
  char 65
  call S
  call SLOT
  closecapture 12
  ret

COMMITINSTR:
  call __prefix
  opencapture 13
  char 63
  char 6f
  char 6d
  char 6d
  char 69
  char 74
  call S
  call LABEL
  closecapture 13
  ret

ENDINSTR:
  call __prefix
  opencapture 14
  char 65
  char 6e
  char 64
  call S
  call CODE
  closecapture 14
  ret

FAILINSTR:
  call __prefix
  opencapture 15
  char 66
  char 61
  char 69
  char 6c
  closecapture 15
  ret

FAILTWICEINSTR:
  call __prefix
  opencapture 16
  char 66
  char 61
  char 69
  char 6c
  char 74
  char 77
  char 69
  char 63
  char 65
  closecapture 16
  ret

LIMITINSTR:
  call __prefix
  opencapture 17
  char 6c
  char 69
  char 6d
  char 69
  char 74
  call S
  call BIT
  call S
  call UNSIGNED
  call S
  call SLOT
  closecapture 17
  ret

OPENCAPTUREINSTR:
  call __prefix
  opencapture 18
  char 6f
  char 70
  char 65
  char 6e
  char 63
  char 61
  char 70
  char 74
  char 75
  char 72
  char 65
  call S
  call SLOT
  closecapture 18
  ret

PARTIALCOMMITINSTR:
  call __prefix
  opencapture 19
  char 70
  char 61
  char 72
  char 74
  char 69
  char 61
  char 6c
  char 63
  char 6f
  char 6d
  char 6d
  char 69
  char 74
  call S
  call LABEL
  closecapture 19
  ret

RETINSTR:
  call __prefix
  opencapture 20
  char 72
  char 65
  char 74
  closecapture 20
  ret

CHARINSTR:
  call __prefix
  opencapture 21
  char 63
  char 68
  char 61
  char 72
  call S
  call HEXBYTE
  closecapture 21
  ret

RANGEINSTR:
  call __prefix
  opencapture 22
  char 72
  char 61
  char 6e
  char 67
  char 65
  call S
  call HEXBYTE
  call S
  call HEXBYTE
  closecapture 22
  ret

BITMASKINSTR:
  call __prefix
  opencapture 23
  char 62
  char 69
  char 74
  char 6d
  char 61
  char 73
  char 6b
  call S
  catch L38
  call BOOLEAN
  call UNSIGNED
  commit __NEXT__
L38:
  call HEXBYTE
  call S
  catch L39
  counter 1 2
CTR1:
  call HEXBYTE
  call S
  partialcommit __NEXT__
  condjump 1 CTR1
  commit __NEXT__
L39:
  closecapture 23
  ret

ANYINSTR:
  call __prefix
  opencapture 24
  char 61
  char 6e
  char 79
  closecapture 24
  ret

VARINSTR:
  call __prefix
  opencapture 25
  char 76
  char 61
  char 72
  call S
  call SLOT
  closecapture 25
  ret

COUNTERINSTR:
  call __prefix
  opencapture 26
  char 63
  char 6f
  char 75
  char 6e
  char 74
  char 65
  char 72
  call S
  call REGISTER
  call S
  call UNSIGNED
  closecapture 26
  ret

CONDJUMPINSTR:
  call __prefix
  opencapture 27
  char 63
  char 6f
  char 6e
  char 64
  char 6a
  char 75
  char 6d
  char 70
  call S
  call REGISTER
  call S
  call LABEL
  closecapture 27
  ret

LABELDEF:
  call __prefix
  opencapture 28
  call LABEL
  call COLON
  closecapture 28
  ret

HEXBYTE:
  call __prefix
  opencapture 29
  counter 2 2
CTR2:
  catch SET40_0
  range 30 39
  commit L40
SET40_0:
  catch SET40_1
  range 41 46
  commit L40
SET40_1:
  range 61 66
L40:
  condjump 2 CTR2
  closecapture 29
  ret

BOOLEAN:
  call __prefix
  opencapture 30
  catch L42
  char 74
  char 72
  char 75
  char 65
  commit L41
L42:
  char 66
  char 61
  char 6c
  char 73
  char 65
L41:
  closecapture 30
  ret

LABEL:
  call __prefix
  opencapture 31
  catch SET45_0
  range 30 39
  commit L45
SET45_0:
  catch SET45_1
  range 41 5a
  commit L45
SET45_1:
  catch SET45_2
  range 5f 5f
  commit L45
SET45_2:
  range 61 7a
L45:
  catch L44
  counter 4 63
CTR4:
  catch SET46_0
  range 30 39
  commit L46
SET46_0:
  catch SET46_1
  range 41 5a
  commit L46
SET46_1:
  catch SET46_2
  range 5f 5f
  commit L46
SET46_2:
  range 61 7a
L46:
  partialcommit __NEXT__
  condjump 4 CTR4
  commit __NEXT__
L44:
  closecapture 31
  ret

CODE:
  call __prefix
  opencapture 32
  call UNSIGNED
  closecapture 32
  ret

SLOT:
  call __prefix
  opencapture 33
  call UNSIGNED
  closecapture 33
  ret

REGISTER:
  call __prefix
  opencapture 34
  call UNSIGNED
  closecapture 34
  ret

TYPE:
  call __prefix
  opencapture 35
  call UNSIGNED
  closecapture 35
  ret

UNSIGNED:
  call __prefix
  opencapture 36
  range 30 39
L48:
  catch L47
LOOP47:
  range 30 39
L49:
  partialcommit LOOP47
L47:
  closecapture 36
  ret

BIT:
  call __prefix
  opencapture 37
  range 30 31
L50:
  closecapture 37
  ret

COLON:
  call __prefix
  opencapture 38
  char 3a
  closecapture 38
  ret


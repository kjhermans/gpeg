-- GPEG compiler, release 0.5.15

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
  range 20
  commit L2
MACRO2_1:
  range 07 0d
L2:
  catch L1
LOOP1:
  catch MACRO3_1
  range 20
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
  range 2d
  range 2d
  range 5b
  range 5b
  catch L4
LOOP4:
  catch L5
  range 5d
  range 5d
  failtwice
L5:
  range 00 ff
  partialcommit LOOP4
L4:
  range 5d
  range 5d
  closecapture 3
  ret

COMMENT:
  opencapture 4
  range 2d
  range 2d
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
  range 0a
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
  call VARINSTR
  commit L17
L31:
  catch L32
  call COUNTERINSTR
  commit L17
L32:
  call CONDJUMPINSTR
L17:
  closecapture 7
  ret

END:
  call __prefix
  opencapture 8
  catch L34
  range 00 ff
  failtwice
L34:
  closecapture 8
  ret

BACKCOMMITINSTR:
  call __prefix
  opencapture 9
  range 62
  range 61
  range 63
  range 6b
  range 63
  range 6f
  range 6d
  range 6d
  range 69
  range 74
  call S
  call LABEL
  closecapture 9
  ret

CALLINSTR:
  call __prefix
  opencapture 10
  range 63
  range 61
  range 6c
  range 6c
  call S
  call LABEL
  closecapture 10
  ret

CATCHINSTR:
  call __prefix
  opencapture 11
  range 63
  range 61
  range 74
  range 63
  range 68
  call S
  call LABEL
  closecapture 11
  ret

CLOSECAPTUREINSTR:
  call __prefix
  opencapture 12
  range 63
  range 6c
  range 6f
  range 73
  range 65
  range 63
  range 61
  range 70
  range 74
  range 75
  range 72
  range 65
  call S
  call SLOT
  closecapture 12
  ret

COMMITINSTR:
  call __prefix
  opencapture 13
  range 63
  range 6f
  range 6d
  range 6d
  range 69
  range 74
  call S
  call LABEL
  closecapture 13
  ret

ENDINSTR:
  call __prefix
  opencapture 14
  range 65
  range 6e
  range 64
  call S
  call CODE
  closecapture 14
  ret

FAILINSTR:
  call __prefix
  opencapture 15
  range 66
  range 61
  range 69
  range 6c
  closecapture 15
  ret

FAILTWICEINSTR:
  call __prefix
  opencapture 16
  range 66
  range 61
  range 69
  range 6c
  range 74
  range 77
  range 69
  range 63
  range 65
  closecapture 16
  ret

LIMITINSTR:
  call __prefix
  opencapture 17
  range 6c
  range 69
  range 6d
  range 69
  range 74
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
  range 6f
  range 70
  range 65
  range 6e
  range 63
  range 61
  range 70
  range 74
  range 75
  range 72
  range 65
  call S
  call SLOT
  closecapture 18
  ret

PARTIALCOMMITINSTR:
  call __prefix
  opencapture 19
  range 70
  range 61
  range 72
  range 74
  range 69
  range 61
  range 6c
  range 63
  range 6f
  range 6d
  range 6d
  range 69
  range 74
  call S
  call LABEL
  closecapture 19
  ret

RETINSTR:
  call __prefix
  opencapture 20
  range 72
  range 65
  range 74
  closecapture 20
  ret

RANGEINSTR:
  call __prefix
  opencapture 21
  range 72
  range 61
  range 6e
  range 67
  range 65
  call S
  catch L35
  call BOOLEAN
  call UNSIGNED
  commit __NEXT__
L35:
  call HEXBYTE
  call S
  catch L36
  counter 1 2
CTR1:
  call HEXBYTE
  call S
  partialcommit __NEXT__
  condjump 1 CTR1
  commit __NEXT__
L36:
  closecapture 21
  ret

VARINSTR:
  call __prefix
  opencapture 22
  range 76
  range 61
  range 72
  call S
  call SLOT
  closecapture 22
  ret

COUNTERINSTR:
  call __prefix
  opencapture 23
  range 63
  range 6f
  range 75
  range 6e
  range 74
  range 65
  range 72
  call S
  call REGISTER
  call S
  call UNSIGNED
  closecapture 23
  ret

CONDJUMPINSTR:
  call __prefix
  opencapture 24
  range 63
  range 6f
  range 6e
  range 64
  range 6a
  range 75
  range 6d
  range 70
  call S
  call REGISTER
  call S
  call LABEL
  closecapture 24
  ret

LABELDEF:
  call __prefix
  opencapture 25
  call LABEL
  call COLON
  closecapture 25
  ret

HEXBYTE:
  call __prefix
  opencapture 26
  counter 2 2
CTR2:
  catch SET37_0
  range 30 39
  commit L37
SET37_0:
  catch SET37_1
  range 41 46
  commit L37
SET37_1:
  range 61 66
L37:
  condjump 2 CTR2
  closecapture 26
  ret

BOOLEAN:
  call __prefix
  opencapture 27
  catch L39
  range 74
  range 72
  range 75
  range 65
  commit L38
L39:
  range 66
  range 61
  range 6c
  range 73
  range 65
L38:
  closecapture 27
  ret

LABEL:
  call __prefix
  opencapture 28
  catch SET42_0
  range 30 39
  commit L42
SET42_0:
  catch SET42_1
  range 41 5a
  commit L42
SET42_1:
  catch SET42_2
  range 5f 5f
  commit L42
SET42_2:
  range 61 7a
L42:
  catch L41
  counter 4 63
CTR4:
  catch SET43_0
  range 30 39
  commit L43
SET43_0:
  catch SET43_1
  range 41 5a
  commit L43
SET43_1:
  catch SET43_2
  range 5f 5f
  commit L43
SET43_2:
  range 61 7a
L43:
  partialcommit __NEXT__
  condjump 4 CTR4
  commit __NEXT__
L41:
  closecapture 28
  ret

CODE:
  call __prefix
  opencapture 29
  call UNSIGNED
  closecapture 29
  ret

SLOT:
  call __prefix
  opencapture 30
  call UNSIGNED
  closecapture 30
  ret

REGISTER:
  call __prefix
  opencapture 31
  call UNSIGNED
  closecapture 31
  ret

TYPE:
  call __prefix
  opencapture 32
  call UNSIGNED
  closecapture 32
  ret

UNSIGNED:
  call __prefix
  opencapture 33
  range 30 39
L45:
  catch L44
LOOP44:
  range 30 39
L46:
  partialcommit LOOP44
L44:
  closecapture 33
  ret

BIT:
  call __prefix
  opencapture 34
  range 30 31
L47:
  closecapture 34
  ret

COLON:
  call __prefix
  opencapture 35
  range 3a
  closecapture 35
  ret


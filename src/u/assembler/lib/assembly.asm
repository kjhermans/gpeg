-- GPEG compiler, release 0.4.8

  call TOP
  end 0

TOP:
  opencapture 0
  call INSTRUCTIONS
  closecapture 0
  ret

S:
  opencapture 1
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
  closecapture 1
  ret

MULTILINECOMMENT:
  opencapture 2
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
  closecapture 2
  ret

COMMENT:
  opencapture 3
  range 2d
  range 2d
  catch L6
LOOP6:
  range 5c
L7:
  partialcommit LOOP6
L6:
  range 6e
  closecapture 3
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
  opencapture 4
  call INSTRUCTION
  catch L13
LOOP13:
  call INSTRUCTION
  partialcommit LOOP13
L13:
  call END
  closecapture 4
  ret

INSTRUCTION:
  call __prefix
  opencapture 5
  catch L15
  call RULEINSTR
  commit L14
L15:
  call LABELDEF
L14:
  closecapture 5
  ret

RULEINSTR:
  call __prefix
  opencapture 6
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
  call OPENCAPTUREINSTR
  commit L17
L26:
  catch L27
  call PARTIALCOMMITINSTR
  commit L17
L27:
  catch L28
  call RETINSTR
  commit L17
L28:
  catch L29
  call RANGEINSTR
  commit L17
L29:
  catch L30
  call VARINSTR
  commit L17
L30:
  catch L31
  call COUNTERINSTR
  commit L17
L31:
  call CONDJUMPINSTR
L17:
  closecapture 6
  ret

END:
  call __prefix
  opencapture 7
  catch L33
  range 00 ff
  failtwice
L33:
  closecapture 7
  ret

BACKCOMMITINSTR:
  call __prefix
  opencapture 8
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
  closecapture 8
  ret

CALLINSTR:
  call __prefix
  opencapture 9
  range 63
  range 61
  range 6c
  range 6c
  call S
  call LABEL
  closecapture 9
  ret

CATCHINSTR:
  call __prefix
  opencapture 10
  range 63
  range 61
  range 74
  range 63
  range 68
  call S
  call LABEL
  closecapture 10
  ret

CLOSECAPTUREINSTR:
  call __prefix
  opencapture 11
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
  closecapture 11
  ret

COMMITINSTR:
  call __prefix
  opencapture 12
  range 63
  range 6f
  range 6d
  range 6d
  range 69
  range 74
  call S
  call LABEL
  closecapture 12
  ret

ENDINSTR:
  call __prefix
  opencapture 13
  range 65
  range 6e
  range 64
  call S
  call CODE
  closecapture 13
  ret

FAILINSTR:
  call __prefix
  opencapture 14
  range 66
  range 61
  range 69
  range 6c
  closecapture 14
  ret

FAILTWICEINSTR:
  call __prefix
  opencapture 15
  range 66
  range 61
  range 69
  range 6c
  range 74
  range 77
  range 69
  range 63
  range 65
  closecapture 15
  ret

OPENCAPTUREINSTR:
  call __prefix
  opencapture 16
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
  closecapture 16
  ret

PARTIALCOMMITINSTR:
  call __prefix
  opencapture 17
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
  closecapture 17
  ret

RETINSTR:
  call __prefix
  opencapture 18
  range 72
  range 65
  range 74
  closecapture 18
  ret

RANGEINSTR:
  call __prefix
  opencapture 19
  range 72
  range 61
  range 6e
  range 67
  range 65
  call S
  counter 0 1
CTR0:
  call HEXBYTE
  call S
  condjump 0 CTR0
  catch L34
  counter 1 2
CTR1:
  call HEXBYTE
  call S
  partialcommit __NEXT__
  condjump 1 CTR1
  commit __NEXT__
L34:
  closecapture 19
  ret

VARINSTR:
  call __prefix
  opencapture 20
  range 76
  range 61
  range 72
  call S
  call SLOT
  closecapture 20
  ret

COUNTERINSTR:
  call __prefix
  opencapture 21
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
  closecapture 21
  ret

CONDJUMPINSTR:
  call __prefix
  opencapture 22
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
  closecapture 22
  ret

LABELDEF:
  call __prefix
  opencapture 23
  call LABEL
  call COLON
  closecapture 23
  ret

HEXBYTE:
  call __prefix
  opencapture 24
  counter 2 2
CTR2:
  catch SET35_2
  range 30 39
  commit L35
SET35_2:
  catch SET35_4
  range 61 66
  commit L35
SET35_4:
  range 41 46
L35:
  condjump 2 CTR2
  closecapture 24
  ret

LABEL:
  call __prefix
  opencapture 25
  counter 3 1
CTR3:
  catch SET37_2
  range 61 7a
  commit L37
SET37_2:
  catch SET37_4
  range 41 5a
  commit L37
SET37_4:
  catch SET37_6
  range 30 39
  commit L37
SET37_6:
  range 5f
L37:
  condjump 3 CTR3
  catch L36
  counter 4 63
CTR4:
  catch SET38_2
  range 61 7a
  commit L38
SET38_2:
  catch SET38_4
  range 41 5a
  commit L38
SET38_4:
  catch SET38_6
  range 30 39
  commit L38
SET38_6:
  range 5f
L38:
  partialcommit __NEXT__
  condjump 4 CTR4
  commit __NEXT__
L36:
  closecapture 25
  ret

CODE:
  call __prefix
  opencapture 26
  call UNSIGNED
  closecapture 26
  ret

SLOT:
  call __prefix
  opencapture 27
  call UNSIGNED
  closecapture 27
  ret

REGISTER:
  call __prefix
  opencapture 28
  call UNSIGNED
  closecapture 28
  ret

TYPE:
  call __prefix
  opencapture 29
  call UNSIGNED
  closecapture 29
  ret

UNSIGNED:
  call __prefix
  opencapture 30
  range 30 39
L40:
  catch L39
LOOP39:
  range 30 39
L41:
  partialcommit LOOP39
L39:
  closecapture 30
  ret

COLON:
  call __prefix
  opencapture 31
  range 3a
  closecapture 31
  ret


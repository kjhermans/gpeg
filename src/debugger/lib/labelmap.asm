-- GPEG compiler, release 0.5.11

  call LABELS
  end 0

LABELS:
  catch L1
LOOP1:
  call LABEL
  partialcommit LOOP1
L1:
  ret

__prefix:
  catch L2
LOOP2:
  catch MACRO3_1
  range 20
  commit L3
MACRO3_1:
  range 07 0d
L3:
  partialcommit LOOP2
L2:
  ret

LABEL:
  call __prefix
  opencapture 1
  call IDENT
  call COLON
  call UNSIGNED
  closecapture 1
  ret

IDENT:
  call __prefix
  opencapture 2
  catch SET4_0
  range 41 5a
  commit L4
SET4_0:
  catch SET4_1
  range 5f 5f
  commit L4
SET4_1:
  range 61 7a
L4:
  catch L5
LOOP5:
  catch SET6_0
  range 30 39
  commit L6
SET6_0:
  catch SET6_1
  range 41 5a
  commit L6
SET6_1:
  catch SET6_2
  range 5f 5f
  commit L6
SET6_2:
  range 61 7a
L6:
  partialcommit LOOP5
L5:
  closecapture 2
  ret

COLON:
  call __prefix
  range 3a
  ret

UNSIGNED:
  call __prefix
  opencapture 3
  range 30 39
L8:
  catch L7
LOOP7:
  range 30 39
L9:
  partialcommit LOOP7
L7:
  closecapture 3
  ret


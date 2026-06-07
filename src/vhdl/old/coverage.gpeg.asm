-- GPEG compiler, release 0.5.13

  call test
  end 0

test:
  call test_backcommit
  call enter
  call test_fail
  call enter
  call test_failtwice
  call enter
  call test_commit
  call enter
  call test_set_counter
  call enter
  call test_capture
  call enter
  ret

enter:
  range 0a
  ret

test_backcommit:
  catch L1
  range 68
  range 65
  range 6c
  range 6c
  range 6f
  backcommit OUT1
L1:
  fail
OUT1:
  range 68
  range 65
  range 6c
  range 6c
  range 6f
  ret

test_fail:
  catch L3
  catch L4
  range 68
  range 65
  range 6c
  range 6c
  range 6f
  backcommit OUT4
L4:
  fail
OUT4:
  commit L2
L3:
  range 68
  range 69
  range 74
  range 68
  range 65
  range 72
  range 65
L2:
  ret

test_failtwice:
  range 22
  catch L6
LOOP6:
  catch L7
  range 22
  failtwice
L7:
  range 00 ff
  partialcommit LOOP6
L6:
  range 22
  ret

test_commit:
  catch L9
  range 68
  range 69
  range 74
  range 68
  range 65
  range 72
  range 65
  commit L8
L9:
  range 68
  range 65
  range 6c
  range 6c
  range 6f
L8:
  ret

test_set_counter:
  counter 0 5
CTR0:
  range 61 7a
L11:
  condjump 0 CTR0
  ret

test_capture:
  opencapture 1
  catch L12
LOOP12:
  range 61 7a
L13:
  partialcommit LOOP12
L12:
  closecapture 1
  ret


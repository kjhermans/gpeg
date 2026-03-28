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
  char 0a
  ret

test_backcommit:
  catch __L1
  char 68
  char 65
  char 6c
  char 6c
  char 6f
  backcommit __L2
__L1:
  fail
__L2:
  char 68
  char 65
  char 6c
  char 6c
  char 6f
  ret

test_fail:
  catch __L3
  catch __L5
  char 68
  char 65
  char 6c
  char 6c
  char 6f
  backcommit __L6
__L5:
  fail
__L6:
  commit __L4
__L3:
  char 68
  char 69
  char 74
  char 68
  char 65
  char 72
  char 65
__L4:
  ret

test_failtwice:
  char 22
  catch __L7
__L8:
  catch __L9
  char 22
  failtwice
__L9:
  any
  partialcommit __L8
__L7:
  char 22
  ret

test_commit:
  catch __L11
  char 68
  char 69
  char 74
  char 68
  char 65
  char 72
  char 65
  commit __L12
__L11:
  char 68
  char 65
  char 6c
  char 6c
  char 6f
__L12:
  ret

test_set_counter:
  counter 1 5
__L13:
  set 000000000000000000000000feffff0700000000000000000000000000000000
  condjump 1 __L13
  ret

test_capture:
  opencapture 0
  catch __L14
__L15:
  set 000000000000000000000000feffff0700000000000000000000000000000000
  partialcommit __L15
__L14:
  closecapture 0
  ret


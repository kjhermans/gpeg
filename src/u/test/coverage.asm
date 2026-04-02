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
  quad 68656c6c
  char 6f
  backcommit __L2
__L1:
  fail
__L2:
  quad 68656c6c
  char 6f
  ret

test_fail:
  catch __L3
  catch __L5
  quad 68656c6c
  char 6f
  backcommit __L6
__L5:
  fail
__L6:
  commit __L4
__L3:
  quad 68697468
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
  catch __L10
  quad 68697468
  char 65
  char 72
  char 65
  commit __L11
__L10:
  quad 68656c6c
  char 6f
__L11:
  ret

test_set_counter:
  counter 0 5
__L12:
  set 000000000000000000000000feffff0700000000000000000000000000000000
  condjump 0 __L12
  ret

test_capture:
  opencapture 0
  catch __L13
__L14:
  set 000000000000000000000000feffff0700000000000000000000000000000000
  partialcommit __L14
__L13:
  closecapture 0
  ret


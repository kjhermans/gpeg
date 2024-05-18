  call MAP
  end 0

MAP:
  opencapture 0
  call DEFINITION
  catch __L1
__L2:
  call DEFINITION
  partialcommit __L2
__L1:
  call END
  closecapture 0
  ret

S:
  opencapture 1
  set 002e000001000000000000000000000000000000000000000000000000000000
  catch __L3
__L4:
  set 002e000001000000000000000000000000000000000000000000000000000000
  partialcommit __L4
__L3:
  closecapture 1
  ret

MULTILINECOMMENT:
  opencapture 2
  quad 2d2d5b5b
  catch __L5
__L6:
  catch __L7
  char 5d
  char 5d
  failtwice
__L7:
  any
  partialcommit __L6
__L5:
  char 5d
  char 5d
  closecapture 2
  ret

COMMENT:
  opencapture 3
  char 2d
  char 2d
  catch __L8
__L9:
  set fffbffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
  partialcommit __L9
__L8:
  char 0a
  closecapture 3
  ret

__prefix:
  catch __L10
__L11:
  catch __L12
  call MULTILINECOMMENT
  commit __L13
__L12:
  catch __L14
  call COMMENT
  commit __L15
__L14:
  call S
__L15:
__L13:
  partialcommit __L11
__L10:
  ret

END:
  call __prefix
  opencapture 4
  catch __L16
  any
  failtwice
__L16:
  closecapture 4
  ret

DEFINITION:
  call __prefix
  opencapture 5
  call IDENT
  call UNSIGNED
  closecapture 5
  ret

IDENT:
  call __prefix
  opencapture 6
  set 0000000000000000feffff87feffff0700000000000000000000000000000000
  catch __L17
  counter 0 63
__L18:
  set 000000000000ff03feffff87feffff0700000000000000000000000000000000
  partialcommit __NEXT__
  condjump 0 __L18
  commit __L17
__L17:
  closecapture 6
  ret

UNSIGNED:
  call __prefix
  opencapture 7
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L19
__L20:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L20
__L19:
  closecapture 7
  ret


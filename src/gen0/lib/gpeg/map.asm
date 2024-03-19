  call TOP
  end 0

TOP:
  call MAP
  call END
  ret

S:
  set 002e000001000000000000000000000000000000000000000000000000000000
  catch __L1
__L2:
  set 002e000001000000000000000000000000000000000000000000000000000000
  partialcommit __L2
__L1:
  ret

MULTILINECOMMENT:
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
  ret

COMMENT:
  char 2d
  char 2d
  catch __L6
__L7:
  set fffbffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
  partialcommit __L7
__L6:
  char 0a
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

END:
  call __prefix
  catch __L14
  any
  failtwice
__L14:
  ret

MAP:
  call __prefix
  catch __L15
__L16:
  opencapture 0
  call MAPPING
  closecapture 0
  partialcommit __L16
__L15:
  ret

MAPPING:
  call __prefix
  call IDENT
  call S
  call NUMBER
  ret

IDENT:
  call __prefix
  opencapture 1
  set 0000000000000000feffff87feffff0700000000000000000000000000000000
  catch __L17
  counter 0 63
__L18:
  set 000000000000ff03feffff87feffff0700000000000000000000000000000000
  partialcommit __NEXT__
  condjump 0 __L18
  commit __L17
__L17:
  closecapture 1
  ret

NUMBER:
  call __prefix
  opencapture 2
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L19
__L20:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L20
__L19:
  closecapture 2
  ret


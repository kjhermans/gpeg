  call TRANSFORM
  end 0

TRANSFORM:
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
  call SLOT
  call COLON
  call EXPRESSION
  closecapture 5
  ret

SLOT:
  call __prefix
  opencapture 6
  call IDENT
  closecapture 6
  ret

EXPRESSION:
  call __prefix
  opencapture 7
  call TERM
  catch __L17
__L18:
  call TERM
  partialcommit __L18
__L17:
  closecapture 7
  ret

TERM:
  call __prefix
  opencapture 8
  catch __L19
  call STRING
  commit __L20
__L19:
  catch __L21
  call REFERENCE
  commit __L22
__L21:
  call CHAR
__L22:
__L20:
  closecapture 8
  ret

STRING:
  call __prefix
  opencapture 9
  char 27
  opencapture 10
  catch __L23
__L24:
  catch __L25
  char 5c
  catch __L27
  set 0000000080000000000000100040540000000000000000000000000000000000
  commit __L28
__L27:
  char 78
  counter 0 2
__L29:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 0 __L29
__L28:
  commit __L26
__L25:
  set ffffffff7fffffffffffffefffffffffffffffffffffffffffffffffffffffff
__L26:
  partialcommit __L24
__L23:
  closecapture 10
  char 27
  closecapture 9
  ret

REFERENCE:
  call __prefix
  opencapture 11
  call DOLLAR
  call IDENT
  closecapture 11
  ret

CHAR:
  call __prefix
  opencapture 12
  char 30
  char 78
  counter 1 2
__L30:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 1 __L30
  closecapture 12
  ret

IDENT:
  call __prefix
  opencapture 13
  set 0000000000000000feffff87feffff0700000000000000000000000000000000
  catch __L31
  counter 2 63
__L32:
  set 000000000000ff03feffff87feffff0700000000000000000000000000000000
  partialcommit __NEXT__
  condjump 2 __L32
  commit __L31
__L31:
  closecapture 13
  ret

COLON:
  call __prefix
  opencapture 14
  char 3a
  closecapture 14
  ret

DOLLAR:
  call __prefix
  opencapture 15
  char 24
  closecapture 15
  ret


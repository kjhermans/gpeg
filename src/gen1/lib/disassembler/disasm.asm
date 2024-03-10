  call TOP
  end 0

TOP:
  opencapture 0
  call INSTRUCTION
  catch __L1
__L2:
  call INSTRUCTION
  partialcommit __L2
__L1:
  closecapture 0
  ret

INSTRUCTION:
  opencapture 1
  catch __L3
  call any
  commit __L4
__L3:
  catch __L5
  call backcommit
  commit __L6
__L5:
  catch __L7
  call call
  commit __L8
__L7:
  catch __L9
  call catch
  commit __L10
__L9:
  catch __L11
  call char
  commit __L12
__L11:
  catch __L13
  call closecapture
  commit __L14
__L13:
  catch __L15
  call commit
  commit __L16
__L15:
  catch __L17
  call condjump
  commit __L18
__L17:
  catch __L19
  call counter
  commit __L20
__L19:
  catch __L21
  call end
  commit __L22
__L21:
  catch __L23
  call endisolate
  commit __L24
__L23:
  catch __L25
  call endreplace
  commit __L26
__L25:
  catch __L27
  call fail
  commit __L28
__L27:
  catch __L29
  call failtwice
  commit __L30
__L29:
  catch __L31
  call intrpcapture
  commit __L32
__L31:
  catch __L33
  call isolate
  commit __L34
__L33:
  catch __L35
  call jump
  commit __L36
__L35:
  catch __L37
  call maskedchar
  commit __L38
__L37:
  catch __L39
  call noop
  commit __L40
__L39:
  catch __L41
  call opencapture
  commit __L42
__L41:
  catch __L43
  call partialcommit
  commit __L44
__L43:
  catch __L45
  call quad
  commit __L46
__L45:
  catch __L47
  call range
  commit __L48
__L47:
  catch __L49
  call replace
  commit __L50
__L49:
  catch __L51
  call ret
  commit __L52
__L51:
  catch __L53
  call set
  commit __L54
__L53:
  catch __L55
  call skip
  commit __L56
__L55:
  catch __L57
  call span
  commit __L58
__L57:
  catch __L59
  call testany
  commit __L60
__L59:
  catch __L61
  call testchar
  commit __L62
__L61:
  catch __L63
  call testquad
  commit __L64
__L63:
  catch __L65
  call testset
  commit __L66
__L65:
  catch __L67
  call trap
  commit __L68
__L67:
  call var
__L68:
__L66:
__L64:
__L62:
__L60:
__L58:
__L56:
__L54:
__L52:
__L50:
__L48:
__L46:
__L44:
__L42:
__L40:
__L38:
__L36:
__L34:
__L32:
__L30:
__L28:
__L26:
__L24:
__L22:
__L20:
__L18:
__L16:
__L14:
__L12:
__L10:
__L8:
__L6:
__L4:
  closecapture 1
  ret

any:
  opencapture 2
  char 00
  char 00
  char 03
  char e4
  closecapture 2
  ret

backcommit:
  opencapture 3
  char 00
  char 04
  char 03
  char c0
  opencapture 4
  any
  any
  any
  any
  closecapture 4
  closecapture 3
  ret

call:
  opencapture 5
  char 00
  char 04
  char 03
  char 82
  opencapture 6
  any
  any
  any
  any
  closecapture 6
  closecapture 5
  ret

catch:
  opencapture 7
  char 00
  char 04
  char 03
  char 93
  opencapture 8
  any
  any
  any
  any
  closecapture 8
  closecapture 7
  ret

char:
  opencapture 9
  char 00
  char 04
  char 03
  char d7
  opencapture 10
  any
  any
  any
  any
  closecapture 10
  closecapture 9
  ret

closecapture:
  opencapture 11
  char 00
  char 04
  char 03
  char 00
  opencapture 12
  any
  any
  any
  any
  closecapture 12
  closecapture 11
  ret

commit:
  opencapture 13
  char 00
  char 04
  char 03
  char 36
  opencapture 14
  any
  any
  any
  any
  closecapture 14
  closecapture 13
  ret

condjump:
  opencapture 15
  char 00
  char 08
  char 03
  char 21
  opencapture 16
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 16
  closecapture 15
  ret

counter:
  opencapture 17
  char 00
  char 08
  char 03
  char 56
  opencapture 18
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 18
  closecapture 17
  ret

end:
  opencapture 19
  char 00
  char 04
  char 00
  char d8
  opencapture 20
  any
  any
  any
  any
  closecapture 20
  closecapture 19
  ret

endisolate:
  opencapture 21
  char 00
  char 00
  char 30
  char 05
  closecapture 21
  ret

endreplace:
  opencapture 22
  char 00
  char 00
  char 03
  char 99
  closecapture 22
  ret

fail:
  opencapture 23
  char 00
  char 00
  char 03
  char 4b
  closecapture 23
  ret

failtwice:
  opencapture 24
  char 00
  char 00
  char 03
  char 90
  closecapture 24
  ret

intrpcapture:
  opencapture 25
  char 00
  char 08
  char 00
  char 0f
  opencapture 26
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 26
  closecapture 25
  ret

isolate:
  opencapture 27
  char 00
  char 04
  char 30
  char 03
  opencapture 28
  any
  any
  any
  any
  closecapture 28
  closecapture 27
  ret

jump:
  opencapture 29
  char 00
  char 04
  char 03
  char 33
  opencapture 30
  any
  any
  any
  any
  closecapture 30
  closecapture 29
  ret

maskedchar:
  opencapture 31
  char 00
  char 08
  char 03
  char 65
  opencapture 32
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 32
  closecapture 31
  ret

noop:
  opencapture 33
  char 00
  char 00
  char 00
  char 00
  closecapture 33
  ret

opencapture:
  opencapture 34
  char 00
  char 04
  char 03
  char 9c
  opencapture 35
  any
  any
  any
  any
  closecapture 35
  closecapture 34
  ret

partialcommit:
  opencapture 36
  char 00
  char 04
  char 03
  char b4
  opencapture 37
  any
  any
  any
  any
  closecapture 37
  closecapture 36
  ret

quad:
  opencapture 38
  char 00
  char 04
  char 03
  char 7e
  opencapture 39
  any
  any
  any
  any
  closecapture 39
  closecapture 38
  ret

range:
  opencapture 40
  char 00
  char 08
  char 03
  char bd
  opencapture 41
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 41
  closecapture 40
  ret

replace:
  opencapture 42
  char 00
  char 08
  char 03
  char 48
  opencapture 43
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 43
  closecapture 42
  ret

ret:
  opencapture 44
  char 00
  char 00
  char 03
  char a0
  closecapture 44
  ret

set:
  opencapture 45
  char 00
  char 20
  char 03
  char ca
  opencapture 46
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 46
  closecapture 45
  ret

skip:
  opencapture 47
  char 00
  char 04
  char 03
  char 30
  opencapture 48
  any
  any
  any
  any
  closecapture 48
  closecapture 47
  ret

span:
  opencapture 49
  char 00
  char 20
  char 03
  char e1
  opencapture 50
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 50
  closecapture 49
  ret

testany:
  opencapture 51
  char 00
  char 04
  char 03
  char 06
  opencapture 52
  any
  any
  any
  any
  closecapture 52
  closecapture 51
  ret

testchar:
  opencapture 53
  char 00
  char 08
  char 03
  char 9a
  opencapture 54
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 54
  closecapture 53
  ret

testquad:
  opencapture 55
  char 00
  char 08
  char 03
  char db
  opencapture 56
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 56
  closecapture 55
  ret

testset:
  opencapture 57
  char 00
  char 24
  char 03
  char 63
  opencapture 58
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 58
  closecapture 57
  ret

trap:
  opencapture 59
  char ff
  char 00
  char ff
  char ff
  closecapture 59
  ret

var:
  opencapture 60
  char 00
  char 04
  char 03
  char ee
  opencapture 61
  any
  any
  any
  any
  closecapture 61
  closecapture 60
  ret


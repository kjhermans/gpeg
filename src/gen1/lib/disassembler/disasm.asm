  call TOP
  end 0

TOP:
  call INSTRUCTION
  catch __L1
__L2:
  call INSTRUCTION
  partialcommit __L2
__L1:
  ret

INSTRUCTION:
  catch __L3
  call instr_any
  commit __L4
__L3:
  catch __L5
  call instr_backcommit
  commit __L6
__L5:
  catch __L7
  call instr_bitmask
  commit __L8
__L7:
  catch __L9
  call instr_call
  commit __L10
__L9:
  catch __L11
  call instr_catch
  commit __L12
__L11:
  catch __L13
  call instr_char
  commit __L14
__L13:
  catch __L15
  call instr_closecapture
  commit __L16
__L15:
  catch __L17
  call instr_commit
  commit __L18
__L17:
  catch __L19
  call instr_condjump
  commit __L20
__L19:
  catch __L21
  call instr_counter
  commit __L22
__L21:
  catch __L23
  call instr_end
  commit __L24
__L23:
  catch __L25
  call instr_endisolate
  commit __L26
__L25:
  catch __L27
  call instr_endreplace
  commit __L28
__L27:
  catch __L29
  call instr_fail
  commit __L30
__L29:
  catch __L31
  call instr_failtwice
  commit __L32
__L31:
  catch __L33
  call instr_intrpcapture
  commit __L34
__L33:
  catch __L35
  call instr_isolate
  commit __L36
__L35:
  catch __L37
  call instr_jump
  commit __L38
__L37:
  catch __L39
  call instr_noop
  commit __L40
__L39:
  catch __L41
  call instr_opencapture
  commit __L42
__L41:
  catch __L43
  call instr_partialcommit
  commit __L44
__L43:
  catch __L45
  call instr_quad
  commit __L46
__L45:
  catch __L47
  call instr_range
  commit __L48
__L47:
  catch __L49
  call instr_replace
  commit __L50
__L49:
  catch __L51
  call instr_ret
  commit __L52
__L51:
  catch __L53
  call instr_set
  commit __L54
__L53:
  catch __L55
  call instr_skip
  commit __L56
__L55:
  catch __L57
  call instr_span
  commit __L58
__L57:
  catch __L59
  call instr_testany
  commit __L60
__L59:
  catch __L61
  call instr_testchar
  commit __L62
__L61:
  catch __L63
  call instr_testquad
  commit __L64
__L63:
  catch __L65
  call instr_testset
  commit __L66
__L65:
  catch __L67
  call instr_trap
  commit __L68
__L67:
  call instr_var
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
  ret

instr_any:
  opencapture 0
  char 00
  char 00
  char 03
  char e4
  closecapture 0
  ret

instr_backcommit:
  char 00
  char 04
  char 03
  char c0
  opencapture 1
  any
  any
  any
  any
  closecapture 1
  ret

instr_bitmask:
  char 00
  char 10
  char 03
  char 65
  opencapture 2
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
  closecapture 2
  ret

instr_call:
  char 00
  char 04
  char 03
  char 82
  opencapture 3
  any
  any
  any
  any
  closecapture 3
  ret

instr_catch:
  char 00
  char 04
  char 03
  char 93
  opencapture 4
  any
  any
  any
  any
  closecapture 4
  ret

instr_char:
  char 00
  char 04
  char 03
  char d7
  opencapture 5
  any
  any
  any
  any
  closecapture 5
  ret

instr_closecapture:
  char 00
  char 04
  char 03
  char 00
  opencapture 6
  any
  any
  any
  any
  closecapture 6
  ret

instr_commit:
  char 00
  char 04
  char 03
  char 36
  opencapture 7
  any
  any
  any
  any
  closecapture 7
  ret

instr_condjump:
  char 00
  char 08
  char 03
  char 21
  opencapture 8
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 8
  ret

instr_counter:
  char 00
  char 08
  char 03
  char 56
  opencapture 9
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 9
  ret

instr_end:
  char 00
  char 04
  char 00
  char d8
  opencapture 10
  any
  any
  any
  any
  closecapture 10
  ret

instr_endisolate:
  opencapture 11
  char 00
  char 00
  char 30
  char 05
  closecapture 11
  ret

instr_endreplace:
  opencapture 12
  char 00
  char 00
  char 03
  char 99
  closecapture 12
  ret

instr_fail:
  opencapture 13
  char 00
  char 00
  char 03
  char 4b
  closecapture 13
  ret

instr_failtwice:
  opencapture 14
  char 00
  char 00
  char 03
  char 90
  closecapture 14
  ret

instr_intrpcapture:
  char 00
  char 08
  char 00
  char 0f
  opencapture 15
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 15
  ret

instr_isolate:
  char 00
  char 04
  char 30
  char 03
  opencapture 16
  any
  any
  any
  any
  closecapture 16
  ret

instr_jump:
  char 00
  char 04
  char 03
  char 33
  opencapture 17
  any
  any
  any
  any
  closecapture 17
  ret

instr_noop:
  opencapture 18
  char 00
  char 00
  char 00
  char 00
  closecapture 18
  ret

instr_opencapture:
  char 00
  char 04
  char 03
  char 9c
  opencapture 19
  any
  any
  any
  any
  closecapture 19
  ret

instr_partialcommit:
  char 00
  char 04
  char 03
  char b4
  opencapture 20
  any
  any
  any
  any
  closecapture 20
  ret

instr_quad:
  char 00
  char 04
  char 03
  char 7e
  opencapture 21
  any
  any
  any
  any
  closecapture 21
  ret

instr_range:
  char 00
  char 08
  char 03
  char bd
  opencapture 22
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 22
  ret

instr_replace:
  char 00
  char 08
  char 03
  char 48
  opencapture 23
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 23
  ret

instr_ret:
  opencapture 24
  char 00
  char 00
  char 03
  char a0
  closecapture 24
  ret

instr_set:
  char 00
  char 20
  char 03
  char ca
  opencapture 25
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
  closecapture 25
  ret

instr_skip:
  char 00
  char 04
  char 03
  char 30
  opencapture 26
  any
  any
  any
  any
  closecapture 26
  ret

instr_span:
  char 00
  char 20
  char 03
  char e1
  opencapture 27
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
  closecapture 27
  ret

instr_testany:
  char 00
  char 04
  char 03
  char 06
  opencapture 28
  any
  any
  any
  any
  closecapture 28
  ret

instr_testchar:
  char 00
  char 08
  char 03
  char 9a
  opencapture 29
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 29
  ret

instr_testquad:
  char 00
  char 08
  char 03
  char db
  opencapture 30
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 30
  ret

instr_testset:
  char 00
  char 24
  char 03
  char 63
  opencapture 31
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
  closecapture 31
  ret

instr_trap:
  opencapture 32
  char ff
  char 00
  char ff
  char ff
  closecapture 32
  ret

instr_var:
  char 00
  char 04
  char 03
  char ee
  opencapture 33
  any
  any
  any
  any
  closecapture 33
  ret


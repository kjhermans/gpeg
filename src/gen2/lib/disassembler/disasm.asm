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
  catch __L5
  catch __L7
  catch __L9
  catch __L11
  catch __L13
  catch __L15
  catch __L17
  catch __L19
  catch __L21
  catch __L23
  catch __L25
  catch __L27
  catch __L29
  catch __L31
  catch __L33
  catch __L35
  catch __L37
  catch __L39
  catch __L41
  catch __L43
  catch __L45
  catch __L47
  catch __L49
  catch __L51
  catch __L53
  catch __L55
  catch __L57
  catch __L59
  catch __L61
  catch __L63
  catch __L65
  catch __L67
  catch __L69
  catch __L71
  catch __L73
  catch __L75
  catch __L77
  catch __L79
  call instr_any
  commit __L80
__L79:
  call instr_backcommit
__L80:
  commit __L78
__L77:
  call instr_bitmask
__L78:
  commit __L76
__L75:
  call instr_call
__L76:
  commit __L74
__L73:
  call instr_catch
__L74:
  commit __L72
__L71:
  call instr_char
__L72:
  commit __L70
__L69:
  call instr_closecapture
__L70:
  commit __L68
__L67:
  call instr_commit
__L68:
  commit __L66
__L65:
  call instr_condjump
__L66:
  commit __L64
__L63:
  call instr_counter
__L64:
  commit __L62
__L61:
  call instr_end
__L62:
  commit __L60
__L59:
  call instr_eq
__L60:
  commit __L58
__L57:
  call instr_fail
__L58:
  commit __L56
__L55:
  call instr_failtwice
__L56:
  commit __L54
__L53:
  call instr_gt
__L54:
  commit __L52
__L51:
  call instr_gteq
__L52:
  commit __L50
__L49:
  call instr_imoveto
__L50:
  commit __L48
__L47:
  call instr_intrpcapture
__L48:
  commit __L46
__L45:
  call instr_irmoveto
__L46:
  commit __L44
__L43:
  call instr_jump
__L44:
  commit __L42
__L41:
  call instr_lt
__L42:
  commit __L40
__L39:
  call instr_lteq
__L40:
  commit __L38
__L37:
  call instr_moveto
__L38:
  commit __L36
__L35:
  call instr_neq
__L36:
  commit __L34
__L33:
  call instr_noop
__L34:
  commit __L32
__L31:
  call instr_opencapture
__L32:
  commit __L30
__L29:
  call instr_partialcommit
__L30:
  commit __L28
__L27:
  call instr_quad
__L28:
  commit __L26
__L25:
  call instr_range
__L26:
  commit __L24
__L23:
  call instr_ret
__L24:
  commit __L22
__L21:
  call instr_rmoveto
__L22:
  commit __L20
__L19:
  call instr_set
__L20:
  commit __L18
__L17:
  call instr_skip
__L18:
  commit __L16
__L15:
  call instr_span
__L16:
  commit __L14
__L13:
  call instr_testany
__L14:
  commit __L12
__L11:
  call instr_testchar
__L12:
  commit __L10
__L9:
  call instr_testquad
__L10:
  commit __L8
__L7:
  call instr_testset
__L8:
  commit __L6
__L5:
  call instr_trap
__L6:
  commit __L4
__L3:
  call instr_var
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

instr_eq:
  char 00
  char 04
  char 00
  char 03
  opencapture 11
  any
  any
  any
  any
  closecapture 11
  ret

instr_fail:
  opencapture 12
  char 00
  char 00
  char 03
  char 4b
  closecapture 12
  ret

instr_failtwice:
  opencapture 13
  char 00
  char 00
  char 03
  char 90
  closecapture 13
  ret

instr_gt:
  char 00
  char 04
  char 00
  char 05
  opencapture 14
  any
  any
  any
  any
  closecapture 14
  ret

instr_gteq:
  char 00
  char 04
  char 00
  char 06
  opencapture 15
  any
  any
  any
  any
  closecapture 15
  ret

instr_imoveto:
  opencapture 16
  char 00
  char 00
  char 00
  char 09
  closecapture 16
  ret

instr_intrpcapture:
  char 00
  char 08
  char 00
  char 0f
  opencapture 17
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 17
  ret

instr_irmoveto:
  opencapture 18
  char 00
  char 00
  char 00
  char 0a
  closecapture 18
  ret

instr_jump:
  char 00
  char 04
  char 03
  char 33
  opencapture 19
  any
  any
  any
  any
  closecapture 19
  ret

instr_lt:
  char 00
  char 04
  char 00
  char 0c
  opencapture 20
  any
  any
  any
  any
  closecapture 20
  ret

instr_lteq:
  char 00
  char 04
  char 00
  char 11
  opencapture 21
  any
  any
  any
  any
  closecapture 21
  ret

instr_moveto:
  char 00
  char 04
  char 00
  char 12
  opencapture 22
  any
  any
  any
  any
  closecapture 22
  ret

instr_neq:
  char 00
  char 04
  char 00
  char 14
  opencapture 23
  any
  any
  any
  any
  closecapture 23
  ret

instr_noop:
  opencapture 24
  char 00
  char 00
  char 00
  char 00
  closecapture 24
  ret

instr_opencapture:
  char 00
  char 04
  char 03
  char 9c
  opencapture 25
  any
  any
  any
  any
  closecapture 25
  ret

instr_partialcommit:
  char 00
  char 04
  char 03
  char b4
  opencapture 26
  any
  any
  any
  any
  closecapture 26
  ret

instr_quad:
  char 00
  char 04
  char 03
  char 7e
  opencapture 27
  any
  any
  any
  any
  closecapture 27
  ret

instr_range:
  char 00
  char 08
  char 03
  char bd
  opencapture 28
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 28
  ret

instr_ret:
  opencapture 29
  char 00
  char 00
  char 03
  char a0
  closecapture 29
  ret

instr_rmoveto:
  char 00
  char 04
  char 00
  char 18
  opencapture 30
  any
  any
  any
  any
  closecapture 30
  ret

instr_set:
  char 00
  char 20
  char 03
  char ca
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
  closecapture 31
  ret

instr_skip:
  char 00
  char 04
  char 03
  char 30
  opencapture 32
  any
  any
  any
  any
  closecapture 32
  ret

instr_span:
  char 00
  char 20
  char 03
  char e1
  opencapture 33
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
  closecapture 33
  ret

instr_testany:
  char 00
  char 04
  char 03
  char 06
  opencapture 34
  any
  any
  any
  any
  closecapture 34
  ret

instr_testchar:
  char 00
  char 08
  char 03
  char 9a
  opencapture 35
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 35
  ret

instr_testquad:
  char 00
  char 08
  char 03
  char db
  opencapture 36
  any
  any
  any
  any
  any
  any
  any
  any
  closecapture 36
  ret

instr_testset:
  char 00
  char 24
  char 03
  char 63
  opencapture 37
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
  closecapture 37
  ret

instr_trap:
  opencapture 38
  char ff
  char 00
  char ff
  char ff
  closecapture 38
  ret

instr_var:
  char 00
  char 04
  char 03
  char ee
  opencapture 39
  any
  any
  any
  any
  closecapture 39
  ret


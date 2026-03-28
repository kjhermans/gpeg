  call TOP
  end 0

TOP:
  call JSON
  ret

UTF8CHAR:
  any
  ret

SPACE:
  set 002e000001000000000000000000000000000000000000000000000000000000
  catch __L1
__L2:
  set 002e000001000000000000000000000000000000000000000000000000000000
  partialcommit __L2
__L1:
  ret

MULTILINECOMMENT:
  char 2f
  char 2a
  catch __L3
__L4:
  catch __L5
  char 2a
  char 2f
  failtwice
__L5:
  any
  partialcommit __L4
__L3:
  char 2a
  char 2f
  ret

COMMENT:
  char 2f
  char 2f
  catch __L7
__L8:
  set fffbffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
  partialcommit __L8
__L7:
  char 0a
  ret

__prefix:
  catch __L9
__L10:
  catch __L11
  catch __L13
  call MULTILINECOMMENT
  commit __L14
__L13:
  call COMMENT
__L14:
  commit __L12
__L11:
  call SPACE
__L12:
  partialcommit __L10
__L9:
  ret

END:
  call __prefix
  catch __L15
  any
  failtwice
__L15:
  ret

JSON:
  call __prefix
  call VALUE
  call END
  ret

HASH:
  call __prefix
  call CBOPEN
  call OPTHASHELTS
  call CBCLOSE
  ret

OPTHASHELTS:
  call __prefix
  catch __L17
  call HASHELTS
  commit __NEXT__
__L17:
  ret

HASHELTS:
  call __prefix
  call HASHELT
  catch __L18
__L19:
  call COMMA
  call HASHELT
  partialcommit __L19
__L18:
  ret

HASHELT:
  call __prefix
  call STRING
  call COLON
  call VALUE
  ret

ARRAY:
  call __prefix
  call ABOPEN
  call OPTARRAYELTS
  call ABCLOSE
  ret

OPTARRAYELTS:
  call __prefix
  catch __L20
  call ARRAYELTS
  commit __NEXT__
__L20:
  ret

ARRAYELTS:
  call __prefix
  call VALUE
  catch __L21
__L22:
  call COMMA
  call VALUE
  partialcommit __L22
__L21:
  ret

VALUE:
  call __prefix
  catch __L23
  catch __L25
  catch __L27
  catch __L29
  catch __L31
  catch __L33
  catch __L35
  call BIGSTRING
  commit __L36
__L35:
  call STRING
__L36:
  commit __L34
__L33:
  call FLOAT
__L34:
  commit __L32
__L31:
  call INT
__L32:
  commit __L30
__L29:
  call BOOL
__L30:
  commit __L28
__L27:
  call NULL
__L28:
  commit __L26
__L25:
  call HASH
__L26:
  commit __L24
__L23:
  call ARRAY
__L24:
  ret

BIGSTRING:
  call __prefix
  char 22
  char 22
  char 22
  catch __L37
__L38:
  catch __L39
  char 22
  char 22
  char 22
  failtwice
__L39:
  call UTF8CHAR
  partialcommit __L38
__L37:
  char 22
  char 22
  char 22
  ret

STRING:
  call __prefix
  char 22
  catch __L41
__L42:
  catch __L43
  char 5c
  catch __L45
  set 0000000004000000000000104440140000000000000000000000000000000000
  commit __L46
__L45:
  char 75
  counter 1 4
__L47:
  set 000000000000ff037e0000007e00000000000000000000000000000000000000
  condjump 1 __L47
__L46:
  commit __L44
__L43:
  catch __L48
  char 22
  failtwice
__L48:
  call UTF8CHAR
__L44:
  partialcommit __L42
__L41:
  char 22
  ret

INT:
  call __prefix
  catch __L50
  char 2d
  commit __NEXT__
__L50:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L51
__L52:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L52
__L51:
  ret

FLOAT:
  call __prefix
  catch __L53
  char 2d
  commit __NEXT__
__L53:
  catch __L54
__L55:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L55
__L54:
  char 2e
  set 000000000000ff03000000000000000000000000000000000000000000000000
  catch __L56
__L57:
  set 000000000000ff03000000000000000000000000000000000000000000000000
  partialcommit __L57
__L56:
  ret

BOOL:
  call __prefix
  catch __L58
  char 74
  char 72
  char 75
  char 65
  commit __L59
__L58:
  char 66
  char 61
  char 6c
  char 73
  char 65
__L59:
  ret

NULL:
  call __prefix
  char 6e
  char 75
  char 6c
  char 6c
  ret

CBOPEN:
  call __prefix
  char 7b
  ret

CBCLOSE:
  call __prefix
  char 7d
  ret

ABOPEN:
  call __prefix
  char 5b
  ret

ABCLOSE:
  call __prefix
  char 5d
  ret

COMMA:
  call __prefix
  char 2c
  ret

COLON:
  call __prefix
  char 3a
  ret


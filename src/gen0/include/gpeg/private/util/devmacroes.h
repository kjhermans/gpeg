#ifndef _DEVMACROES_H_
#define _DEVMACROES_H_

static
int devmacro_debug=1;

#ifdef _DEBUG
#include <stdio.h>
#include <time.h>
#endif

#ifdef _DEBUG
#define DBGMSG(...) if (devmacro_debug) { \
  char tim[ 64 ]; \
  time_t t = time(0); \
  struct tm* tm = localtime(&t); \
  strftime(tim, sizeof(tim), "%a, %d %b %Y %T %z", tm); \
  fprintf(stderr, "%s: DEBUG: %s: %d: ", tim, __FILE__, __LINE__); \
  fprintf(stderr, __VA_ARGS__); \
}
#else
#define DBGMSG(...)
#endif

#define TODO(...) { \
  fprintf(stderr, "In %s (%s:%d) TODO: ", \
    __PRETTY_FUNCTION__, __FILE__, __LINE__); \
  fprintf(stderr, __VA_ARGS__); \
}

#ifdef _DEBUG
#define ASSERT(cnd) { if (!(cnd)) { DBGMSG("Assertion failed in %s:%d\n", __FILE__, __LINE__); abort(); } }
#else
#define ASSERT(cnd)
#endif

#ifdef _DEBUG
#define RETURN_ERR(cod) { DBGMSG("Function %s return error code %d.\n", __PRETTY_FUNCTION__, cod); return (cod); }
#else
#define RETURN_ERR(cod) { return (cod); }
#endif
  
#ifdef _DEBUG
#define CHECK(fnc) { int __r = (fnc); if (__r) { DBGMSG("Error %d in %s:%d\n", __r, __FILE__, __LINE__); RETURN_ERR(__r) } }
#else
#define CHECK(fnc) { int __r = (fnc); if (__r) { return __r; } }
#endif
  
#ifdef _DEBUG
#define CHECK2(fnc, alt) { int __r = (fnc); if (__r) { DBGMSG("Error %d in %s:%d\n", __r, __FILE__, __LINE__); (alt); RETURN_ERR(__r) } }
#else
#define CHECK2(fnc, alt) { int __r = (fnc); if (__r) { return __r; } }
#endif
  
#ifdef _DEBUG
#define DEBUGFUNCTION { DBGMSG("Function %s\n", __PRETTY_FUNCTION__); }
#else
#define DEBUGFUNCTION
#endif
  
#ifdef _DEBUG 
#define RETURN_OK { DBGMSG("Function %s returns Ok.\n", __PRETTY_FUNCTION__); return 0; }
#else
#define RETURN_OK { return 0; }
#endif

#endif

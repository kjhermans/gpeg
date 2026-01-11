/*
 * Copyright 2018 Kees-Jan Hermans <kees.jan.hermans@gmail.com>
 * Written by Kees-Jan Hermans 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

/**
 * Parses an IPv4 address string in 'decimal-dot' notation.
 * The result is an IPv4 address in network order.
 * On little endian systems, you can't use this type as a number.
 */
int ipv4_parse
  (const char* string, uint32_t* address)
{
  unsigned char result[ 4 ] = { 0, 0, 0, 0 };
  unsigned havenum = 0;
  unsigned curnum = 0;
  unsigned nelts = 0;

  while (1) {
    if ((*string) >= '0' && (*string) <= '9') {
      unsigned n = (*string) - '0';
      curnum = ((curnum * 10) + n);
      havenum = 1;
    } else if ((*string) == '.' || (*string) == 0) {
      if (nelts == 4) {
        return ~0; /* Too many elements */
      }
      if (!havenum) {
        return ~0; /* No number before '.' */
      }
      if (curnum > 255) {
        return ~0; /* Element value too big */
      }
      result[nelts] = (unsigned char)curnum;
      ++nelts;
      if ((*string) == 0) {
        if (nelts != 4) {
          return ~0; /* Not enough elements */
        }
        memcpy(address, result, 4);
        return 0;
      }
      curnum = 0;
      havenum = 0;
    } else {
      return ~0; /* Token error */
    }
    ++string;
  }
}

static
char buffer[ 64 ];

char* ipv4_tostring
  (uint32_t address)
{
  uint8_t* e = (uint8_t*)(&address);

  snprintf(buffer, sizeof(buffer), "%u.%u.%u.%u", e[0],e[1],e[2],e[3]);
  return buffer;
}

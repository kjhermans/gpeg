-- Grammar:

CERTIFICATE    <- GENERICLIST

BERLENGTH      <- &|0_______| {:bl: . } /
                  0x81 {:bl: . } /
                  0x82 {:bl: .. } /
                  0x83 {:bl: ... } /
                  0x84 {:bl: .... }

ANY            <- GENERICLIST / OID / INTEGER / IPV4 / NULL /
                  BSTRING / PSTRING / ISTRING / USTRING / OSTRING /
                  GENERICSET / GCTXSPCLASS / TIMESTAMP /
                  BOOLEAN

GENERICLIST    <- SEQUENCE BERLENGTH <:$bl:1:32:LISTCONTENT>
GENERICSET     <- SET BERLENGTH <:$bl:1:32:LISTCONTENT>
GCTXSPCLASS    <- CTXSPCLASS BERLENGTH <:$bl:1:32:LISTCONTENT>
LISTCONTENT    <- { ANY }* !.

SEQUENCE       <- 0x30
SET            <- 0x31
CTXSPCLASS     <- 0xa3
INTEGER        <- INTEGERTYPE BERLENGTH <:$bl:1:32:INTEGERVALUE>
INTEGERTYPE    <- 0x02 / 0xa0
INTEGERVALUE   <- { .* }
IPV4           <- 0x40 0x04 { .... }
NULL           <- 0x05 0x00
BITSTRING      <- 0x03
TIMESTAMP      <- 0x17 BERLENGTH <:$bl:1:32:TIMECONTENT>
TIMECONTENT    <- { .* }
BOOLEAN        <- 0x01 0x01 { . }

PRINTABLESTRING <- 0x13
IASTRING        <- 0x16
UTF8STRING      <- 0x0c
OCTETSTRING     <- 0x04

BSTRING         <- BITSTRING BERLENGTH <:$bl:1:32:STRINGCNT>
PSTRING         <- PRINTABLESTRING BERLENGTH <:$bl:1:32:STRINGCNT>
ISTRING         <- IASTRING BERLENGTH <:$bl:1:32:STRINGCNT>
USTRING         <- UTF8STRING BERLENGTH <:$bl:1:32:STRINGCNT>
OSTRING         <- OCTETSTRING BERLENGTH <:$bl:1:32:STRINGCNT>
STRINGCNT       <- { .* }

OID            <- 0x06 BERLENGTH <:$bl:1:32:OIDVALUE>
OIDVALUE       <- { { . } { |1_______|* |0_______| }* }

-- Hexinput:

300906035504080c025554

-- Result:

OK

-- Grammar:

JREAP           <- X0 / X1 / X7

X0              <- !.
X7              <- !.

TTR             <- { |_| }
APV             <- { |____| }
ABML            <- {:abml: .. }
JRE_SI          <- ..
TA              <- { |____| }
DVT             <- { |____| ... }

X1              <- &AH1 <:$abml:1:16: X1PAYLOAD >
AH1             <- 0x31 TTR SP3 APV ABML JRE_SI TA DVT

SP1             <- |_|
SP2             <- |__|
SP3             <- |___|

X1PAYLOAD       <- .*

-- Hexinput:

3181002401a1d29a4d7ecc1e0b824b7800020c671da41a891bc1020a1356a963530e4e2c

-- Result:

OK

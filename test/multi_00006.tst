-- Test sets

TEST <- [a-z]						a	OK
TEST <- [a-z]						0	NOK
TEST <- [a-z]^2						a	NOK
TEST <- [a-z]^2						aa	OK
TEST <- [a-z]^2						ab	OK
TEST <- [a-z]^2						a0	NOK
TEST <- [a-z]^2						abx	OK
TEST <- [a-z]^2						a0x	NOK

TEST <- [a-z0-9]					a	OK
TEST <- [a-z0-9]					0	OK
TEST <- [a-z0-9]					;	NOK
TEST <- [a-z0-9]^2					a	NOK
TEST <- [a-z0-9]^2					aa	OK
TEST <- [a-z0-9]^2					ab	OK
TEST <- [a-z0-9]^2					a0	OK
TEST <- [a-z0-9]^2					0a	OK
TEST <- [a-z0-9]^2					a;	NOK
TEST <- [a-z0-9]^2					abx	OK
TEST <- [a-z0-9]^2					a0x	OK
TEST <- [a-z0-9]^2					0ax	OK
TEST <- [a-z0-9]^2					0a;	OK
TEST <- [a-z0-9]^2					a;x	NOK

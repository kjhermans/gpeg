-- Evaluation order

TEST <- ( 'a' / 'b' ) / ( 'c' / 'd' )		a	OK
TEST <- ( 'a' / 'b' ) / ( 'c' / 'd' )		b	OK
TEST <- ( 'a' / 'b' ) / ( 'c' / 'd' )		c	OK
TEST <- ( 'a' / 'b' ) / ( 'c' / 'd' )		d	OK
TEST <- 'a' 'b' / 'c' 'd'			abd	OK
TEST <- 'a' 'b' / 'c' 'd'			acd	NOK
TEST <- 'a' 'b' / 'c' 'd'			ab	OK
TEST <- 'a' 'b' / 'c' 'd'			cd	OK
TEST <- 'a' 'b' / 'c' 'd'			bcd	NOK
TEST <- ( 'a' 'b' ) / 'c' 'd'			abd	OK
TEST <- ( 'a' 'b' ) / 'c' 'd'			acd	NOK
TEST <- ( 'a' 'b' ) / 'c' 'd'			ab	OK
TEST <- ( 'a' 'b' ) / 'c' 'd'			cd	OK
TEST <- ( 'a' 'b' ) / 'c' 'd'			bcd	NOK
TEST <- 'a' ( 'b' / 'c' ) 'd'			acd	OK
TEST <- 'a' ( 'b' / 'c' ) 'd'			ab	NOK
TEST <- 'a' ( 'b' / 'c' ) 'd'			cd	NOK

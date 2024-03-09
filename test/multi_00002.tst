TEST <- { 'a' }					a		OK
TEST <- { 'a' / 'b' }				a		OK
TEST <- { 'a' / 'b' }				b		OK
TEST <- { 'a' / 'b' }				c		NOK
TEST <- { { 'a' / 'b' } / { 'c' } }		a		OK
TEST <- { { 'a' / 'b' } / { 'c' } }		b		OK
TEST <- { { 'a' / 'b' } / { 'c' } }		c		OK
TEST <- { { 'a' / 'b' } / { 'c' } }		d		NOK
TEST <- { 'a' } { 'a' } { 'a' / 'b' }		aaa		OK
TEST <- { 'a' } { 'a' } { 'a' / 'b' }		aab		OK
TEST <- { 'a' } { 'a' } { 'a' / 'b' }		aac		NOK

TEST <- { [a-z] / [0-9] } { [a-z] / [0-9] }	aa		OK
TEST <- { [a-z] / [0-9] } { [a-z] / [0-9] }	99		OK
TEST <- { [a-z] / [0-9] } { [a-z] / [0-9] }	.a		NOK

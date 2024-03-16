-- Recursive quantifiers

TEST <- { { 'a' }^4 'b' }^2			aaaabaaaab	OK
TEST <- { { 'a' }^4 'b' }^2			aaaabcaaaab	NOK
TEST <- { { 'a' }^4 'b' }^2			aaaacaaaab	NOK
TEST <- { { 'a' }^4 'b' }^2			aaabaaaab	NOK
TEST <- { { 'a' }^4 'b' }^2			aaaabaaab	NOK

TEST <- { { 'a'^2 'b' }^3 'c' }^2		aabaabaabcaabaabaabc	OK

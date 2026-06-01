-- Grammar:

TEST  <- DATUM+
DATUM <- { .... } <:$_:1:32:VALUE>
VALUE <- { .* }

-- Hexinput:

000000056161616161000000036262626363

-- Result:

OK

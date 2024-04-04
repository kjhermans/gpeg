-- Grammar:

item <- ({ %s* '<' {:tag: %w+ } %s* '>' (item / %s* { (!(%s* '<') .)+ })
          %s* '</' $tag '>' })+

-- Input:

<personinfo>
  <firstname>KJ</firstname>
  <lastname>Hermans</lastname>
  <address>Somewhere</address>
  <city>Sometown</city>
  <country>Someland</country>
</personinfo>

-- Result:

OK

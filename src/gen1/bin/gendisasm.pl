#!/usr/bin/perl

my $instrfile = shift @ARGV;
my $instrperl = `cat $instrfile`;
my $instrhash = eval $instrperl || die "Need instructions file";

print "TOP <- INSTRUCTION+
INSTRUCTION <- instr_" . join(" /\n  instr_", sort(keys(%{$instrhash}))) . "\n\n";

foreach my $key (sort(keys(%{$instrhash}))) {
  my $instr = $instrhash->{$key};
  print "instr_$instr->{mnem} <- ";
  if ($instr->{size} <= 4) {
    print "{ ";
  }
  my @array = ( $instr->{opcode} =~ m/../g );
  print "0x" . join(' 0x', @array);
  if ($instr->{size} > 4) {
    print " { " . join('', (('.') x ($instr->{size}-4))) . " }\n";
  } else {
    print " }\n";
  }
}

1;

#!/usr/bin/perl

my $instrfile = shift @ARGV;
my $instrperl = `cat $instrfile`;
my $instrhash = eval $instrperl || die "Need instructions file";

print "TOP <- INSTRUCTION+
INSTRUCTION <- " . join(" /\n  ", sort(keys(%{$instrhash}))) . "\n\n";

foreach my $instr (values(%{$instrhash})) {
  print "$instr->{mnem} <- ";
  my @array = ( $instr->{opcode} =~ m/../g );
  print "0x" . join(' 0x', @array);
  if ($instr->{size} > 4) {
    print " { " . join('', (('.') x ($instr->{size}-4))) . " }\n";
  } else {
    print "\n";
  }
}

1;

#!/usr/bin/perl

use strict;
my %defines;

while (scalar(@ARGV)) {
  my $arg = shift @ARGV;
  if ($arg =~ s/^-//) {
    if ($arg =~ s/^D//) {
      if ($arg =~ /^(.*)=(.*)/) {
        $defines{$1} = $2;
      } else {
        $defines{$arg} = 1;
      }
    }
  } else {
    unshift @ARGV, $arg;
    last;
  }
}

my $file = shift @ARGV;
my $text = `cat $file` || die "Could not absorb file $file";
my $chn0 = 0;

print STDERR "File $file\n";

print STDERR "- Evaluation inclusions\n";
while ($text =~ /#include\s+"(.*)?"/) {
  my $finc = $1;
  if (-f $finc) {
    my $tinc = `cat $finc` || die "Could not absorb inclusion '$finc'.";
    if ($text =~ s/#include\s+"$finc"/$tinc/) {
      $chn0 = 1;
    }
  } else {
    die "Could not resolve inclusion '$finc'.";
  }
}

print STDERR "- Evaluation expresions\n";
my $chn1 = 0;
{
  my $loopchng;
  do {
    $loopchng = 0;
    foreach my $key (keys(%defines)) {
      my $orig = "$text";
      $text =~
        s/#ifdef\s+$key\s*\n?(.*)?#endif\s*\n?/($defines{$key}?$1:'')/esg;
      if ($text ne $orig) {
        $chn1 = 1;
        $loopchng = 1;
      }
    }
  } while ($loopchng);
}

print STDERR "- Evaluation defines\n";
my $chn2 = 0;
{
  my $loopchng;
  do {
    $loopchng = 0;
    foreach my $key (keys(%defines)) {
      my $orig = "$text";
      $text =~ s/$key/$defines{$key}/g;
      if ($text ne $orig) {
        $chn2 = 1;
        $loopchng = 1;
      }
    }
  } while ($loopchng);
}

if ($chn0 || $chn1 || $chn2) {
  open FILE, "> $file";
  syswrite FILE, $text;
  close FILE;
}

1;

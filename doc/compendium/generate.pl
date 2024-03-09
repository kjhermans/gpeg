#!/usr/bin/perl

my $instructionsfile = shift;
my $texdir = shift || '.';

my $instructionshash = `cat $instructionsfile`;
my $instructions = eval $instructionshash;

open FILE, '> table_instr.tex';

print FILE '
%\\begin{table}[]
\\begin{center}
%\\caption{gpeg Assembly Instructions}
\\label{tab:naig_assembly}
\\begin{longtable}{lll}
\\textbf{Mnemonic} & \\textbf{Param1} & \\textbf{Param2} \\\\
\\endhead
';

foreach my $i (sort(keys(%{$instructions}))) {
  my $key = "$i";
  $key =~ s/([_])/\\$1/g;
  my $p1 = $instructions->{$i}{param1};
  my $p2 = $instructions->{$i}{param2};
  if ($p1 eq 'address') { $p1 = 'LABEL'; }
  if ($p2 eq 'address') { $p2 = 'LABEL'; }
  if ($p1 eq 'LABEL' && $p2 ne '-') {
    my $tmp = $p1; $p1 = $p2; $p2 = $tmp;
  }
  print FILE "'$key' \& $p1 \& $p2 \\\\\n";
}

print FILE '\\end{longtable}
\\end{center}
%\\end{table}
';
close FILE;

open FILE, '> table_bytecode.tex';

print FILE '
%\\begin{table}[]
\\begin{center}
%\\caption{gpeg Bytecode Instructions}
\\label{tab:naig_bytecode}
\\begin{longtable}{lllll}
\\textbf{Mnemonic} & \\textbf{Opcode} & \\textbf{Param1} & \\textbf{Param2} & \\textbf{Length} \\\\
\\endhead
';

foreach my $i (sort(keys(%{$instructions}))) {
  my $instr = $i;
  $instr =~ s/([_])/\\$1/g;
  print FILE $instr . ' & ' . sprintf("%.8x", $instructions->{$i}{instr}) .
    " \& $instructions->{$i}{param1} \& $instructions->{$i}{param2} " .
    " \& $instructions->{$i}{size} " .
    "\\\\\n";
}

print FILE '\\end{longtable}
\\end{center}
%\\end{table}
';
close FILE;

1;

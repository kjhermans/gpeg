#!/usr/bin/perl

my @instr = (
  'end',
  'range',
  'limit',
  'call',
  'ret',
  'catch',
  'commit',
  'backcommit',
  'partialcommit',
  'fail',
  'failtwice',
  'var',
  'opencapture',
  'closecapture',
  'counter',
  'condjump',
);

open LIST, "> instructions.tex";

for (my $i=0; $i < scalar(@instr); $i++) {
  my $instr = $instr[$i];
  open FILE, "> instr_$instr.tex";
  print LIST
"
\\newpage
\\input{instr_$instr.tex}
";
  print FILE
"\\subsection{Instruction: $instr}

\\subsubsection{Summary}

\\InputIfFileExists{instr_$instr" . "_summary.tex}{}{}

\\subsubsection{Grammar and Compiling}

\\InputIfFileExists{instr_$instr" . "_compiling.tex}{}{}

\\subsubsection{Assembly Syntax}

\\InputIfFileExists{instr_$instr" . "_assembly.tex}{}{}

\\subsubsection{Bytecode}

\\InputIfFileExists{instr_$instr" . "_bytecode.tex}{}{}
";
  close FILE;
}

1;

#!/usr/bin/perl

my $instr = shift @ARGV;
my $gram = shift @ARGV;

my $s = `cat $instr`;
my $structure = eval($s);

my $grammar = `cat $gram`;

my $texindex = '';
foreach my $key (sort keys(%{$structure})) {
  my $tit = "$key";
  my $mode = $structure->{$key}{mode};
  $tit =~ s/([_])/\\$1/g;
  $texindex .=
    "\\newpage\n" .
    "\\input{instr_" . lc($key) . ".tex}\n\n";
  my $instrfile = './instr_' . lc($key) . '.tex';
#  if (! -f $instrfile) {
    open INSTR, '>', $instrfile;
    print INSTR
      "\\subsection{Instruction: " . $tit . "}\n\n";
#    if ($mode eq '0') {
#      print INSTR
#        "\\subsubsection{Mode}\n" .
#        "This instruction is available in mode 0 (parser).\n";
#    } elsif ($mode eq '1') {
#      print INSTR
#        "\\subsubsection{Mode}\n" .
#        "This instruction is available in mode 1 (script interpreter).\n";
#    } elsif ($mode eq 'both') {
#      print INSTR
#        "\\subsubsection{Mode}\n" .
#        "This instruction is available in both mode 0 (parser)" .
#        " and mode 1 (script interpreter).\n";
#    }
    my $rulekey = uc($key);
    my $rule;
    if ($key !~ /^scr_/) {
      $rulekey .= 'INSTR';
    }
    if ($grammar =~ /^$rulekey\s+<-\s+(.*)$/m) {
      $rule = "$rulekey <- $1";
      my $cache = {};
      my @elts = split(/\s+/, $1);
      foreach my $elt (@elts) {
        if ($elt =~ /^[a-zA-Z0-9_]+$/
            && $grammar =~ /^$elt\s+<-\s+(.*)$/m
            && !defined($cache->{$elt}))
        {
          $rule .= "\n$elt <- $1";
          $cache->{$elt} = 1;
        }
      }
    }
    print INSTR
      "\\subsubsection{Summary}\n\n" .
      "\\InputIfFileExists{instr_$key" . "_summary.tex}{}{}\n\n" .
      "\\subsubsection{Grammar and Compiling}\n\n" .
      "\\InputIfFileExists{instr_$key" . "_compiling.tex}{}{}\n\n" .
      "\\subsubsection{Assembly Syntax}\n\n" .
"\\begin{myquote}
\\begin{verbatim}
$rule
\\end{verbatim}
\\end{myquote}

" .
      "\\InputIfFileExists{instr_$key" . "_assembly.tex}{}{}\n\n" .
      "\\subsubsection{Bytecode Encoding}\n\n" .
      "This instruction has a size of " . $structure->{$key}{size} .
      " bytes and is structured in bytecode as follows:\n\n" .
      "\%DEADBEEF\n" .
      "\%DEADBEEF\n" .
      "\\InputIfFileExists{instr_$key" . "_bytecode.tex}{}{}\n\n" .
      "\\subsubsection{Execution State Change}\n\n" .
      ".\n" .
      "\n" .
      "\\InputIfFileExists{instr_$key" . "_state.tex}{}{}\n\n" .
      "";
    close INSTR;
#  }
  my $texbytes =
#    "\\newline\n" .
    '$_{00}$\ ' . "\n" .
    '\\fbox{%' . "\n" .
    '  \\parbox{20pt}{%' . "\n" .
    sprintf("%.2x", (($structure->{$key}{instr} >> 24) & 0xff)) . "\n" .
    '  }%' . "\n" .
    '}' . "\n" .
    '\\fbox{%' . "\n" .
    '  \\parbox{20pt}{%' . "\n" .
    sprintf("%.2x", (($structure->{$key}{instr} >> 16) & 0xff)) . "\n" .
    '  }%' . "\n" .
    '}' . "\n" .
    '\\fbox{%' . "\n" .
    '  \\parbox{20pt}{%' . "\n" .
    sprintf("%.2x", (($structure->{$key}{instr} >> 8) & 0xff)) . "\n" .
    '  }%' . "\n" .
    '}' . "\n" .
    '\\fbox{%' . "\n" .
    '  \\parbox{20pt}{%' . "\n" .
    sprintf("%.2x", (($structure->{$key}{instr} >> 0) & 0xff)) . "\n" .
    '  }%' . "\n" .
    '}' . "\n";

  for ($i=4; $i < $structure->{$key}{size}; $i += 4) {
    $texbytes .=
#      "\\newline\n" .
"\n\n\n" .
      '$_{' . sprintf("%.2d", $i) . '}$\ ' . "\n" .
      '\\fbox{%' . "\n" .
      '  \\parbox{20pt}{%' . "\n" .
      '00' . "\n" .
      '  }%' . "\n" .
      '}' . "\n" .
      '\\fbox{%' . "\n" .
      '  \\parbox{20pt}{%' . "\n" .
      '00' . "\n" .
      '  }%' . "\n" .
      '}' . "\n" .
      '\\fbox{%' . "\n" .
      '  \\parbox{20pt}{%' . "\n" .
      '00' . "\n" .
      '  }%' . "\n" .
      '}' . "\n" .
      '\\fbox{%' . "\n" .
      '  \\parbox{20pt}{%' . "\n" .
      '00' . "\n" .
      '  }%' . "\n" .
      '}' . "\n";
  }

  replace($instrfile, '%DEADBEEF', '%DEADBEEF', $texbytes);
}

replace('./compendium.tex', '%DEADBEEF', '%DEADBEEF', $texindex);

sub replace
{
  my ($path, $begin, $end, $replace) = @_;
  my $contents = `cat $path`;
  if ($contents =~ s/$begin.*$end/$begin\n$replace\n$end/s) {
    open FILE, '>', $path;
    print FILE $contents;
    close FILE;
  }
}

1;

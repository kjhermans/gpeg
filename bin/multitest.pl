#!/usr/bin/perl

my $file = shift @ARGV;
my $compiler = shift @ARGV;
my $assembler = shift @ARGV;
my $engine = shift @ARGV;
my $disassembler = shift @ARGV;

my $table = `cat $file`;
my @tests = split(/\n/, $table);

my $tmpfile="/tmp/test$$";

system("rm -f $tmpfile.$n.log");

print "Multitest $file\n";
system("rm -f /tmp/success.$file.log /tmp/failure.$file.log");

my $n = 0;
foreach my $test (@tests) {
  $test =~ s/--.*^//;
  next if ($test =~ /^$/);
  my @fields = split(/\t+/, $test);
  if (scalar(@fields) >= 3) {
    ++$n;
    my $header = sprintf "TEST #%.3d - ", $n;
    print $header;
    system("echo \"---- $header\" >> $tmpfile.$n.log");
    open FILE, "> $tmpfile.gpeg"; print FILE $fields[0]; close FILE;
    open FILE, "> $tmpfile.txt"; print FILE $fields[1]; close FILE;
    my $c = "$compiler";
    if ($fields[3]) {
      $c .= " $fields[ 3 ]";
    }
    $c =~ s/GRAMMAR/$tmpfile.gpeg/g;
    $c =~ s/ASM/$tmpfile.asm/g;
    $c .= " 2>>$tmpfile.$n.log";
    my $x = system($c);
    if ($x) {
      print "Compile NOK - ";
      if ($fields[2] eq 'ERR_COMP') {
        print "Test Ok\n";
        system("cat $tmpfile.$n.log >> /tmp/success.$file.log");
      } else {
        print "Test NOK\n";
        system("cat $tmpfile.$n.log >> /tmp/failure.$file.log");
      }
      next;
    } else {
      print "Compile Ok  - ";
    }
    my $a = "$assembler";
    $a =~ s/ASM/$tmpfile.asm/g;
    $a =~ s/BYTECODE/$tmpfile.byc/g;
    $a .= " 2>>$tmpfile.$n.log";
    system("echo \"---- Grammar:\" >> $tmpfile.$n.log");
    system("cat $tmpfile.gpeg >> $tmpfile.$n.log");
    system("echo \"\" >> $tmpfile.$n.log");
    system("echo \"---- Assembly:\" >> $tmpfile.$n.log");
    system("cat $tmpfile.asm >> $tmpfile.$n.log");
    my $x = system($a);
    system("hexdump -C $tmpfile.byc >> $tmpfile.$n.log");
    if (-x $disassembler) {
      system("echo \"---- Disassembly:\" >> $tmpfile.$n.log");
      system("$disassembler -i $tmpfile.byc >> $tmpfile.$n.log 2>\&1");
    } else {
      system("echo \"---- No disassembly: $disassembler\" >> $tmpfile.$n.log");
    }
#    system("\$ROOT/main/disassembler/naid $tmpfile.byc >> $tmpfile.$n.log");
    if ($x) {
      print "Assembly NOK - ";
      if ($fields[2] eq 'ERR_ASM') {
        print "Test Ok\n";
        system("cat $tmpfile.$n.log >> /tmp/success.$file.log");
      } else {
        print "Test NOK\n";
        system("cat $tmpfile.$n.log >> /tmp/failure.$file.log");
      }
      next;
    } else {
      print "Assembly Ok  - ";
    }
    my $e = "$engine";
    $e =~ s/BYTECODE/$tmpfile.byc/g;
    $e =~ s/INPUT/$tmpfile.txt/g;
    $e .= " >>$tmpfile.$n.log " . '2>&1';
    my $x = system($e);
    if ($x) {
      print "Engine NOK - ";
      if ($fields[2] eq 'NOK') {
        print "Test Ok\n";
        system("cat $tmpfile.$n.log >> /tmp/success.$file.log");
      } else {
        print "Test NOK\n";
        system("cat $tmpfile.$n.log >> /tmp/failure.$file.log");
      }
      next;
    } else {
      print "Engine Ok  - ";
      if ($fields[2] eq 'OK') {
        print "Test Ok\n";
        system("cat $tmpfile.$n.log >> /tmp/success.$file.log");
      } else {
        print "Test NOK\n";
        system("cat $tmpfile.$n.log >> /tmp/failure.$file.log");
      }
    }
  }
}

system("rm $tmpfile.*");

1;

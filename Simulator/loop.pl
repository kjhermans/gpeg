## Simulated resources

use Data::Dumper;
use strict;

my $opcode_match = 0x01;
my $opcode_jump  = 0x02;

my $instrfetch_time = 1;

my (
  $instr,
  $input,
  $stack,
) = (
  [
    ( ( $opcode_match << 24 ) | ( ord('a') ) ),
    ( ( $opcode_jump << 24 )  | 0x00 ),
  ],
  [ 'a', 'a', 'a' ],
  [],
);

## Machine state

my $machine = {
  state => {
    'ifreg' => 0, ## Instruction offset register
    'iflck' => 0, ## Zero == not locked for writing
    'icreg' => 0, ## Instruction content register
    'iclck' => 0, ## 
  }
};

my $instrfetch = {
};

for (my $i=0; $i < 100; $i++) {
  print STDERR "==== Step $i\n";
  print STDERR Dumper $machine->{state};
  print STDERR Dumper $instrfetch->{state};
  system_cycle();
  sleep(.2);
}

exit 0;

##---- functions ----##

sub system_cycle
{
  $machine->{oldstate} = state_copy($machine->{state});
  $instrfetch->{oldstate} = state_copy($instrfetch->{state});

  machine_cycle();
  instrfetch_cycle();
}

sub machine_cycle
{
}

sub instrfetch_cycle
{
  if ($machine->{oldstate}{iflck} == 0) {
    $machine->{state}{iflck} = 1;
    $instrfetch->{state}{instrfetch} = $instrfetch_time;
  }
  if ($instrfetch->{oldstate}{instrfetch}) {
    $instrfetch->{state}{instrfetch} = $instrfetch->{oldstate}{instrfetch}-1;
  }
  if (defined($instrfetch->{oldstate}{instrfetch})
      && $instrfetch->{oldstate}{instrfetch} == 0)
  {
    my $offset = $machine->{oldstate}{ifreg};
    $machine->{state}{iflck} = 0;
    $machine->{state}{icreg} = $instr->[ $offset ];
    delete $instrfetch->{state}{instrfetch};
  }
}

sub state_copy
{
  my $s = shift;
  my $r = {};
  foreach my $key (keys(%{$s})) {
    $r->{"$key"} = $s->{$key};
  }
  return $r;
}

1;

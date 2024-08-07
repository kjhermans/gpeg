$VAR1 = {
          'any' => {
                     'instr' => 996,
                     'mnem' => 'any',
                     'mode' => 0,
                     'opcode' => '000003e4',
                     'size' => 4
                   },
          'backcommit' => {
                            'instr' => 263104,
                            'mnem' => 'backcommit',
                            'mode' => 0,
                            'opcode' => '000403c0',
                            'param1' => 'address',
                            'size' => 8,
                            'terse' => 1
                          },
          'bitmask' => {
                         'instr' => 1049445,
                         'mnem' => 'bitmask',
                         'mode' => 0,
                         'opcode' => '00100365',
                         'param1' => 'nbits',
                         'param2' => 'bits',
                         'param3' => 'andmask',
                         'param4' => 'ormask',
                         'size' => 20,
                         'terse' => 1
                       },
          'call' => {
                      'instr' => 263042,
                      'mnem' => 'call',
                      'mode' => 0,
                      'opcode' => '00040382',
                      'param1' => 'address',
                      'size' => 8,
                      'terse' => 1
                    },
          'catch' => {
                       'instr' => 263059,
                       'mnem' => 'catch',
                       'mode' => 0,
                       'opcode' => '00040393',
                       'param1' => 'address',
                       'size' => 8,
                       'terse' => 1
                     },
          'char' => {
                      'instr' => 263127,
                      'mnem' => 'char',
                      'mode' => 0,
                      'opcode' => '000403d7',
                      'param1' => 'char',
                      'size' => 8
                    },
          'closecapture' => {
                              'instr' => 262912,
                              'mnem' => 'closecapture',
                              'mode' => 0,
                              'opcode' => '00040300',
                              'param1' => 'slot',
                              'size' => 8,
                              'terse' => 1
                            },
          'commit' => {
                        'instr' => 262966,
                        'mnem' => 'commit',
                        'mode' => 0,
                        'opcode' => '00040336',
                        'param1' => 'address',
                        'size' => 8,
                        'terse' => 1
                      },
          'condjump' => {
                          'instr' => 525089,
                          'mnem' => 'condjump',
                          'opcode' => '00080321',
                          'param1' => 'register',
                          'param2' => 'address',
                          'size' => 12
                        },
          'counter' => {
                         'instr' => 525142,
                         'mnem' => 'counter',
                         'mode' => 0,
                         'opcode' => '00080356',
                         'param1' => 'register',
                         'param2' => 'value',
                         'size' => 12
                       },
          'end' => {
                     'instr' => 262360,
                     'mnem' => 'end',
                     'mode' => 'both',
                     'opcode' => '000400d8',
                     'param1' => 'code',
                     'size' => 8,
                     'terse' => 1
                   },
          'eq' => {
                    'instr' => 262147,
                    'mnem' => 'eq',
                    'opcode' => '00040003',
                    'size' => 8
                  },
          'fail' => {
                      'instr' => 843,
                      'mnem' => 'fail',
                      'mode' => 0,
                      'opcode' => '0000034b',
                      'size' => 4,
                      'terse' => 1
                    },
          'failtwice' => {
                           'instr' => 912,
                           'mnem' => 'failtwice',
                           'mode' => 0,
                           'opcode' => '00000390',
                           'size' => 4
                         },
          'gt' => {
                    'instr' => 262149,
                    'mnem' => 'gt',
                    'opcode' => '00040005',
                    'size' => 8
                  },
          'gteq' => {
                      'instr' => 262150,
                      'mnem' => 'gteq',
                      'opcode' => '00040006',
                      'size' => 8
                    },
          'imoveto' => {
                         'instr' => 9,
                         'mnem' => 'imoveto',
                         'opcode' => '00000009',
                         'size' => 4
                       },
          'intrpcapture' => {
                              'instr' => 524303,
                              'mnem' => 'intrpcapture',
                              'opcode' => '0008000f',
                              'size' => 12
                            },
          'irmoveto' => {
                          'instr' => 10,
                          'mnem' => 'irmoveto',
                          'opcode' => '0000000a',
                          'size' => 4
                        },
          'jump' => {
                      'instr' => 262963,
                      'mnem' => 'jump',
                      'mode' => 'both',
                      'opcode' => '00040333',
                      'param1' => 'address',
                      'size' => 8,
                      'terse' => 1
                    },
          'lt' => {
                    'instr' => 262156,
                    'mnem' => 'lt',
                    'opcode' => '0004000c',
                    'size' => 8
                  },
          'lteq' => {
                      'instr' => 262161,
                      'mnem' => 'lteq',
                      'opcode' => '00040011',
                      'size' => 8
                    },
          'moveto' => {
                        'instr' => 262162,
                        'mnem' => 'moveto',
                        'opcode' => '00040012',
                        'size' => 8
                      },
          'neq' => {
                     'instr' => 262164,
                     'mnem' => 'neq',
                     'opcode' => '00040014',
                     'size' => 8
                   },
          'noop' => {
                      'instr' => 0,
                      'mnem' => 'noop',
                      'mode' => 'both',
                      'opcode' => '00000000',
                      'size' => 4
                    },
          'opencapture' => {
                             'instr' => 263068,
                             'mnem' => 'opencapture',
                             'mode' => 0,
                             'opcode' => '0004039c',
                             'param1' => 'slot',
                             'size' => 8,
                             'terse' => 1
                           },
          'partialcommit' => {
                               'instr' => 263092,
                               'mnem' => 'partialcommit',
                               'mode' => 0,
                               'opcode' => '000403b4',
                               'param1' => 'address',
                               'size' => 8
                             },
          'quad' => {
                      'instr' => 263038,
                      'mnem' => 'quad',
                      'mode' => 0,
                      'opcode' => '0004037e',
                      'param1' => 'quad',
                      'size' => 8
                    },
          'range' => {
                       'instr' => 525245,
                       'mnem' => 'range',
                       'mode' => 0,
                       'opcode' => '000803bd',
                       'param1' => 'from',
                       'param2' => 'until',
                       'size' => 12,
                       'terse' => 1
                     },
          'ret' => {
                     'instr' => 928,
                     'mnem' => 'ret',
                     'mode' => 0,
                     'opcode' => '000003a0',
                     'size' => 4,
                     'terse' => 1
                   },
          'rmoveto' => {
                         'instr' => 262168,
                         'mnem' => 'rmoveto',
                         'opcode' => '00040018',
                         'size' => 8
                       },
          'set' => {
                     'instr' => 2098122,
                     'mnem' => 'set',
                     'mode' => 0,
                     'opcode' => '002003ca',
                     'param1' => 'set',
                     'size' => 36,
                     'terse' => 1
                   },
          'skip' => {
                      'instr' => 262960,
                      'mnem' => 'skip',
                      'mode' => 0,
                      'opcode' => '00040330',
                      'param1' => 'number',
                      'size' => 8
                    },
          'span' => {
                      'instr' => 2098145,
                      'mnem' => 'span',
                      'mode' => 0,
                      'opcode' => '002003e1',
                      'param1' => 'set',
                      'size' => 36
                    },
          'testany' => {
                         'instr' => 262918,
                         'mnem' => 'testany',
                         'mode' => 0,
                         'opcode' => '00040306',
                         'param1' => 'address',
                         'size' => 8
                       },
          'testchar' => {
                          'instr' => 525210,
                          'mnem' => 'testchar',
                          'mode' => 0,
                          'opcode' => '0008039a',
                          'param1' => 'address',
                          'param2' => 'char',
                          'size' => 12
                        },
          'testquad' => {
                          'instr' => 525275,
                          'mnem' => 'testquad',
                          'mode' => 0,
                          'opcode' => '000803db',
                          'param1' => 'address',
                          'param2' => 'quad',
                          'size' => 12
                        },
          'testset' => {
                         'instr' => 2360163,
                         'mnem' => 'testset',
                         'mode' => 0,
                         'opcode' => '00240363',
                         'param1' => 'address',
                         'param2' => 'set',
                         'size' => 40
                       },
          'trap' => {
                      'instr' => 4278255615,
                      'mnem' => 'trap',
                      'mode' => 'both',
                      'opcode' => 'ff00ffff',
                      'size' => 4
                    },
          'var' => {
                     'instr' => 263150,
                     'mnem' => 'var',
                     'mode' => 0,
                     'opcode' => '000403ee',
                     'param1' => 'slot',
                     'size' => 8,
                     'terse' => 1
                   }
        };

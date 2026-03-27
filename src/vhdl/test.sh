ghdl -a --std=08 gpeg_engine.vhd gpeg_engine_tb.vhd && \
ghdl -e --std=08 gpeg_engine_tb && \
#ghdl -r --std=08 gpeg_engine_tb --stop-time=1000000us
ghdl -r --std=08 gpeg_engine_tb

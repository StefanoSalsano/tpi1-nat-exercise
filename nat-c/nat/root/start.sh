#!/bin/bash

echo -n "Starting TCPDump..."
tcpdump -i any -w /hostlab/nat.pcap -s0  > /dev/null &
echo "Done."


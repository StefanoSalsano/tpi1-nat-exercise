#!/bin/bash

echo -n "Starting TCPDump..."
tcpdump -i any -w /hostlab/server.pcap -s0  > /dev/null &
echo "Done."


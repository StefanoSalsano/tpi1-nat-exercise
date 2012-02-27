#!/bin/bash

echo -n "Starting TCPDump..."
tcpdump -i any -w /hostlab/client.pcap -s0  > /dev/null &
echo "Done."


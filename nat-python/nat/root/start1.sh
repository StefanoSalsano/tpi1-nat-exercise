#!/bin/bash

echo -n "Starting TCPDump..."
tcpdump -i any -w /hosthome/nat.pcap -s0 > /dev/null &
echo "Done."


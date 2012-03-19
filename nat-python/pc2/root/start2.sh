#!/bin/bash

echo -n "Starting TCPDump..."
tcpdump -i any -w /hosthome/server.pcap -s0 &
echo "Done."



#!/bin/bash

echo -n "Starting TCPDump..."
tcpdump -i any -w /hosthome/client.pcap -s0 &
echo "Done."




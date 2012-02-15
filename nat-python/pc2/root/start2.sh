#!/bin/bash

echo -n "Starting TCPDump..."
tcpdump -i any -w /hosthome/server.pcap -s0  > /dev/null &
echo "Done."

echo -n "Staring echo server..."
python /root/serverUDP.py > /dev/null &
echo "Done."

#!/bin/bash

echo -n "Starting TCPDump..."
tcpdump -i any -w /hosthome/client.pcap -s0  > /dev/null &
echo "Done."

echo -n "Starin<g echo client..."
python /root/clientUDP.py > /dev/null &
echo "Done."


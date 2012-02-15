# Server program

from socket import *

# Set the socket parameters
host = "192.168.1.101"
port = 30000
buf = 1024
addr = (host,port)

# Create socket and bind to address
UDPSock = socket(AF_INET,SOCK_DGRAM)
UDPSock.bind(addr)

response = "ECHO RECEIVED"

# Receive messages
while 1:
	data,addr = UDPSock.recvfrom(buf)
	addr = (addr[0], 51000)
	if not data:
		print "Client has exited!"
		break
	else:
		print "\nReceived message '", data,"'"
		UDPSock.sendto(response,addr)
		break

# Close socket
UDPSock.close()

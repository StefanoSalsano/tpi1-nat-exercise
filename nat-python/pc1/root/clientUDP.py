# Client program

from socket import *

# Set the socket parameters
host = "192.168.1.101"
port = 30000
buf = 1024
addr = (host,port)

# Create socket
UDPSock = socket(AF_INET,SOCK_DGRAM)
data = "ECHO REQUEST"

# Send messages
if(UDPSock.sendto(data,addr)):
	print "Sending message '",data,"'....."

while 1:
	response,addr2 = UDPSock.recvfrom(buf)
	if response:
		print response
		break
				
# Close socket
UDPSock.close()

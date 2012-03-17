####
# Author: Marzio D'Alessandro
# Date: 16-03-2012
# Server UDP
# invia ECHO RESPONSE in risposta alle ECHO REQUEST del client dopo aver atteso l'intervallo in secondi
# specificato da quest'ultimo.
####

from socket import *
from time import *

# Set the socket parameters
host = "192.168.1.101" #indirizzo IP del server
port = 30000  #porta su cui il server deve porsi in ascolto
buf = 1024  #numero massimo di byte leggibili per volta dal buffer di ricezione
addr = (host,port)

# Create socket and bind to address
UDPSock = socket(AF_INET,SOCK_DGRAM)
UDPSock.bind(addr)


cont = 1 #contatore del numero di ECHO REQUEST ricevute
# Receive messages
while 1:
	seconds = 0
	check = 0 #variabile di controllo impostata ad 1 quando si riesce correttamente a decifrare il numero di secondi da attendere
	data,addr = UDPSock.recvfrom(buf)
	if not data:
		print "Il client ha chiuso la connessione"
		break
	else:
		print "Messaggio ricevuto: '", data,"'"
		dataSplitted = data.split("#")
		try:
			seconds = int(dataSplitted[1])
			check = 1
		except ValueError: #eccezione lanciata nel caso il numero di secondi sia non decifrabile
			print "messaggio ricevuto corrotto non attendero' alcun secondo prima di inviare la risposta"
		if check == 1:
			print "aspetto %d secondi" %seconds
			sleep(seconds)
		response	= "ECHO RECEIVED %d" %cont
		UDPSock.sendto(response,addr)
		print "Sto inviando il messaggio '",response,"'...."
		
	cont += 1

# Close socket
UDPSock.close()
print "Server terminato"

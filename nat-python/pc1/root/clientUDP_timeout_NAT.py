####
# Author: Marzio D'Alessandro
# Date: 16-03-2012
# Client UDP
# invia, finche' l'utente lo richiede, messaggi ECHO REQUEST al server UDP
# specificando il tempo in secondi che deve attendere il server prima di rispondergli con un ECHO RESPONSE.
# In questo modo l'utente puo' inviare piu' messaggi al server con un timeout crescente
# potendo cosi' valutare quanto tempo il nat mantiene in tabella l'associazione <10.0.0.101, 192.168.1.1> (vedere config rete netkit)
# infatti se scade il timeout il server inviera' il pacchetto a 192.168.1.1 (l'interfaccia eth2 del router) e questo non rinstradera'
# il pacchetto verso il client avente indirizzo 10.0.0.101.
####


from socket import *

# Set the socket parameters
host = "192.168.1.101" #indirizzo IP del server
port = 30000 #porta del server
buf = 1024 #numero massimo di byte leggibili per volta dal buffer di ricezione
addr = (host,port)

# Create socket
UDPSock = socket(AF_INET,SOCK_DGRAM)
cont = 1 #contatore delle richieste inoltrate al server

while 1:
	seconds = 0
	#il blocco while che segue ha il compito di prendere correttamente dall'utente il numero di secondi
	#che si vuole far attendere al server, in modo da inserirlo nel ECHO REQUEST
	while 1:
		userInput = raw_input("Inserisci il numero di secondi che il server deve attendere o -1>>> ")
		try:
			seconds = int(userInput)
		except ValueError:
			print "devi inserire un numero corretto!"
			continue
		if seconds >= -1:
			break

			
	if seconds == -1:
		print "Si e' deciso di arrestare il client"
		break
	data = "ECHO REQUEST %d#%d" %(cont,seconds) #si utilizza il '#' come separatore in modo da permettere al server di effettuare parsing
	# Invio del messaggio al server
	if UDPSock.sendto(data,addr):
		print "Sto inviando il messaggio '",data,"'...."

	response,addr2 = UDPSock.recvfrom(buf)
	if response:
		print "Ricevuto dal server il messaggio "+response
	else: 
		print "Il server ha chiuso la connessione"
		break
	cont += 1
				
# Close socket
UDPSock.close()
print "Client disconnesso e terminato"



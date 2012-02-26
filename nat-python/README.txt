****************************************************************
             GUIDA ALL'AVVIO DELL'ESERCIZIO - VERSIONE PYTHON
****************************************************************

---------------------------------------------------------------------------
Testato su Distribuzione Netkit-2.8-K2.8-F5.2.iso tramite VM con VirtualBox
Stefano Sanfilippo
---------------------------------------------------------------------------

1. Portarsi nella cartella nat-python, ad esempio se ci si trova in knoppix, e la cartella e' sul Desktop: 'cd Desktop/nat-python'

2. Avviare il file start.sh con il comando './start.sh'. In questo modo vengono avviate le macchine virtuali nat, pc1 e pc2

3. Portarsi sul terminale della VM nat

4. Digitare  './start1.sh', viene avviato tcpdump con scrittura sul file nat.pcap nella cartella home ( knoppix per la live Netkit ), considerazione valida anche ai passi 6,8.

5. Portarsi sul terminale della VM pc2

6. Digitare './start2.sh', viene avviato tcpdump con scrittura sul file server.pcap. Viene eseguito inoltre il file serverUDP.py che avvia un processo in attesa di messaggi sulla porta 3000.

7. Portarsi sul terminale della VM pc1

8. Digitare './start3.sh', viene avviato tcpdump con scrittura sul file client.pcap. Viene eseguito inoltre il file clientUDP.py che avvia un processo che invia un messaggio UDP alla VM pc2. Il messaggio giunge a destinazione attraverso la VM nat.

9. Portarsi sui terminali delle VM pc1,pc2, nat e terminare i processi tcpdump tramite il comando 'pkill tcpdump'

10. Portarsi sul terminale della macchina host e digitare 'lcrash' per terminare tutte le VM ( assicurarsi di essere nella cartella nat-pyton, in caso contrario ripetere il pass 1 )

11. Digitare sul terminale della macchina host 'wireshark client.pcap', in questo modo si avvia il programma per analizzare il file client.pcap ottenuto in precedenza.

12. Ripetere il passo 11 cambiando il file da aprire: 'wireshark server.pcap', 'wireshark nat.pcap'

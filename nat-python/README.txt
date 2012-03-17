****************************************************************
             GUIDA ALL'AVVIO DELL'ESERCIZIO - VERSIONE PYTHON
****************************************************************

---------------------------------------------------------------------------
Testato su Distribuzione Netkit-2.8-K2.8-F5.2.iso tramite VM con VirtualBox
e su netkit versione 2.6.
Stefano Sanfilippo
Marzio D'Alessandro
---------------------------------------------------------------------------

1. Portarsi nella cartella nat-python, ad esempio se ci si trova in knoppix, e la cartella e' sul Desktop: 'cd Desktop/nat-python'

2. Avviare il file start.sh con il comando './start.sh'. In questo modo vengono avviate le macchine virtuali nat, pc1 e pc2

3. Portarsi sul terminale della VM nat

4. Digitare  './start1.sh', viene avviato tcpdump con scrittura sul file nat.pcap nella cartella home ( knoppix per la live Netkit ).

5. Portarsi sul terminale della VM pc2

6. Digitare './start2.sh', viene avviato tcpdump con scrittura sul file server.pcap. 

7. Lanciare il server UDP desiderato con il comando python seguito dal nome del file da eseguire.
   Ad esempio lanciare: <python serverUDP_timeout_NAT.py>

8. Portarsi sul terminale della VM pc1

9. Digitare './start3.sh', viene avviato tcpdump con scrittura sul file client.pcap. 

10. Lanciare il client UDP desiderato con il comando python seguito dal nome del file da eseguire.
   Ad esempio lanciare: <python clientUDP_timeout_NAT.py>

11. Portarsi sui terminali delle VM pc1,pc2, nat e terminare i processi tcpdump tramite il comando 'pkill tcpdump', prima però terminare con CTRL ^ C i programmi server e client.

12. Portarsi sul terminale della macchina host e digitare 'lcrash' per terminare tutte le VM ( assicurarsi di essere nella cartella nat-pyton, in caso contrario ripetere il pass 1 )

13. Digitare sul terminale della macchina host 'wireshark client.pcap', in questo modo si avvia il programma per analizzare il file client.pcap ottenuto in precedenza.

14. Ripetere il passo precedente cambiando il file da aprire: 'wireshark server.pcap', 'wireshark nat.pcap'

NOTA: potrebbe essere necessario dare diritti di esecuzione ai vari script .sh (esempio chmod +x start.sh).
Nella cartella nat-python è presente il file show_timeout.png che mostra una prova di esecuzione del programma serverUDP_timeout_NAT.py- clientUDP_timeout_NAT.py e mette in evedenza come un timeout di 180 sec sia sufficiente a svuotare la tabella NAT.


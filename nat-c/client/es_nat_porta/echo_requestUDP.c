#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>

#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERV_PORT   30000
#define CLI_PORT   5194  
#define MAXLINE     1024

int main(int argc, char *argv[ ]) {
  int   sockfd, n;
  char  recvline[MAXLINE + 1];
  struct    sockaddr_in   servaddr;
  struct    sockaddr_in   cliaddr;
  char echo_request[] = "Echo request";	
 
 if (argc != 2) { /* controlla numero degli argomenti */
    fprintf(stderr, "utilizzo: echo_request <indirizzo IP server>\n");
    exit(1);
  }

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { /* crea il socket */
    perror("errore in socket");
    exit(1);
  }
  /*modif*/
  memset((void *)&cliaddr, 0, sizeof(cliaddr));
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  cliaddr.sin_port = htons(CLI_PORT); /* numero di porta del client */

  if (bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0) {
    perror("errore in bind");
    exit(1);
  }

   /*modif*/
  memset((void *)&servaddr, 0, sizeof(servaddr));      /* azzera servaddr */
  servaddr.sin_family = AF_INET;       /* assegna il tipo di indirizzo */
  servaddr.sin_port = htons(SERV_PORT);  /* assegna la porta del server */
  /* assegna l'indirizzo del server prendendolo dalla riga di comando. L'indirizzo è una stringa da convertire in intero secondo network byte order. */
  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
                /* inet_pton (p=presentation) vale anche per indirizzi IPv6 */
    fprintf(stderr, "errore in inet_pton per %s\n", argv[1]);
    exit(1);
  }

  /* Invia al server il pacchetto di richiesta */
  if (sendto(sockfd, echo_request, strlen(echo_request), 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
    perror("errore in sendto");
    exit(1);
  }
  printf("UDP echo request inviata. in attesa della risposta dal server...\n");
  /* Legge dal socket il pacchetto di risposta */
  n = recvfrom(sockfd, recvline, MAXLINE, 0 , NULL, NULL);
  if (n < 0) {
    perror("errore in recvfrom");
    exit(1);
  }
  if (n > 0) {
    recvline[n] = 0;        /* aggiunge il carattere di terminazione */
    if (fputs(recvline, stdout) == EOF)   {  /* stampa recvline sullo stdout */
      fprintf(stderr, "errore in fputs\n");
      exit(1);
    }
  }
  exit(0);
}

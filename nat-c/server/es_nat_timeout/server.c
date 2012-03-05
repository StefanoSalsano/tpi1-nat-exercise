#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERV_PORT     30000
#define _M_TIME       1
#define _M_ACK		  2	   


struct MSG
{
	int type;
	int time;
};

typedef struct MSG MSG ;

// Inizializzazione della variabile sockaddr_in
void addr_init (struct sockaddr_in *addr, int port, long int ip)  
{
        addr->sin_family=AF_INET;
        addr->sin_port = htons ((u_short) port);
        addr->sin_addr.s_addr=ip;
}


void delete_MSG(MSG *m)
{
	free(m);
}

int main(int argc, char **argv)  
{
  int sd;
  socklen_t len;
  struct sockaddr_in addr;

	// Inizializzazione dell'indirizzo
  addr_init (&addr,SERV_PORT,INADDR_ANY);

	// Creazione del socket
	
	if ((sd=socket(AF_INET,SOCK_DGRAM,0))<0)  
	{
		printf ("Impossibile creare un socket UDP\n");
		exit(3);
	}
	
	  // Lego il socket appena creato all'indirizzo del server
  if (bind(sd, (struct sockaddr*) &addr, sizeof(addr))<0)  {
          printf ("Impossibile aprire una connessione sulla porta %d\n"
                          "La porta potrebbe essere già in uso da un'altra applicazione\n",SERV_PORT);
          exit(2);
  }
  
  while(1)
  {
		MSG *m ; 
		m = (MSG*) malloc(sizeof(MSG));
		len = sizeof(addr);
	
		if (recvfrom(sd, m,sizeof(MSG), 0 , (struct sockaddr *)&addr, &len ) < 0 )
		{
			perror("errore in recvfrom");
			exit(-1);
		}
		
		if( m->type == _M_TIME)
		{
			printf ("MESSAGGIO DEL CLIENT [ %s:%d, time = %d]  \n" , inet_ntoa(addr.sin_addr), ntohs(addr.sin_port) , m->time);
		}
		
		sleep(m->time);
		
		m->type = _M_ACK;
		m->time = -1 ;

		
		if (sendto(sd, m, sizeof(MSG), 0, (struct sockaddr *) &addr, sizeof(addr) ) < 0) 
		{
			perror("errore in sendto");
			exit(-1);
		}
		else
		{
			printf ("INVIO ACK AL CLIENT\n\n\n\n");
		}
		
  	delete_MSG(m);

	}
	close(sd);
	
	return(0);
}

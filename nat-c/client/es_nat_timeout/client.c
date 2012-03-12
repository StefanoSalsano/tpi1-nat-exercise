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
void addr_init (struct sockaddr_in *addr, int port, long int ip)  {
        addr->sin_family=AF_INET;
        addr->sin_port = htons ((u_short) port);
        addr->sin_addr.s_addr=ip;
}


MSG *create_MSG( int type , int time )
{
	MSG *m ;
	m = (MSG * )malloc( sizeof( MSG ) ) ;

	m->type = type ;
	m->time = time ;
	return m ;
}

void delete_MSG(MSG *m)
{
	free(m);
}

int main(int argc, char **argv)  
{

	int time,sd;
	int var1,var2,var3,var4;
	struct sockaddr_in server;
	char bool;

 if (argc != 2) { /* controlla numero degli argomenti */
    fprintf(stderr, "utilizza: ./client <indirizzo IP server>\n");
    exit(1);
  }

	// Controllo che l'IP del server passato sia un indirizzo IPv4 valido
	if (sscanf(argv[1],"%d.%d.%d.%d",&var1,&var2,&var3,&var4) != 4)  {
		printf ("%s non è un indirizzo IPv4 valido\n",argv[1]);
		exit(2);
	}

	// Inizializzazione dell'indirizzo
	addr_init (&server,SERV_PORT,inet_addr(argv[1]));
	
	if ((sd=socket(AF_INET,SOCK_DGRAM,0))<0)  
	{
		printf ("Impossibile creare un socket UDP\n");
		exit(3);
	}

	bool = 1;
	while (bool)
	{
		printf ("Inserisci il tempo di attesa [sec]: ");
		scanf ("%d",&time);
		printf("\n");
		
		MSG *m ; 
		m = create_MSG( _M_TIME ,time );

		/* Invia al server il pacchetto di richiesta*/
		if (sendto(sd, m, sizeof(MSG),0, (struct sockaddr *) &server, sizeof(server)) < 0) 
		{
			perror("errore in sendto");
			exit(-1);
		}

    memset(m , 0 , sizeof(MSG) );

		/* legge dal socket il pacchetto di risposta */
		
		if (recvfrom(sd, m,sizeof(MSG), 0 , NULL, NULL) < 0) 
		{
			perror("errore in recvfrom");
			exit(-1);
		}
		
		if( m->type == _M_ACK)
		{
			printf ("ACK DAL SERVER \n");
		}
		
		delete_MSG(m);
		
		char c;
		printf ("vuoi mandare un altro messaggio (y/n): ");
		 	 
		while(getchar() != '\n'); // per svuotare l'stdin
		
		scanf("%c",&c);
		printf("\n");
		
		if( c != 'y')
		{
			bool = 0 ;
		}
		
	}
	close(sd);
	
	return(0); 
}

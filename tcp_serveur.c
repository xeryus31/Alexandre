// tcp_serveur.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#define PORT 10000


int main(void) {

  //Recuperation du domaine indiqué
  char rep[100];
  printf("Entrez votre répertoire : ");
  fgets(rep, 100,stdin);
  char *pos = strchr(rep, '\n'); *pos = '\0';
  printf("Chaine = -%s-\n", rep);

  //Demande du port
  int port;
  printf("Entrez le port : \n"); 
  scanf("%d", &port);  
  
  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
  socklen_t recsize = sizeof(sin);
    
  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  int csock;
  socklen_t crecsize = sizeof(csin);
 
  /* Creation d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
  sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
  sin.sin_port = htons(port);               /* Listage du port */
  bind(sock, (struct sockaddr*)&sin, recsize);

  /* Demarrage du listage (mode server) */
  listen(sock, 5);

  /* Attente d'une connexion client 
  csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
  printf("Un client se connecte avec la socket %d de %s:%d\n",
         csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

  /*Communication avec le serveur

  // reception
  char buffer[200];
  recv(csock, buffer, 200, 0);
  printf("%s\n", buffer);

  //envoi
  char reponse[32] = "Recu !";
  send(csock, reponse, 32, 0);



  /* Fermeture de la socket client et de la socket serveur 
  close(csock);
  close(sock);*/

  /* Attente d'une connexion client */
  for(;;) {

  /* Attente d'une connexion client */
    csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
    printf("Un client se connecte avec la socket %d de %s:%d\n",
           csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

    pid_t pid = fork(); //on duplique le processus
    if (pid == 0) {
      /*Communication avec le client*/
      // reception
      char buffer[200];
      recv(csock, buffer, 200, 0);
      printf("%s\n", buffer);

      //envoi
      char reponse[32] = "Recu !";
      send(csock, reponse, 32, 0);


      exit(0);
          /* Fermeture de la socket client et de la socket serveur */
      close(csock);
      close(sock);
    }

  }
  return EXIT_SUCCESS;


}//main

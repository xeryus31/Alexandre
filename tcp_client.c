// tcp_client.c

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
  //Demande de l'URL
  char url[100];
  int port=8001;
  int sock;
  struct sockaddr_in sin;

  //Recuperation du domaine indiqué
  printf("Entrez votre url : ");
  fgets(url, 100,stdin);
  char *pos = strchr(url, '\n'); *pos = '\0';
  printf("Chaine = -%s-\n", url);

  if (strlen(url) == 1)
  {
    strcpy(url, "index.html");

    printf("Entrez le port"); //Demande du port, par défaut 80
    scanf("%d", &port);  
  }

  /* Configuration de la connexion */
  struct hostent *hostinfo;
  hostinfo = gethostbyname(url);
  sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);


  /*Trouver l'adresse ip du domaine indiqué*/
  if (hostinfo) {
    struct in_adrr **pptr;
    //printf("Adresse IP de l'hote : %s\n", inet_ntoa(sin.sin_addr));
  }

/*Ouverture de la connexion TCP sur l'IP avec le port indiqué*/

  /* Creation de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Tentative de connexion au serveur */
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));

  /*Communication avec le serveur*/

    /* Requete GET */
  char requete[200] = "GET ";
  strcat(requete,url);
  strcat(requete," HTTP/1.1");  

    /* Envoi */
  send(sock, requete  ,200, 0);

    /* Reception */
  int nbcar;
  char buffer[200]="";
  do{
      nbcar = recv(sock, buffer, 200,0);
      printf("%s\n", buffer);
  }while(nbcar >0);
  
 
  
  /* Fermeture de la socket client */
  close(sock);

 



  return EXIT_SUCCESS;



 }

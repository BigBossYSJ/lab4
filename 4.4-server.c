#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    char buf[100];
    int k;
    socklen_t len;
    int sock_desc,temp_sock_desc;
    struct sockaddr_in server,client;

    memset(&server,0,sizeof(server));
    memset(&client,0,sizeof(client));

    //Create a socket
    sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if(sock_desc==-1)
    {
        printf("Socket creation fail!");
        exit(1);
    }

         server.sin_family=AF_INET;
         server.sin_addr.s_addr=INADDR_ANY;
         server.sin_port=htons(8888);//Port want to use for comunicate

    if(k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server))<0)
    {
        printf("Binding fail!");
        exit(1);
    }

    k=listen(sock_desc,20);
    if(k==-1)
    {
        printf("Listening fail!");
        exit(1);
    }
 len=sizeof(client);//VERY IMPORTANT
    temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);
    if(temp_sock_desc==-1)
    {
        printf("Temporary socket creation fail!");
        exit(1);
    }

    while(1)
    {
        k=recv(temp_sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Receiving Message Fail!");
            exit(1);
        }
      printf("Messages receives from the client are : %s",buf);
        printf("\nEnter any messages to be send to the client: ");

        fgets(buf,100,stdin);
        // Enter end to stop chat
        if(strncmp(buf,"end",3)==0)
            break;

        k=send(temp_sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Sending Messages Fail!");
            exit(1);
        }
    }
   exit(0);
    return 0;
}

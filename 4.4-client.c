#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char buf[100];
    int k;
    int sock_desc;
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    //Create socket
    sock_desc=socket(AF_INET,SOCK_STREAM,0);

    if(sock_desc==-1)
    {
        printf("Socket creation fail!");
        exit(1);
    }

    client.sin_family=AF_INET;
    client.sin_addr.s_addr= inet_addr("192.168.0.140");
    client.sin_port= htons( 8888 );

    //Connect to remote server
    if(k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client))<0)
    {
        printf("Fail to connect to the server");
        exit(1);
    }

    while(1)
    {
        printf("\nPlease enter any message to be send to the server: ");
        fgets(buf,100,stdin);
	//Enter end to stop the chat
        if(strncmp(buf,"end",3)==0)
            break;

        k=send(sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Sending messages fail!");
            exit(1);
        }

        k=recv(sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Receive messages fail!");
            exit(1);
        }

        printf("Messages receive from the server are : %s",buf);
    }
    exit(0);
    return 0;
}

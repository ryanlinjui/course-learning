#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT_NUM 8080

#define BUFFER_SIZE 1024
#define MAX_CLIENT_NUM 5

#define HTTP_HEAD "HTTP/1.1 200 OK\r\n\n"

#define HTML_FILE \
HTTP_HEAD \
"<!DOCTYPE html>"\
"<html>"\
    "<head>"\
    "</head>"\
    "<body>"\
       "41047035S Ryan"\
    "</body>"\
"</html>\r\n\n"\

#define SERVER_MESSAGE "Hello Client"

int main()
{
    // Create server socket
    int32_t server_sockfd=0, client_sockfd=0;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); // 0 is base setting. To let kernal auto choose protocol
    if (server_sockfd < 0)
    {
        perror("TCP server socket create error");
        exit(1);
    }
    puts("TCP server socket created");

    // Setting server socket information
    struct sockaddr_in server_info;
    memset(&server_info, 0, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(PORT_NUM);
    server_info.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    // Bind setting
    if(bind(server_sockfd, (struct sockaddr*)&server_info, sizeof(server_info)) < 0)
    {
        perror("Bind error");
        close(server_sockfd);
        exit(1);
    }

    // Listen setting
    printf("Bind to the port number: %d\n", PORT_NUM);
    if(listen(server_sockfd, MAX_CLIENT_NUM) == -1)
    {
        perror("Listen error");
        close(server_sockfd);
        exit(1);
    }
    puts("Listening...\n");

    struct sockaddr_in client_info;
    socklen_t client_info_size=0;
    char buffer[BUFFER_SIZE];
    while(1)
    {
        // Wait for client
        memset(&client_info, 0, sizeof(client_info));
        int32_t client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_info, &client_info_size);
        puts("Client connected");

        // Read buffer from client. read() can replace by recv()
        memset(buffer, 0, sizeof(buffer));
        read(client_sockfd,buffer,sizeof(buffer));        
        printf("Read from client: %s\n", buffer);
        
        if(buffer[0]=='G' && buffer[1]=='E' && buffer[2] == 'T')
        {
            memset(buffer, 0, sizeof(buffer));
            strncpy(buffer, HTML_FILE,strlen(HTML_FILE));
        }
        else
        {
            memset(buffer, 0, sizeof(buffer));
            strncpy(buffer, SERVER_MESSAGE,strlen(SERVER_MESSAGE));
        }

        // Write buffer to client. write() can replace by send()
        write(client_sockfd,buffer,sizeof(buffer));
        printf("Write to client: %s\n", buffer);

        // Close connection
        close(client_sockfd);
        puts("Client disconnected\n");
    }
    return 0;
}

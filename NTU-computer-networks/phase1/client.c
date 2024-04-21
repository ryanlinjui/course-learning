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

int main()
{
    char buffer[BUFFER_SIZE];

    // Create client socket
    int32_t client_sockfd=0;
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0); // 0 is base setting. To let kernal auto choose protocol
    if (client_sockfd < 0)
    {
        perror("TCP client socket create error");
        exit(1);
    }
    puts("TCP client socket created");

    // Setting client socket information
    struct sockaddr_in client_info;
    memset(&client_info, 0, sizeof(client_info));
    client_info.sin_family = AF_INET;
    client_info.sin_port = htons(PORT_NUM);
    client_info.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    // Connect to server
    if(connect(client_sockfd,(struct sockaddr *)&client_info,sizeof(client_info))==-1)
    {
        puts("Connection error");
        exit(1);
    }
    puts("Server connected\n");
    
    // Write buffer to server. write() can replace by send()
    memset(buffer, 0, sizeof(buffer));
    scanf("%s",buffer);
    write(client_sockfd,buffer,sizeof(buffer));
    printf("Write to server: %s\n", buffer);

    // Read buffer from client. read() can replace by recv()
    memset(buffer, 0, sizeof(buffer));
    read(client_sockfd,buffer,sizeof(buffer));        
    printf("Read from server: %s\n", buffer);

    // Close connection
    close(client_sockfd);
    puts("Close connection\n");
    
    return 0;
}

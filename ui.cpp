/**
 * @brief sender.c -- multicasts a message to a multicast group
 *
 */
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFF_SIZE 128
/*#define HELLO_PORT 12345
#define HELLO_GROUP "225.0.0.37"*/

int main(int argc, char *argv[])
{
     struct sockaddr_in addr;
     int fd;
     char message[BUFF_SIZE];
     char *ipAddress = argv[1];
     char *userName = argv[3];
     unsigned short port = atoi(argv[2]);
     char *groupName = argv[4];
     char userMessage[BUFF_SIZE];
     char userNamePrefix[BUFF_SIZE];
     int fdSender;
     char writeBuff[BUFF_SIZE];
     char *fifoSender = "../fifoSender";
     pid_t pid;
     int stop = 0;
     
     mkfifo(fifoSender, 0666);
     fdSender = open(fifoSender, O_WRONLY);
     pid = getpid();
     /* create what looks like an ordinary UDP socket */

     /* now just sendto() our destination! */
     while(!stop) 
     {
          ///////////////////////////////////////////////////////////////////////////////////////////////
          std::cout << "\n\nPlease insert your choice: \n\n"
          "0. Inhabitate a CROSS colony \n"
          "1. Inhabitate a SINGLE LINE colony \n"
          "2. exit\n\n"
          << '\n';
          int choice;

          __fpurge(stdin);
          __fpurge(stdout);
          std::cin >> choice;
          memset(message, 0, sizeof(BUFF_SIZE));
          memcpy(message, &choice, sizeof(int));
          
          write(fdSender, message, BUFF_SIZE);

          int x, y;

          switch(choice)
          {
            case 0 :
                 std::cout << "insert x coordinate:" << '\n';
                 
                 std::cin >> x;
                 std::cout << "insert y coordinate:" << '\n';
                 
                 std::cin >> y;
               
            break;
            case 1 :
                 std::cout << "insert x coordinate:" << '\n';
                 
                 std::cin >> x;
                 std::cout << "insert y coordinate:" << '\n';
                 
                 std::cin >> y;
                 
            break;
          }
          ///////////////////////////////////////////////////////////////////////////////////////////
          //memset(userMessage, 0, sizeof(BUFF_SIZE));
          //fgets(message, BUFF_SIZE, stdin);
          //strcat(userMessage, message);

          memset(message, 0, sizeof(BUFF_SIZE));
          memcpy(message, &x, sizeof(int));
          __fpurge(stdin);
          __fpurge(stdout);
          write(fdSender, message, BUFF_SIZE);

          memset(message, 0, sizeof(BUFF_SIZE));
          memcpy(message, &y, sizeof(int));
          __fpurge(stdin);
          __fpurge(stdout);
          write(fdSender, message, BUFF_SIZE);
     }

     sprintf(writeBuff, "%d", pid);
     write(fdSender, writeBuff, BUFF_SIZE);
     close(fdSender);
     unlink(fifoSender);
     
     return 0;
}

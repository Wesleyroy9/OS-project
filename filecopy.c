#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void main()
{
  char buffer[100];
  char childbuff[100];
  int fd[2], des, bytes, target;

  pipe(fd);

  if(fork()) {
    
    close(fd[0]);

    
    des = open("input.txt", O_RDONLY);
    bytes = read(des, buffer, sizeof(buffer));

    
    write(fd[1], buffer, bytes);
  } else {
    
    close(fd[1]);

    
    read(fd[0], childbuff, sizeof(childbuff));
    close(fd[0]);

   
    printf("\nReceived string is -- %s", childbuff);
    target = open("copy.txt", O_CREAT |O_WRONLY, 00777);
    write(target, childbuff, (strlen(childbuff)-1));
    
  }
}

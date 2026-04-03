////////////////////// CLIENT SIDE Application///////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdbool.h>


int ReadLine(int Sock , char *line , int max)
{
    int i = 0;
    char ch = '\0';
    int n = 0;

    while(i < max-1)
    {
        n = read(Sock , &ch , 1);
        if(n <= 0)
        {
            break;
        }

        line[i++] = ch;
        if(ch == '\n')
        {
            break;
        }
    }   //end pf while

    line[i] ='\0';
    return i;
}
//////////////////////////////////////////////////////////////////////////////
//
// Command Line Argument Application
/*
    1st : IP Address
    2nd : Port Number
    3rd : Targeted File name
    4th : New file name
*/
//  ./client    127.0.0.1    9000       Demo.txt       A.txt
//   argv[0]    argv[1]     argv[2]     argv[3]     argv[4]
//
//   argc = 5
//
////////////////////////////////////////////////////////////////////////////////
int main(int argc , char *argv[])
{

    int Sock = 0;
    int Port = 0;
    int iRet = 0;
    long FIleSize = 0;

    char * ip = NULL;        //argv[1]
    char *FileName = NULL;   //argv[2]
    char *OutFileName = NULL;//argv[3]

    char Header[64] = {'\0'};

    struct sockaddr_in ServerAddr;
    

    if((argc < 5) || (argc > 5))
    {
        printf("Unable to proceed as invalid number of arguments\n");

        printf("PLease provide below arguments : \n");
        printf("1st argument : IP Address\n");
        printf("2nd argument : Port Number\n");
        printf("3rd argument : Targeted File name\n");
        printf("4th argument : New file name\n");

        return -1;
    }

    //stored command line args into variables
    ip = argv[1];
    Port = atoi(argv[2]);
    FileName = argv[3];
    OutFileName = argv[4];

    ////////////////////////////////////////////////////////////////////////////////////////////
    // Step 1 : create TCP socket 
    /////////////////////////////////////////////////////////////////////////////////////////////

    Sock = socket(AF_INET , SOCK_STREAM , 0);

    if(Sock < 0)
    {
        printf("UNable to create client socket\n");
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    // Step 2 : Connect with server 
    /////////////////////////////////////////////////////////////////////////////////////////////

    memset(&ServerAddr , 0 , sizeof(ServerAddr));

    //initialise
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);
    
    //Convert the IP Address into binary format (127.0.0.1 to binary)

    inet_pton(AF_INET , ip , &ServerAddr.sin_addr);

    //Connect server and client
    iRet = connect(Sock , (struct sockaddr*)&ServerAddr , sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to connect with server\n");
        close(Sock);
        return -1;
    }

    //Sending file name to server
    write(Sock, FileName ,strlen(FileName));
    write (Sock , "\n" , 1);

    ////////////////////////////////////////////////////////////////////////////////////////////
    // Step 3 : Send file name 
    /////////////////////////////////////////////////////////////////////////////////////////////

    iRet = ReadLine(Sock , Header , sizeof(Header));

    if(iRet <= 0)
    {
        printf("Server gets disconnected abnormally\n");
        close(Sock);
        return -1;
    }

    
    sscanf(Header, "OK %ld" , &FIleSize); // 1700 yenar
    printf("File size is : %ld\n",FIleSize);


    ////////////////////////////////////////////////////////////////////////////////////////////
    // Step 4 : Create new file
    /////////////////////////////////////////////////////////////////////////////////////////////

    int outfd = 0;  //for creating a.txt

    outfd = open(OutFileName , O_CREAT | O_WRONLY | O_TRUNC , 0777);

    if(outfd < 0)
    {
        printf("UNable to create downloaded file\n");
        return -1;
    }

    char Buffer[1024] = {'\0'};
    long recieved = 0;
    long remaining = 0;
    int n = 0;
    int toRead = 0;

    while(recieved < FIleSize)
    {
        remaining = FIleSize - recieved;

        if(remaining > 1024)
        {
            toRead = 1024;
        }
        else
        {
            toRead = remaining;
        }

        n = read(Sock , Buffer , toRead);

        write(outfd , Buffer , n);
        recieved = recieved + n;
    }//end of while

    close(outfd);
    close(Sock);

    if(recieved == FIleSize)
    {
        printf("Download complete...\n");
        return 0;
    }
    else
    {
        printf("Download failed..\n");
        return -1;

    }


    return 0;
}//end of main
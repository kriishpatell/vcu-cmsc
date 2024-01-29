#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

 
#define PORT 2111
 
void bubble_sort(int list[], int n){
	int i, j, k;
	for(i = 0; i < (n-1); i++){
		for(j = 0; j < (n-i-1); j++){
			if(list[j] > list[j + 1]){
				k = list[j];
				list[j] = list[j+1];
				list[j+1] = k;
			}
		}
	}
}

main()
{
	int sock1,sock2, clength;
	sock1 =  socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serv,cli;
 
	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(sock1,(struct sockaddr *)&serv, sizeof(serv));
	listen(sock1,5);
	clength = sizeof(cli);
	int i=0;
	char buf[50];
	int num[100];
        
	while(1){
		sock2 = accept(sock1,(struct sockaddr *)&cli, (socklen_t *)&clength);
        cout << "\n CLIENT CONNECTED" << endl;
		//printf("\n Client Connected\n");
        read(sock2,buf,50);
        cout << "\n DISPLAY : " << buf << endl;
        //printf("Display: %s",buf);
		FILE* fp = fopen(buf,"r");

		// while not at end of file
		while(!feof(fp)){

			// fill with '\0' 
			for(i=0;i<50;i++){
				buf[i]='\0';
			}   

			// read from file to buf
			fread(buf, sizeof(char), 49, fp);
			
			// 
			for(int j = 0; j < i; j++){
				fscanf(fp, "%d", &num[j]);
			}
			bubble_sort(num, 50);
			write(sock2,num,50);
		}
		write(sock2,"cmsc312",50);
		fclose(fp);
		cout << "\n testing" << endl;
		//printf ("testing");
    }
	return 0;
}



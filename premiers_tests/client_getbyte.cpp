// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <string>
#include <cstring>
#include <iostream>
#include <bitset>
#define PORT 9999 

using namespace std;
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    string s = "Hello from client";
    char hello [s.size() + 1];
    strcpy(hello, s.c_str());
    bitset<8> buffer[1];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    char type;
    while(read(sock, buffer, 1))
	{
		cout << buffer[0]; 
		type = getchar();

        // Pour la partie suivante, on pourrait faire une seule fonction, qui renvoie un objet de type message 

		if (a == "A") { 		// type ADD

			// On définit les buffers adaptés à la taille de chaque champ du message, si j'ai bien compris
			bitset<8> buffer_add[27];
			Add_message add {buffer_add};

		} else if (a == "C") { // type CONTROL

            bitset<8> buffer_controle[11];   
            Control_message control {buffer_control};
		
        } else if (a == "D") { // type REDUCE

            bitset<8> buffer_reduce[22];
            Reduce_message add {buffer_reduce};
        			
		} else if (a == "E") { // type EXECUTE
		
            bitset<8> buffer_exec[30];
            Execute_message add {buffer_exec};
        	
		} else if (a == "L") { // type MASTER
		
            bitset<8> buffer_master[24];
            Master_message add {buffer_master};
        	 
		} else if (a == "M") { // type MODIFY
		
            bitset<8> buffer_modify[33];
            Modify_message add {buffer_modify};
        	
		} else if (a == "R") { // type REMOTE
		
            bitset<8> buffer_remote[18];
            Remote_message add {buffer_remote};
        	
		} else if (a == "Z") { // type PROTOCOL
		
            bitset<8> buffer_protocol[12];
            Protocol_message add {buffer_protocol};
        	
		}

	}
    return 0; 
} 


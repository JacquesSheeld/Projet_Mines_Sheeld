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
#include "structure_messages.cpp"

using namespace std;


int main(int argc, char** argv) 
{ 	
	if (argc != 2){
		cout << "usage : " << argv[0] << " [--port=]" << endl;
		return 0;
	}
	char* check = new char[7];
	strncpy(check, argv[1], 7);
	check[7] = '\0';
	if (strcmp("--port=",check) != 0){
		cout << "usage : " << argv[0] << " [--port=]" << endl;
		return 0;
	}
	char* port = new char[strlen(argv[1]) - 7];
	strncpy(port, argv[1] + 7, strlen(argv[1]) - 7);
	port[strlen(argv[1]) - 7] = '\0';
	int PORT = atoi(port);

    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
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

    uint8_t buffer[1];
    uint8_t a;
    int n_add = 0;
    int n_control = 0;
    int n_reduce = 0;
    int n_execution = 0;
    int n_master = 0;
    int n_modify = 0;
    int n_remote = 0;
    int n_protocol = 0;
    int n_erreur = 0;
    while(read(sock, buffer, 1))
	{
		a = buffer[0]; //On est sur de lire un uint8 à cette étape, car on commence un nouveau message


		if (a == 'A') { 		// type ADD
            
            uint64_t time[1];
            read(sock, time, 8);

            uint16_t sid[1];
            read(sock, sid, 2);

            uint64_t qid[1];
            read(sock, qid, 8);

            uint32_t price[1];
            read(sock, price, 4);

            uint32_t volume[1];
            read(sock, volume, 4);

            char status[1];
            read(sock, status, 1);

            Add_message add {a, time[0], sid[0], qid[0], price[0], volume[0], status[0]};
            n_add += 1;
            //add.Display();

		} else if (a == 'C') { // type CONTROL

            uint64_t time[1];
            read(sock, time, 8);

            uint16_t sid[1];
            read(sock, sid, 2);

            char status[1];
            read(sock, status, 1);

            Control_message control {a, time[0], sid[0], status[0]};
            n_control += 1;
            //control.Display();
		
        } else if (a == 'D') { // type REDUCE

            uint64_t time[1];
            read(sock, time, 8);

            uint16_t sid[1];
            read(sock, sid, 2);

            uint64_t qid[1];
            read(sock, qid, 8);

            uint32_t volume[1];
            read(sock, volume, 4);

            Reduce_message reduce {a, time[0], sid[0], qid[0], volume[0]};
            n_reduce += 1;
            //reduce.Display();
        			
		} else if (a == 'E') { // type EXECUTION
		
            uint64_t time[1];
            read(sock, time, 8);

            uint16_t sid[1];
            read(sock, sid, 2);

            uint64_t qid[1];
            read(sock, qid, 8);

            uint32_t volume[1];
            read(sock, volume, 4);

            uint64_t mid[1];
            read(sock, mid, 8);

            Execution_message exec {a, time[0], sid[0], qid[0], volume[0], mid[0]};
            n_execution += 1;
            //exec.Display();

		} else if (a == 'L') { // type MASTER
		
            uint64_t time[1];
            read(sock, time, 8);

            uint16_t sid[1];
            read(sock, sid, 2);

            char symbol[8];
            read(sock, symbol, 8);

            char currency[8];
            read(sock, currency, 8);

            uint8_t lot[1];
            read(sock, lot, 1);

            uint8_t tick[1];
            read(sock, tick, 1);

            char classification[1];
            read(sock, classification, 1);

            //Master_message master {a, time[0], sid[0], symbol, currency, lot[0], tick[0], classification[0]};
            n_master += 1;
            Master_message master {a, time[0], sid[0], symbol, currency, lot[0], tick[0], classification[0]}; 
            // master.Display();           

		} else if (a == 'M') { // type MODIFY
		
            uint64_t time[1];
            read(sock, time, 8);

            uint16_t sid[1];
            read(sock, sid, 2);

            uint64_t qid[1];
            read(sock, qid, 8);

            uint64_t nid[1];
            read(sock, nid, 8);

            uint32_t price[1];
            read(sock, price, 4);

            uint32_t volume[1];
            read(sock, volume, 4);

            Modify_message modify {a, time[0], sid[0], qid[0], nid[0], price[0], volume[0]};
            n_modify += 1;
            //modify.Display();

		} else if (a == 'R') { // type REMOTE

            uint64_t time[1];
            read(sock, time, 8);

            uint16_t sid[1];
            read(sock, sid, 2);

            uint64_t qid[1];
            read(sock, qid, 8);

            Remote_message remote {a, time[0], sid[0], qid[0]};	
            n_remote += 1;
            //remote.Display();	
        	
		} else if (a == 'Z') { // type PROTOCOL
		
            uint64_t time[1];
            read(sock, time, 8);

            uint32_t version[1];
            read(sock, version, 4);

            Protocol_message protocol {a, time[0], version[0]};
            n_protocol += 1;
            //protocol.Display();
        	
		}

            else{
                  cout << "erreur :" << a << endl;
                  n_erreur += 1;
            }
	}
    cout << "nb add : " << n_add << endl;
    cout << "nb control : " << n_control << endl;
    cout << "nb execute : " << n_execution << endl;
    cout << "nb reduce : " << n_reduce << endl;
    cout << "nb remote : " << n_remote << endl;
    cout << "nb master : " << n_master << endl;
    cout << "nb modify : " << n_modify << endl;
    cout << "nb protocol : " << n_protocol << endl;
    cout << "nb erreur : " << n_erreur << endl;
    return 0; 
} 


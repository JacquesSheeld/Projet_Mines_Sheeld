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
#include "assert.h"
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

    //char buffer[1];
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
    int nread = read(sock, &a, sizeof a);
    if (nread != 0){
      assert(nread == sizeof a);
    }
    while(nread != 0)
	{
	  //a = buffer[0]; //On est sur de lire un char à cette étape, car on commence un nouveau message


		if (a == 'A') { 		// type ADD
            
            uint64_t time;
            assert(read(sock, &time, sizeof time) == sizeof time);
	    
            uint16_t sid;
            assert(read(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(read(sock, &qid, sizeof qid) == sizeof qid);

            uint32_t price;
            assert(read(sock, &price, sizeof price) == sizeof price);

            uint32_t volume;
            assert(read(sock, &volume, sizeof volume) == sizeof volume);

            char* side = new char[1];
            assert(read(sock, side, 1) == 1);

            Add_message add {a, time, sid, qid, price, volume, side};
            n_add += 1;
            //add.Display();
	    delete [] side;
		} else if (a == 'C') { // type CONTROL

            uint64_t time;
            assert(read(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(read(sock, &sid, sizeof sid) == sizeof sid);

            char* status = new char[1];
            assert(read(sock, status, 1) == 1);
            Control_message control {a, time, sid, status};
            n_control += 1;
            //control.Display();
	    delete [] status;
        } else if (a == 'D') { // type REDUCE

            uint64_t time;
            assert(read(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(read(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(read(sock, &qid, sizeof qid) == sizeof qid);

            uint32_t volume;
            assert(read(sock, &volume, sizeof volume) == sizeof volume);

            Reduce_message reduce {a, time, sid, qid, volume};
            n_reduce += 1;
            //reduce.Display();
        			
		} else if (a == 'E') { // type EXECUTION
		
            uint64_t time;
            assert(read(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(read(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(read(sock, &qid, sizeof qid) == sizeof qid);

            uint32_t volume;
            assert(read(sock, &volume, sizeof volume) == sizeof volume);

            uint64_t mid;
            assert(read(sock, &mid, sizeof mid) == sizeof mid);

            Execution_message exec {a, time, sid, qid, volume, mid};
            n_execution += 1;
            //exec.Display();
	    
		} else if (a == 'L') { // type MASTER
		
            uint64_t time;
            assert(read(sock, &time, sizeof time) == sizeof time);
	    

            uint16_t sid;
            assert(read(sock, &sid, sizeof sid) == sizeof sid);

	    char* symbol = new char[8];
            assert(read(sock, symbol, sizeof symbol) == sizeof symbol);

	    char* currency = new char[8];
            assert(read(sock, currency, sizeof currency) == sizeof currency);

            uint8_t lot;
            assert(read(sock, &lot, sizeof lot) == sizeof lot);

            uint8_t tick;
            assert(read(sock, &tick, sizeof tick) == sizeof tick);

	    char* classification = new char[1];
            assert(read(sock, classification, sizeof classification) == sizeof classification);

            //Master_message master {a, time[0], sid[0], symbol, currency, lot[0], tick[0], classification[0]};
            n_master += 1;
            Master_message master {a, time, sid, symbol, currency, lot, tick, classification}; 
            // master.Display();           
	    delete [] symbol;
	    delete [] currency;
	    delete [] classification;
		} else if (a == 'M') { // type MODIFY
		
            uint64_t time;
            assert(read(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(read(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(read(sock, &qid, sizeof qid) == sizeof qid);

            uint64_t nid;
            assert(read(sock, &nid, sizeof nid) == sizeof nid);

            uint32_t price;
            assert(read(sock, &price, sizeof price) == sizeof price);

            uint32_t volume;
            assert(read(sock, &volume, sizeof volume) == sizeof volume);

            Modify_message modify {a, time, sid, qid, nid, price, volume};
            n_modify += 1;
            //modify.Display();

		} else if (a == 'R') { // type REMOTE

            uint64_t time;
            assert(read(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(read(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(read(sock, &qid, sizeof qid) == sizeof qid);

            Remote_message remote {a, time, sid, qid};	
            n_remote += 1;
            //remote.Display();	
        	
		} else if (a == 'Z') { // type PROTOCOL
		
            uint64_t time;
            assert(read(sock, &time, sizeof time) == sizeof time);

            uint32_t version;
            assert(read(sock, &version, sizeof version) == sizeof version);

            Protocol_message protocol {a, time, version};
            n_protocol += 1;
            //protocol.Display();
        	
		}

            else{
                  cout << "erreur :" << a << endl;
                  n_erreur += 1;
            }

		nread = read(sock, &a, sizeof a);
		if (nread!= 0){
		  assert (nread == sizeof a);
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


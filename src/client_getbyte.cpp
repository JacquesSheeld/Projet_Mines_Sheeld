#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <string>
#include <cstring>
#include <iostream>
#include <bitset>
#include "../include/structure_messages.h"
#include "assert.h"
using namespace std;
template<typename T>
int insread(int sock, T *data, int num){
  int nread = 0; 
  while (nread < num){
    int a = read(sock, data, num - nread);
    if (a == 0){
      break;}
    else{
      nread += a;
    }
    }
  return nread;
}

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
    int nread = insread(sock, &a, sizeof a);
    if (nread != 0){
      assert(nread == sizeof a);
    }
    message *m;
    message mes = message(0,0);
    m = &mes;
    while(nread != 0)
	{
	  //a = buffer[0]; //On est sur de lire un char à cette étape, car on commence un nouveau message


		if (a == 'A') { 		// type ADD
            
            uint64_t time;
            assert(insread(sock, &time, sizeof time) == sizeof time);
	    
            uint16_t sid;
            assert(insread(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(insread(sock, &qid, sizeof qid) == sizeof qid);

            uint32_t price;
            assert(insread(sock, &price, sizeof price) == sizeof price);

            uint32_t volume;
            assert(insread(sock, &volume, sizeof volume) == sizeof volume);

            char* side = new char[1];
            assert(insread(sock, side, 1) == 1);

            Add_message add {a, time, sid, qid, price, volume, side};
	    m = &add;
            n_add += 1;
            //add.Display();
	    delete [] side;
		} else if (a == 'C') { // type CONTROL

            uint64_t time;
            assert(insread(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(insread(sock, &sid, sizeof sid) == sizeof sid);

            char* status = new char[1];
            assert(insread(sock, status, 1) == 1);
            Control_message control {a, time, sid, status};
	    m = &control;
            n_control += 1;
            //control.Display();
	    delete [] status;
        } else if (a == 'D') { // type REDUCE

            uint64_t time;
            assert(insread(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(insread(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(insread(sock, &qid, sizeof qid) == sizeof qid);

            uint32_t volume;
            assert(insread(sock, &volume, sizeof volume) == sizeof volume);

            Reduce_message reduce {a, time, sid, qid, volume};
	    m = &reduce;
            n_reduce += 1;
            //reduce.Display();
        			
		} else if (a == 'E') { // type EXECUTION
		
            uint64_t time;
            assert(insread(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(insread(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(insread(sock, &qid, sizeof qid) == sizeof qid);

            uint32_t volume;
            assert(insread(sock, &volume, sizeof volume) == sizeof volume);

            uint64_t mid;
            assert(insread(sock, &mid, sizeof mid) == sizeof mid);

            Execution_message execution {a, time, sid, qid, volume, mid};
	    m = &execution;
            n_execution += 1;
            //exec.Display();
	    
		} else if (a == 'L') { // type MASTER
		
            uint64_t time;
            assert(insread(sock, &time, sizeof time) == sizeof time);
	    

            uint16_t sid;
            assert(insread(sock, &sid, sizeof sid) == sizeof sid);

	    char symbol1;
	    char symbol2;
	    char symbol3;
	    char symbol4;
	    char symbol5;
	    char symbol6;
	    char symbol7;
	    char symbol8;
            assert(insread(sock, &symbol1, sizeof symbol1) == sizeof symbol1);
	    assert(insread(sock, &symbol2, sizeof symbol2) == sizeof symbol2);
	    assert(insread(sock, &symbol3, sizeof symbol3) == sizeof symbol3);
	    assert(insread(sock, &symbol4, sizeof symbol4) == sizeof symbol4);
	    assert(insread(sock, &symbol5, sizeof symbol5) == sizeof symbol5);
	    assert(insread(sock, &symbol6, sizeof symbol6) == sizeof symbol6);
	    assert(insread(sock, &symbol7, sizeof symbol7) == sizeof symbol7);
	    assert(insread(sock, &symbol8, sizeof symbol8) == sizeof symbol8);
	    char symbol[9] = {symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, symbol7, symbol8,'\0'};
	    char currency1;
	    char currency2;
	    char currency3;
	    char currency4;
	    char currency5;
	    char currency6;
	    char currency7;
	    char currency8;
	    
            assert(insread(sock, &currency1, sizeof currency1) == sizeof currency1);
	    assert(insread(sock, &currency2, sizeof currency2) == sizeof currency2);
	    assert(insread(sock, &currency3, sizeof currency3) == sizeof currency3);
	    assert(insread(sock, &currency4, sizeof currency4) == sizeof currency4);
	    assert(insread(sock, &currency5, sizeof currency5) == sizeof currency5);
	    assert(insread(sock, &currency6, sizeof currency6) == sizeof currency6);
	    assert(insread(sock, &currency7, sizeof currency7) == sizeof currency7);
	    assert(insread(sock, &currency8, sizeof currency8) == sizeof currency8);
	    char currency[9] = {currency1, currency2, currency3, currency4, currency5, currency6, currency7, currency8, '\0'};
            uint8_t lot;
            assert(insread(sock, &lot, sizeof lot) == sizeof lot);

            uint8_t tick;
            assert(insread(sock, &tick, sizeof tick) == sizeof tick);

	    char classification;
            assert(insread(sock, &classification, sizeof classification) == sizeof classification);

            n_master += 1;
            Master_message master {a, time, sid, symbol, currency, lot, tick, classification};
	    m = &master;
		} else if (a == 'M') { // type MODIFY
		
            uint64_t time;
            assert(insread(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(insread(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(insread(sock, &qid, sizeof qid) == sizeof qid);

            uint64_t nid;
            assert(insread(sock, &nid, sizeof nid) == sizeof nid);

            uint32_t price;
            assert(insread(sock, &price, sizeof price) == sizeof price);

            uint32_t volume;
            assert(insread(sock, &volume, sizeof volume) == sizeof volume);

            Modify_message modify {a, time, sid, qid, nid, price, volume};
	    m = &modify;
            n_modify += 1;
            //modify.Display();

		} else if (a == 'R') { // type REMOTE

            uint64_t time;
            assert(insread(sock, &time, sizeof time) == sizeof time);

            uint16_t sid;
            assert(insread(sock, &sid, sizeof sid) == sizeof sid);

            uint64_t qid;
            assert(insread(sock, &qid, sizeof qid) == sizeof qid);

            Remote_message remote {a, time, sid, qid};
	    m = &remote;
            n_remote += 1;
            //remote.Display();	
        	
		} else if (a == 'Z') { // type PROTOCOL
		
            uint64_t time;
            assert(insread(sock, &time, sizeof time) == sizeof time);

            uint32_t version;
            assert(insread(sock, &version, sizeof version) == sizeof version);

            Protocol_message protocol {a, time, version};
	    m = &protocol;
            n_protocol += 1;
            //protocol.Display();
        	
		}

            else{
                  cout << "erreur :" << a << endl;
		  m->Display();
                  n_erreur += 1;
            }

		nread = insread(sock, &a, sizeof a);
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


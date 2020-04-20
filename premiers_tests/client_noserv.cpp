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
#include <fstream>
using namespace std;
ifstream file("../../arkw.p3",ios::in|ios::binary);


template<typename T>
  int fread(T data, int b){
  int c = 0;
  for(int i = 0; i < b; ++i){
    if(file >> data){
      c+=1;
    }
  }
  return c;
}

int main(int argc, char** argv) 
{ 	    //char buffer[1];
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

    int nread = fread(a, sizeof a);
    while(nread != 0)
	{
	  //a = buffer[0]; //On est sur de lire un char à cette étape, car on commence un nouveau message
	  fread(a, sizeof a);
		if (a == 'A') { 		// type ADD
            
            uint64_t time;
            fread(time, sizeof time);
	    
            uint16_t sid;
            fread(sid, sizeof sid);

            uint64_t qid;
            fread(qid, sizeof qid);

            uint32_t price;
            fread(price, sizeof price);

            uint32_t volume;
            fread(volume, sizeof volume);

            char* side = new char[1];
            fread(side, 1);

            Add_message add {a, time, sid, qid, price, volume, side};
            n_add += 1;
            //add.Display();
		} else if (a == 'C') { // type CONTROL

            uint64_t time;
            fread(time, sizeof time);

            uint16_t sid;
            fread(sid, sizeof sid);

            char* status = new char[1];
            fread(status, 1);
            Control_message control {a, time, sid, status};
            n_control += 1;
            //control.Display();
        } else if (a == 'D') { // type REDUCE

            uint64_t time;
            fread(time, sizeof time);

            uint16_t sid;
            fread(sid, sizeof sid);

            uint64_t qid;
            fread(qid, sizeof qid);

            uint32_t volume;
            fread(volume, sizeof volume);

            Reduce_message reduce {a, time, sid, qid, volume};
            n_reduce += 1;
            //reduce.Display();
        			
		} else if (a == 'E') { // type EXECUTION
		
            uint64_t time;
            fread(time, sizeof time);

            uint16_t sid;
            fread(sid, sizeof sid);

            uint64_t qid;
            fread(qid, sizeof qid);

            uint32_t volume;
            fread(volume, sizeof volume);

            uint64_t mid;
            fread(mid, sizeof mid);

            Execution_message exec {a, time, sid, qid, volume, mid};
            n_execution += 1;
            //exec.Display();
	    
		} else if (a == 'L') { // type MASTER
		
            uint64_t time;
            fread(time, sizeof time);
	    

            uint16_t sid;
            fread(sid, sizeof sid);

	    char* symbol = new char[8];
            fread(symbol, sizeof symbol);

	    char* currency = new char[8];
            fread(currency, sizeof currency);

            uint8_t lot;
            fread(lot, sizeof lot);

            uint8_t tick;
            fread(tick, sizeof tick);

	    char* classification = new char[1];
            fread(classification, sizeof classification);

            //Master_message master {a, time[0], sid[0], symbol, currency, lot[0], tick[0], classification[0]};
            n_master += 1;
            Master_message master {a, time, sid, symbol, currency, lot, tick, classification}; 
            // master.Display();           
		} else if (a == 'M') { // type MODIFY
		
            uint64_t time;
            fread(time, sizeof time);

            uint16_t sid;
            fread(sid, sizeof sid);

            uint64_t qid;
            fread(qid, sizeof qid);

            uint64_t nid;
            fread(nid, sizeof nid);

            uint32_t price;
            fread(price, sizeof price);

            uint32_t volume;
            fread(volume, sizeof volume);

            Modify_message modify {a, time, sid, qid, nid, price, volume};
            n_modify += 1;
            //modify.Display();

		} else if (a == 'R') { // type REMOTE

            uint64_t time;
            fread(time, sizeof time);

            uint16_t sid;
            fread(sid, sizeof sid);

            uint64_t qid;
            fread(qid, sizeof qid);

            Remote_message remote {a, time, sid, qid};	
            n_remote += 1;
            //remote.Display();	
        	
		} else if (a == 'Z') { // type PROTOCOL
		
            uint64_t time;
            fread(time, sizeof time);

            uint32_t version;
            fread(version, sizeof version);

            Protocol_message protocol {a, time, version};
            n_protocol += 1;
            //protocol.Display();
        	
		}

            else{
                  cout << "erreur :" << a << endl;
                  n_erreur += 1;
            }

		nread = fread(a, sizeof a);
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

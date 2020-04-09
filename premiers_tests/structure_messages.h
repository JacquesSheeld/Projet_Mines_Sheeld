#include <string>
#include <cstdint>
#include <iostream>

using namespace std;

class message {
	protected:
		uint8_t type;
		uint64_t time;

	public:
		message(uint8_t _type, uint64_t _time);
};

class Add_message : public message { // Type : A
	protected:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
		uint32_t price;
		uint32_t volume;
		char status;
	public:
		Add_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid, uint32_t _price, uint32_t _volume, char _status);
		void Display();

};

class Control_message : public message { // Type : C
	protected:
		uint16_t sid; // encodage du produit 
		char status;
	public:
		Control_message(uint8_t _type, uint64_t _time, uint16_t _sid, char _status);
		void Display();
};

class Reduce_message : public message { // Type : D
	protected:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
		uint32_t volume;	
	public:
		Reduce_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid, uint32_t _volume);
		void Display();
	
};

class Execution_message : public message {	// Type : E
	protected:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
		uint32_t volume;
		uint64_t mid;
	public:
		Execution_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid, uint32_t _volume, uint64_t _mid);
		void Display();
	
};

class Master_message : public message{ // Type : L
	protected:
		uint16_t sid; // encodage du produit 
		char symbol[8];
		char currency[8];
		uint8_t lot;
		uint8_t tick;
		char classification;
	public:
		Master_message(uint8_t _type, uint64_t _time, uint16_t _sid, char _symbol[8], char _currency[8], uint8_t _lot, uint8_t _tick, char _classification);
		void Display();
	
};

class Modify_message : public message { // Type : M
	protected:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
		uint64_t nid;
		uint32_t price;
		uint32_t volume;	
	public:
		Modify_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid, uint64_t _nid, uint32_t _price, uint32_t _volume);
		void Display();
	
};

class Remote_message : public message{ // Type : R
	protected:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
	public:
		Remote_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid);
		void Display();
	
};

class Protocol_message : public message{ // Type : Z
	protected:
		uint32_t version;
	public:
		Protocol_message(uint8_t _type, uint64_t _time, uint32_t _version);
		void Display();
	
};

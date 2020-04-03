#include <string>
#include <cstdint>
#include <iostream>

using namespace std;

class message {
	protected:
		uint8_t type;
		uint64_t time;

	public:
		message();
};

class Add_message : public message { // Type : A
	protected:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
		uint32_t price;
		uint32_t volume;
		char status;
	public:
		Add_message();
};

class Control_message : public message { // Type : C
	protected:
		uint16_t sid; // encodage du produit 
		char Operating_status;
	public:
		Control_Message();
}

class Reduce_message : public message { // Type : D
	public:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
		uint32_t volume;	
	protected:
		Reduce_message();
	
};

class Execution_message : public message {	// Type : E
	public:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
		uint32_t volume;
		uint64_t mid;
	protected:
		Execution_message();
	
};

class Master_message : public message{ // Type : L
	public:
		uint16_t sid; // encodage du produit 
		char symbol[8];
		char currency[8];
		uint8_t lot;
		uint8_t tick;
		char classification	
	protected:
		Master_message();
	
};

class Modify_message : public message { // Type : M
	public:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
		uint64_t nid;
		uint32_t price;
		uint32_t volume;	
	protected:
		Modify_message();
	
};

class Remote_message : public message{ // Type : R
	public:
		uint16_t sid; // encodage du produit 
		uint64_t qid;
	protected:
		Remote_message();
	
};

class Protocol_message : public message{ // Type : Z
	public:
		uint32_t version;
	protected:
		Protocol_message();
	
};

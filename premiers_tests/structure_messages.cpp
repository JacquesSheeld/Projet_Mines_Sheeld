#include <string>
#include <cstdint>
#include <iostream>

using namespace std;

class message {
	protected:
		uint8_t letter;
		uint64_t time;
};

class Add_message : public message {
	protected:
		uint16_t symbol_ID; // encodage du produit 
		uint64_t ID;
		uint32_t price;
		uint32_t volume;
		char status;
	public:
		Add_message()
};



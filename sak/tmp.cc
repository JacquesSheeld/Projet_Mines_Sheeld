/*
	Copyright (c) 2020 SheeldMarket
*/

//
//	Template of packed and aligned structure for p3l stream reading
//
//	to compile: g++ -std=c++17 a.cc
//

static_assert(__cplusplus >= 201703L, "Must use a C++17 or later compiler");

#include <unistd.h>

#include <assert.h>
#include <stdint.h>

// the "[[gnu::packed]]" attribute tells the compiler to use packed classes/structures/types
// i.e. types with no holes in them i.e. stream of bytes (or bits)

// a union is a piece of memory which can be interpreted as different types
// depending on the member being accessed
union [[gnu::packed]] Message {
	// type is the first member of all structures
	char type;

	// the add message
	struct [[gnu::packed]] Add {
		char type;
		uint64_t time;
		uint16_t sid;
		uint64_t qid;
		uint32_t price;
		uint32_t volume;
		char side;
	} add;

	// the master message
	struct [[gnu::packed]] Master {
		char type;
		uint64_t time;
		uint16_t sid;
		char symbol[8];
		char currency[8];
		uint8_t lot;
		uint8_t tick;
		char classification;
	} master;
};

void print(Message::Add a) {
	// some printing goes here
}

void print(Message::Master m) {
	// some printing goes here
}

void work(int fd) {
	// being lazy here: no error handling..!
	// in a real program each function call must be checked against all possible errors

	// idiomatic for ever loop
	for (;;) {
		Message msg;

		// read the first byte
		int status = read(fd, &msg.type, sizeof msg.type);
		if (status == 0) {
			// we are done -- exit the loop
			break;
		}
		assert(status == sizeof msg.type);

		// choose the union member based on the type (1st byte)
		switch (msg.type) {
		case 'A':
			// read the rest of the message
			status += read(fd, &msg.type + status, sizeof msg.add - status);
			// check all is good
			assert(status == sizeof msg.add);
			// print it
			print(msg.add);
			// done
			break;
		case 'L':
			status += read(fd, &msg.type + status, sizeof msg.master - status);
			assert(status == sizeof msg.master);
			print(msg.master);
			break;
		default:
			assert(!"This should not happen!");
			break;
		}
	}
}

int main() {
	// do not forget to properly nitialize the file descriptior
	// using zero means stdin i.e. standard input
	int fd = 0;

	work(fd);
}


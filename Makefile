# make
CXX = g++
EXE = Client
OBJS = structure_messages.o client_getbyte.o
all: Client

Client: $(OBJS)
		$(CXX) $^ -o $@
%.o: src/%.cpp
	$(CXX) $< -c


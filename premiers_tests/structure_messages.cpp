#include "structure_messages.h"
using namespace std;
// Message général

using Clock = chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

message::message(uint8_t _type, uint64_t _time): type(_type), time(_time) {
	const Clock::duration duration_nanoseconds = chrono::nanoseconds(_time);
	const TimePoint TimePoint_message(duration_nanoseconds);
	time_message = Clock::to_time_t(TimePoint_message);
};


// ADD

Add_message::Add_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid, uint32_t _price, uint32_t _volume, char _status):
	message(_type, _time),
	sid(_sid),
	qid(_qid),
	price(_price),
	volume(_volume),
	status(_status) {};
								
void Add_message::Display(){
	cout << "type : " << type << endl << "time : " << time << endl << "sid : " << sid << endl << "qid : " << qid << endl <<  "price : " << price << endl << "volume : " << volume << endl << "status : " << status << endl << endl;
}

// CONTROL

Control_message::Control_message(uint8_t _type, uint64_t _time, uint16_t _sid, char _status):
	message(_type, _time),
	sid(_sid),
	status(_status) {};

void Control_message::Display(){
	cout << "type : " << type << endl << "time : " << time << endl << "sid : " << sid << endl << "status : " << status << endl << endl;
}

// REDUCE

Reduce_message::Reduce_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid, uint32_t _volume):
	message(_type, _time),
	sid(_sid),
	qid(_qid),
	volume(_volume) {};

void Reduce_message::Display(){
	cout << "type : " << type << endl << "time : " << time << endl << "sid : " << sid << endl << "qid : " << qid << endl << "volume : " << volume << endl << endl;
}

// EXECUTION

Execution_message::Execution_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid, uint32_t _volume, uint64_t _mid):
	message(_type, _time),
	sid(_sid),
	qid(_qid),
	volume(_volume),
	mid(_mid) {};

void Execution_message::Display(){
	cout << "type : " << type << endl << "time : " << time << endl << "sid : " << sid << endl << "qid : " << qid << endl << "volume : " << volume << endl << "mid : " << mid << endl << endl;
}

// MASTER

Master_message::Master_message(uint8_t _type, uint64_t _time, uint16_t _sid, char* _symbol, char* _currency, uint8_t _lot, uint8_t _tick, char _classification):
	message(_type, _time),
	sid(_sid),
	symbol(_symbol),
	currency(_currency),
	lot(_lot),
	tick(_tick),
	classification(_classification) {};

void Master_message::Display(){
	cout << "type : " << type << endl << "time : " << time << endl << "sid : " << sid << endl << "symbol : " << symbol << endl << "currency : " << currency << endl << "lot : " << lot << endl << "tick : " << tick << endl << "classification : " << classification << endl << endl;
}
// MODIFY

Modify_message::Modify_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid, uint64_t _nid, uint32_t _price, uint32_t _volume):																				
	message(_type, _time),
	sid(_sid),
	qid(_qid),
	nid(_nid),
	price(_price),
	volume(_volume) {};

void Modify_message::Display(){
	cout << "type : " << type << endl << "time : " << time << endl << "sid : " << sid << endl << "qid : " << qid << endl << "nid : " << nid << endl << "price : " << price << endl << "volume : " << volume << endl << endl;
}

// REMOTE

Remote_message::Remote_message(uint8_t _type, uint64_t _time, uint16_t _sid, uint64_t _qid):
	message(_type, _time),
	sid(_sid),
	qid(_qid) {};

void Remote_message::Display(){
	cout << "type : " << type << endl << "time : " << time << endl << "time_t : " << ctime(&time_message) << endl << "sid : " << sid << endl << "qid : " << qid << endl << endl;
}

// PROTOCOL

Protocol_message::Protocol_message(uint8_t _type, uint64_t _time, uint32_t _version):
	message(_type, _time),
	version(_version) {};

void Protocol_message::Display(){
	cout << "type : " << type << endl << "time : " << time << endl << "version : " << version << endl << endl;
}
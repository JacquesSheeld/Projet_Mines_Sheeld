#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct order{
	
	uint64_t time;
	uint64_t qid;
	uint32_t price;
	uint32_t volume;

	order(uint64_t _time, uint64_t _qid, uint32_t _price, uint32_t _volume): time(_time), qid(_qid), price(_price), volume(_volume) {};

	order(Add_message& message): time(message.time), qid(message.qid), price(message.price), volume(message.volume) {};
};

function<bool(order&, order&)> greater = [](const order& order_1,const order& order_2){return (order_1 -> qid) > (order_2 -> qid);};


class symbol_storage {

protected:
	uint16_t symbol;
	char currency[9];
	uint8_t lot;
	uint8_t tick;
	char status;
	char classification;

	vector<order> buy_queue;
	priority_queue<order&, vector<order&>, decltype(great)> buy_binary(great);

	vector<order> sell_queue;
	priority_queue<order&, vector<order&>, decltype(great)> sell_binary(great);

	vector<Execution_message&> Exec;
	vector<Control_message&> Contr;
	vector<Modify_message&> Modif;
	vector<Reduce_message&> Reduc;

public:

	void add(Add_message& message) {
		order ord (message);
		side = message.side;
		if (side == "B"){
			buy_queue.push_back(ord);
			buy_binary.push(ord);
		} else if (side == "S") {
			sell_queue.push_back(ord);
			sell_binary.push_back(ord);
		}
	}

	void add(Execution_message& message) {
		Exec.push_back(message);
		// search the qid in buy_binary or sell_binary
		// remove the qid from buys or sells
	}

	void add(Control_message& message) {
		Contr.push_back(message);
		status = message.status;
	}

	void add(Modify_message& message) {
		Modif.push_back(message);
		// search the qid in buy_binary or sell_binary
		// remove the qid from buys and sells, create an add message with the values
		// add the message;
	}

	void add(Reduce_message& message) {
		Reduc.push_back(message);
		// search the qid in buy_binary or sell_binary
		// change the volume of the order
	}

};


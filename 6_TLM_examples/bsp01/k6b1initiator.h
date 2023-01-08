struct Initiator : public sc_module {
	sc_port<BusIF> busPort; 
	SC_HAS_PROCESS(Initiator);
	//Constructor
	Initiator(sc_module_name name) {
		SC_THREAD(generateTransactions);
	}
	//Processes
	void generateTransactions(){
		startTransaction(WRITE, 0, 't');
		startTransaction(WRITE, 32, 'e');
		startTransaction(WRITE, 1, 's');
		startTransaction(WRITE, 33, 't');
		startTransaction(READ, 0, 0);
		startTransaction(READ, 32, 0);
		startTransaction(READ, 1, 0);
		startTransaction(READ, 33, 0);
		startTransaction(READ, 31, 0);
		startTransaction(READ, 63, 0);
	}
	//Transaction object
	TransObject t1;
private:
	void startTransaction(Cmd tCmd, 
		unsigned int address, char data){
		t1.address = address;
		t1.data = data;
		t1.transCmd = tCmd;
		busPort->transaction(t1);
		cout <<"@ "<<setw(6)<<sc_time_stamp();
		if(tCmd == READ){
			cout <<" | Initiator READ  | A: "<<setw(3)<<address;
			cout <<" | D: "<<t1.data<<endl;
		}
		else {
			cout <<" | Initiator WRITE | A: "<<setw(3)<<address;
			cout <<" | D: "<<t1.data<<endl;
		}
		wait(10, SC_NS);
	}
};
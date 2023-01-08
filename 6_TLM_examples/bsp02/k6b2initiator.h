struct Initiator : public sc_module, tlm_bw_transport_if<> {
	tlm_initiator_socket<> iSocket;
	SC_HAS_PROCESS(Initiator);
	//Constructor
	Initiator(sc_module_name name) : iSocket("iSocket") {
		SC_THREAD(generateTransactions);
		iSocket.bind(*this);
	}
	//Processes
	void generateTransactions(){
		startTransaction(TLM_WRITE_COMMAND, 0, 't');
		startTransaction(TLM_WRITE_COMMAND, 1, 'l');
		startTransaction(TLM_WRITE_COMMAND, 2, 'm');
		startTransaction(TLM_READ_COMMAND, 0, 0);
		startTransaction(TLM_READ_COMMAND, 1, 0);
		startTransaction(TLM_READ_COMMAND, 2, 0);
	}
	//TLM-2.0 Interface methods (dummy)
	tlm_sync_enum nb_transport_bw( tlm_generic_payload& tObj,
                      tlm_phase& phase, sc_time& delay ) {
		return TLM_ACCEPTED;
	}
	void invalidate_direct_mem_ptr(uint64 startAddress,
                                  uint64 endAddress) {
	}
private:
	void startTransaction(tlm_command cmd, 
		  uint64 address, uchar data){
		delay = SC_ZERO_TIME;
		dataBuf = data;
		//Setup transaction object
		t1.set_command(cmd);
		t1.set_address(address);
		t1.set_data_ptr(&dataBuf);
		//Call interface method
		iSocket->b_transport(t1, delay);
		cout <<"@ "<<setw(6)<<sc_time_stamp();
		if(cmd == TLM_READ_COMMAND){
			cout <<" | Initiator READ  | A: "<<setw(3)<<address;
			cout <<" | D: "<<dataBuf<<endl;
		}
		else {
			cout <<" | Initiator WRITE | A: "<<setw(3)<<address;
			cout <<" | D: "<<dataBuf<<endl;
		}
		wait(10, SC_NS);
	}
	sc_time delay;
	uchar dataBuf;
	tlm_generic_payload t1;
};
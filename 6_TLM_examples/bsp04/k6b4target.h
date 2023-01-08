struct Target : public sc_module {
	simple_target_socket<Target> tSocket;
	//Constructor
	Target(sc_module_name name){
		tSocket.register_b_transport(this, &Target::transport);
		for(int i=0;i<SIZE;i++){
			memArray[i] = '?'; 
		}
	}
	//Interface method
	void transport(tlm_generic_payload& tObj, sc_time& delay){
		tlm_command   cmd = tObj.get_command();
		uint64        address = tObj.get_address();
		uchar         *dataPtr = tObj.get_data_ptr();
		sc_assert((address >= 0) && (address < SIZE));
		if(cmd == TLM_WRITE_COMMAND){
			memArray[address] = *dataPtr;
		}
		else {
			*dataPtr = memArray[address];
		}
		wait(5, SC_NS);
	}
private:
	char memArray[SIZE]; //Memory array
};
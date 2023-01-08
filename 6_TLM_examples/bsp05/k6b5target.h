#define SIZE 12 //Target size in bytes
struct Target : public sc_module {
	simple_target_socket<Target> tSocket;
	//Constructor
	Target(sc_module_name name){
		tSocket.register_b_transport(this, &Target::transport);
		memset(mem, 0, SIZE); //Initialize array
	}
	//Interface method
	void transport(tlm_generic_payload& tObj, sc_time& delay){
		tlm_command   cmd = tObj.get_command();
		uint64        startAdr = tObj.get_address();
		uchar         *dataPtr = tObj.get_data_ptr();
		unsigned int  transferLen = tObj.get_data_length();
		unsigned int  burstSize = transferLen/4;
		if(startAdr > SIZE-transferLen) {
			tObj.set_response_status(TLM_ADDRESS_ERROR_RESPONSE); 
			return;
		}
		if(cmd == TLM_WRITE_COMMAND){
			memcpy(&mem[startAdr], dataPtr, transferLen);
			cout << "Target Write, Burst Length = "<<burstSize<<endl;
		}
		else {
			memcpy(dataPtr, &mem[startAdr], transferLen);
			cout << "Target Read, Burst Length = "<<burstSize<<endl;
		}
		tObj.set_response_status(TLM_OK_RESPONSE);
		delay = delay + sc_time(burstSize*10, SC_NS);
	}
private:
	uchar mem[SIZE]; //Memory array
};
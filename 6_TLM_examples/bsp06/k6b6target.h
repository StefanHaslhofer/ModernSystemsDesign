#define SIZE 12 //Target size in bytes
struct Target : public sc_module {
	simple_target_socket<Target> tSocket;
	//Constructor
	Target(sc_module_name name){
		tSocket.register_b_transport(this, &Target::transport);
		memset(mem, 0x55, SIZE); //Initialize array
	}
	//Interface method
	void transport(tlm_generic_payload& tObj, sc_time& delay){
		uint64        startAdr = tObj.get_address();
		uchar         *dataPtr = tObj.get_data_ptr();
		uchar         *bePtr = tObj.get_byte_enable_ptr();
		unsigned int  beLen = tObj.get_byte_enable_length();
		unsigned int  transferLen = tObj.get_data_length();
		unsigned int  burstSize = transferLen/4;
		tObj.set_response_status(TLM_OK_RESPONSE);
		if(startAdr > SIZE-transferLen) {
			SC_REPORT_ERROR("Target", "Address out of range.");
			return;
		}
		if(tObj.is_write()){
			if(bePtr != 0){ //Transfer using byte enables
				for(unsigned int i=0; i<transferLen; i++){
					if(bePtr[i%beLen] == 0xFF)
					   mem[startAdr+i] = dataPtr[i];
				}
			}
			else { //No byte enables
				memcpy(&mem[startAdr], dataPtr, transferLen);
			}
			cout << "Target Write, Burst Length = "<<burstSize<<endl;
		}
		else {
			memcpy(dataPtr, &mem[startAdr], transferLen);
			cout << "Target Read, Burst Length = "<<burstSize<<endl;
		}
		delay = delay + sc_time(burstSize*10, SC_NS);
	}
private:
	uchar mem[SIZE]; //Memory array
};
struct Target : public sc_module, tlm_fw_transport_if<> {
	tlm_target_socket<> tSocket;
	//Constructor
	Target(sc_module_name name){
		for(int i=0;i<SIZE;i++){
			memArray[i] = '?'; 
		}
		tSocket.bind(*this);
	}
	//TLM-2.0 Interface methods
	void b_transport(tlm_generic_payload& tObj, sc_time& delay){
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
	//Dummy methods
	tlm_sync_enum nb_transport_fw( tlm_generic_payload& tObj,
                 tlm_phase& phase, sc_time& delay ) {
		return TLM_ACCEPTED;
	}
	bool get_direct_mem_ptr(tlm_generic_payload& tObj,
        tlm_dmi& dmiData) {
		return false;
	}
	unsigned int transport_dbg(tlm_generic_payload& tObj) {
		return 0;
	}
private:
	char memArray[SIZE]; //Memory array
};
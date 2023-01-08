struct Router : public sc_module, 
	tlm_bw_transport_if<>, tlm_fw_transport_if<> {
	tlm_target_socket<> tSocket;
	tlm_initiator_socket<> iSocket[NO_OF_TARGETS];
	//Constructor
	Router(sc_module_name name) {
		tSocket.bind(*this);
		iSocket[0].bind(*this);
		iSocket[1].bind(*this);
	}
	//Interface methods forward path
	void b_transport(tlm_generic_payload& tObj, sc_time& delay){
		unsigned int targetIndex = getTarget(tObj);
		iSocket[targetIndex]->b_transport(tObj, delay);
	}
	tlm_sync_enum nb_transport_fw( tlm_generic_payload& tObj,
                 tlm_phase& phase, sc_time& delay ) {
		unsigned int targetIndex = getTarget(tObj);
		return iSocket[targetIndex]->
			    nb_transport_fw(tObj, phase, delay);
	}
	bool get_direct_mem_ptr(tlm_generic_payload& tObj,
        tlm_dmi& dmiData) {
		unsigned int targetIndex = getTarget(tObj);
		return iSocket[targetIndex]->
			    get_direct_mem_ptr(tObj, dmiData);
	}
	unsigned int transport_dbg(tlm_generic_payload& tObj) {
		unsigned int targetIndex = getTarget(tObj);
		return iSocket[targetIndex]->transport_dbg(tObj);
	}
	//Interface methods backward path
	tlm_sync_enum nb_transport_bw( tlm_generic_payload& tObj,
                      tlm_phase& phase, sc_time& delay ) {
		return tSocket->nb_transport_bw(tObj, phase, delay);
	}
	void invalidate_direct_mem_ptr(uint64 startAddress,
                                  uint64 endAddress) {
		tSocket->invalidate_direct_mem_ptr(startAddress, endAddress);
	}
private:
	unsigned int getTarget(tlm_generic_payload& tObj) {
		unsigned int index;
		index = unsigned(tObj.get_address() / SIZE);
		sc_assert(index < NO_OF_TARGETS);
		tObj.set_address( tObj.get_address() - uint64(index*SIZE) );
		return index;
	}
};

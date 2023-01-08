struct Router : public sc_module, public BusIF {
	sc_port<BusIF> targetPort[NO_OF_TARGETS]; 
	//Constructor
	Router(sc_module_name name) {
	}
	//Interface method
	void transaction(TransObject &tObj){
		unsigned int targetIndex;
		targetIndex = tObj.address / SIZE;
		sc_assert(targetIndex < NO_OF_TARGETS);
		tObj.address = tObj.address - targetIndex*SIZE;
		targetPort[targetIndex]->transaction(tObj);
	}
};
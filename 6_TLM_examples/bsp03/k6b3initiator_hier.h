struct InitiatorHier : public sc_module {
	tlm_initiator_socket<> iSocketHier;
	Initiator *i1; //Instantiate initiator
	//Constructor
	InitiatorHier(sc_module_name name) {
		i1 = new Initiator("i1");
		i1->iSocket.bind(iSocketHier);
	}
};
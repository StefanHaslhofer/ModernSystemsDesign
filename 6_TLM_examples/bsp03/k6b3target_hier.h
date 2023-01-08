struct TargetHier : public sc_module {
	tlm_target_socket<> tSocketHier;
	Target *t1; //Instantiate Target
	//Constructor
	TargetHier(sc_module_name name){
		t1 = new Target("t1");
		tSocketHier.bind(t1->tSocket);
	}
};
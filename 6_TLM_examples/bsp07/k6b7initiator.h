#define USE_BYTE_ENABLES 1
struct Initiator : public sc_module {
	simple_initiator_socket<Initiator> iSocket;
	SC_HAS_PROCESS(Initiator);
	//Constructor
	Initiator(sc_module_name name) {
		SC_THREAD(generateTransactions);
	}
	//Processes
	void generateTransactions(){
		unsigned int dataBuf[3] = {0x12345678, 
			0xDEADBEEF, 0xDEADC0DE};
		unsigned int byteEnables[2] = {0xffff0000, 0x0000ffff};
		delay = SC_ZERO_TIME;
		t1.set_write();
		t1.set_address(4);
		t1.set_data_ptr((uchar*)dataBuf);
		t1.set_data_length(8);
		if(USE_BYTE_ENABLES)
			t1.set_byte_enable_ptr((uchar*)byteEnables);
		else
			t1.set_byte_enable_ptr(0);
		t1.set_byte_enable_length(8);
		t1.set_streaming_width(4);
		t1.set_response_status(TLM_INCOMPLETE_RESPONSE);
		iSocket->b_transport(t1, delay);
		if(t1.is_response_error())
			SC_REPORT_ERROR("Initiator", "Response error.");
		wait(delay);
		delay = SC_ZERO_TIME;
		t1.set_read();
		t1.set_address(0);
		t1.set_data_ptr((uchar*)dataBuf);
		t1.set_data_length(12);
		t1.set_byte_enable_ptr(0);
		t1.set_byte_enable_length(0);
		t1.set_streaming_width(12);
		t1.set_response_status(TLM_INCOMPLETE_RESPONSE);
		iSocket->b_transport(t1, delay);
		if(t1.is_response_error())
			SC_REPORT_ERROR("Initiator", "Response error.");
		wait(delay);
		cout <<"@ "<<setw(6)<<sc_time_stamp();
		cout <<", Initiator array: ";
		for(int i=0; i<3; i++){
			cout <<hex<< dataBuf[i] << " ";
		}
		cout << endl;
	}
	tlm_generic_payload t1;
	sc_time delay;
};
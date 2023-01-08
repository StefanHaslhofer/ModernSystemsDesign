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
		unsigned int  startAdr = (unsigned int)tObj.get_address();
		uchar         *dataPtr = tObj.get_data_ptr();
		uchar         *bePtr = tObj.get_byte_enable_ptr();
		unsigned int  beLen = tObj.get_byte_enable_length();
		unsigned int  transferLen = tObj.get_data_length();
		unsigned int  sWid = tObj.get_streaming_width();
		tObj.set_response_status(TLM_OK_RESPONSE);
		if(startAdr > SIZE-sWid) {
			SC_REPORT_ERROR("Target", "Address out of range.");
			return;
		}
		if(tObj.is_write()){
			for(unsigned int i=0; i<transferLen; i++){
				if(((bePtr!=0)&&(bePtr[i%beLen] == 0xFF))
					|| (bePtr==0)){
				   mem[startAdr + i%sWid] = dataPtr[i];
				}
			}
		}
		else {
			for(unsigned int i=0; i<transferLen; i++){
				dataPtr[i] = mem[i%sWid + startAdr];
			}
		}
		delay = sc_time(10, SC_NS);
	}
private:
	uchar mem[SIZE]; //Memory array
};
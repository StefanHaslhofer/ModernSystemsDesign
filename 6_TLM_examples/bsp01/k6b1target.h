struct Target : public sc_module, public BusIF {
	//Constructor
	Target(sc_module_name name){
		for(int i=0;i<SIZE;i++){
			memArray[i] = '?'; 
		}
	}
	//Interface method
	void transaction(TransObject &tObj){
		wait(5, SC_NS);
		sc_assert((tObj.address >= 0) && (tObj.address < SIZE));
		if(tObj.transCmd == WRITE){
			memArray[tObj.address] = tObj.data;
		}
		else {
			tObj.data = memArray[tObj.address];
		}
	}
private:
	char memArray[SIZE]; //Memory array
};
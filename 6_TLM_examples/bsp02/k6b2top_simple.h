#include <iostream>
#include <iomanip>
using namespace std;
#include <systemc>
using namespace sc_core;
using namespace sc_dt;
#include "tlm.h"
using namespace tlm;

#define SIZE 32 //Target size in bytes
#include "k6b2initiator.h"
#include "k6b2target.h"
struct Toplevel : public sc_module {
	Initiator *i1;
	Target    *t1;
	//Constructor
	Toplevel(sc_module_name name) {
		i1 = new Initiator("i1");
		t1 = new Target("t1");
		i1->iSocket.bind(t1->tSocket);
	}
};
#include <iostream>
#include <iomanip>
using namespace std;
#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc>
using namespace sc_core;
using namespace sc_dt;
#include "tlm.h"
using namespace tlm;
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
using namespace tlm_utils;

#define SIZE 32 //Target size in bytes
#include "k6b4initiator.h"
#include "k6b4target.h"
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
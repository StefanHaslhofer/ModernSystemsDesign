#include <iostream>
#include <iomanip>
using namespace std;
#include <systemc>
using namespace sc_core;
using namespace sc_dt;
#include "tlm.h"
using namespace tlm;

#define NO_OF_TARGETS 2 //Number of targets
#define SIZE 32 //Target size in bytes
#include "k6b2initiator.h"
#include "k6b2target.h"
#include "k6b2router.h"
struct Toplevel : public sc_module {
	Initiator *i1;
	Target    *t1, *t2;
	Router	 *r1;
	//Constructor
	Toplevel(sc_module_name name) {
		i1 = new Initiator("i1");
		t1 = new Target("t1");
		t2 = new Target("t2");
		r1 = new Router("r1");
		i1->iSocket.bind(r1->tSocket);
		r1->iSocket[0].bind(t1->tSocket);
		r1->iSocket[1].bind(t2->tSocket);
	}
};
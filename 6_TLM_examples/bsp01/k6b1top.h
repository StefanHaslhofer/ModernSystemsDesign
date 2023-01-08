#include <iostream>
#include <iomanip>
using namespace std;
#include <systemc>
using namespace sc_core;

#define SIZE 32 //Target size in bytes
#define NO_OF_TARGETS 2 //Number of targets
#include "k6b1interface.h"
#include "k6b1initiator.h"
#include "k6b1target.h"
#include "k6b1router.h"
struct Toplevel : public sc_module {
	Initiator *i1;
	Target *t1, *t2;
	Router *r1;
	//Constructor
	Toplevel(sc_module_name name) {
		i1 = new Initiator("i1");
		t1 = new Target("t1");
		t2 = new Target("t2");
		r1 = new Router("r1");
		i1->busPort(*r1);
		r1->targetPort[0](*t1);
		r1->targetPort[1](*t2);
	}
};
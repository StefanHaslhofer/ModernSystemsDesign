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
#include "k6b3initiator_hier.h"
#include "k6b3target_hier.h"
struct Toplevel : public sc_module {
	InitiatorHier *i1;
	TargetHier    *t1;
	//Constructor
	Toplevel(sc_module_name name) {
		i1 = new InitiatorHier("i1");
		t1 = new TargetHier("t1");
		i1->iSocketHier.bind(t1->tSocketHier);
	}
};
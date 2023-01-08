enum Cmd {READ, WRITE};

struct TransObject {
	Cmd transCmd;
	char data;
	unsigned int address;
};

struct BusIF : public sc_interface {
	virtual void transaction(TransObject&) = 0;
};
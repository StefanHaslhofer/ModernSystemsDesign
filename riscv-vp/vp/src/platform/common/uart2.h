#ifndef RISCV_ISA_UART2_H
#define RISCV_ISA_UART2_H
#define BAUDRATE 31250

#include <cstdlib>
#include <cstring>

#include <systemc>

#include <tlm_utils/simple_target_socket.h>

struct UART2 : public sc_core::sc_module {
	tlm_utils::simple_target_socket<UART2> tsock;

	interrupt_gateway *plic = 0;
	uint32_t irq_number = 0;
	sc_core::sc_event run_event;

	std::queue<char> rx_fifo;

	// memory mapped configuration registers
	
	uint32_t rx_data = 0x8000055;
	uint32_t rx_ctrl = 1;
	uint32_t tx_ctrl = 1;
	uint32_t tx_data = 1;
	std::unordered_map<uint64_t, uint32_t *> addr_to_reg;

	enum {
		TX_DATA_ADDR = 0x00,
		RX_DATA_ADDR = 0x04,
        TX_CTRL_ADDR = 0x08,
        RX_CTRL_ADDR = 0x0C,
	};

	SC_HAS_PROCESS(UART2);

	UART2(sc_core::sc_module_name, uint32_t irq_number) : irq_number(irq_number) {
		tsock.register_b_transport(this, &UART2::transport);
		SC_THREAD(run);

		addr_to_reg = {
		    {TX_DATA_ADDR, &tx_data},
			{RX_DATA_ADDR, &rx_data},
			{TX_CTRL_ADDR, &tx_ctrl},
			{RX_CTRL_ADDR, &rx_ctrl}
		};
	}

	void transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay) {
		auto addr = trans.get_address();
		auto cmd = trans.get_command();
		auto len = trans.get_data_length();
		auto ptr = trans.get_data_ptr();

		auto it = addr_to_reg.find(addr);

		if ((cmd == tlm::TLM_READ_COMMAND) && (addr == RX_DATA_ADDR)) {
			*((uint32_t *)ptr) = *it->second;
		}

		(void)delay;  // zero delay
	}

	void run() {
		while (true) {
			run_event.notify(sc_core::sc_time(BAUDRATE, sc_core::SC_NS));
			sc_core::wait(run_event);  // wait 32000 NS

			// fill with random data
			for (auto &n : rx_fifo) {
				n = rand();  // random printable char
			}

			plic->gateway_trigger_interrupt(irq_number);
		}
	}
};

#endif  // RISCV_ISA_SENSOR_H

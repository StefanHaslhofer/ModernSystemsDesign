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
	std::queue<char> tx_fifo;

	// memory mapped configuration registers
	
	uint32_t rx_data = 0;
	uint32_t rx_ctrl = 0;
	uint32_t tx_ctrl = 0;
	uint32_t tx_data = 0;
	std::unordered_map<uint64_t, uint32_t *> addr_to_reg;

	uint8_t rx_en = 0;
	size_t rx_cnt = 0;

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

		switch(addr)
		{
			case TX_DATA_ADDR:
				break;
			case RX_DATA_ADDR:

				if(cmd != tlm::TLM_READ_COMMAND) {
					// ignore write
					break;
				}

				// return rxdata
				if(rx_fifo.empty()) {
					rx_data |= 0x80000000;   // set bit 31 to 1 -> empty
				} else {
					rx_data &= 0x00000000;
					rx_data |= rx_fifo.front();
					rx_fifo.pop();
				}

				*((uint32_t*)ptr) = rx_data; 

				break;
			case TX_CTRL_ADDR:
				break;
			case RX_CTRL_ADDR:
				if (cmd == tlm::TLM_READ_COMMAND) {
					*((uint32_t*)ptr) = rx_ctrl;
				} else {
					rx_ctrl = *((uint32_t*)ptr);
					rx_en = rx_ctrl;
					rx_cnt = (rx_ctrl &= 0x00070000) >> 16;
				}

				break;
			
		}
		(void) delay;
	}

	void run() {
		while (true) {
			run_event.notify(sc_core::sc_time(BAUDRATE, sc_core::SC_NS));
			sc_core::wait(run_event);  // wait 32000 NS

			if(rx_en == 1 && rx_fifo.size() < 8) {
				rx_fifo.push(rand() % 26 + 65);

				if (rx_cnt == size(rx_fifo)) {
					plic->gateway_trigger_interrupt(irq_number);
				}
			}
		}
	}
};

#endif  // RISCV_ISA_SENSOR_H

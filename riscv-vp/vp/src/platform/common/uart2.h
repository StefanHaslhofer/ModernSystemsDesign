#ifndef RISCV_ISA_UART2_H

#include <cstdlib>
#include <cstring>

#include <systemc>

#include <tlm_utils/simple_target_socket.h>

struct UART2 : public sc_core::sc_module {
	tlm_utils::simple_target_socket<UART2> tsock;

	interrupt_gateway *plic = 0;
	uint32_t irq_number = 0;
	sc_core::sc_event run_event;

	// memory mapped data frame
	std::array<uint8_t, 64> data_frame;

	// memory mapped configuration registers
	uint32_t scaler = 25;
	uint32_t filter = 0;
	std::unordered_map<uint64_t, uint32_t *> addr_to_reg;

	enum {
		SCALER_REG_ADDR = 0x80,
		FILTER_REG_ADDR = 0x84,
	};

	UART2(sc_core::sc_module_name, uint32_t irq_number) : irq_number(irq_number) {
		tsock.register_b_transport(this, &UART2::transport);
		SC_THREAD(run);

		addr_to_reg = {
		    {SCALER_REG_ADDR, &scaler},
		    {FILTER_REG_ADDR, &filter},
		};
	}
};

#endif  // RISCV_ISA_SENSOR_H

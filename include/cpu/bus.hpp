#pragma once

#include <cstdint>
#include "cpu.hpp"
#include "nes_common.hpp"

/** @brief Bus class
 * 
 * This class represents the cpu bus of the NES.
 */
class Bus {
    public: // Bus interface
        Bus();
        ~Bus();
        void write(h_word address, byte data);
        byte read(h_word address, bool bReadOnly = false);

    private: // Devices interface
        CPU cpu;

        // for now, we only have a CPU and some RAM
        std::array<byte, 64*oxFFFf> ram;
};
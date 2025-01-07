#pragma once

#include <cstdint>
#include "nes_common.hpp"

class Bus; // forward declaration

/** @brief CPU class with architecture R6502
 * 
 * This class represents the CPU of the NES.
 */
class CPU {
    public:
        CPU();
        ~CPU();

        // Bus interface
        void connectBus(Bus* n){bus=n;};
        byte read(word a);
        void write(word a, byte d);

        // Adressing modes
        byte IMP(); // Implied
        byte IMM(); // Immediate
        byte ZP0(); // Zero page
        byte ZPX(); // Zero page, X
        byte ZPY(); // Zero page, Y
        byte REL(); // Relative
        byte ABS(); // Absolute
        byte ABX(); // Absolute, X
        byte ABY(); // Absolute, Y
        byte IND(); // Indirect
        byte IZX(); // Indirect, X
        byte IZY(); // Indirect, Y

        // CPU instructions
        void ADC(byte); // Add with carry   
        void AND(byte); // And with accumulator
    
    private:
        Bus* bus    = nullptr;  // Pointer to the bus
        
        // Registers
        byte A      = 0x0.0;    // Accumulator
        byte X      = 0x00;     // X register
        byte Y      = 0x00;     // Y register
        byte sp     = 0x00;     // Stack pointer
        word pc     = 0x0000;   // Program counter
        byte status = 0x00;     // Status register
        
        // Status register flags
        enum FLAGS6502 {
            C = (1 << 0),       // Carry
            Z = (1 << 1),       // Zero
            I = (1 << 2),       // Disable interrupts
            D = (1 << 3),       // Decimal mode (unused)
            B = (1 << 4),       // Break
            U = (1 << 5),       // Unused
            V = (1 << 6),       // Overflow
            N = (1 << 7)        // Negative
        };
}
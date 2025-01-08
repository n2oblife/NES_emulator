#pragma once

#include <cstdint>
#include "nes_common.hpp"
#include "bus.hpp"

// class Bus; // forward declaration

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

        // CPU cycle functions 
        void clock(); // Perform one clock cycle
        void reset(); // Reset the CPU
        void irq();   // Interrupt request
        void nmi();   // Non-maskable interrupt

        // Helper functions
        byte fetch(); // Fetch the next byte from memory

    
    private:   
        // Registers
        byte A      = 0x00;    // Accumulator
        byte X      = 0x00;     // X register
        byte Y      = 0x00;     // Y register
        byte sp     = 0x00;     // Stack pointer
        word pc     = 0x0000;   // Program counter
        byte status = 0x00;     // Status register

        // Bus connection
        Bus* bus    = nullptr;  // Pointer to the bus
        byte read(word address);
        void write(word address, byte data);

    private:
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
        byte ADC(); // Add with carry   
        byte AND(); // And with accumulator
        byte ASL(); // Arithmetic shift left
        byte BCC(); // Branch if carry clear
        byte BCS(); // Branch if carry set
        byte BEQ(); // Branch if equal
        byte BIT(); // Bit test
        byte BMI(); // Branch if minus
        byte BNE(); // Branch if not equal
        byte BPL(); // Branch if positive
        byte BRK(); // Break
        byte BVC(); // Branch if overflow clear
        byte BVS(); // Branch if overflow set
        byte CLC(); // Clear carry
        byte CLD(); // Clear decimal
        byte CLI(); // Clear interrupt disable
        byte CLV(); // Clear overflow
        byte CMP(); // Compare
        byte CPX(); // Compare X register
        byte CPY(); // Compare Y register
        byte DEC(); // Decrement
        byte DEX(); // Decrement X register
        byte DEY(); // Decrement Y register
        byte EOR(); // Exclusive OR
        byte INC(); // Increment
        byte INX(); // Increment X register
        byte INY(); // Increment Y register
        byte JMP(); // Jump
        byte JSR(); // Jump subroutine
        byte LDA(); // Load accumulator
        byte LDX(); // Load X register
        byte LDY(); // Load Y register
        byte LSR(); // Logical shift right
        byte NOP(); // No operation
        byte ORA(); // Or with accumulator
        byte PHA(); // Push accumulator
        byte PHP(); // Push processor status
        byte PLA(); // Pull accumulator
        byte PLP(); // Pull processor status
        byte ROL(); // Rotate left
        byte ROR(); // Rotate right
        byte RTI(); // Return from interrupt
        byte RTS(); // Return from subroutine
        byte SBC(); // Subtract with carry
        byte SEC(); // Set carry
        byte SED(); // Set decimal
        byte SEI(); // Set interrupt disable
        byte STA(); // Store accumulator
        byte STX(); // Store X register
        byte STY(); // Store Y register
        byte TAX(); // Transfer accumulator to X
        byte TAY(); // Transfer accumulator to Y
        byte TSX(); // Transfer stack pointer to X
        byte TXA(); // Transfer X to accumulator
        byte TXS(); // Transfer X to stack pointer
        byte TYA(); // Transfer Y to accumulator

        byte XXX(); // Illegal opcode
        
    private:
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

        // Convenience functions to access status register
        byte GetFlag(FLAGS6502 flag);
        void SetFlag(FLAGS6502 flag, bool setFlag);

    private:
        // Helper variables
        byte fetched = 0x00;    // Data fetched from memory
        word addr_abs = 0x0000; // Absolute address
        word addr_rel = 0x00;   // Relative address
        byte opcode = 0x00;     // Current opcode
        byte cycles = 0;        // Remaining cycles

    private:
        // Instruction lookup table and setup
        struct INSTRUCTION {
            std::string name;                   // Name of the instruction
            byte (CPU::*operate)() = nullptr;   // Function pointer to the operation
            byte (CPU::*addrmode)() = nullptr;  // Function pointer to the addressing mode
            byte cycles = 0;                    // Number of cycles required for the instruction
        };

        std::vector<INSTRUCTION> lookup;

}
#pragma once

#include <cstdint>
#include "nes_common.hpp"
#include "bus.hpp"

/**
 * @class CPU
 * @brief Emulates the R6502 CPU architecture for the NES.
 * 
 * This class implements the core functionalities of the NES CPU, including its 
 * registers, instruction set, and interaction with the system bus.
 */
class CPU {
public:
    /** 
     * @brief Default constructor for CPU class.
     */
    CPU();

    /** 
     * @brief Default destructor for CPU class.
     */
    ~CPU();

    /** 
     * @brief Connects the CPU to the system bus.
     * 
     * @param n Pointer to the Bus instance to connect.
     */
    void connectBus(Bus* n) { bus = n; };

    /**
     * @brief Executes a single clock cycle.
     */
    void clock();

    /** 
     * @brief Resets the CPU to its initial state.
     */
    void reset();

    /** 
     * @brief Handles an interrupt request (IRQ).
     */
    void irq();

    /** 
     * @brief Handles a non-maskable interrupt (NMI).
     */
    void nmi();

    /** 
     * @brief Fetches the next byte from memory.
     * 
     * @return The fetched byte.
     */
    byte fetch();

private:
    // Registers
    byte a = 0x00;      /**< Accumulator register. */
    byte x = 0x00;      /**< X index register. */
    byte y = 0x00;      /**< Y index register. */
    byte sp = 0x00;     /**< Stack pointer. */
    h_word pc = 0x0000; /**< Program counter. */
    byte status = 0x00; /**< Status register. */

    // Bus connection
    Bus* bus = nullptr; /**< Pointer to the system bus. */

    /** 
     * @brief Reads a byte from the specified memory address.
     * 
     * @param address Memory address to read from.
     * @return The byte read from memory.
     */
    byte read(h_word address);

    /** 
     * @brief Writes a byte to the specified memory address.
     * 
     * @param address Memory address to write to.
     * @param data The byte to write.
     */
    void write(h_word address, byte data);

    // Addressing modes
    /** @brief Implied addressing mode. */
    byte IMP();

    /** @brief Immediate addressing mode. */
    byte IMM();

    /** @brief Zero page addressing mode. */
    byte ZP0();

    /** @brief Zero page, X addressing mode. */
    byte ZPX();

    /** @brief Zero page, Y addressing mode. */
    byte ZPY();

    /** @brief Relative addressing mode. */
    byte REL();

    /** @brief Absolute addressing mode. */
    byte ABS();

    /** @brief Absolute, X addressing mode. */
    byte ABX();

    /** @brief Absolute, Y addressing mode. */
    byte ABY();

    /** @brief Indirect addressing mode. */
    byte IND();

    /** @brief Indexed indirect addressing mode (X). */
    byte IZX();

    /** @brief Indirect indexed addressing mode (Y). */
    byte IZY();

    // CPU instructions
    byte ADC(); /**< Add with carry. */
    byte AND(); /**< Logical AND with accumulator. */
    byte ASL(); /**< Arithmetic shift left. */
    byte BCC(); /**< Branch if carry clear. */
    byte BCS(); /**< Branch if carry set. */
    byte BEQ(); /**< Branch if equal. */
    byte BIT(); /**< Test bits in memory with accumulator. */
    byte BMI(); /**< Branch if negative. */
    byte BNE(); /**< Branch if not equal. */
    byte BPL(); /**< Branch if positive. */
    byte BRK(); /**< Force break. */
    byte BVC(); /**< Branch if overflow clear. */
    byte BVS(); /**< Branch if overflow set. */
    byte CLC(); /**< Clear carry flag. */
    byte CLD(); /**< Clear decimal mode. */
    byte CLI(); /**< Clear interrupt disable flag. */
    byte CLV(); /**< Clear overflow flag. */
    byte CMP(); /**< Compare accumulator with memory. */
    byte CPX(); /**< Compare X register with memory. */
    byte CPY(); /**< Compare Y register with memory. */
    byte DEC(); /**< Decrement memory. */
    byte DEX(); /**< Decrement X register. */
    byte DEY(); /**< Decrement Y register. */
    byte EOR(); /**< Exclusive OR with accumulator. */
    byte INC(); /**< Increment memory. */
    byte INX(); /**< Increment X register. */
    byte INY(); /**< Increment Y register. */
    byte JMP(); /**< Jump to location. */
    byte JSR(); /**< Jump to subroutine. */
    byte LDA(); /**< Load accumulator. */
    byte LDX(); /**< Load X register. */
    byte LDY(); /**< Load Y register. */
    byte LSR(); /**< Logical shift right. */
    byte NOP(); /**< No operation. */
    byte ORA(); /**< Logical OR with accumulator. */
    byte PHA(); /**< Push accumulator to stack. */
    byte PHP(); /**< Push processor status to stack. */
    byte PLA(); /**< Pull accumulator from stack. */
    byte PLP(); /**< Pull processor status from stack. */
    byte ROL(); /**< Rotate left. */
    byte ROR(); /**< Rotate right. */
    byte RTI(); /**< Return from interrupt. */
    byte RTS(); /**< Return from subroutine. */
    byte SBC(); /**< Subtract with carry. */
    byte SEC(); /**< Set carry flag. */
    byte SED(); /**< Set decimal mode. */
    byte SEI(); /**< Set interrupt disable flag. */
    byte STA(); /**< Store accumulator in memory. */
    byte STX(); /**< Store X register in memory. */
    byte STY(); /**< Store Y register in memory. */
    byte TAX(); /**< Transfer accumulator to X. */
    byte TAY(); /**< Transfer accumulator to Y. */
    byte TSX(); /**< Transfer stack pointer to X. */
    byte TXA(); /**< Transfer X to accumulator. */
    byte TXS(); /**< Transfer X to stack pointer. */
    byte TYA(); /**< Transfer Y to accumulator. */
    byte XXX(); /**< Illegal opcode. */

    // Status register flags
    enum FLAGS6502 {
        C = (1 << 0), /**< Carry flag. */
        Z = (1 << 1), /**< Zero flag. */
        I = (1 << 2), /**< Interrupt disable flag. */
        D = (1 << 3), /**< Decimal mode (unused). */
        B = (1 << 4), /**< Break flag. */
        U = (1 << 5), /**< Unused flag. */
        V = (1 << 6), /**< Overflow flag. */
        N = (1 << 7)  /**< Negative flag. */
    };

    // Helper functions
    /** 
     * @brief Gets the value of a status register flag.
     * 
     * @param flag The flag to retrieve.
     * @return The value of the flag (0 or 1).
     */
    byte GetFlag(FLAGS6502 flag);

    /** 
     * @brief Sets or clears a status register flag.
     * 
     * @param flag The flag to modify.
     * @param setFlag Whether to set (true) or clear (false) the flag.
     */
    void SetFlag(FLAGS6502 flag, bool setFlag);

    private:
        // Helper variables
        byte fetched    = 0x00;     // Data fetched from memory
        h_word addr_abs = 0x0000;   // Absolute address
        h_word addr_rel = 0x00;     // Relative address
        byte opcode     = 0x00;     // Current opcode
        byte cycles     = 0;        // Remaining cycles

    private:
        // Instruction lookup table and setup
        /**
        * @brief Function pointer to the instruction's operation.
        * 
        * Points to a member function of the CPU class that implements the 
        * specific behavior of the instruction.
        */
        struct INSTRUCTION {
            std::string name;                   // Name of the instruction
            byte (CPU::*operate)() = nullptr;   // Function pointer to the operation
            byte (CPU::*addrmode)() = nullptr;  // Function pointer to the addressing mode
            byte cycles = 0;                    // Number of cycles required for the instruction
        };

        std::vector<INSTRUCTION> lookup;

}
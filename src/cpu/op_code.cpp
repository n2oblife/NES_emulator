#include "cpu.hpp"

// Addressing Modes
byte CPU::IMP() {
    fetched = A;
    return 0;
}

byte CPU::IMM() {
    addr_abs = pc++;
    return 0;
}

bytes CPU::ZP0(){
    addr_abs = read(pc);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

// Op code
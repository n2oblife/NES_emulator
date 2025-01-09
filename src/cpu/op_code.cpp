#include "cpu.hpp"

// Addressing Modes
byte CPU::IMP() {
    fetched = a;
    return 0;
}

byte CPU::IMM() {
    addr_abs = pc++;
    return 0;
}

byte CPU::ZP0(){
    addr_abs = read(pc);
    pc++;
    /* mask for a zero page
    because 2 high bytes are page number
    and 2 lowest are page's offset
    */
    addr_abs &= 0x00FF;
    return 0;
}

byte CPU::ZPX(){
    addr_abs = (read(pc) + x);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

byte CPU::ZPY(){
    addr_abs = (read(pc) + y);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

byte CPU::ABS(){
    h_word page_offset = read(pc);
    pc++;
    h_word page_number = read(pc);
    pc++;
    addr_abs = (page_number << 8) | page_offset;
    return 0;
}

byte CPU::ABX(){
    h_word page_offset = read(pc);
    pc++;
    h_word page_number = read(pc);
    pc++;
    
    addr_abs = (page_number << 8) | page_offset;
    addr_abs += x;

    // check if needing of changing page and a loading clock cycle more
    if ((addr_abs & 0xFF00) != (page_number <<8))
        return 1;
    else
        return 0
    
    return 0;
}

// Op code
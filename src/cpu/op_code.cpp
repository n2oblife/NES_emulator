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

byte CPU::ABY(){
    h_word page_offset = read(pc);
    pc++;
    h_word page_number = read(pc);
    pc++;
    
    addr_abs = (page_number << 8) | page_offset;
    addr_abs += y;

    // check if needing of changing page and a loading clock cycle more
    if ((addr_abs & 0xFF00) != (page_number <<8))
        return 1;
    else
        return 0
    
    return 0;
}

byte CPU::IND(){
    h_word ptr_offset = read(pc);
    pc++;
    h_word ptr_number = read(pc);
    pc++;
    
    h_word ptr = (ptr_number<<8) | ptr_offset;

    if (ptr_offset = 0x00FF) // Simulate page boundary HW bug 
        addr_abs = (read(ptr & 0xFF00)<<8) | read(ptr+0);
    else // behave normally
        addr_abs = (read(ptr+1)<<8) | read(ptr+0);
    
    return 0;
}

byte CPU::IZX(){
    h_word addr = read(pc);
    pc++;

    h_word addr_offset = read((h_word)(addr + (h_word)(x)) & 0x00FF);
    h_word addr_page = read((h_word)(addr + (h_word)(x+1)) & 0x00FF);

    addr_abs = (addr_page<<8) | addr_offset;

    return 0;
}

byte CPU::IZY(){
    h_word addr = read(pc);
    pc++;

    h_word addr_offset = read(addr & 0x00FF);
    h_word addr_page = read((addr+1) & 0x00FF);

    addr_abs = (addr_page<<8) | addr_offset;
    addr_abs += y;

    if ((addr_abs & 0x00FF) != (addr_page<<8)) // in case of out of bound and needing one more clock cycle
        return 1;
    else
        return 0;
}

// branching and jumping only close to the current addr_abs
byte CPU::REL(){
    addr_rel = read(pc);
    pc++;

    // checking if signed number
    if (addr_rel & 0x80)
        addr_rel |= 0xFF00;
    return 0;
}

// Instructions

byte CPU::fetch(){
    if(!(lookup[opcode].addrmode == &CPU::IMP))
        fetched = read(addr_abs);
    return fetched;
}

byte CPU::AND(){
    fetch();
    a = a & fetched;
    setFlag(Z, a==0x00);
    setFlag(N, a==0x80);
    return 1;
}

byte CPU::BCS(){
    // TODO 40:36
}
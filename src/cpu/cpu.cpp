#include cpu.hpp

CPU::CPU() {
    // It is 16x16 entries. This gives 256 instructions. It is arranged to that the bottom
	// 4 bits of the instruction choose the column, and the top 4 bits choose the row.
    // The table is one big initialiser list of initialiser lists...
    lookup = {
		{ "BRK", &CPU::BRK, &CPU::IMM, 7 },{ "ORA", &CPU::ORA, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::ZP0, 3 },{ "ASL", &CPU::ASL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHP", &CPU::PHP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::IMM, 2 },{ "ASL", &CPU::ASL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABS, 4 },{ "ASL", &CPU::ASL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BPL", &CPU::BPL, &CPU::REL, 2 },{ "ORA", &CPU::ORA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ZPX, 4 },{ "ASL", &CPU::ASL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLC", &CPU::CLC, &CPU::IMP, 2 },{ "ORA", &CPU::ORA, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABX, 4 },{ "ASL", &CPU::ASL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "JSR", &CPU::JSR, &CPU::ABS, 6 },{ "AND", &CPU::AND, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "BIT", &CPU::BIT, &CPU::ZP0, 3 },{ "AND", &CPU::AND, &CPU::ZP0, 3 },{ "ROL", &CPU::ROL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLP", &CPU::PLP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::IMM, 2 },{ "ROL", &CPU::ROL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "BIT", &CPU::BIT, &CPU::ABS, 4 },{ "AND", &CPU::AND, &CPU::ABS, 4 },{ "ROL", &CPU::ROL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BMI", &CPU::BMI, &CPU::REL, 2 },{ "AND", &CPU::AND, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ZPX, 4 },{ "ROL", &CPU::ROL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEC", &CPU::SEC, &CPU::IMP, 2 },{ "AND", &CPU::AND, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ABX, 4 },{ "ROL", &CPU::ROL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTI", &CPU::RTI, &CPU::IMP, 6 },{ "EOR", &CPU::EOR, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::ZP0, 3 },{ "LSR", &CPU::LSR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHA", &CPU::PHA, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::IMM, 2 },{ "LSR", &CPU::LSR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::ABS, 3 },{ "EOR", &CPU::EOR, &CPU::ABS, 4 },{ "LSR", &CPU::LSR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVC", &CPU::BVC, &CPU::REL, 2 },{ "EOR", &CPU::EOR, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ZPX, 4 },{ "LSR", &CPU::LSR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLI", &CPU::CLI, &CPU::IMP, 2 },{ "EOR", &CPU::EOR, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ABX, 4 },{ "LSR", &CPU::LSR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTS", &CPU::RTS, &CPU::IMP, 6 },{ "ADC", &CPU::ADC, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ADC", &CPU::ADC, &CPU::ZP0, 3 },{ "ROR", &CPU::ROR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLA", &CPU::PLA, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::IMM, 2 },{ "ROR", &CPU::ROR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::IND, 5 },{ "ADC", &CPU::ADC, &CPU::ABS, 4 },{ "ROR", &CPU::ROR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVS", &CPU::BVS, &CPU::REL, 2 },{ "ADC", &CPU::ADC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ZPX, 4 },{ "ROR", &CPU::ROR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEI", &CPU::SEI, &CPU::IMP, 2 },{ "ADC", &CPU::ADC, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ABX, 4 },{ "ROR", &CPU::ROR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZP0, 3 },{ "STA", &CPU::STA, &CPU::ZP0, 3 },{ "STX", &CPU::STX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "DEY", &CPU::DEY, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "TXA", &CPU::TXA, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "STY", &CPU::STY, &CPU::ABS, 4 },{ "STA", &CPU::STA, &CPU::ABS, 4 },{ "STX", &CPU::STX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCC", &CPU::BCC, &CPU::REL, 2 },{ "STA", &CPU::STA, &CPU::IZY, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZPX, 4 },{ "STA", &CPU::STA, &CPU::ZPX, 4 },{ "STX", &CPU::STX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "TYA", &CPU::TYA, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::ABY, 5 },{ "TXS", &CPU::TXS, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::NOP, &CPU::IMP, 5 },{ "STA", &CPU::STA, &CPU::ABX, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::IMM, 2 },{ "LDA", &CPU::LDA, &CPU::IZX, 6 },{ "LDX", &CPU::LDX, &CPU::IMM, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "LDY", &CPU::LDY, &CPU::ZP0, 3 },{ "LDA", &CPU::LDA, &CPU::ZP0, 3 },{ "LDX", &CPU::LDX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "TAY", &CPU::TAY, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::IMM, 2 },{ "TAX", &CPU::TAX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "LDY", &CPU::LDY, &CPU::ABS, 4 },{ "LDA", &CPU::LDA, &CPU::ABS, 4 },{ "LDX", &CPU::LDX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCS", &CPU::BCS, &CPU::REL, 2 },{ "LDA", &CPU::LDA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "LDY", &CPU::LDY, &CPU::ZPX, 4 },{ "LDA", &CPU::LDA, &CPU::ZPX, 4 },{ "LDX", &CPU::LDX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "CLV", &CPU::CLV, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::ABY, 4 },{ "TSX", &CPU::TSX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "LDY", &CPU::LDY, &CPU::ABX, 4 },{ "LDA", &CPU::LDA, &CPU::ABX, 4 },{ "LDX", &CPU::LDX, &CPU::ABY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "CPY", &CPU::CPY, &CPU::IMM, 2 },{ "CMP", &CPU::CMP, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPY", &CPU::CPY, &CPU::ZP0, 3 },{ "CMP", &CPU::CMP, &CPU::ZP0, 3 },{ "DEC", &CPU::DEC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INY", &CPU::INY, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::IMM, 2 },{ "DEX", &CPU::DEX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "CPY", &CPU::CPY, &CPU::ABS, 4 },{ "CMP", &CPU::CMP, &CPU::ABS, 4 },{ "DEC", &CPU::DEC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BNE", &CPU::BNE, &CPU::REL, 2 },{ "CMP", &CPU::CMP, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ZPX, 4 },{ "DEC", &CPU::DEC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLD", &CPU::CLD, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ABX, 4 },{ "DEC", &CPU::DEC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "CPX", &CPU::CPX, &CPU::IMM, 2 },{ "SBC", &CPU::SBC, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPX", &CPU::CPX, &CPU::ZP0, 3 },{ "SBC", &CPU::SBC, &CPU::ZP0, 3 },{ "INC", &CPU::INC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INX", &CPU::INX, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::IMM, 2 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::SBC, &CPU::IMP, 2 },{ "CPX", &CPU::CPX, &CPU::ABS, 4 },{ "SBC", &CPU::SBC, &CPU::ABS, 4 },{ "INC", &CPU::INC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BEQ", &CPU::BEQ, &CPU::REL, 2 },{ "SBC", &CPU::SBC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ZPX, 4 },{ "INC", &CPU::INC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SED", &CPU::SED, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ABX, 4 },{ "INC", &CPU::INC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
	};
}

CPU::~CPU() {
    // TODO
}

CPU::read(h_word address) {
    return bus->read(address,false);
}

CPU::write(h_word address, byte data) {
    bus->write(address, data);
}

CPU::clock() {
    if (cycles == 0) {
        opcode = read(pc);
        pc++;
        // get number of cycles needed for the operation
        cycles = lookup[opcode].cycles;

        // get number of more cycles needed for the operation
        byte additional_cycle1 = (this->*lookup[opcode].addrmode)();
        byte additional_cycle2 = (this->*lookup[opcode].operate)();
        // add additional cycles depending on the operation's results
        cycles += (additional_cycle1 & additional_cycle2);
    }
    cycles--;
}

// Status Register Flags
void CPU::SetFlag(FLAGS6502 flag, bool setFlag) {
    if (setFlag)
        status |= flag;     // set flag
    else
        status &= ~flag;    // clear flag
}
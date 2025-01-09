#include "bus.hpp"

Bus::Bus() {
    // TODO change when implementing other devices
    // reset ram content, TODO change when array is no more
    for (auto &i : ram) i=0x00;

    // connect CPU to bus
    cpu.connectBus(this);
}

void Bus::write(h_word address, byte data) {
    if (address >= 0x0000 && address <= BUS_RANGE)
        ram[address] = data;
}

void Bus::read(h_word address, bool bReadOnly) {
    if (address >= 0x0000 && address <= BUS_RANGE)
        return ram[address];
    
    return 0x00; 
}


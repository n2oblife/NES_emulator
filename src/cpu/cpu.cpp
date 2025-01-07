#include cpu.hpp

CPU::CPU() {
    // TODO
}

CPU::~CPU() {
    // TODO
}

CPU::read(word a) {
    return bus->read(a,false);
}

CPU::write(word a, byte d) {
    bus->write(a, d);
}
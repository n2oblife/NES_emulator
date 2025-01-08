# NES Emulator

Welcome to the **NES Emulator** project! This is a personal implementation of an NES emulator inspired by the excellent work of [One Lone Coder](https://github.com/OneLoneCoder/olcNES) and his educational video playlist on building emulators.

The project aims to replicate the functionality of the Nintendo Entertainment System (NES), implementing its CPU, PPU (Picture Processing Unit), APU (Audio Processing Unit), and other key components to play classic NES games.

## Resources and Inspiration

This emulator is based on:
- [One Lone Coder's NES Emulator Playlist](https://www.youtube.com/playlist?list=PLrOv9FMX8xJHqMvSGB_9G9nZZ_4IgteYf)  
- [One Lone Coder's olcNES Repository](https://github.com/OneLoneCoder/olcNES)

## Features

- Full emulation of the 6502 CPU.
- Partial or complete implementation of NES PPU for graphics rendering.
- Memory management and mapping for NES cartridges (mapper support).
- Basic input support for NES controllers.
- Modular design for code clarity and extensibility.

## Project Structure

```
NES_emulator/
├── include/        # Header files for emulator components
├── src/            # Source files for emulator logic
├── roms/           # Directory for NES ROM files (not included in the repo)
├── build/          # Build directory for compiled binaries
├── README.md       # Project documentation
├── CMakeLists.txt  # Build configuration (CMake)
└── LICENSE         # License for this project
```

## Build Instructions

### Prerequisites

Make sure you have the following installed on your system:
- A C++ compiler supporting C++17 or later (e.g., GCC, Clang).
- [SDL2](https://www.libsdl.org/download-2.0.php) library for handling graphics, input, and audio.
- [CMake](https://cmake.org/) for build configuration.

### Building the Project

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd NES_emulator
   ```

2. Create a build directory and navigate into it:
   ```bash
   mkdir build
   cd build
   ```

3. Configure the project using CMake:
   ```bash
   cmake ..
   ```

4. Build the project:
   ```bash
   make
   ```

5. Run the emulator:
   ```bash
   ./nes_emulator <path-to-rom-file>
   ```

## Usage

To use the emulator, provide the path to an NES ROM file as an argument when running the executable:
```bash
./nes_emulator roms/example.nes
```

## Development Goals

- **Accuracy**: Aim to replicate the behavior of the original NES as closely as possible.
- **Scalability**: Modular design to allow for future extensions, such as additional mappers or debugging tools.
- **Performance**: Optimize for smooth gameplay and minimal latency.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

Special thanks to:
- [One Lone Coder](https://github.com/OneLoneCoder) for his educational resources and inspiration.
- The retro gaming community for keeping the NES alive and well.

## Disclaimer

This emulator is for educational purposes only. You must legally own any ROMs you use with this emulator.

# robot.bicycle

## Hardware
The following is a list of the electrical hardware used on the bicycle:

- Rear hub Motor Controller: [Accelnet Panel ADP-090-36](http://www.copleycontrols.com/motion/pdf/Accelnet_Panel_ADP.pdf)
- Steer Motor Controller: [Accelnet Micro Panel ACJ-055-18](http://www.copleycontrols.com/motion/pdf/Accelnet_Micro_Panel.pdf)
- Steer motor: [Teknic M-3441](http://www.teknic.com/files/product_info/N34_Industrial_Grade_Motors_v3.2.pdf)
- Rear hub motor: [Amped Bikes Rear Direct Drive](http://ampedbikes.com/kits.html)
- Wheel Encoders: [US Digital H5-50-N-D](http://usdigital.com/assets/general/119_h5_datasheet_1.pdf)
- Inertial Measurement Unit:
    - [Invensense MPU-6050](http://www.invensense.com/mems/gyro/mpu6050.html)
    - [Sparkfun Electronics Triple Axis Accelerometer & Gyro Breakout - MPU-6050](https://www.sparkfun.com/products/11028)
- Microcontroller:
    - [Olimex STM32 H-407](http://www.olimex.com/dev/pdf/ARM/ST/STM32-H107.pdf)
    - [STM32F407ZG Product page](http://www.st.com/internet/mcu/product/252136.jsp)
    - [STM32F407ZG Datasheet](http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/DM00037051.pdf)
    - [STM32F407ZG Reference Manual](http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/REFERENCE_MANUAL/DM00031020.pdf)
- Quadruple Differential Line Receivers: [TI AM26C32IN](http://www.ti.com/litv/pdf/slls104i)
- JTAG Cable: [Olimex ARM-USB-TINY-H](https://www.olimex.com/Products/ARM/JTAG/ARM-USB-TINY-H/)
- Wireless Radio: [XBee-PRO 802.15.4 extended-range module w/ RPSMA connector](http://www.digi.com/products/model?mid=3270)
- USB to RS232 Cable: [FTDI US232R-10](http://www.ftdichip.com/Support/Documents/DataSheets/Cables/DS_US232R-10_R-100-500.pdf)
- USB to Xbee board [XBee Explorer Dongle](https://www.sparkfun.com/products/9819)

## Wiring Notes
All connections between various components of the robot bicycle are documented
in a [Google Drive spreadsheet](https://docs.google.com/spreadsheet/ccc?key=0Asn6BMg-bB_EdHdMVVBqRTA4Q3IteWdEN1VJOXBDZHc).

## Resources
- Debugging and flashing software [OpenOCD](http://openocd.berlios.de/web/)
- Real time operating system [ChibiOS/RT](http://www.chibios.org/)

## Dependencies
The following libraries are necessary for building all (but not some) of the
executables in this project:
- Eigen 3
- LAPACKE
- FFTW
- Qt4
- Google Protocol Buffers for C++ and Python, and compiler

These can be found in the Ubuntu repositories as:

    libeigen3-dev liblapacke-dev libfftw3-dev libqt4-def libprotobuf-dev
    protobuf-compiler python-protobuf

This project also depends on Matlab.

## Toolchain
To compile the code that runs on the microcontroller, the following toolchain
is used:
[GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded)
The version used is 4.9-2014-q4-major.

As most computers will be running a 64-bit kernel, libraries for ia32/i386
architecture will need to be installed if not already. For recent versions of
Ubuntu, you can simply install the `gcc-multilib` package.

The CMake toolchain file in this project assumes the archive has been extracted
to $ENV{HOME}/toolchain. If it exists in a different location, the toolchain
file will need to be modified or alternative toolchain file must be provided.

To compile the code that runs on the host, a version of `gcc` that supports the
C++11 standard must be provided.

## Build System
This project uses a number of other projects which are included as submodules.
Some of the submodules (e.g. libbicycle) also contain their own submodules.
However, none of the nested submodules are necessary for building and recursive
initialization can be avoided. You can update the submodules with:

    $ git submodule update --init

which will also initialize the submodules if not yet done.

### Dataprocessing and Firmware
This project builds a number of different tools. To build, simply call `cmake`
to generate the project makefiles, and then call `make`. Here is an example:

    oliver@arcturus ~/repos/robot.bicycle$ mkdir build
    oliver@arcturus ~/repos/robot.bicycle$ cd build/
    oliver@arcturus ~/repos/robot.bicycle/build$ cmake ..
    oliver@arcturus ~/repos/robot.bicycle/build$ make -j4

However, a number of the project targets depend on Matlab and will only be
built if Matlab is installed and MATLAB_ROOT is defined in CMake. This can be
done using `ccmake` after the initial build tree is created to modify the cache
settings

    oliver@arcturus ~/repos/robot.bicycle/build$ ccmake .

or by passing it as an argument to `cmake`

    oliver@arcturus ~/repos/robot.bicycle/build$ cmake -DMATLAB_ROOT=/home/oliver/matlab/r2014 ..

If a toolchain is not specified, CMake will assume the target system to be the
same as the build host and preset some CMake variables which cannot be changed,
including the compilers. As cross-compilation is used to build the firmware,
the firmware CMake project is called as an external project and a file with
toolchain information is passed as a build configuration argument. See
`firmware/toolchain-arm-none-eabi.cmake` for an example toolchain file.

## Acknowledgements
This project has been supported in part by NSF Award #0928339.

This repository is forked from a project started by Dale Lukas Peterson. The
original repo can be found here: https://github.com/hazelnusse/robot.bicycle

A number of people have contributed this project including:
Dale Lukas Peterson, Derek Pell, Kenny Koller, Kenny Lyons, Bo Fu, Colin Smith,
Andrew Kickertz, Jason Moore, Ziqi Yin, and Gilbert Gede.

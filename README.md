# TM4Cware
A Linux development environment for TI's Tiva devices, distilled from [Christian Jaan's excellent blog post, "Getting Started with the TI Stellaris LaunchPad on Linux"](https://www.jann.cc/2012/12/11/getting_started_with_the_ti_stellaris_launchpad_on_linux.html).

## Setting up the Development Environment

### Install the necessary software
You will need to install ARM's GNU Embedded Toolchain, OpenOCD, and LM4Flash. The toolchain allows us to compile and link our embedded C code. OpenOCD--which stands for Open On-Chip Debugger--enables us to use the JTAG debugger on the Tiva board to flash the chip. And finally, LM4flash carries out the flashing operation.

**NOTE**: [...] indicates that you should replace the contents with your own values.

#### ARM's GNU Embedded Toolchain
1. Go to [ARM's webpage](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) to download the embedded toolchain.

2. Once downloaded, go to the directory containing the .tar.bz2 file, and extract the contents by executing:

	`tar xvjf [toolchain filename].tar.bz2` 

3. Copy output directory into your desired install directory using `cp [toolchain directory] [install directory path]`.

4. Add the toolchain to your path by executing:

	`export $PATH=[path-to-toolchain-directory/bin]:$PATH`

Alternatively, you can place this line in your `~/.bashrc` and then call `source ~/.bashrc`.

5. Check that the PATH variable was succesfully updated by calling `arm-none-eabi-gcc --version`. If version information about ARM's cross-compiler is printed, then you were successful.

#### LM4Flash

1. Download LM4Flash by executing:

	`git clone https://github.com/utzig/lm4tools.git`

2. Navigate to the `lm4tools/lm4flash` and build LM4Flash by executing:

	`make`

3. Copy the entire lm4tools directory into your install directory. 

4. Add the `lm4tools/lm4flash` directory to the path using the `export' command.

5. Execute `lm4flash -V` to confirm that the program was correctly built and the PATH variable was successfully updated.
	
#### OpenOCD

1. Download OpenOCD by executing:

	 `git clone git://git.code.sf.net/p/openocd/code openocd.git`

2. Navigate into the `openocd.git`, and build the software by executing:

```
./bootstrap
./configure --prefix=/usr --enable-maintainer-mode --enable-stlink --enable-ti-icdi
make
sudo make install
```

### Operating the Development Enviroment
To use the development enviroment:

**One-and-Done Step:** Build all the driver software by going to the root directory `TM4Cware` and executing `make`

1. Place your C code in the `proj` directory

2. Open the `Makefile` and update the MAIN variable with the name of your main C file.

3. Finally to build and flash, execute:

```
make clean
make
make flash
```

## Adding Custom Drivers to your Project

### Adding drivers in the `proj` Directory:
The easiest way to add drivers new drivers to your project is as follows:

1. Copy your C file and corresponding header file into the `proj` directory found in the root directory of your project.

2. Open the `proj/Makefile`, and navigate to the part of the file titled "Rules for building custom drivers".

3. Copy the example rule and paste it under this header.

4. Change the .o filename to your driver's filename.

5. Execute the following to build and flash your code (make sure you `#include` your driver code in your source code):

```
make clean
make
make flash
```

### Adding drivers in the `driverlib` Directory:
For more permanent drivers:

1. Copy your C file and corresponding header file into the `driverlib` directory found in the root directory of your project.

2. Open `driverlib/Makefile`, and navigate to the part of the file titled "Rules for building the driver library".

3. Copy one of the existing rules, and paste it at the end of the long list. Modify this pasted rule by renaming the .o file with the name of your driver. For example, if my driver files were named UART.c and UART.h, I would modify that line by changing `${COMPILER}/[some other driver].o` to `${COMPILER}/UART.o`.

4. Navigate to your root directory.

5. From there you can build your drivers by executing:

```
make clean
make
make flash
```
6. Now you can compile your project code with your drivers. Keep in mind that you must reference the header file in your code using `#include "driverlib/[driver].h"`.

## Adding Interrupt Handlers to your Project
If want to use hardware interrupts in your project, you will have to write interrupt handlers. Once you have written the handler, you must integrate it into the existing project code:

1. Open `proj/startup_gcc.c` and navigate to the section titled "Forward declaration of the custom interrupt handlers."

2. In this section, add your handler prototype.

3. Then navigate to the end of the file. Here you will find the default interrupt handler functions which act as placeholders for unimplemented interrupt handlers. For debugging purposes, these functions contain an empty `while (1)` loop.

4. Copy and paste one of the default handler functions you see there and replace the function name with that of your handler.

## Debugging and Troubleshooting Tips
1. If you get an "Undefined reference to" compilation error after adding a new driver, it's most likely because you haven't added a Makefile target to compile that driver.

2. If you see your code contains interrupts, and during runtime you can tell it has ceased typical operation, it's potentially stuck in a do-nothing loop of a default interrupt handler.

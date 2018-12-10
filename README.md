# TM4Cware
A Linux development environment for TI's Tiva devices, distilled from [Christian Jaan's excellent blog post, "Getting Started with the TI Stellaris LaunchPad on Linux"](https://www.jann.cc/2012/12/11/getting_started_with_the_ti_stellaris_launchpad_on_linux.html).

## Setting up the Development Environment

### Install the necessary software
You will need to install ARM's GNU Embedded Toolchain, OpenOCD, and LM4Flash. The toolchain allows us to compile and link our embedded C code. OpenOCD--which stands for Open On-Chip Debugger--enables us to use the JTAG debugger on the Tiva board to flash the chip. And finally, LM4flash carries out the flashing operation.

**NOTE**: [...] indicates that you should replace the contents with your own values.

#### ARM's GNU Embedded Toolchain
1. Go to [ARM's webpage](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) to download the embedded toolchain.

2. Once downloaded, go to the directory containing the .tar.bz2 file, and extract the contents by executing:

	tar xvjf [toolchain filename].tar.bz2 

3. Copy output directory into your desired install directory using `cp [toolchain directory] [install directory path]`.

4. Add the toolchain to your path by executing:

	export $PATH=[path-to-toolchain-directory/bin]:$PATH	

Alternatively, you can place this line in your '~/.bashrc' and then call `source ~/.bashrc`.

5. Check that the PATH variable was succesfully updated by calling `arm-none-eabi-gcc --version`. If version information about ARM's cross-compiler is printed, then you were successful.

#### LM4Flash

1. Download LM4Flash by executing:

	git clone https://github.com/utzig/lm4tools.git

2. Navigate to the `lm4tools/lm4flash` and build LM4Flash by executing:

	make

3. Copy the entire lm4tools directory into your install directory. 

4. Add the `lm4tools/lm4flash` directory to the path using the `export' command.

5. Execute `lm4flash -V` to confirm that the program was correctly built and the PATH variable was successfully updated.
	
#### OpenOCD

1. Download OpenOCD by executing:

	 git clone git://git.code.sf.net/p/openocd/code openocd.git 

2. Navigate into the `openocd.git`, and build the software by executing:

	./bootstrap
	./configure --prefix=/usr --enable-maintainer-mode --enable-stlink --enable-ti-icdi
	make
	sudo make install

### Operating the Development Enviroment
To use the development enviroment:

1. Place your C code in the proj directory

2. Open the `Makefile` and update the MAIN variable with the name of your main C file.

3. Finally to build and flash, execute:

	make clean
	make
	make flash


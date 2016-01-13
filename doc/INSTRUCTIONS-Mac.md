# Setup for Mac OS X

20151110 Damir Cavar


## How to set up the compiler environment on a Mac

I used OSX El Capitan 10.11.1 and did the following:

* Installed Xcode from the Appstore App
* Start Xcode and accept license
* It will install more components then
* Install MacPorts for El Capitan
* run the following commands in Terminal

	sudo port selfupdate
	sudo port install cmake
	sudo port install boost

Download the Mac OSX archive of Foma from:

https://bitbucket.org/mhulden/foma/downloads

Unpack it and *cd* into the resulting folder OSX and copy:

* fomalib.h and fomalibconf.h to /usr/local/include using this command:

	sudo cp include/foma*.h /usr/local/include/.

You can verify that the files are in place by using:

	ls /usr/local/include/foma*

You should see this:

	/usr/local/lib/libfoma.0.9.18.dylib	/usr/local/lib/libfoma.a

* copy the libraries to /usr/local/lib:

	sudo cp libfoma.* /usr/local/lib/.

Verify that the libraries are in place using this command:

	ls /usr/local/lib/libfoma*

You should see this output:

	/usr/local/lib/libfoma.0.9.18.dylib	/usr/local/lib/libfoma.a

* Copy the binaries to /usr/local/bin:

	sudo chmod +x cgflookup flookup foma
	sudo cp cgflookup flookup foma /usr/local/bin/.



## Build Foma on your Mac

If you want to be build your binaries/libraries of Foma on your Mac:
Download the tar archive from this page 

https://bitbucket.org/mhulden/foma/downloads . 

You do not want to doanload the OSX version, but the generic version instead. 
Type 'make' in order to compile and get all the executables and libraries. 
In case you get an error message like this libtool:   error: unrecognised 
option: '-static', edit the Makefile by changing the line # 41 from 
"AR = libtool" to "AR = /Applications/Xcode.app/Contents/Developer/Toolchains/
XcodeDefault.xctoolchain/usr/bin/libtool". Omit the quotation marks, of course. 
In case the Xcode path does not exist on your OS X, try finding where the 
Xcode''s version of libtool is located on your machine. If everything goes well, 
you should see cgflookup, flookup, foma, libfoma.a and libfoma.0.9.18.dylib appear in your 
build directory.




C Application RAW Software
=================================
Target System: RMOS3 V3.20
Memory Model : COMPACT
Languages    : C

Overview:
--------------

In this project, the XDB debugger is used together with RMOS3 V3.20. 


Project Layout:
-------------------------

This project is built from C++ modules.     
These objects are linked together with the startup file. 
The linker generates a loadable file in Intel 80386 object module format.
The CAD-UL Debug Preprocessor converts this loadable file into 
a symbol file for the XDB debugger.

    * The startup folder:
      This folder contains a reference to $(RMOS3)\lib\cadul\cstart.obj. 

    * The source folder:
      This folder contains the C (C**) modules

    * The LIB folder:
      This folder contains the RMOS3 - libraries and the GAT - file
	  or refernces to the RMOS3 product files.

    * The xdb folder:
      This folder contains the XDB startup file that initializes the XDB
      debugger for this application.

    * readme.txt
      The file you are currently reading.
 
    * linker.map
      This file specifies the linker build protocol and map file.


XDB Startup File:
-------------------------

    The XDB startup file "demo.xdb" is executed at the beginning of each
    invocation of XDB. It's main purpose is to define a number of toolbar
    buttons to simplify loading and starting. The following 
    buttons are generated:

    * Load:
      Use this button to load the hex record file containing the example
      code and data down to RMOS3 V3.20.
      Load the symbol information to the XDB debugger.

    * Start:
      This button runs the application from the entry point into
      the function main().




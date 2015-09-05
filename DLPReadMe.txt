READ ME FIle

*********************************************||*******************************************

Divyesh Bhagwanji Chudasama - A817622
Copyright © 2012

Discrete Logarithm in Finite Fields and Applications to Cryptography
- MSc Project

*********************************************||*******************************************

Integrated Development Environments

	i.	Visual Studio 2010
	ii.	Eclipse IDE (C/C++) with compilers Mingw and Cygwin

*********************************************||*******************************************

Executable Files

.exe files have been provided for direct testing, for:

	i.   ex_search
	ii.  BSGS
	iii. Pollard_Rho
	iv.  Pohlig_Hellman

Please see below for why .exe files haven't been provided for …_2n have not been provided.

*********************************************||*******************************************

Source Code Instructions

All relevant source codes are included in the folder `Source_Codes'.

The files(1):

	i.	ex_search.cpp
	ii.	BSGS.cpp
	iii.	Pollard_Rho.cpp
	iv.	Pohlig_Hellman.cpp

will all have to be compiled with the header file 'std_lib_facilities.h' included. There should be no problem compiling the files, however Pohlig_Hellman.cpp may throw an error regarding empty array size based on IDE used. For this case please use an alternative IDE, i.e. the error occurs in Visual Studio 2010 and so Eclipse IDE was used as an alternative. The files(1) will require INPUT arguments alpha, beta and n from the user.

The files(2):

	i.	ex_search_2n.cpp
	ii.	BSGS_2n.cpp
	iii.	Pollard_Rho_2n.cpp

will require the use of an additional library - the GaloisFieldLib.lib file. This can be included through the IDE's Project ---> 'Project Properties' tab. If the code does not compile after including the GaloisFieldLib.lib library, then do one of two things;

	i.	Either include the 'std_lib_facilities.h' header file manually and re-compile. If this still doesn't work then

	ii.	You will need to build the Galois Field Library as a `Static Library Project' from scratch and then include it as an additional library when compiling. For this the individual class and header files for the library have been included in the folder `GaloisFieldLibrary'. 

Files(2) need arguments to be changed from the source code accordingly. These arguments have been highlighted in the source code comments.

ALL PROGRAMS ARE EXECUTABLE!!!

*********************************************||*******************************************

Thesis

The relevant thesis files are included in the folder `Thesis'.

	i.	DLPThesisFinal2.pdf - The PDF version of Project Dissertation
	ii.	DLPThesisFinal2.tex - The ORIGINAL LaTeX version of the Project Dissertation
	iii.	luthesis.cls - The Loughborough University thesis theme file, used for the Dissertation

The pdf file can be viewed as normal, however to access the .tex and .cls files, the ENTIRE LaTeX package needs to be installed on the machine.

*********************************************||*******************************************

NOTE: For ease of use and compatibility it is advised to use Visual Studio 2010 and Eclipse IDE (C/C++), but not essential. If alternative IDE's are preferred then please feel free to use them/it.

ENJOY!


/*-----------------------------ex_search_2n.cpp---------------------------------

Implementation of the Exhaustive Search/Brute Force method for computing the
unique integer x such beta=alpha^x for the Discrete Logarithm Problem in the 
finite field GF(2^n), where n is the value of the field exponent, alpha and beta 
are Galois Field Elements and prim_poly is the primitive polynomial of the field.

Code written by Divyesh B Chudasama on 14/08/2012.
Copyright (c) 2012

-------------------------------ex_search_2n.cpp-------------------------------*/

/*--------------------------Exhaustive Search Method--------------------------*/

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include "std_lib_facilities.h"
#include "GaloisFieldElement.h"

using namespace galois;

unsigned int prim_poly[6] = {1, 0, 0, 1, 0, 1}; // Initialising primitive polynomial

GaloisField gf(5, prim_poly); // Creating Galois Field, where the integer value 
							  // represents the exponent n, i.e. 2^n. This value
							 // has to be changed according to the power

GaloisFieldElement alpha(&gf, 2); // Galois Field Element alpha...change value accoridingly
GaloisFieldElement beta(&gf, 3); // Galois Field element beta...change value accordingly

unsigned int o = (2^5)-1; // Exponent power corresponds to value assigned above
                          // when initialising Galois Field.

int ex_search(GaloisFieldElement alpha, GaloisFieldElement beta, unsigned int o){ // Function Exhaustive Search

vector<GaloisFieldElement> B1; // List

GaloisFieldElement b(&gf, 1);

unsigned int x;

for(x=0; x<o; x++){

       B1.push_back(b); // Adding entries to list B1
       b=(b*alpha);

		//std:cout <<"list of vector values: "<< b << std::endl;
        }

for(unsigned int y=0; y<B1.size(); y++){ 

        if(B1[y]==beta) // Comparing list value to find a match with beta

        return y;
}
}

/*-------------------------End of Exhaustive Search Method--------------------*/

/*--------------------------------Main Function-------------------------------*/

int main(){

	int ans;

	double time, timedif; // Double is used here to show small values

    time = (double) clock(); // Get the initial time
    time = time/CLOCKS_PER_SEC;  // Time in seconds 
    
    cout<<"\n Divyesh B Chudasama"
          "\n Copyright (c) 2012";
	
    cout<<"\n \n Implementation of the Exhaustive Search/Brute force method for" 
		"\n computing the unique integer x such that beta = alpha^x, for the" 
		"\n Discrete Logarithm Problem in the finite field GF(2^n), where n is" 
		"\n the value of the field exponent, alpha and beta are Galois Field" 
		"\n Elements and prim_poly is the primitive polynomial of the field. ";

    ans = ex_search(alpha, beta, 31); // Calling the function Exhaustive Search
	// the third input changes depending on the value of n in (2^n) - 1

    cout<<endl<<"\n \n The discrete logarithm x is: "<<ans<<endl<<endl;

	timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time; // Calling clock() 
    //function from start of program, subtracting its return value, then to 
    //obtain the final processor time in seconds, divide the value returned 
    //by clock() by CLOCK_PER_SEC
    
    cout<<"\n The processor time elapsed is: "<<timedif<<" seconds"<<endl<<endl;
  
	keep_window_open();

    return 0;
}

/*---------------------------End of Main Function-----------------------------*/








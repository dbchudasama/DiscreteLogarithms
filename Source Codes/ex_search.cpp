/*-----------------------------ex_search.cpp------------------------------------

Implementation of the Exhaustive Search/Brute force method for computing the 
unique integer x such that alpha^x=beta for the Discrete Logarithm Problem in 
GF(p), with cyclic group G, order n, generator alpha and group element beta.

Code written by Divyesh B Chudasama on 07/07/2012.
Copyright (c) 2012

-------------------------------ex_search.cpp----------------------------------*/

/*--------------------------Exhaustive Search Method--------------------------*/

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include "std_lib_facilities.h"

int ex_search(int alpha, int beta, int n){ // Function Exhaustive Search
    
int b = 1;
int x = 0; 
        
while (beta != b){
      b = b*alpha;
      x = x+ 1;
      }
      
      return x;
}

/*-------------------------End of Exhaustive Search Method--------------------*/

/*--------------------------------Main Function-------------------------------*/

int main(){
    
int alpha;
int beta;
int n;
int ans = 0;

    double time, timedif; // Double is used here to show small values

    time = (double) clock(); // Get the initial time
    time = time/CLOCKS_PER_SEC;  // Time in seconds 
    
    cout<<"\n Divyesh B Chudasama"
          "\n Copyright (c) 2012";

    cout<<"\n \n Implementation of the Exhaustive Search Method for computing the unique" 
          "\n integer x such that x = log_{alpha}beta for the Discrete" 
          "\n Logarithm Problem in GF(p), with cyclic group G, order n," 
          "\n generator alpha and group element beta. ";
             
    cout<<"\n \n Please enter a value for the generator `alpha': ";
    cin>>alpha;
    cout<<"\n Please enter a value for the element `beta': ";
    cin>>beta;
    cout<<"\n Please enter a value for the order `n' of the group:";
    cin>>n;
    
    ans = ex_search(alpha, beta, n); // Calling the function Exhaustive Search
    
    cout<<endl<<"\n The discrete logarithm x is: "<<ans<<endl<<endl;
    
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time; // Calling clock() 
    //function from start of program, subtracting its return value, then to 
    //obtain the final processor time in seconds, divide the value returned 
    //by clock() by CLOCK_PER_SEC
    
    cout<<"\n The processor time elapsed is: "<<timedif<<" seconds"<<endl<<endl;
    
    keep_window_open();
    
    return 0;
}       
    
/*---------------------------End of Main Function-----------------------------*/




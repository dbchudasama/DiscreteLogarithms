/*----------------------------------BSGS_2n.cpp---------------------------------

Implementation of Shanks' Baby-Step Giant Step Method for computing the unique 
integer x such that beta=alpha^x for the Discrete Logarithm Problem, in the 
finite field GF(2^n), where n is the value of the field exponent, alpha and beta 
are Galois Field Elements and prim_poly is the primitive polynomial of the field.

Code written by Divyesh B Chudasama on 25/08/2012.
Copyright (c) 2012

---------------------------------BSGS_2n.cpp----------------------------------*/

/*-----------------------------Variable Declarations--------------------------*/

#include "stdafx.h"
#include <stdio.h>
#include "std_lib_facilities.h"
#include <iostream>
#include <math.h>
#include <list>
#include <time.h>
#include "GaloisFieldElement.h"

using namespace galois;

unsigned int prim_poly[9] = {1, 0, 0, 0, 1, 1, 1, 0, 1}; // Initialising primitive polynomial

GaloisField gf(8, prim_poly); // Creating Galois Field, where the integer value 
							  // represents the exponent n, i.e. 2^n. This value
							 // has to be changed according to the power

GaloisFieldElement alpha(&gf, 2); // Galois Field Element alpha is fixed at value 2
GaloisFieldElement beta(&gf, 4); // Galois Field element beta...change value accordingly

/*********************************Functions************************************/

/*------------------------Multiplicative inverse in Z[n]----------------------*/

struct  euclidean { // Creating a structure called euclidean
        
        GaloisFieldElement a; // First element in struct 
        GaloisFieldElement b; // Second element in struct
        GaloisFieldElement c; // Third element in struct
        
};

euclidean extended_euclidean(GaloisFieldElement g, GaloisFieldElement h) // Function extended_euclidean that 
																		// will return type euclidean
{
    // Using the extended Euclidean algorithm to find integers x such and y such
    // that ax+ny = d, where d=gcd(g,h)

    GaloisFieldElement d,q,r;
    
    //Step 1.  
    if(h==0){ 
    d=g; // d<-g
    GaloisFieldElement x(&gf, 1); // x<-1
    GaloisFieldElement y(&gf, 0); // y<-0

	euclidean result= {d,x,y}; // In the struct euclidean, elements 1,2 and 3 
                             // are d,x and y respectively
    
    return result; // return result
}
    
    //Step 2.
	GaloisFieldElement x(&gf, 1); // x<-1
    GaloisFieldElement y(&gf, 0); // y<-0
    GaloisFieldElement x2(&gf, 1);// x2<-1
    GaloisFieldElement x1(&gf, 0); // x1<-0
    GaloisFieldElement y2(&gf, 0); // y2<-0
    GaloisFieldElement y1(&gf, 1); // y1<-1
   
    
    //Step 3.
    while (h>0) { // While h is NOT equal to 0 do the following:
          
          q=g/h; // q<-a/n
          r=g-(q*h); // r<-a-(q*n)
          x=x2-(q*x1); // x<-(x2-(q*x1))
          y=y2-(q*y1); // y<-y2-(q*y1)
          g=h; // a<-n
          h=r; // n<-r
          x2=x1; // x2<-x1
          x1=x; // x1<-x
          y2=y1; // y2<-y1
          y1=y; // y1<-y
    }
    
    //Step 4.
    d=g; // d<-g
    x=x2; // x<-x2
    y=y2; // y<-y2
    
    euclidean result={d,x,y}; // In the struct euclidean, elements 1,2 and 3 
                             // are d,x and y respectively
    
    return result; // return result
    
}   // This ends the extended Euclidean's algorithm

GaloisFieldElement mult_inv(GaloisFieldElement alpha, GaloisFieldElement n){
        
    // Making a new structure
    euclidean result_new = extended_euclidean(alpha,n); /*Calling the function 
                                                    extended_euclidean and 
                                                    assigning it as type 
                                                    euclidean*/ 
	
	if(!(result_new.a>1)) // If d (the first element in the struct) is greater 1 
                         //then a^(-1) mod n does not exist 

	return result_new.b; // Return x (the second element in the struct)
	
	else
	
	return result_new.a;
}   

/*---------------------End of Multiplicative inverse in Z[n]------------------*/

/*-----------------------Square and Multiply algorithm------------------------*/

GaloisFieldElement s_and_m(GaloisFieldElement alpha, int A){
    
    GaloisFieldElement b(&gf, 1);

    while(A>0) // While A>0 do:
    {
              if ((A-1)==0) // If A-1=0
              {
                              b=b*alpha; //b=b*alpha            
              }
              alpha=alpha*alpha; // alpha=alpha^2
             
              A=A/2; // A=[A/2]
    }
    return b; // Return b
    
}

/*------------------------End of Square and Multiply--------------------------*/ 

/*----------------------------Big-Step Giant-Step function--------------------*/

int bsgs(GaloisFieldElement alpha, GaloisFieldElement beta, unsigned int o){ 
    unsigned int m;
    unsigned int j;
	double f;
	GaloisFieldElement s(&gf, 1); // s is fixed to 1, GaloisFieldElement for conveniency
    GaloisFieldElement p = ((alpha^8)-s) + s; // p = ((2^n)-1) + 1 = (2^n), the value of the
										  // power is to be changed according to n
    unsigned int i;
    unsigned int x;
    
//Step 1.
f = pow(2.0, 8.0) - 1; // For conveniency values of type double have been used
					   // the second input is to be changed based on the value
					   // of n

m=int(sqrt(f))+1; //  Setting variable m to the square root of o then add 1


//Step 2.
vector<GaloisFieldElement> B1; // B1 is a list of entries of values of size m
vector<GaloisFieldElement> B2; // Second list for sorting, this is the same as B1

/*-----------------Baby Step: B=(j, (alpha^j)modp) for 0<=j<m----------------*/

for(j=0;j<m;j++)
{				
			
                 B1.push_back((alpha^j)); // Adds a new element at each
                 // iteration to list B1, where the second element from each 
                 // pair is (alpha^j). 

                 B2.push_back((alpha^j)); // Adding elements to list B2
              
                 }

sort(B2.begin(), B2.end()); // Sorting the second list 

//Step 3.
GaloisFieldElement c;

c = mult_inv(alpha,p); // Assigning integer c to multiplicative inverse of 
                        // (alpha^-1)modp


GaloisFieldElement e;

e = s_and_m(c,m); // Using square and multiply method to 
				  //calculate (alpha^-m)

/*------------------------------End of Baby Step-----------------------------*/

/*------Giant Steps: gamma=(beta)(alpha^(-m*i))modp, 2)gamma^i where i=1,2,3..... and then 
comparing the values with the BabyStep results to find a common value---------*/ 

//Step 4.
GaloisFieldElement gamma;

bool endwhile=true; 
int z;
i=0;
while(endwhile){
              
              gamma=s_and_m(e,i); // square and multiply for values (e^i)modp
              gamma=gamma*beta; // gamma = gamma*beta
              
              for(int l=0; l<m; l++){
                      
              if(B2[l]==gamma){ // Comparing values from B2 to gamma
                            endwhile=false; 
                            z=i; 
                            
              for (unsigned int delta=0; delta<m; delta++){
                  
                  if (B2[l]==B1[delta]){ // Comparing lists B2 and B1 to find 
                  // the common component in both
                  j=delta;
             
                  }
                            }
              }
              }
              gamma=0;
              i++;
              }
              
              x=(z*m)+j;  // x=(z*m)+j    
              
                         return x;
              
                         }                        

/*-----------------------------End of Giant Step------------------------------*/

/*-------------------End of Baby-Step Giant-Step Function---------------------*/

/*****************************End of Functions*********************************/

/*-------------------------------Main Function--------------------------------*/

int main(){

    double time, timedif; // Double is used here to show small values

    time = (double) clock(); // Get the intial time
    time = time/CLOCKS_PER_SEC;  // Time in seconds
    
    cout<<"\n Divyesh B Chudasama"
          "\n Copyright (c) 2012";
          
    cout<<"\n \n Implementation of Shanks' Baby-Step Giant-Step Method for computing" 
          "\n the unique integer x such that beta = alpha^x, for the" 
		  "\n Discrete Logarithm Problem in the finite field GF(2^n), where n is" 
		  "\n the value of the field exponent, alpha and beta are Galois Field" 
		  "\n Elements and prim_poly is the primitive polynomial of the field. ";

    int x=bsgs(alpha,beta,255); // Calling the function Baby-Step Giant-Step
							   // the last input is to be changed based on 
							   // (2^n)-1

    cout<<endl<<"\n The discrete logarithm x is: "<<x<<endl<<endl;
    
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time; // Calling clock() 
    //function from start of program, subtracting its return value, then to 
    //obtain the final processor time in seconds, divide the value returned 
    //by clock() by CLOCK_PER_SEC
    
    cout<<"\n The processor time elapsed is: "<<timedif<<" seconds"<<endl<<endl;
    
    keep_window_open();
    
    return 0;
}       
    
/*----------------------------End of Main Function----------------------------*/    













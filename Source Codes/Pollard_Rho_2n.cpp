/*---------------------------pollard_rho.cpp------------------------------------

Implementation of Pollard's Rho Method for computing the unique integer x such 
that beta=alpha^x for the Discrete Logarithm Problem, in the finite field GF(2^n),
where n is the value of the field exponent, alpha and beta are Galois Field 
Elements and prim_poly is the primitive polynomial of the field.

Code written by Divyesh B Chudasama on 26/08/2012.
Copyright (c) 2012

-----------------------------pollard_rho.cpp----------------------------------*/

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include "std_lib_facilities.h"
#include "GaloisFieldElement.h"

using namespace galois;

unsigned int prim_poly[7] = {1, 0, 0, 0, 0, 1, 1}; // Initialising primitive polynomial

GaloisField gf(6, prim_poly); // Creating Galois Field, where the integer value 
							  // represents the exponent n, i.e. 2^n. This value
							 // has to be changed according to the power

GaloisFieldElement alpha(&gf, 2); // Galois Field Element alpha is fixed at value 2
GaloisFieldElement beta(&gf, 4); // Galois Field element beta...change value accordingly

unsigned int O = int(pow(2.0, 6.0))-1; // Exponent power corresponds to value assigned above
									   // when initialising Galois Field.

/********************************Functions*************************************/

/*--------------------Set functions for S1, S2 and S3-------------------------*/

GaloisFieldElement f(GaloisFieldElement x){// Function f(x_i) for sequence of group elements x_(i+1) where,
             // x=(x_i)
    
    if(x==0){ // If x_i is an element of S2
                x=(x*x);// x_(i+1)=((x_i)^2)
                }
                
                else if(x==1){ // If x_i is an element of S3
                     x=(alpha*x); // x_(i+1)=(alpha*(x_i))
                     }
                     
                else if(x==2){ // If x_i is an element of S1
                     x=(beta*x); // x_(i+1)=(beta*(x_i))
                     }
                     return x;
                     }

GaloisFieldElement g(GaloisFieldElement x, GaloisFieldElement a){ // Function g(x_i,a_i) for sequence of integers a_(i+1)
                     // where x=(x_i) and a=(a_i)/a_(i+1)
    
	GaloisFieldElement c(&gf, 1); // c=1, for use with x==1 condition
	GaloisFieldElement f(&gf, 2); // f=2, for use with x==0 condition

    if(x==0){ // If x_i is an element of S2
               a=(f*a); // a_(i+1)=(2*(a_i))
               }
               
               else if(x==1){ // If x_i is an element of S3
                    a=(a+c); // a_(i+1)=(a_i)+1
                    }
                    
               else if(x==2){ // If x_i is an element of S1
                    a=a; // a_(i+1)=a_i
                    } 
                    return a;      
                    }
                    
GaloisFieldElement h(GaloisFieldElement x, GaloisFieldElement b){ // Function h(x_i,b_i) for sequence of integers b_(i+1)
                     // where x=(x_i) and b=(b_i)/b_(b+1)
    
	GaloisFieldElement e(&gf, 1); // e=1, for use with x==2 condition
	GaloisFieldElement q(&gf, 2); // q=2, for use with x==0 condition

    if(x==0){ // If x_i is an element of S2
               b=(q*b); // b_(i+1)=(2*(b_i))
               }
               
               else if(x==1){ // If x_i is an element of S3
                    b=b; // b_(i+1)=(b_i)
                    }
                    
               else if(x==2){ // If x_i is an element of S1
                    b=(b+e); // b_(i+1)=(b_i)+1
                    }
                    return b;
                    }
                                   
/*--------------------End of Set functions for S1, S2 and S3-----------------*/

/*-------------------------Pollard's Rho function-----------------------------*/

GaloisFieldElement pollard_rho(GaloisFieldElement alpha, GaloisFieldElement beta, unsigned int O){ // Pollard's rho method function
    
    unsigned int i;
    
    vector<GaloisFieldElement> x; // Vector list x
    vector<GaloisFieldElement> a; // Vector list a
    vector<GaloisFieldElement> b; // Vector list b
    
	GaloisFieldElement w(&gf, 1); // w=1, w is equivalent to x_0
	GaloisFieldElement u(&gf, 0); // u=0, u is equivalent to a_0
	GaloisFieldElement p(&gf, 0); // p=0, p is equivalent to b_0

    x.push_back(w); // Adding entry x_0=1 to the vector list x
    a.push_back(u); // Adding entry a_0=0 to the vector list a
    b.push_back(p); // Adding entry b_0=0 to the vector list b
    
    GaloisFieldElement X;
    GaloisFieldElement A;
    GaloisFieldElement B;
    GaloisFieldElement r;
    GaloisFieldElement c;
    GaloisFieldElement d;
    GaloisFieldElement e;
    
	GaloisFieldElement z(&gf, 0); // z=0
    
	GaloisFieldElement t;
	GaloisFieldElement T(&gf, 1); // T=1
	
	t = (alpha^6) - T; // t = (2^n) - 1. The exponent will change based on 
					   // the value of n. Alpha, and T have been used for 
					   // efficieny and convenience.

    for(i=1; i<O; i++){
    // Computing the values x_i, a_i and b_i using the quantities of x_(i-1),
    // a_(i-1) and b(i-1) computed previously from functions f, g and h         
             
             c=f(x[i-1]); // c=f(x_(i-1))
             
             x.push_back(c); // Each iterative value of c is added to vector 
             // list x
             
             d=(g(x[i-1], a[i-1])); // d=g(x_(i-1),a_(i-1))
             a.push_back(d); // Each iterative value of d is added to vector 
             // list a
             
             e=(h(x[i-1], b[i-1])); // e=h(x_(i-1),b(i-1))
             b.push_back(e); // Each iterative value of e is added to vector 
             // list b

             }
             
    for(i=1; i<O; i++){
    // Now computing x_(2i), a_(2i) and b_(2i)
            
             if(x[i]==x[2*i]){
            
             X=f(f(x[(2*i)-2])); // X=x_(2i)
             
             A=(g(f(x[(2*i)-2]), g(x[(2*i)-2], a[(2*i)-2]))); // A=a_(2i)
        
             B=(h(f(x[(2*i)-2]), h(x[(2*i)-2], b[(2*i)-2]))); // B=b_(2i)
             
             break;
             }
             }
    for(i=1; i<O; i++){     
       if( x[i] == X ){ // If x_i = x_(2i)
                   
                r=(b[i]-B); // r=((b_i)-b_(2i))
                
       if(r==0){ // If r=0
            cout<<"\n \n `Pollard's rho method failed to find unique integer x as r=0!"
                  "\n No Discrete Logarithm x exists for the primitive polynomial!'"<<endl;
            return r;
            break; // Terminate algorithm with failure
            }

            else{
                  
                z=(a[i]-A)/(B-b[i]); // z=(((a_i)-a_(2i))/(b_(2i)-b_i))
              
                 if(z<0){ // If z is -ve
                         z=(t+z); // then ((2^n)-1)+z
                         }
                         }
                 return z;
                 break;
                 }
                 
}
}

/*-------------------------End of Pollard's Rho function----------------------*/

/*****************************End of Functions*********************************/

/*-------------------------------Main function--------------------------------*/

int main(){
    
    double time, timedif; // Double is used here to show small values

    time = (double) clock(); // Get the intial time
    time = time/CLOCKS_PER_SEC;  // Time in seconds 
    
    cout<<"\n Divyesh B Chudasama"
          "\n Copyright (c) 2012";
    
    cout<<"\n \n Implementation of Pollard's Rho Method for computing" 
          "\n the unique integer x such that beta = alpha^x, for the" 
		  "\n Discrete Logarithm Problem in the finite field GF(2^n), where n is" 
		  "\n the value of the field exponent, alpha and beta are Galois Field" 
		  "\n Elements and prim_poly is the primitive polynomial of the field. ";
       
    GaloisFieldElement y;
	y = pollard_rho(alpha, beta, 63); //Calling the function Pollard Rho
									 //  the last input is to be changed based on 
							         // (2^n)-1

    cout<<endl<<"\n The discrete logarithm x is: "<<y<<endl<<endl;
    
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time; // Calling clock() 
    //function from start of program, subtracting its return value, then to 
    //obtain the final processor time in seconds, divide the value returned 
    //by clock() by CLOCK_PER_SEC
    
    cout<<"\n The processor time elapsed is: "<<timedif<<" seconds"<<endl<<endl;
    
    keep_window_open();
    
    return 0;
}       

/*---------------------------End of Main function-----------------------------*/









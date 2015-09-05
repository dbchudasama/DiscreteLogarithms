/*---------------------------pollard_rho.cpp------------------------------------

Implementation of Pollard's Rho Method for computing the unique integer x such 
that x = log_{alpha}(beta) for the Discrete Logarithm Problem in GF(p), with 
cyclic group G, order n, generator alpha and group element beta.

Code written by Divyesh B Chudasama on 09/07/2012.
Copyright (c) 2012

-----------------------------pollard_rho.cpp----------------------------------*/

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include "std_lib_facilities.h"

/********************************Functions*************************************/

/*--------------------Set functions for S1, S2 and S3-------------------------*/

int alpha;
int beta;
int n;

int f(int x){// Function f(x_i) for sequence of group elements x_(i+1) where,
             // x=(x_i)
    
    if(x%3==0){ // If x_i is an element of S2
                x=(x*x)%n;// x_(i+1)=((x_i)^2)modn
                }
                
                else if(x%3==1){ // If x_i is an element of S3
                     x=(alpha*x)%n; // x_(i+1)=(alpha*(x_i))modn
                     }
                     
                else if(x%3==2){ // If x_i is an element of S1
                     x=(beta*x)%n; // x_(i+1)=(beta*(x_i))modn
                     }
                     return x;
                     }

int g(int x, int a){ // Function g(x_i,a_i) for sequence of integers a_(i+1)
                     // where x=(x_i) and a=(a_i)/a_(i+1)
    
    if(x%3==0){ // If x_i is an element of S2
               a=(2*a); // a_(i+1)=(2*(a_i))
               }
               
               else if(x%3==1){ // If x_i is an element of S3
                    a=(a+1); // a_(i+1)=(a_i)+1
                    }
                    
               else if(x%3==2){ // If x_i is an element of S1
                    a=a; // a_(i+1)=a_i
                    } 
                    return a;      
                    }
                    
int h(int x, int b){ // Function h(x_i,b_i) for sequence of integers b_(i+1)
                     // where x=(x_i) and b=(b_i)/b_(b+1)
    
    if(x%3==0){ // If x_i is an element of S2
               b=(2*b); // b_(i+1)=(2*(b_i))
               }
               
               else if(x%3==1){ // If x_i is an element of S3
                    b=b; // b_(i+1)=(b_i)
                    }
                    
               else if(x%3==2){ // If x_i is an element of S1
                    b=(b+1); // b_(i+1)=(b_i)+1
                    }
                    return b;
                    }
                                   
/*--------------------End of Set functions for S1, S2 and S3-----------------*/

/*-------------------------Pollard's Rho function-----------------------------*/

int pollard_rho(int alpha, int beta, int n){ // Pollard's rho method function
    
    int i;
    
    vector<int> x; // Vector list x
    vector<int> a; // Vector list a
    vector<int> b; // Vector list b
    
    x.push_back(1); // Adding entry x_0=1 to the vector list x
    a.push_back(0); // Adding entry a_0=0 to the vector list a
    b.push_back(0); // Adding entry b_0=0 to the vector list b
    
    int X;
    int A;
    int B;
    int r;
    int c;
    int d;
    int e;
    int z = 0;
    int p=n-1;
    
    
    for(i=1; i<n; i++){
    // Computing the values x_i, a_i and b_i using the quantities of x_(i-1),
    // a_(i-1) and b(i-1) computed previously from functions f, g and h         
             
             c=f(x[i-1]); // c=f(x_(i-1))
             
             x.push_back(c); // Each iterative value of c is added to vector 
             // list x
             
             d=(g(x[i-1], a[i-1]))%p; // d=g(x_(i-1),a_(i-1))
             a.push_back(d); // Each iterative value of d is added to vector 
             // list a
             
             e=(h(x[i-1], b[i-1]))%p; // e=h(x_(i-1),b(i-1))
             b.push_back(e); // Each iterative value of e is added to vector 
             // list b

             }
             
    for(i=1; i<n; i++){
    // Now computing x_(2i), a_(2i) and b_(2i)
            
             if(x[i]==x[2*i]){
            
             X=f(f(x[(2*i)-2])); // X=x_(2i)
             
             A=(g(f(x[(2*i)-2]), g(x[(2*i)-2], a[(2*i)-2])))%p; // A=a_(2i)
        
             B=(h(f(x[(2*i)-2]), h(x[(2*i)-2], b[(2*i)-2])))%p; // B=b_(2i)
             
             break;
             }
             }
    for(i=1; i<n; i++){     
       if( x[i] == X ){ // If x_i = x_(2i)
                   
                r=(b[i]-B); // r=((b_i)-b_(2i))
                
       if(r==0){ // If r=0
            cout<<"\n \n 'Pollard's rho method failed to find unique integer x as r=0!"
                  "\n No Discrete Logarithm x for the above values!'"<<endl;
            return r;
            break; // Terminate algorithm with failure
            }

            else{
                  
                 z=(a[i]-A)/(B-b[i]); // z=(((a_i)-a_(2i))/(b_(2i)-b_i))
                 z= z%p;
                 if(z<0){ // If z is -ve
                         z=(p+z); // then mod(n-1)+z
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
    
    cout<<"\n \n Implementation of Pollard's Rho Method for computing the unique" 
          "\n integer x such that x = log_{alpha}beta for the Discrete" 
          "\n Logarithm Problem in GF(p), with cyclic group G, order n," 
          "\n generator alpha and group element beta. ";
              
    cout<<"\n \n Please enter a value for the generator `alpha': ";
    cin>>alpha;
    cout<<"\n Please enter a value for the element `beta': ";
    cin>>beta;
    cout<<"\n Please enter a value for the order `n' of the group:";
    cin>>n;
    
    int y=pollard_rho(alpha, beta, n); //Calling the function Pollard Rho
    
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







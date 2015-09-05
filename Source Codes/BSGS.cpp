/*----------------------------------BSGS.cpp------------------------------------

Implementation of Shanks' Baby-Step Giant Step Method for computing the unique 
integer x such that x = log_{alpha}(beta) for the Discrete Logarithm Problem,
in GF(p), with cyclic group G, order n, generator alpha and group element beta.

Code written by Divyesh B Chudasama on 17/06/2012.
Copyright (c) 2012

---------------------------------BSGS.cpp-------------------------------------*/

/*-----------------------------Variable Declarations--------------------------*/

#include <stdio.h>
#include "std_lib_facilities.h"
#include <iostream>
#include <math.h>
#include <list>
#include <time.h>

using namespace std;

/*********************************Functions************************************/

/*------------------------Multiplicative inverse in Z[n]----------------------*/

struct  euclidean { // Creating a structure called euclidean
        
        int a; // First element in struct 
        int b; // Second element in struct
        int c; // Third element in struct
        
};

euclidean extended_euclidean(int a, int n) // Function extended_euclidean that 
                                           // will return type euclidean
{
    // Using the extended Euclidean algorithm to find integers x such and y such
    // that ax+ny = d, where d=gcd(a,n)

    int x,y,d,q,r;
    
    //Step 1.  
    if(n==0){ 
    d=a; // d<-a
    x=1; // x<-1
    y=0; // y<-0
    
    euclidean result={d,x,y}; // In the struct euclidean, elements 1,2 and 3 
                             // are d,x and y respectively
    
    return result; // return result
}
    
    //Step 2.
    int x2=1; // x2<-1
    int x1=0; // x1<-0
    int y2=0; // y2<-0
    int y1=1; // y1<-1
   
    
    //Step 3.
    while (n>0) { // While n>0 do the following:
          
          q=a/n; // q<-a/n
          r=a-(q*n); // r<-a-(q*n)
          x =(x2-(q*x1)); // x<-(x2-(q*x1))
          y=y2-(q*y1); // y<-y2-(q*y1)
          a=n; // a<-n
          n=r; // n<-r
          x2=x1; // x2<-x1
          x1=x; // x1<-x
          y2=y1; // y2<-y1
          y1=y; // y1<-y
    }
    
    //Step 4.
    d=a; // d<-a
    x=x2; // x<-x2
    y=y2; // y<-y2
    
    euclidean result={d,x,y}; // In the struct euclidean, elements 1,2 and 3 
                             // are d,x and y respectively
    
    return result; // return result
    
}   // This ends the extended Euclidean's algorithm

int mult_inv(int alpha,int n){
        
    // Making a new structure
    euclidean result_new = extended_euclidean(alpha,n); /*Calling the function 
                                                    extended_euclidean and 
                                                    assigning it as type 
                                                    euclidean*/ 
    
    if(!(result_new.a>1)){ // If d (the first element in the struct) is greater 1 
                           //then a^(-1) mod n does not exist 

	return result_new.b; // Return x (the second element in the struct)

	} 
	
	else {
    
	cout<<"\n \n Multiplicative inverse cannot be computed, please check input!"<<endl;

    return result_new.a;    
}
}

/*---------------------End of Multiplicative inverse in Z[n]------------------*/

/*-----------------------Square and Multiply algorithm------------------------*/

int s_and_m(int alpha, int A, int n){
    
    int b=1;
    
    while(A>0) // While A>0 do:
    {
              if ((A-1)%2==0) // If A=1{mod2}
              {
                              b=b*alpha; //b=b*alpha
                              b=b%n; // b=(b*alpha)modn
              }
              alpha=alpha*alpha; // alpha=alpha^2
              alpha=alpha%n; // alpha=alpha^2(modn)
              A=int(A/2); // A=[A/2]
    }
    return b; // Return b
    
}

/*------------------------End of Square and Multiply--------------------------*/ 

/*----------------------------Big-Step Giant-Step function--------------------*/

int bsgs(int alpha, int beta, int n){ 
    int m;
    int j;
    int p=n+1; 
    int i;
    int x;
    
//Step 1.
m=int(sqrt(n))+1; //  Setting variable m to the square root of n then add 1

//Step 2.
vector<int> B1; // B1 is a list of entries of values of size m
vector<int> B2; // Second list for sorting, this is the same as B1

/*-----------------Baby Step: B=(j, (alpha^j)modp) for 0<=j<m----------------*/

double a;
a = double(alpha);
for(j=0;j<m;j++)
{				
			
                 B1.push_back((int(pow(a, j)))%p); // Adds a new element at each
                 // iteration to list B1, where the second element from each 
                 // pair is (alpha^j)modp. 
                 B2.push_back((int(pow(a, j)))%p); // Adding elements to list B2
              
                 }

sort(B2.begin(), B2.end()); // Sorting the second list 

//Step 3.
int c=mult_inv(alpha,p); // Assigning integer c to multiplicative inverse of 
                        // (alpha^-1)modp

double e=double(s_and_m(c,m,p)); // Using square and multiply method to 
//calculate (alpha^-m)modp.

/*------------------------------End of Baby Step-----------------------------*/

/*------Giant Steps: gamma=(beta)(alpha^(-m*i))modp, 2)gamma^i where i=1,2,3..... and then 
comparing the values with the BabyStep results to find a common value---------*/ 

//Step 4.
int gamma;

bool endwhile=true; 
int z;
i=0;
while(endwhile){
              
              gamma=s_and_m(e,i,p); // square and multiply for values (e^i)modp
              gamma=gamma*beta; // gamma = gamma*beta
              gamma=gamma%p; // gamma = (gamma)modp
              
              for(int l=0; l<m; l++){
                      
              if(B2[l]==gamma){ // Comparing values from B2 to gamma
                            endwhile=false; 
                            z=i; 
                            
              for (int delta=0; delta<m; delta++){
                  
                  if (B2[l]==B1[delta]){ // Comparing lists B2 and B1 to find 
                  // the common component in both
                  j=delta;
                  //cout << j << endl;
                  }
                            }
              }
              }
              gamma=0;
              i++;
              }
              //return z;
              
              x=(z*m)+j;  // x=(z*m)+j    
              
                         return x;
              
                         }                        

/*-----------------------------End of Giant Step------------------------------*/

/*-------------------End of Baby-Step Giant-Step Function---------------------*/

/*****************************End of Functions*********************************/

/*-------------------------------Main Function--------------------------------*/
int main(){
    
int alpha;
int beta;
int n;

    double time, timedif; // Double is used here to show small values

    time = (double) clock(); // Get the intial time
    time = time/CLOCKS_PER_SEC;  // Time in seconds 
    
    cout<<"\n Divyesh B Chudasama"
          "\n Copyright (c) 2012";
          
    cout<<"\n \n Implementation of Shanks' Baby-Step Giant-Step Method for computing" 
          "\n the unique integer x such that x = log_{alpha}beta for the" 
          "\n Discrete Logarithm Problem in GF(p), with cyclic group G, order n," 
          "\n generator alpha and group element beta. ";
             
    cout<<"\n \n Please enter a value for the generator `alpha': ";
    cin>>alpha;
    cout<<"\n Please enter a value for the element `beta': ";
    cin>>beta;
    cout<<"\n Please enter a value for the order `n' of the group:";
    cin>>n;
    
    int x=bsgs(alpha,beta,n); // Calling the function Baby-Step Giant-Step
    
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

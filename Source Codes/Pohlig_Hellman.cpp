/*----------------------------Pohlig_Hellman.cpp--------------------------------

Implementation of the Pohlig-Hellman Algorithm for computing the unique integer 
x such that x = log_{alpha}(beta) for the Discrete Logarithm Problem,in GF(p), 
with cyclic group G, order n, generator alpha and group element beta.

Code written by Divyesh B Chudasama on 12/08/2012.
Copyright (c) 2012

---------------------------------Pohlig_Hellman.cpp---------------------------*/

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "std_lib_facilities.h"

/*********************************Functions************************************/

struct ph{ // Structure ph
       vector<int> a; // First element in structure
       vector<int> b; // Second element in structure
       };
       
struct  euclidean { // Creating another structure called euclidean
        
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
    
    if(!(result_new.a>1)) // If d (the first element in the struct) is greater 1 
                         //then a^(-1) mod n does not exist 
    return result_new.b; // Return x (the second element in the struct)
    
    else 
    
    return result_new.a; 
}

/*--------------------------Greatest Common Divisor---------------------------*/

int gcd(int a,int b) { // Function gcd for use in Chinese Remainde Theorem
    if(a==0)
    return b;
    if(b==0)
    return a;
    if(a>b)
    return(gcd(a%b,b)); // Greatest Common Divisor (a mod(b), b)
    if(b>a)
    return(gcd(b%a,a)); // Greatest Common Divisor (b mod(a), a)
    }
    
/*----------------------End of Greatest Common Divisor------------------------*/

/*----------------------------Inverse Function--------------------------------*/    
    
int inverse(int a,int b) {// Function inverse for use in CRT
                 // here a-->modulus,b-->element 
    int gcd,x=0,y=1,k=a;
    int u=1, v=0, m, n, q, r;
    gcd = b;
    while(a!=0){ // a is NOT equal to 0
           q=gcd/a; // q<-gcd/a
           r=gcd%a; // r<-gcd mod a
           m=x-u*q; // m<-x-(u*q)
           n=y-v*q; // n<-y-(v*q)
           gcd=a; // gcd<-a
           a=r; // a<-r
           x=u; // x<-u
           y=v; // y<-u
           u=m; // u<-m
           v=n; // v<-n
           }
           while(y<0){
                 y=k+y;
           }return y; // Give back value of y
}

/*-------------------------End of Inverse function----------------------------*/

/*--------------------------Chinese Remainder Theorem-------------------------*/

int ChineseTheorem(vector<int> x, vector<int> Z){ // Function Chinese Remainder 
                                                  // Theorem
int k = x.size(); // k is the size of vector x
int m[k],a[k],i,n=1; // Initialising array's m and a of size k i.e equivalent to
                     // the size of vector x and integers i and n. Assigning n
                     // to value 1.

for(i=0;i<k;i++){ // i iterates from 0 to (vector size x)-1
                 a[i] = Z[i]; // Assigning array a to vector Z
                 m[i] = x[i]; // Assigning array m to vector x 
                 if(i>0){
                         if(gcd(m[i-1],m[i])!=1){ // If the Greastest Common
                         //Divisor of (m[i-1],m[i]) is NOT equal to 1
                         return 1;
                         }
                         }
                         n=n*m[i]; // Every iterative value of array m is
                         // multiplied by n then assigned to n
                         }
                         int sol=0,B=1;
                         for(i=0;i<k;i++){
                         B=a[i]*(n/m[i])*inverse(m[i],n/m[i]); // Integer B is 
                         // equivalent to array a multiplied by (n divided by 
                         //array m) multiplied by the inverse of (array m and n
                         //divided by array m), for which i iterates from 0 to 
                         //vector size x
                         sol=sol+B; // sol = sol add the value of B
                         }sol=sol%n; // sol = sol mod n
return sol;
}

/*---------------------End of Chinese Remainder Theorem-----------------------*/

/*-------------------------Square and Multiply algorithm----------------------*/
       
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

/*---------------------End of Square and Multiply algorithm-------------------*/

/*--------------------------Prime Factorisation-------------------------------*/

ph prime_fact(int n) {// Function prime factorisation part of structure ph

int i = 2;
int count;
vector<int> q, c;
 
while (n > 1 && i <= n) { // n has to be both greater then 1 AND less than and 
                         // equal to i. && Boolean operator AND, hence will only
                         // work if both conditions on left and right hand sides
                         // are satisfied
  
  if (n % i == 0){ // If n mod i is NOT equal to 0
        
        q.push_back(i); // Adding i values to vector q
        count = 1;
        n = n / i; // n = n divided by i
        while (n % i == 0) { // n mod i is NOT equal to 0
              count = count + 1;
              n = n / i;
              }
        
        c.push_back(count); // Adding count values to vector c
        }
  i = i + 1;
  }
  ph pH = {q,c}; // Storing vectors q and c in pH
  return pH; // Give back pH
}

/*-------------------------End of Prime Factorisation-------------------------*/

/*-------------------------Pohlig-Hellman algorithm---------------------------*/

int PHellman(int a, int b, int n){
    
    vector<int> g, l, alp, A, B;
    int z = 0, q = 0, e = 0, delta, gamma, alpha, beta, r;

    int p=n+1;
    ph x=prime_fact(n); // Calling function prime factorisation and factorising 
                        // for prime factors of the value of order n
   
    for(int k = 0; k<x.a.size();k++){ // k goes from 0 to value of (prime
                                      // facotorisation - 1)
    
    q = x.a[k]; // q = values of primes factors a[k]
    e= x.b[k]; // e = exponential values of prime factors b[k]
    B.push_back(int(pow((double)x.a[k], x.b[k]))); // Calculating q^e and adding
                                                   // to vector B
    l.push_back(0); // l_[-1]=0
    gamma=1;
   
    for(int j =0; j<e;j++){ // j goes from 0 to (maximum exponent value - 1)
   
    alpha=s_and_m(a, n/q, p); // Square and multiply method for (a^(n/q))
    // then equating to alpha
    gamma=gamma*(s_and_m(a, (l[j]*((int)(pow((double) q, j-1)))), p));
    // Square and multiply method for gamma*a^((l_[j-1])*(q^[j-1])) then mod p
    // and assigning to gamma
    gamma=gamma%p; // Gamma = gamma mod(p)
    
    for(int i=0;i<=x.a[k]-1;i++){ // i goes from 0 to q-1
   
    z=s_and_m(a, ((n*i)/x.a[k]), p); // Square and multiply method for a^((n*i)/q)
                                     // then mod p and assigning to z
   
    g.push_back(z); // Adding z value to vector g
}

    beta=mult_inv(gamma, p); // Multiplicative inverse of gamma then mod p 
                             // and assigning to beta
    beta=beta*b; 
    while(beta<0){
    beta=beta+p;
}
    beta = beta%p; // beta mod(p)
    
    beta=s_and_m(beta, (n/(int(pow((double)x.a[k], j+1)))),p); 
    // Square and multiply for beta^(n/q^(j+1)) then mod p. Assigning value to
    // beta
    for(int y=0; y<g.size(); y++){ // y goes from 0 to (size of vector g) - 1
    if(beta==g[y]){ // Comparing values of beta and y^th value in vector g
    l.push_back(y); // Adding y values to vector vector l
   
    g.clear(); // Clearing vecotr g
    break;
}
}
}
int t =0;
    for(int q=1;q<l.size();q++){// q goes from 1 to (size of l) - 1
        t = t + (l[q]*((int)pow((double) x.a[k], q-1)));
        // t + (l[q]*(prime factors^(q-1))) then assign to t
        }
        
        A.push_back(t); // Adding t values to the vector A
l.clear(); // Clearing vector l
}

int m = ChineseTheorem(B, A); // Calling the function Chinese Remainder Theorem
                              // to solve pair of congruences A and B. Equate to 
                              // integer m
return m; // Give back value of m
}

/*---------------------End of Pohlig-Hellman algorithm------------------------*/

/*****************************End of Functions*********************************/

/*-------------------------------Main Function--------------------------------*/

int main(){
    
    int alpha, beta ,n;
    
     double time, timedif; // Double is used here to show small values

    time = (double) clock(); // Get the intial time
    time = time/CLOCKS_PER_SEC;  // Time in seconds 
    
    cout<<"\n Divyesh B Chudasama"
          "\n Copyright (c) 2012";
          
     cout<<"\n \n Implementation of the Pohlig Hellman algorithm for computing" 
          "\n the unique integer x such that x = log_{alpha}beta for the" 
          "\n Discrete Logarithm Problem in GF(p), with cyclic group G, order n," 
          "\n generator alpha and group element beta. ";
          
    cout<<"\n \n Please enter a value for 'alpha': ";
    cin>>alpha;
    cout<<"\n Please enter a value for 'beta': ";
    cin>>beta;
    cout<<"\n Please enter a value for 'n': ";
    cin>>n;
   
   int r = PHellman(alpha, beta, n); // Calling function Pohlig Hellman
   
   if(r==1)
            
            cout<<"\n There is no unique solution to this problem.\n\n";
   
   else if(r > 1)
    
    cout<<endl<<"\n The discrete logarithm x is: "<<r<<endl<<endl;
    
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time; // Calling clock() 
    //function from start of program, subtracting its return value, then to 
    //obtain the final processor time in seconds, divide the value returned 
    //by clock() by CLOCK_PER_SEC
    
    cout<<"\n The processor time elapsed is: "<<timedif<<" seconds"<<endl<<endl;
    
    keep_window_open();
       
}

/*----------------------------End of Main Function----------------------------*/






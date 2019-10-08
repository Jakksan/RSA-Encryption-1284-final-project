#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <gmp.h>
#include <ctime>


using namespace std;

// Compile command:
// g++ generatePrimes.cpp -o generatePrimes -lgmp -lgmpxx
// Note: This is the first thing that should be run by the program

void generateRandom(char c_str[], int size);

int main(){

  // This cstring will be used for storing our initial large random number
  char *cstr = new char [300];

  FILE *file; // FILE ptr called file, it's very creative...

  // Clear the old contents out of the file
  fclose( fopen("./tmp/primes.txt", "w") );

  // Reopen the file so we can append to it.
  file = fopen("./tmp/primes.txt", "a");

  // use these for nicer output in the for loop
  char varnames[] = { 'P', 'Q' };

  // We want two large primes, P & Q, so we run the loop twice.
  // It's important to use a loop here so the (huge)variables will be forgotten
  // after each iteration, giving the program enough memory to keep working.
  for(int i=0; i<2; i++) {
    generateRandom(cstr, 300);

    // Generate a large prime number (300 digits) using the code below
    mpz_t random; // will store the random number temporarily
    mpz_t P; // make a new mpz_t number for P

    // set the digits of placeholder to the chars of the cstring, in base 10
    mpz_set_str(random, cstr, 10);

    // P = the next prime after random
    mpz_nextprime(P, random);

    // Output what the random number was, what it's length was, and wheather P
    // is prime or not.
    cout << "Random " << varnames[i] << ":\n" << P << endl;
    cout << "Length " << varnames[i] << ": "<< mpz_sizeinbase(P, 2) << "bits." << endl;
    cout << "Is " << varnames[i] << "prime? \n";
    cout << "1 = Almost definitely. 0 = Not prime.\n";
    cout << "Result: " << mpz_probab_prime_p(P, 50) << endl;

    // We need to put our new prime number into a form that can be added to a file.
    char *prime_cstr = new char [300];
    mpz_get_str(prime_cstr, 10, P);

    // Append the new prime to primes.txt for later use by the program
    fputs (prime_cstr, file); // the prime cstring
    fputs ("\n",file);        // and a newline

    cout << endl;

  }

  // Primes were generated successfully, and added to ./storage/primes.txt
  return(0);
}

void generateRandom(char c_str[], int size) {
  for (int i = 0; i < size; i++) {

    // Seed the random number generator.
    static float seed = 0;
    if ( seed == 0 ) {
      srand(time(0));
      seed = time(0);
    }

    // Create random digits
    int number = rand() % 8 + 1;  // get a random digit
    char newchar = '0' + number;  // convert that digit to a char

    // Add digit to the end of cstrings as chars
    c_str[i] = newchar;
  }
}

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <ctime>
#include <cctype>

// compile with the following command:
// g++ encrypt.cpp -o encrypt -lgmp -lgmpxx

using namespace std;

int main() {

  //// IGNORE ///// Open primes.txt for reading (Now Irrelevant)
  //// ifstream primeFile;
  //// primeFile.open("./storage/primes.txt", fstream::in);

  // We need to access the numbers in the public key file
  ifstream nFile;
  nFile.open("./keys/publicKey.txt", fstream::in);

  //// IGNORE /////
  //// Create+Assign P, Q, N, and phi(N) strings
  //// string P_string;
  //// string Q_string;
  //// string phiN_string;

  // These are the only two things we will need to encrypt our message.
  string N_string;
  string E_string;

  //// IGNORE /////
  // getline(primeFile, P_string);
  // getline(primeFile, Q_string);
  // getline(nFile, phiN_string);
  // primeFile.close();

  // Get the text stored in our file
  getline(nFile, N_string);
  getline(nFile, E_string);

  nFile.close(); // close the file, we no longer need it, and it uses memory

  //// GMP works with cstrings, so we put them into that format here ////
  char *cstr_N = new char [N_string.length() + 1];
  strcpy(cstr_N, N_string.c_str());
  mpz_t N;
  mpz_set_str(N, cstr_N, 10);
  delete []cstr_N;

  char *cstr_E = new char [E_string.length() + 1];
  strcpy(cstr_E, E_string.c_str());
  mpz_t E;
  mpz_set_str(E, cstr_E, 10);
  delete []cstr_E;

  /*
  //// Ignore /////
  char *cstr_P = new char [P_string.length() + 1];
  strcpy(cstr_P, P_string.c_str());
  mpz_t P;
  mpz_set_str(P, cstr_P, 10);
  delete []cstr_P;
  */




  // Get a message from the user to encrypt
  mpz_t M;
  string input;
  cout << "Text to encrypt: " << endl;
  getline(cin, input); // get the whole line of text from the user
  char *in_cstr = new char [input.length() + 1];
  strcpy(in_cstr, input.c_str());

  ////// Convert ascii->decimal //////
  // 3 digits per char, so make array big enough to hold the size of our new array
  char *decimal_cstr = new char [ input.length() * 3 + 1];

  for (int i = 0; i < input.length()+1; i++) {
    char c = in_cstr[i];
    int ascii_num = int(in_cstr[i]);

    // Add the padding(simple leading zeros) & convert int to a cstr
    char *ascii_cstr = new char [ 3 ];
    sprintf(ascii_cstr, "%03d", ascii_num);
    cout << ascii_cstr << " ";
    for (int j = 0; j < 3; j++) {
      decimal_cstr[( i*3 + j)] = ascii_cstr[j]; // 3 digs per char
    }
    delete []ascii_cstr;

  }
  cout << endl;

  mpz_set_str(M, decimal_cstr, 10);
  cout << "Decimal Value: " << M << endl;

  mpz_t C; // ciphertext variable
  cout << "\nCiphertext:\n ----------------------------------------" << endl;
  mpz_powm_sec(C, M, E, N);
  cout << C << endl;

  //mpz_powm_sec(M, C, N, N);
  //cout << M << endl;

  // Create mpz_t numbers for P, Q, N, and phi(N)
  /*

  char *cstr_Q = new char [Q_string.length() + 1];
  strcpy(cstr_Q, Q_string.c_str());
  mpz_t Q;
  mpz_set_str(Q, cstr_Q, 10);
  delete []cstr_Q;
  cout << "2" << endl;

  char *cstr_phiN = new char [phiN_string.length() + 1];
  strcpy(cstr_phiN, phiN_string.c_str());
  mpz_t phiN;
  mpz_set_str(phiN, cstr_phiN, 10);
  delete []cstr_phiN;
  cout << "4" << endl;
  */

  return(0);
}

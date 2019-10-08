#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <gmp.h>
#include <ctime>

using namespace std;

int main() {

  // Open txt for reading
  ifstream primeFile;
  primeFile.open("../primes.txt", fstream::in);
  
  // Create+Assign P & Q strings
  string P_string;
  string Q_string;
  getline(primeFile, P_string); 
  getline(primeFile, Q_string);
  primeFile.close();
  

  // Output our products
  cout << "\nProducts\n--------------------------------------------" << endl;
  cout << "P: \n" << P_string << endl;
  cout << "Q: \n" << Q_string << "\n" << endl;

  // Create mpz_t numbers for P&Q
  char *cstr_P = new char [P_string.length() + 1];
  strcpy(cstr_P, P_string.c_str());
  mpz_t P;
  mpz_set_str(P, cstr_P, 10);

  char *cstr_Q = new char [Q_string.length() + 1];
  strcpy(cstr_Q, Q_string.c_str());
  mpz_t Q;
  mpz_set_str(Q, cstr_Q, 10);
  

  // We won't need these c strings again
  delete []cstr_P;
  delete []cstr_Q;

  // Find phi(N)
  mpz_t phi_N;
  mpz_t P_tmp;
  mpz_t Q_tmp;

  mpz_sub_ui(P_tmp, P, 1); // P_tmp = P - 1
  mpz_sub_ui(Q_tmp, Q, 1);


  mpz_set_str(P, "0", 10);
  mpz_set_str(Q, "0", 10);
  
  mpz_lcm(phi_N, P_tmp, Q_tmp); // phi_N = (P-1) * (Q-1)
  cout << "\nPhi(N)\n----------------------------------------------" << endl;
  cout << phi_N << endl;

  // Get E from public key
  ifstream publicFile;
  publicFile.open("../keys/publicKey.txt", fstream::in); 
  string E_string;
  string empty;
  getline(publicFile, empty); 
  getline(publicFile, E_string);
  publicFile.close();
  

  
  char *cstr_E = new char [E_string.length() + 1];
  strcpy(cstr_E, E_string.c_str());
  mpz_t E;
  mpz_set_str(E, cstr_E, 10);
  delete []cstr_E;

  cout << "\nPriv Key\n--------------------------------------------" << endl;
  mpz_t D;
  mpz_mod(D, E, phi_N);
  cout << D << endl;
    

  ofstream outputsFile;
  outputsFile.open("../keys/privateKey.txt", fstream::out);
  outputsFile << phi_N << "\n";
  outputsFile << D << "\n";


}

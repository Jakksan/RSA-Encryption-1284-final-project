#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <gmp.h>
#include <ctime>

using namespace std;

int main() {

  // Open primes.txt for reading
  ifstream primeFile;
  primeFile.open("./storage/primes.txt", fstream::in);
  
  // Create+Assign P & Q strings
  string P_string;
  string Q_string;
  getline(primeFile, P_string); 
  getline(primeFile, Q_string);

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

  // Now we simply multiply them together
  mpz_t N;
  mpz_mul(N, P, Q);
  cout << "Resultant(N)\n------------------------------------------" << endl;
  cout << N << endl;

  // Find phi(N)
  mpz_t phi_N;
  mpz_t P_tmp;
  mpz_t Q_tmp;

  mpz_sub_ui(P_tmp, P, 1); // P_tmp = P - 1
  mpz_sub_ui(Q_tmp, Q, 1);

  mpz_mul(phi_N, P_tmp, Q_tmp); // phi_N = (P-1) * (Q-1)
  cout << "\nPhi(N)\n----------------------------------------------" << endl;
  cout << phi_N << endl;

  ofstream outputsFile;
  outputsFile.open("./storage/N_and_PhiN.txt", fstream::out);
  outputsFile << N << "\n";
  outputsFile << phi_N << "\n";


}

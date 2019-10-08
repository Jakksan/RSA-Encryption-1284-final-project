#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <gmp.h>
#include <ctime>

// Compile with the following command:
// g++ publickey_gen.cpp -o publickey_gen -lgmp -lgmpxx

using namespace std;


int main() {

  // Open primes.txt for reading
  ifstream primeFile;
  primeFile.open("./tmp/primes.txt", fstream::in);

  // Create+Assign P & Q strings
  string P_string;
  string Q_string;
  getline(primeFile, P_string);
  getline(primeFile, Q_string);

  // Output our products
  cout << "\nProducts (Do not go in pub key)"
  << "\n--------------------------------------------" << endl;
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

  cout << "\nExponent(E)\n-------------------------------------------" << endl;
  string E = "65537";
  cout << E << "\n" << endl;

  ofstream outputsFile;
  outputsFile.open("../keys/publicKey.txt", fstream::out);
  outputsFile << N << "\n";
  outputsFile << E << "\n";
  outputsFile.close();


}

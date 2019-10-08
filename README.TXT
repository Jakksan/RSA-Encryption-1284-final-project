Welcome to my RSA encryption program! (Decryption hopefully coming soon)

########################################################
################ Important side notes ##################
########################################################

The program makes uses of the GNU Multiple Precision Arithmetic library, or GMP for short.
The library makes it possible to work with incredibly large numbers, and without this 
library I would have had to use, relatively speaking, small numbers to do all of my 
encryption. 

Make sure GMP is correctly installed before attempting to compile this program.
You can download it here:
https://gmplib.org/

########################################################

Never actually be used for anything with sensitive data, as it is very insecure. 
It was build for educational purposes and does not follow any RSA standards. 
Seriously, go use another program for your encryption needs.

########################################################
########## Compiling and Using the program #############
########################################################
Compile:
g++ generatePrimes.cpp -o generatePrimes -lgmp -lgmpxx
g++ publickey_gen.cpp -o publickey_gen -lgmp -lgmpxx
g++ encrypt.cpp -o encrypt -lgmp -lgmpxx

Run (in this order):

The program works by first generating two very large prime numbers with generatePrimes.cpp,
compile with this command:
$ g++ generatePrimes.cpp -o generatePrimes -lgmp -lgmpxx

Next, we need to use those primes to generate a "public key" which will be used to encrypt our
message. I could send this public key to anyone, and they could use it to encrypt a message they plan to send back to me. 
To generate the public key, compile publickey_gen.cpp like so:
$ g++ publickey_gen.cpp -o publickey_gen -lgmp -lgmpxx

Now we're ready to start encrypting! Simply compile encrypt.cpp like so:
$ g++ encrypt.cpp -o encrypt -lgmp -lgmpxx

########################################################

Happy encrypting!
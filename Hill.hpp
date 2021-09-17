#ifndef _HILL_HPP_
#define _HILL_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Matrix.hpp"

/**
 * A C++ class to perform encryption/decryption and cryptanalysis using/of the Hill cipher with a 29 character alphabet.
 */ 
class Hill
{
public:
  /**
   * Default constructor. It should set the encryption key to {2,4,3,5} (2-by-2) and the decryption key to its inverse.
   */ 
  Hill();
  
  /**
   * Parameterized constructor.  Use the parameter to set the encryption (E) and decryption (D) keys; if parameter is invalid then set E/D to a 0-by-0 matrix.
   * @param K - a matrix representing the encryption or decryption key.
   * @param encryption - true if the key is the encryption key, false if the key is the decryption key
   */ 
  Hill(const Matrix &K, bool encryption);

  /**
   * Parameterized constructor.  Use the parameters to set the encryption (E) and decryption (D) keys; if a parameter is invalid or inconsistent then set E/D to a 0-by-0 matrix.
   * @param E - encryption key.
   * @param D - decryption key.
   */ 
  Hill(const Matrix &E, const Matrix &D);

  /**
   * Returns the current encryption key.
   * @return the encryption key (Matrix E), if no encryption key is set a 0-by-0 matrix.
   */ 
  Matrix getE() const;

  /**
   * Returns the current decryption key.
   * @return the decryption key (Matrix D), if no decryption key is set a 0-by-0 matrix.
   */ 
  Matrix getD() const;

  /**
   * Sets the encryption key (Matrix E) and decryption key (Matrix D); if the parameter is invalid then set E/D to a 0-by-0 matrix.
   * @param E - encryption key.
   * @return true if set is successful, false otherwise.
   */ 
  bool setE(const Matrix &E);

  /**
   * Sets the decryption key (Matrix D) and encryption key (Matrix E); if the parameter is invalid then set E/D to a 0-by-0 matrix.
   * @param D - decryption key.
   * @return true if set is successful, false otherwise.
   */ 
  bool setD(const Matrix &D);
  
  /**
   * Encrypt the given plaintext using the previous set encryption key, an empty string if the encryption key is invalid.
   * @param P - the plaintext to encrypt
   * @return the ciphertext resulting from encrypting the plaintext using the stored encryption matrix.
   */ 
  std::string encrypt( const std::string & P );

  /**
   * Encrypt the given plaintext using the given encryption key, an empty string if the encryption key is invalid.
   * @param P - the plaintext to encrypt
   * @param E - the key to use to encrypt the plaintext
   * @return the ciphertext resulting from encrypting the plaintext using the given encryption matrix.
   */ 
  std::string encrypt( const std::string & P, const Matrix & E);

  /**
   * Decrypt the given ciphertext using the previous set decryption key, an empty string if the decryption key is invalid.
   * @param C - the ciphertext to decrypt
   * @return the plaintext resulting from decrypting the ciphertext using the stored decryption matrix.
   */ 
  std::string decrypt( const std::string & C );

  /**
   * Decrypt the given ciphertext using the given decryption key, an empty string if the decryption key is invalid.
   * @param C - the plaintext to encrypt
   * @param D - the key to use to decrypt the ciphertext
   * @return the plaintext resulting from decrypting the ciphertext using the given decryption matrix.
   */ 
  std::string decrypt( const std::string & C, const Matrix & D);

  /**
   * Mount a known-plaintext attack against the Hill cipher assuming an n-by-n encryption matrix.  Set E/D to the encryption/decryption key if they can be recovered.
   * @param P - the plaintexts that correspond to C
   * @param C - the ciphertexts that correspond to P 
   * @return true if the encryption and decryption keys have been recovered.
   */ 
  bool kpa( const std::vector<std::string> & P, const std::vector<std::string> & C, unsigned int n);

  int calculateDeterminant(const Matrix A);

  Matrix inv_mod(Matrix A);
 
  

private:
  Matrix D; //current decryption key; must be consistent with E
  Matrix E; //current encryption key; must be consistent with D
  //multiplicative inverses over Z_{29}; e.g., ZI29[1] = 15 is multiplicative inverse of 2. 
  const std::vector<int> ZI29 = {1,15,10,22,6,5,25,11,13,3,8,17,9,27,2,20,12,21,26,16,18,4,24,23,7,19,14,28};


  //convert the string of characters in s to the equivalent numerical values using our 29 character alphabet and put in matrix suitable for n-by-n encryption matrix
  Matrix l2num(const std::string & s, unsigned int n);

  //convert the matrix to a string of characters using our 29 character alphabet
  std::string n2let(const Matrix & A);

  //Calculate the matrix inversion of A, mod 29
  
  //an empty matrix is returned if A is not invertible

  //calculate c = a mod b, where c = [0,b)
  unsigned int mod(int a, int b);

  //For row i of Matrix A, multiply columns j through k by c, mod 29
  //(i.e., in Matlab notation A(i,j:k) = mod(c*A(i,j:k), 29))
  //NOTE: matrix pass by reference means all operations occur in place
  void row_mult(Matrix & A, unsigned int i, unsigned int j, unsigned int k, unsigned int c);

  //Multiply columns j through k of row l of Matrix B by c and subtract from columns j through k of row i of Matrix A, mod 29
  //(i.e., in Matlab notation A(i,j:k) = mod(A(i,j:K) - c*B(l,j:k), 29)
  //NOTE: matrix pass by reference means all operations occur in place
  void row_diff(Matrix & A, unsigned int i, unsigned int j, unsigned int k, Matrix & B, unsigned int l, unsigned int c);

  void row_diff_nomod(Matrix & A, unsigned int i, unsigned int j, unsigned int k, Matrix & B, unsigned int l, double c);

  

  Matrix Identity_creation(unsigned int n);

  Matrix Echelon_Form(Matrix A, Matrix I);

};
#endif

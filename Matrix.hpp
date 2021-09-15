#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdint>

/**
 * This is a basic C++ class to represent two-dimensional matrices.  It's not meant to be difficult but as a refresher on classes.
 */ 
class Matrix
{
public:
  /**
   * Default constructor. It should create a 2-by-2 matrix will all elements set to zero.
   */ 
  Matrix();
  
  /**
   * Parameterized constructor.  Use the parameters to set the matrix element; if parameters are inconsistent then create a 0-by-0 matrix.
   * @param A - values for matrix elements, specified column-wise.
   * @param n - number of columns for the new matrix.
   */ 
  Matrix(const std::vector<int> &A, unsigned int n);

  /**
   * Another parameterized constructor.  Use the parameters to set the matrix element; if parameters are inconsistent then create a 0-by-0 matrix.
   * @param A - values for matrix elements, specified column-wise.
   * @param m - number of rows for the new matrix.
   * @param n - number of columns for the new matrix.
   */ 
  Matrix(const std::vector<int> &A, unsigned int m, unsigned int n);

  /**
   * Returns the element at specified linear index.
   * @param i - column-wise (linear) index of object.
   * @return element at specified linear index or smallest possible value for int if index is invalid.
   */ 
  int get(unsigned int i) const;

  /**
   * Returns the element at specified row, column index.
   * @param i - row index of object.
   * @param j - column index of object.
   * @return element at specified row, column index or smallest possible value for int if index is invalid.
   */ 
  int get(unsigned int i, unsigned int j) const;

  /**
   * Sets the element at specified linear index i to given value; if index is invalid matrix should not be modified.
   * @param i - column-wise (linear) index of object to set.
   * @param ai - value for element at index i
   * @return true if set is successful, false otherwise.
   */ 
  bool set(unsigned int i, int ai);
  
  /**
   * Sets the element at specified row, column index to given value; if either index is invalid matrix should not be modified.
   * @param i - row index of object to set.
   * @param j - column index of object to set.
   * @param aij - value for element at index i, j
   * @return true if set is successful, false otherwise.
   */ 
  bool set(unsigned int i, unsigned int j, int aij);

  /**
   * Returns the size of the matrix along a given dimension (i.e., number of row(s) or column(s))
   * @param dim - 1 for row, 2 for column
   * @return the length of the dimension specified, if dimension is not valid return 0
   */ 
  unsigned int size(unsigned int dim) const;
  
 /**
   * Returns true if the elements for this object and rhs are the same, false otherwise.
   * @param rhs - the Matrix object to compare to this object.
   * @return true if elements in both objects are the same, false otherwise.
   */ 
  bool equal( const Matrix& rhs ) const;

  /**
   * Creates and returns a new Matrix object representing the matrix addition of two Matrix objects.
   * @return a new Matrix object that contains the appropriate summed elements, a 0-by-0 matrix if matrices can't be added.
   * @param rhs - the Matrix object to add to this object.
   */
  const Matrix add( const Matrix &rhs ) const;

  /**
   * Creates and returns a new Matrix object representing the matrix subtraction of two Matrix objects.
   * @return a new Matrix object that contains the appropriate difference elements, a 0-by-0 matrix if matrices can't be subtracted.
   * @param rhs - the Matrix object to subtract from this object.
   */
  const Matrix sub( const Matrix &rhs ) const;

  /**
   * Creates and returns a new Matrix object that is the multiplication of this and the given Matrix object.
   * @return a new Matrix object that contains the multiplication of this and the given Matrix object, a 0-by-0 matrix if matrices can't be multiplied.
   * @param rhs - the Matrix object to multiply with this object.
   */
  const Matrix mult( const Matrix &rhs ) const;

  /**
   * Creates and returns a new Matrix object that is the multiplication of this and the given scalar.
   * @return a new Matrix object that contains the multiplication of this and the given scalar.
   * @param rhs - the scalar value to multiply with this object.
   */
  const Matrix mult( int c ) const;

  /**
   * Creates and returns a new Matrix object that is the power of this.
   * @return a new Matrix object that raises this and to the given power.
   * @param n - the power to which this object should be raised, a 0-by-0 matrix if matrix can't be raised to power.
   */
  const Matrix pow( unsigned int n ) const;

  /**
   * Creates and returns a new Matrix object that is the transpose of this.
   * @return a new Matrix object that is the transpose of this object.
   */
  const Matrix trans() const;
  
  /**
   * Outputs this Matrix object on the given ostream (for debugging).
   * @param out - the ostream object to use to output.
   */ 
  void output( std::ostream &out ) const;

private:
  std::vector<int> A; //our matrix, stored column-wise
  unsigned int m; //number of rows
  unsigned int n; //number of columns
  //NOTE: m, n should be const but making them so complicates the constructors
};
#endif

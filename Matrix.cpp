#include "Matrix.hpp"


Matrix::Matrix()
{
    m = 2;
    n = 2;

    A.push_back(0);
    A.push_back(0);
    A.push_back(0);
    A.push_back(0);
}

Matrix::Matrix(const std::vector<int>& A, unsigned int n)
{

    if ((n == 0)) // inconsistent when no columns
    {
        this->m = 0;
        this->n = 0;
    }
    else if (((A.size() % n) != 0)) { // inconsistent when the m value isn't a whole number
        this->m = 0;
        this->n = 0;

    }
    else {
        for (int i = 0; i < A.size(); i++) { // pushing value based on each integer.
            this->A.push_back(A[i]);
        }

        this->n = n;
        this->m = (A.size() / n); // dividing size by n to get the number of rows.
    }
}


Matrix::Matrix(const std::vector<int>& A, unsigned int m, unsigned int n)
{
    if ((m == 0) && (n == 0)) // 0x0 matrix inconsistent
    {
        this->m = 0;
        this->n = 0;
    }
    else if (((int)m * (int)n) != A.size()) { // inconsistent
        this->m = 0;
        this->n = 0;
    }
    else { // correct value
        for (int i = 0; i < A.size(); i++) {
            this->A.push_back(A[i]);
        }

        this->n = n; // returned value.
        this->m = m;
    }
}

int Matrix::get(unsigned int i) const
{

    int min_lol = std::numeric_limits<int>::min(); // setting INT_MIN to a variable

    if (i >= this->A.size()) { // returning minimum value for linear index greater than size.

        return min_lol;
    }
    else {
        return this->A[i];
    }

}


int Matrix::get(unsigned int i, unsigned int j) const
{
    int min_lol = std::numeric_limits<int>::min();

    if ((i >= this->m) || (j >= this->n)) { // inconsistent for incorrect inputs.
        return min_lol;
    }
    else {
        int lin_ind = ((j * m) + i);

        return this->A[lin_ind];
    }
}


bool Matrix::set(unsigned int i, int ai)
{
    if (i >= this->A.size()) { // checking for linear index greater than size (inconsistent case)
        return false;
    }
    else {
        this->A[i] = ai;
        return true;
    }
}


bool Matrix::set(unsigned int i, unsigned int j, int aij)
{
    if ((i >= this->m) || (j >= this->n)) { // corner values for inconsistent. 
        return false;
    }
    else {
        int lin_ind = ((j * m) + i); // setting linear index.
        this->A[lin_ind] = aij; // assigning the index for true case
        return true;
    }
}


unsigned int Matrix::size(unsigned int dim) const
{
    if (dim == 1) // returning row
    {
        return this->m;
    }
    else if (dim == 2) { // returning column
        return this->n;
    }
    else { // inconsistent case.
        return 0;
    }
}


bool Matrix::equal(const Matrix& rhs) const
{
    int checker = 0; // local variable for counting the value is same or not

    if ((rhs.A.size() == this->A.size()) && (rhs.m == this->m) && (rhs.n == this->n)) { // true corner cases.
        for (int i = 0; i < this->A.size(); i++) {  // run as many times as the matrix is
            if (A[i] == rhs.A[i]) {
                checker++; // add the value to the checker if the current value is the same
            }
            else {
                return false; // return false if not
            }
        }
        if (checker == this->A.size()) {
            return true; // match the value to checker to return true
        }
    }
    else {
        return false;
    }
}


const Matrix Matrix::add(const Matrix& rhs) const
{
    if ((this->m == rhs.m) && (this->n == rhs.n)) { // corner case for true

        std::vector<int> vec(rhs.m * rhs.n);
        Matrix result(vec, rhs.m, rhs.n);

        for (int i = 0; i < this->A.size(); i++) {
            result.A[i] = rhs.A[i] + this->A[i]; // add both values
        }
        return result;
    }
    else {
        std::vector<int> vec;
        Matrix result(vec, 0, 0);

        return result; // inconsistent
    }

}


const Matrix Matrix::sub(const Matrix& rhs) const
{
    if ((this->m == rhs.m) && (this->n == rhs.n)) {

        std::vector<int> vec(rhs.m * rhs.n);
        Matrix result(vec, rhs.m, rhs.n); // instantiate matrix

        for (int i = 0; i < this->A.size(); i++) {
            result.A[i] = this->A[i] - rhs.A[i]; // substract both values.
        }
        return result;
    }
    else {
        std::vector<int> vec;
        Matrix result(vec, 0, 0);

        return result;
    }
}


const Matrix Matrix::mult(const Matrix& rhs) const
{
    Matrix result(std::vector<int>(this->m*rhs.n),this->m,rhs.n);
    int row_add;
    if (this->n == rhs.m) {
        for (int i = 0; i < this->m; i++) {
            for (int j = 0; j < rhs.n; j++) {// dot product for loop
                row_add = 0;
                for (int y = 0; y < rhs.m; y++) {
                    row_add += this->get(i, y) * rhs.get(y, j);
                }
                result.set(i, j, row_add); // return result by setting it
            }
        }
        return result;
    }
    else {
        std::vector<int> vec;
        Matrix res(vec, 0, 0);

        return res; // return 0x0 matrix
    }
}


const Matrix Matrix::mult(int c) const
{
    std::vector<int> vec(this->m * this->n);
    Matrix result(vec, this->m, this->n);

    for (int i = 0; i < this->A.size(); i++) {
        result.A[i] = this->A[i] * c; // scalar multiplication to individual value
    }
    return result;
}

const Matrix Matrix::pow(unsigned int n) const
{
    Matrix result(this->A, this->m, this->n);
	Matrix second(this->A, this->m, this->n);
	if (n == 0)
	{
		std::vector<int> vec;
		Matrix res(vec, 0, 0);
		return res;	
	}
	else if (n == 1)
	{
		return result;
	}
	else
	{
		for (int i = 1; i < n; i++)
		{
			result = result.mult(second);
		}
		return result;
	}

}

const Matrix Matrix::trans() const
{
    std::vector<int> tem(this->n * this->m);
    Matrix result(tem, this->n, this->m);

    for (int x = 0; x < this->n; x++) {
        for (int y = 0; y < this->m; y++) {
            result.set(x, y, this->get(y, x)); // transpose to the side and set result.
        }
    }
    return result;
}


void Matrix::output(std::ostream& out) const
{
    for (int i = 0; i < A.size(); i++)
        out << A[i] << " ";
    return;
}

#include "Hill.hpp"

/**
   * Default constructor. It should set the encryption key to {2,4,3,5} (2-by-2) and the decryption key to its inverse.
   */
Hill::Hill() {

	this->E.set(0, 2);
	this->E.set(1, 4);
	this->E.set(2, 3);
	this->E.set(3, 5);

	this->D.set(0, 12);
	this->D.set(1, 2);
	this->D.set(2, 16);
	this->D.set(3, 28);
}

/**
 * Parameterized constructor.  Use the parameter to set the encryption (E) and decryption (D) keys; if parameter is invalid then set E/D to a 0-by-0 matrix.
 * @param K - a matrix representing the encryption or decryption key.
 * @param encryption - true if the key is the encryption key, false if the key is the decryption key
 */
Hill::Hill(const Matrix& K, bool encryption) {
	if (encryption)
	{
		if (this->calculateDeterminant(K))
		{
			setE(K);
			Matrix inverse = this->inv_mod(this->E);
			setD(inverse);
			//inverse E then set D
		}
		else
		{
			std::vector<int> vec;
			Matrix result(vec, 0, 0);
			setD(result);
			setE(result);
		}
	}
	else
	{
		if (this->calculateDeterminant(K))
		{
			setD(K);
			Matrix inverse = this->inv_mod(this->D);
			setE(inverse);
			//inverse D then set E
		}
		else
		{
			std::vector<int> vec;
			Matrix result(vec, 0, 0);
			setD(result);
			setE(result);
		}
	}
}

/**
 * Parameterized constructor.  Use the parameters to set the encryption (E) and decryption (D) keys; if a parameter is invalid or inconsistent then set E/D to a 0-by-0 matrix.
 * @param E - encryption key.
 * @param D - decryption key.
 */
Hill::Hill(const Matrix& E, const Matrix& D)
{
	if (this->calculateDeterminant(E) && this->calculateDeterminant(D) && E.size(1) == D.size(1) && this->inv_mod(E).equal(D))
	{
		setE(E);
		setD(D);
	}
	else
	{
		std::vector<int> vec;
		Matrix result(vec, 0, 0);
		setD(result);
		setE(result);
	}
}

/**
 * Returns the current encryption key.
 * @return the encryption key (Matrix E), if no encryption key is set a 0-by-0 matrix.
 */
Matrix Hill::getE() const {
	int checker = 0;

	for (int x = 0; x < this->E.size(1); x++) {
		for (int y = 0; y < this->E.size(2); y++) {
			if (this->E.get(x, y) == 0) {
				checker++;
			}
		}
	}

	if (checker == (this->E.size(1) * this->E.size(2))) {
		std::vector<int> vec;
		Matrix result(vec, 0, 0);
		return result;
	}
	else {
		return this->E;
	}
}

/**
 * Returns the current decryption key.
 * @return the decryption key (Matrix D), if no decryption key is set a 0-by-0 matrix.
 */
Matrix Hill::getD() const {
	int checker = 0;

	for (int x = 0; x < this->D.size(1); x++) {
		for (int y = 0; y < this->D.size(2); y++) {
			if (this->D.get(x, y) == 0) {
				checker++;
			}
		}
	}

	if (checker == (this->D.size(1) * this->D.size(2))) {
		std::vector<int> vec;
		Matrix result(vec, 0, 0);
		return result;
	}
	else {
		return this->D;
	}
}

/**
 * Sets the encryption key (Matrix E) and decryption key (Matrix D); if the parameter is invalid then set E/D to a 0-by-0 matrix.
 * @param E - encryption key.
 * @return true if set is successful, false otherwise.
 */
bool Hill::setE(const Matrix& E) {

	if (E.size(1) >= 2 && E.size(1) == E.size(2) && calculateDeterminant(E))
	{
		this->E = E;
		return true;
	}
	else
	{
		std::vector<int> vec;
		Matrix result(vec, 0, 0);
		this->E = result;
		return false;
	}
}

/**
 * Sets the decryption key (Matrix D) and encryption key (Matrix E); if the parameter is invalid then set E/D to a 0-by-0 matrix.
 * @param D - decryption key.
 * @return true if set is successful, false otherwise.
 */
bool Hill::setD(const Matrix& D) {
	if (D.size(1) >= 2 && D.size(1) == D.size(2) && calculateDeterminant(D))
	{
		this->D = D;
		return true;
	}
	else
	{
		std::vector<int> vec;
		Matrix result(vec, 0, 0);
		this->D = result;
		return false;
	}
}

/**
 * Encrypt the given plaintext using the previous set encryption key, an empty string if the encryption key is invalid.
 * @param P - the plaintext to encrypt
 * @return the ciphertext resulting from encrypting the plaintext using the stored encryption matrix.
 */
std::string Hill::encrypt(const std::string& P)
{
	Matrix plain;
	std::string result = "";
	plain = this->l2num(P, this->E.size(2));

	if (this->calculateDeterminant(this->E))
	{
		Matrix cipher = this->E.mult(plain);
		result = this->n2let(cipher);
	}
	else
	{
		result = "";
	}
	return result;

}

/**
 * Encrypt the given plaintext using the given encryption key, an empty string if the encryption key is invalid.
 * @param P - the plaintext to encrypt
 * @param E - the key to use to encrypt the plaintext
 * @return the ciphertext resulting from encrypting the plaintext using the given encryption matrix.
 */
std::string Hill::encrypt(const std::string& P, const Matrix& E)
{
	Matrix plain;
	std::string result = "";
	plain = this->l2num(P, this->E.size(2));

	if (this->calculateDeterminant(E))
	{
		Matrix cipher = E.mult(plain);
		result = this->n2let(cipher);
	}
	else
	{
		result = "";
	}
	return result;
}

/**
 * Decrypt the given ciphertext using the previous set decryption key, an empty string if the decryption key is invalid.
 * @param C - the ciphertext to decrypt
 * @return the plaintext resulting from decrypting the ciphertext using the stored decryption matrix.
 */
std::string Hill::decrypt(const std::string& C)
{
	Matrix cipher;
	std::string result = "";
	cipher = this->l2num(C, this->D.size(2));

	if (this->calculateDeterminant(this->D))
	{
		Matrix plain = this->D.mult(cipher);
		result = this->n2let(plain);
	}
	else
	{
		result = "";
	}
	return result;
}

/**
 * Decrypt the given ciphertext using the given decryption key, an empty string if the decryption key is invalid.
 * @param C - the plaintext to encrypt
 * @param D - the key to use to decrypt the ciphertext
 * @return the plaintext resulting from decrypting the ciphertext using the given decryption matrix.
 */
std::string Hill::decrypt(const std::string& C, const Matrix& D)
{
	Matrix cipher;
	std::string result = "";
	cipher = this->l2num(C, this->D.size(2));

	if (this->calculateDeterminant(D))
	{
		Matrix plain = D.mult(cipher);
		result = this->n2let(plain);
	}
	else
	{
		result = "";
	}
	return result;
}

/**
 * Mount a known-plaintext attack against the Hill cipher assuming an n-by-n encryption matrix.  Set E/D to the encryption/decryption key if they can be recovered.
 * @param P - the plaintexts that correspond to C
 * @param C - the ciphertexts that correspond to P
 * @return true if the encryption and decryption keys have been recovered.
 */
bool Hill::kpa(const std::vector<std::string>& P, const std::vector<std::string>& C, unsigned int n)
{
	return true;
}

int Hill::calculateDeterminant(const Matrix A)
{
	if (A.size(1) == A.size(2))
	{
		if (A.size(1) == 2)
		{
			return A.get(0, 0)*A.get(1, 1) - A.get(0, 1)*A.get(1, 0);
		}
		else if(A.size(1) == 3)
		{
			int multi = 1;
			int sum = 0;
			int counter = 0;
			for (int i = 0; i < A.size(1); ++i)
			{
				multi = 1;
				for (int j = 0; j < A.size(1); ++j)
				{
					int second = j + counter;
					second = mod(second,A.size(1));
					multi *= A.get(j, second);
				}
				sum += multi;
				counter++;
			}

			counter = 0;
			for (int i = 0; i < A.size(1); ++i)
			{
				multi = 1;
				for (int j = A.size(1) - 1; j >= 0; --j)
				{
					int first = A.size(1) - j + counter;
					first = mod(first,A.size(1));
					multi *= A.get(first, j);
				}
				sum -= multi;
				counter++;
			}
			return sum;
		}
		else
		{
			Matrix process = A;
			for (int col = 0; col < process.size(2)-1; ++col)
			{
				for (int row = col + 1; row < process.size(1); ++row)
				{
					this->row_diff_nomod(process, row, 0, process.size(2)-1, process, col, static_cast<double>(process.get(row, col))/ static_cast<double>(process.get(col,col)) );	
				}
			}

			/*for (int i = 0; i < process.size(1); ++i)
			{
				for (int j = 0; j < process.size(2); ++j)
				{
					std::cout << process.get(i, j) << " ";
				}
				std::cout << std::endl;
			}*/
			// debug printing

			int mult = 1;
			for (int i = 0; i < A.size(1); ++i)
			{
				mult *= process.get(i, i);
			}
			return mult;
		}

	}
	else
	{
		return 0;
	}
}


//Private section
//convert the string of characters in s to the equivalent numerical values using our 29 character alphabet and put in matrix suitable for n-by-n encryption matrix
Matrix Hill::l2num(const std::string& s, unsigned int n)
{
	if (n >= 2)
	{
		unsigned int divide = std::floor(s.length() / n);
		unsigned int remain = mod(s.length(),n);
		unsigned int numRow;
		if (remain == 0)
		{
			numRow = divide;
		}
		else
		{
			numRow = divide + 1;
		}

		Matrix res(std::vector<int>(n), n, numRow);

		for (int i = 0; i < s.length(); ++i)
		{
			if (isalpha(s[i]))
			{
				int num = s[i] - 'A';
				res.set(i, num);
			}
			else
			{
				if (s[i] == '.')
				{
					res.set(i, 26);
				}
				else if (s[i] == '?')
				{
					res.set(i, 27);
				}
				else if (s[i] == ' ')
				{
					res.set(i, 28);
				}
			}
		}
		for (int i = s.length(); i < n*numRow; ++i)
		{
			res.set(i, 26);
		}
		return res;
	}
	else
	{
		std::vector<int> vec;
		Matrix result(vec, 0, 0);
		return result;
	}
	
	
}


//convert the matrix to a string of characters using our 29 character alphabet
std::string Hill::n2let(const Matrix& A)
{
	std::string result = "";
	for (int i = 0; i < A.size(1)*A.size(2); ++i)
	{
		int num = mod(A.get(i),29);
		if (num == 26)
		{
			result += '.';
		}
		else if (num == 27)
		{
			result += '?';
		}
		else if (num == 28)
		{
			result += ' ';
		}
		else
		{
			num += 65;
			char c = static_cast<char>(num);
			result += c;
		}
	}
	return result;
}

Matrix Hill::Identity_creation(unsigned int n)
{
	std::vector<int> vec;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == j)
			{
				vec.push_back(1);
			}
			else
			{
				vec.push_back(0);
			}
		}
	}
	Matrix identity(vec, n, n);
	return identity;
}

Matrix Hill::Echelon_Form(Matrix A, Matrix I)
{
	std::vector<int> vec;
	for (int i = 0; i < A.size(1)*A.size(2); ++i)
	{
		vec.push_back(A.get(i));
	}
	for (int i = 0; i < I.size(1)*I.size(2); ++i)
	{
		vec.push_back(I.get(i));	
	}
	Matrix res(vec, A.size(1), A.size(2) + I.size(2));
	return res;

}

//Calculate the matrix inversion of A, mod 29
Matrix Hill::inv_mod(Matrix A) {
	
	if (this->calculateDeterminant(A))
	{
		Matrix I = this->Identity_creation(A.size(1));
		Matrix Echelon = this->Echelon_Form(A, I);
		std::vector<int> temp;
		for (int i = 0; i < Echelon.size(1); ++i)
		{
			// switch row if (i,i) is zero
			if (Echelon.get(i, i) == 0)
			{
				temp.clear();
				for (int j = i + 1; j < Echelon.size(1); ++j)
				{
					if (Echelon.get(j, i) != 0)
					{
						for (int a = 0; a < Echelon.size(2); a++)
						{
							temp.push_back(Echelon.get(j, a));
						}
						for (int a = 0; a < Echelon.size(2); a++)
						{
							Echelon.set(j, a, Echelon.get(i, a));
						}
						for (int a = 0; a < Echelon.size(2); a++)
						{
							Echelon.set(i, a, temp[a]);
						}
						break;
					}
				}
			}
			this->row_mult(Echelon, i, 0, Echelon.size(2)-1, ZI29[Echelon.get(i,i)-1] );

			if (i + 1 < Echelon.size(1))
			{
				for (int a = 0; a <= i; ++a)
				{
					this->row_diff(Echelon, i + 1, 0, Echelon.size(2) - 1, Echelon, i, Echelon.get(i + 1, a));
				}
			}
		}
		
		int counter = 0;
		for (int i = Echelon.size(1) - 2; i >= 0; --i)
		{
			for (int j = Echelon.size(1) - 1 - counter; j<Echelon.size(1); ++j)
			{
				this->row_diff(Echelon, i, 0, Echelon.size(2)-1, Echelon, j, Echelon.get(i,j));
			}
			counter++;
		}

		std::vector<int> vec;
		for (int i = A.size(1)*A.size(2); i < Echelon.size(1)*Echelon.size(2); ++i)
		{
			vec.push_back(Echelon.get(i));
		}
		Matrix res(vec, A.size(1), A.size(2));
		return res;
	}
	else //an empty matrix is returned if A is not invertible
	{
		std::vector<int> vec;
		Matrix result(vec, 0, 0);
		return result;
	}
}

//calculate c = a mod b, where c = [0,b)
unsigned int Hill::mod(int a, int b) {
	unsigned int x;
	if (a >= 0)
	{
		x = a % b;
	}
	else
	{
		int process = a - (2 * a);
		int sub = process % b;
		x = b - sub;
	}
	
	return x;
}

//For row i of Matrix A, multiply columns j through k by c, mod 29
//(i.e., in Matlab notation A(i,j:k) = mod(c*A(i,j:k), 29))
//NOTE: matrix pass by reference means all operations occur in place
void Hill::row_mult(Matrix& A, unsigned int i, unsigned int j, unsigned int k, unsigned int c)
{
	if (i < A.size(1) && j < A.size(2) && k < A.size(2))
	{
		for (int a = j; a <= k; ++a)
		{
			A.set(i, a, mod(A.get(i, a)*c, 29));
		}
	}
}


//Multiply columns j through k of row l of Matrix B by c and subtract from columns j through k of row i of Matrix A, mod 29
//(i.e., in Matlab notation A(i,j:k) = mod(A(i,j:K) - c*B(l,j:k), 29)
//NOTE: matrix pass by reference means all operations occur in place
void Hill::row_diff(Matrix& A, unsigned int i, unsigned int j, unsigned int k, Matrix& B, unsigned int l, unsigned int c)
{
	if (i < A.size(1) && j < A.size(2) && k < A.size(2) && l < B.size(1))
	{
		for (int a = j; a <= k; ++a)
		{
			A.set(i, a, mod( A.get(i, a) - c*(B.get(l,a)), 29));
		}
	}
}

void Hill::row_diff_nomod(Matrix& A, unsigned int i, unsigned int j, unsigned int k, Matrix& B, unsigned int l, double c)
{
	if (i < A.size(1) && j < A.size(2) && k < A.size(2) && l < B.size(1))
	{
		for (int a = j; a <= k; ++a)
		{
			A.set(i, a, static_cast<int>( static_cast<double>(A.get(i, a)) - c*  (static_cast<double>(B.get(l, a)))    ) );
		}
	}
}
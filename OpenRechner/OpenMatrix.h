//================================Explaination===================================================
/*# Matrix Class

The Matrix class is a simple C++ class for storing and transforming matrices. It is designed to handle matrices of integer and double values.

## Class Methods

### Constructors

1. **Default Constructor**:
   - `Matrix() : mt("0") {};`
   - Creates an instance of the `Matrix` class with an empty matrix.

2. **Constructor with Values**:
   - `Matrix(string value) { mt = value; }`
   - Creates an instance of the `Matrix` class by taking a string `value` representing the matrix.

### Accessors and Mutators

3. **set_mat(string new_Matrix)**:
   - `void set_mat(string new_Matrix);`
   - This method allows you to set a new matrix for the `Matrix` instance. It takes a string `new_Matrix` as a parameter, representing the new matrix.

4. **get_mat()**:
   - `string get_mat();`
   - This method returns the current representation of the matrix as a string. You can use it to retrieve the matrix stored in the instance.

### Matrix Transformations

5. **transformtoi()**:
   - `vector<vector<int>> transformtoi();`
   - This method transforms the matrix into a matrix of integer values (`int`) and returns this matrix as a 2D vector. This can be useful if the matrix is stored as a string.

6. **transformtod()**:
   - `vector<vector<double>> transformtod();`
   - This method transforms the matrix into a matrix of double values (`double`) and returns this matrix as a 2D vector. This can be useful for working with double values.

## Usage Example

Here's a simple usage example of the `Matrix` class:

```cpp
#include "OpenMatrix.h"
#include <iostream>

int main() {
    OpenMatrix matrix("1 2 3; 4 5 6");
    std::string matString = matrix.get_mat();
    std::cout << "Matrix: " << matString << std::endl;

    // You can also use the transformtoi() and transformtod() methods here.

    return 0;
}
*/

#pragma once
using namespace std;

/**
 * @class OpenMatrix
 * @brief Class to represent an open matrix.
 */
class OpenMatrix
{
private:
    string mt; ///< Matrix data as a string

public:
    /**
     * @brief Default constructor. Initializes the matrix to "0".
     */
    OpenMatrix() : mt("0") {};

    /**
     * @brief Constructor with a matrix string.
     * @param value The matrix data as a string.
     */
    OpenMatrix(string value) { mt = value; }

    /**
     * @brief Destructor.
     */
    ~OpenMatrix() = default;

    /**
     * @brief Set the matrix data using a string.
     * @param ma_Matrice The matrix data as a string.
     */
    void set_mat(string ma_Matrice);

    /**
     * @brief Get the matrix data as a string.
     * @return The matrix data.
     */
    string get_mat();

    /**
     * @brief Transform the matrix data given by the user as a string to a vector of vectors of integers.
     * @return A 2D vector of integers representing the matrix.
     */
    vector<vector<int>> transformtoi();

    /**
     * @brief Transform the matrix data given by the user as a string to a vector of vectors of doubles.
     * @return A 2D vector of doubles representing the matrix.
     */
    vector<vector<double>> transformtod();
};



/* =========================================Explaination===========================================

	Constructors and Destructor:
        OpenFraction(): Default constructor.
        OpenFraction(int zz, int nn): General constructor with numerator zz and denominator nn.
        OpenFraction(int zz): Type conversion constructor with a single integer zz.
        ~OpenFraction(): Destructor.

    Operator Overloading for Basic Arithmetic Operations:
        operator+, operator-, operator*, and operator/ overloads for addition, subtraction, multiplication, and division.

    Compound Assignment Operators:
        operator+=, operator-=, operator*=, and operator/= for compound addition, subtraction, multiplication, and division.

    Prefix Increment and Decrement Operators:
        operator++ and operator-- for prefix increment and decrement.

    Comparison Operators:
        operator== and operator!= for equality and inequality comparisons.

    Helper Function:
        ggt(int x, int y): A helper function to find the greatest common divisor (GCD).

    Output Function:
        ausgabe(): A function to display the fraction.

    Setter and Getter Methods:
        set, set_z, set_n for setting the numerator and denominator.
        get_z and get_n for retrieving the numerator and denominator.

    Get a New Object:
        get(): Returns a new OpenFraction object with the current numerator and denominator.

    Friend Function for Output:

    operator<< is a friend function that allows overloading the stream output operator << to display the OpenFraction object.
	*/
#pragma once
using namespace std;

    /**
     * @class OpenFraction
     * @brief Class to represent an open fraction.
     */
class OpenFraction
{
private:
    int z; ///< Numerator
    int n; ///< Denominator

public:
    /**
     * @brief Default constructor. Initializes the fraction to 0/1.
     */
    OpenFraction();

    /**
     * @brief General constructor with numerator and denominator.
     * @param zz Numerator.
     * @param nn Denominator.
     */
    OpenFraction(int zz, int nn);

    /**
     * @brief Type conversion constructor with numerator (denominator defaults to 1).
     * @param zz Numerator.
     */
    OpenFraction(int zz);

    /**
     * @brief Destructor.
     */
    ~OpenFraction();

    /**
     * @brief Overload of addition operator for fractions.
     * @param r1 First fraction.
     * @param r2 Second fraction.
     * @return Result of addition as a new fraction.
     */
    friend OpenFraction operator+(OpenFraction r1, OpenFraction r2);

    /**
     * @brief Overload of subtraction operator for fractions.
     * @param r1 First fraction.
     * @param r2 Second fraction.
     * @return Result of subtraction as a new fraction.
     */
    friend OpenFraction operator-(OpenFraction r1, OpenFraction r2);

    /**
     * @brief Overload of multiplication operator for fractions.
     * @param r1 First fraction.
     * @param r2 Second fraction.
     * @return Result of multiplication as a new fraction.
     */
    friend OpenFraction operator*(OpenFraction r1, OpenFraction r2);

    /**
     * @brief Overload of division operator for fractions.
     * @param r1 First fraction.
     * @param r2 Second fraction.
     * @return Result of division as a new fraction.
     */
    friend OpenFraction operator/(OpenFraction r1, OpenFraction r2);

    /**
     * @brief Overload of addition-assignment operator for fractions.
     * @param f Fraction to add.
     * @return Reference to the modified fraction.
     */
    OpenFraction& operator+= (const OpenFraction& f);

    /**
     * @brief Overload of subtraction-assignment operator for fractions.
     * @param f Fraction to subtract.
     * @return Reference to the modified fraction.
     */
    OpenFraction& operator-= (const OpenFraction& f);

    /**
     * @brief Overload of multiplication-assignment operator for fractions.
     * @param f Fraction to multiply by.
     * @return Reference to the modified fraction.
     */
    OpenFraction& operator*= (const OpenFraction& f);

    /**
     * @brief Overload of division-assignment operator for fractions.
     * @param f Fraction to divide by.
     * @return Reference to the modified fraction.
     */
    OpenFraction& operator/= (const OpenFraction& f);

    /**
     * @brief Prefix increment operator for fractions.
     * @return Reference to the modified fraction.
     */
    OpenFraction& operator++();

    /**
     * @brief Prefix decrement operator for fractions.
     * @return Reference to the modified fraction.
     */
    OpenFraction& operator--();

    /**
     * @brief Equality operator for fractions.
     * @param f Fraction to compare.
     * @return True if the fractions are equal, false otherwise.
     */
    bool operator== (const OpenFraction& f);

    /**
     * @brief Inequality operator for fractions.
     * @param f Fraction to compare.
     * @return True if the fractions are not equal, false otherwise.
     */
    bool operator!= (const OpenFraction& f);

    /**
     * @brief Calculate the greatest common divisor (GCD) of two integers.
     * @param x First integer.
     * @param y Second integer.
     * @return GCD of x and y.
     */
    friend int ggt(int x, int y);

    /**
     * @brief Output function to display the fraction.
     */
    void ausgabe();

    /**
     * @brief Check if a number is an integer.
     * @param number The number to check.
     * @return True if the number is an integer, false otherwise.
     */
    bool isInteger(double number);

    /**
     * @brief Set the numerator and denominator of the fraction.
     * @param zz Numerator.
     * @param nn Denominator.
     */
    void set(int zz, int nn) { z = zz; n = nn; }

    /**
     * @brief Set the numerator of the fraction.
     * @param zz Numerator.
     */
    void set_z(int zz) { z = zz; }

    /**
     * @brief Set the denominator of the fraction.
     * @param nn Denominator.
     */
    void set_n(int nn) { n = nn; }

    /**
     * @brief Get the numerator of the fraction.
     * @return The numerator.
     */
    int get_z() { return this->z; }

    /**
     * @brief Get the denominator of the fraction.
     * @return The denominator.
     */
    int get_n() { return this->n; }

    /**
     * @brief Get a copy of the fraction.
     * @return A copy of the fraction.
     */
    OpenFraction get() { return *this; }

    /**
     * @brief Overload of the output operator to display the fraction.
     * @param out The output stream.
     * @param frac The OpenFraction object to display.
     * @return The updated output stream.
     */
    friend ostream& operator<<(ostream& out, OpenFraction& frac);

    /**
     * @brief Convert a double to a fraction.
     * @param value The double value to convert.
     * @param tolerance Tolerance for the conversion.
     * @return The resulting fraction.
     */
    OpenFraction to_frac(double value, double tolerance = 1.0E-6);
};

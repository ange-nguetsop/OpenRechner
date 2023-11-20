#pragma once

/**
 * @brief The OpenComplex class represents a complex number using variants.
 */
class OpenComplex
{
private:
    std::variant<int, float, double> real; /**< The real part of the complex number. */
    std::variant<int, float, double> imag; /**< The imaginary part of the complex number. */

public:
    /**
     * @brief Default constructor that initializes the complex number to 0+0i.
     */
    OpenComplex() { real = 0; imag = 0; }

    /**
     * @brief Parameterized constructor that initializes the complex number with given real and imaginary parts.
     * @param _real The real part of the complex number.
     * @param _imag The imaginary part of the complex number.
     */
    OpenComplex(std::variant<int, float, double> _real, std::variant<int, float, double> _imag) { real = _real; imag = _imag; }

    /**
     * @brief Constructor that initializes the complex number with a real part and sets the imaginary part to 0.
     * @param x The real part of the complex number.
     */
    OpenComplex(std::variant<int, float, double> x) { real = x; imag = 0; }

    /**
     * @brief Destructor for the OpenComplex class.
     */
    ~OpenComplex() {};

    /**
     * @brief Set the real part of the complex number.
     * @param x The new real part to set.
     */
    void set_real(std::variant<int, float, double>  x) { real = x; }

    /**
     * @brief Set the imaginary part of the complex number.
     * @param y The new imaginary part to set.
     */
    void set_imag(std::variant<int, float, double> y) { imag = y; }

    /**
     * @brief Set the imaginary part of the complex number from a C-string.
     * @param _imag The C-string to set the imaginary part.
     */
    void set_imag(const char* _imag);

    /**
     * @brief Set both real and imaginary parts of the complex number.
     * @param x The new real part.
     * @param y The new imaginary part.
     */
    void set_cmplx(std::variant<int, float, double>  x, std::variant<int, float, double>  y) { real = x; imag = y; }

    /**
     * @brief Convert a string to a complex number and set this instance to the parsed value.
     * @param _cmplx The string representation of the complex number.
     */
    void strtocmplx(const std::string& _cmplx);

    /**
     * @brief Get the real part of the complex number.
     * @return The real part of the complex number.
     */
    std::variant<int, float, double> get_real() const { return real; }

    /**
     * @brief Get the imaginary part of the complex number.
     * @return The imaginary part of the complex number.
     */
    std::variant<int, float, double> get_imag() const { return imag; }

    /**
     * @brief Print the complex number in the form 'a+bi'.
     */
    void ausgabe();

    /**
     * @brief Get a reference to the current complex number.
     * @return A reference to the current complex number.
     */
    OpenComplex& get_cmplx() { return *this; }

    // Friend Functions

    /**
     * @brief Overload the addition operator for complex numbers.
     * @param z1 The first complex number.
     * @param z2 The second complex number.
     * @return The result of the addition.
     */
    friend OpenComplex operator+(const OpenComplex& z1, const OpenComplex& z2);

    /**
     * @brief Overload the subtraction operator for complex numbers.
     * @param z1 The first complex number.
     * @param z2 The second complex number.
     * @return The result of the subtraction.
     */
    friend OpenComplex operator-(const OpenComplex& z1, const OpenComplex& z2);

    /**
     * @brief Overload the multiplication operator for complex numbers.
     * @param z1 The first complex number.
     * @param z2 The second complex number.
     * @return The result of the multiplication.
     */
    friend OpenComplex operator*(const OpenComplex& z1, const OpenComplex& z2);

    /**
     * @brief Overload the division operator for complex numbers.
     * @param z1 The first complex number.
     * @param z2 The second complex number (cannot be zero).
     * @return The result of the division.
     */
    friend OpenComplex operator/(const OpenComplex& z1, const OpenComplex& z2);

    /**
     * @brief Overload the output stream operator to print a complex number.
     * @param out The output stream.
     * @param objet The complex number to be printed.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& out, const OpenComplex& objet);

    // Compound Assignment Operators

    /**
     * @brief Overload the compound addition assignment operator for complex numbers.
     * @param z The complex number to add.
     * @return A reference to the updated complex number.
     */
    OpenComplex& operator+= (const OpenComplex& z);

    /**
     * @brief Overload the compound subtraction assignment operator for complex numbers.
     * @param z The complex number to subtract.
     * @return A reference to the updated complex number.
     */
    OpenComplex& operator-= (const OpenComplex& z);

    /**
     * @brief Overload the compound multiplication assignment operator for complex numbers.
     * @param z The complex number to multiply by.
     * @return A reference to the updated complex number.
     */
    OpenComplex& operator*= (const OpenComplex& z);

    /**
     * @brief Overload the compound division assignment operator for complex numbers.
     * @param z The complex number to divide by (cannot be zero).
     * @return A reference to the updated complex number.
     */
    OpenComplex& operator/= (const OpenComplex& z);

    /**
     * @brief Overload the prefix increment operator (++z).
     * Increment the real part.
     * @return A reference to the updated complex number.
     */
    OpenComplex& operator++ ();

    /**
     * @brief Overload the postfix increment operator (z++).
     * Increment the imaginary part.
     * @return A reference to the updated complex number.
     */
    OpenComplex& operator++ (int);

    /**
     * @brief Overload the prefix decrement operator (--z).
     * Decrement the real part.
     * @return A reference to the updated complex number.
     */
    OpenComplex& operator-- ();

    /**
     * @brief Overload the postfix decrement operator (z--).
     * Decrement the imaginary part.
     * @return A reference to the updated complex number.
     */
    OpenComplex& operator-- (int);

    /**
     * @brief Overload the equality operator to compare complex numbers for equality.
     * @param z The complex number to compare with.
     * @return True if the complex numbers are equal, false otherwise.
     */
    bool operator== (const OpenComplex& z);

    /**
     * @brief Overload the inequality operator to compare complex numbers for inequality.
     * @param z The complex number to compare with.
     * @return True if the complex numbers are not equal, false otherwise.
     */
    bool operator!= (const OpenComplex& z);

    /**
     * @brief Convert the complex number to polar form (r, θ).
     * @details Updates the real part to the magnitude (r) and the imaginary part to the angle (θ).
     */
    void polar();

    /**
     * @brief Overload the unary negation operator (-z).
     * @return The complex number with negated real and imaginary parts.
     */
    OpenComplex operator*();

    /**
     * @brief Calculate the magnitude (absolute value) of the complex number.
     * @return The magnitude as a variant type.
     */
    std::variant<int, float, double> betrag();

    /**
     * @brief Calculate the angle (argument) of the complex number.
     * @param art If false, return the argument in radians; if true, return the argument in degrees.
     * @return The argument as a variant type.
     */
    std::variant<int, float, double> winkel(bool art = false);

    /**
     * @brief Get the imaginary part as a double.
     * @return The imaginary part as a double.
     */
    double get_imag_as_double() const;

    /**
     * @brief Get the real part as a double.
     * @return The real part as a double.
     */
    double get_real_as_double() const;
};

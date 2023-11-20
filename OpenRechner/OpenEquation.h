#pragma once
using namespace std;

/**
 * @brief Class to represent an open equation.
 */
class OpenEquation
{
private:
    /// The equation stored as a string.
    string equation;

public:
    /**
     * @brief Default constructor. Initializes the equation to "0".
     */
    OpenEquation() { equation = "0"; }

    /**
     * @brief Constructor with a given equation string.
     * @param _equ The equation string to initialize.
     */
    OpenEquation(string _equ) { equation = _equ; }

    /**
     * @brief Default destructor.
     */
    ~OpenEquation() = default;

    /**
     * @brief Transform the equation as string enter by the user  into a vector of doubles.
     * @return The vector of doubles resulting from the transformation of the equation.
     */
    vector<double> transform();

    /**
     * @brief Get the currently stored equation as a string.
     * @return The current equation as a string.
     */
    string get() { return this->equation; }

    /**
     * @brief Display the equation in the console.
     */
    void display() { cout << this->equation << endl; }

    /**
     * @brief Overload of the output operator to display the equation.
     * @param out The output stream.
     * @param equ The OpenEquation object to display.
     * @return The updated output stream.
     */
    friend ostream& operator<<(ostream& out, OpenEquation equ);
};


# Open Rechner

## Overview
This console line calculator allows users to perform a range of mathematical operations from basic (addition, subtraction, multiplication, division) to complex (utilizing mathematical functions like sin, cos, sqrt, tan, etc.). It can handle complex numbers and convert decimal numbers into fractions. Users can also mix operation types and set priorities using parentheses.

## How It Works

Operating this calculator is straightforward:
- Enter the desired calculation and press the Enter key to display the result.

There are two possible scenarios after performing a calculation:
1. If you declare an operation like `>> a = sqrt(5 * 2) + sin(5)`, the result will be stored in the variable `a`. This variable can be reused at any time for new assignments or to be used in another calculation.
2. If your operation is like `>> sqrt(14*3) + 1/2`, the result will be stored in an automatic system variable named `ans`. This variable's value is updated every time a calculation is performed without being assigned to a specific variable.

### Converting to Fractions
- Use the `frac()` function to convert a decimal number into a rational number (fraction).

### Displaying Variables
- Enter `dsp` to display all variables stored during the session.
- Enter the specific variable name to display its name, value, and type (`int`, `double`, `OpenComplex`, `OpenFraction`, `OpenMatrix`).

### Tip
- During your session, if you prefer not to display the result after each operation, you can add a semicolon at the end of the operation like `>> a = 5 + 2;`. This will store the result directly in the variable `a` without displaying it on the screen. The variable can be displayed by typing its name in the console.

## Upcoming Features
- **Matrix Calculations**: Work is in progress to enable matrix calculations.
- **Equation Solving**: Future updates will include solving equations.

## Getting Started

### Prerequisites
- Ensure you have a C++ compiler installed on your system.

### Installation

1. Clone the repository using the following command:
   ```bash
   git clone https://github.com/your-username/your-repository-name.git


### How to use it?
After cloning the repository, open the Openrechner.cpp file and run it. You'll then be able to take full advantage of the calculator's functionality. 

   
![Alt Exemples](https://github.com/ange-nguetsop/OpenRechner/blob/master/OpenRechner/Exemple1.png)
![Alt Exemples](https://github.com/ange-nguetsop/OpenRechner/blob/master/OpenRechner/Exemple2.png)

## Dependencies
- C++ Standard Library
- exprtk for handling basic expression calculations

## Contributing
Contributions to enhance the calculator's functionality or improve its efficiency are welcome. Please read `CONTRIBUTING.md` for details on our code of conduct and the process for submitting pull requests.

## License
This project is licensed under the MIT License - see the `LICENSE.md` file for details.

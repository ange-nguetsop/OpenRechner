#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <cctype>
#include "OpmlaborVariable.h"

class calculator 
{
public:
    calculator();

    void run();
    void setVariableValue(std::vector<OpmlaborVariable>& variables, std::string name, int _Typ = 3, std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> _value = 0.0);
    OpmlaborVariable getVariableValue(std::vector<OpmlaborVariable>& variables, std::string name);
    bool searchVariable(std::vector<OpmlaborVariable>& variables, std::string _name);
    bool isOperator(std::string c);
    int precedence(char op);
    std::vector<std::string> toRPN(const std::string& expr, std::vector<OpmlaborVariable> Data);
    std::variant<int,float,double,std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex > evalRPN(const std::vector<std::string>& rpn);
    std::string removeSpacesAndEOL(const std::string& input);
    //bool isPatternMatch(const std::string& input);
    int isInteger(std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> number);
    std::string removeSpaces(const std::string& input);
    bool containsAlphabetLetter(const std::string& input);
    bool isVariableNameValid(const std::string& name);
    std::string typeToString(OpmlaborVariable::Type type);
    void displayVar(const OpmlaborVariable& var);
    void displayValue(const std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> var);
    std::string complexToString(const OpenComplex& complex);
    bool isComplexNumber(const std::string& input);
    void DisplayAllVariables(const vector<OpmlaborVariable> var);
    std::string extractTextBetweenParentheses(const std::string& input);

};

#endif // CALCULATOR_H

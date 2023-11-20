#include"stdafx.h"
#include "calculator.h"
#include "exprtk.hpp"
#include <cstdio>

typedef exprtk::symbol_table<double> symbol_table_t;
symbol_table_t symbol_table;
std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> result;

//For basis operations

using namespace std;

calculator::calculator() {}

void calculator::run()
{
	vector<OpmlaborVariable> Data;
	typedef exprtk::expression<double>  expression_t;
	typedef exprtk::parser<double>      parser_t;
	expression_t expression;
	parser_t parser;

	while (true)

	{
	Loop:
		cout << endl;
		cout << endl;

		std::string expr;
		std::cout << ">> ";
		std::getline(std::cin, expr);
		expr = removeSpaces(expr);


		string nameVar = "ans";
		string calc = expr;
		size_t found = calc.find("=");
		calc = removeSpacesAndEOL(calc);
		std::vector<string> rpn;

		if (calc.empty() || calc == "exit") {
			break; //exit the code
		}

		if (calc == "dsp")
		{
			if (!Data.empty())
				DisplayAllVariables(Data);
			else
				cout << "No variables stored yet." << endl;

		}

		else if (calc.find(";") != std::string::npos)
		{
			calc = calc.erase(calc.size() - 1);
			if (calc.find("\"") != std::string::npos) // Es gibt eine Zuweisung in dem string. bsp: a = "Daryl" ;
			{
				nameVar = calc.substr(0, found); // Name der Var wird hier gespeichert Bsp: nameVar = a
				calc = calc.substr(found + 1);  // Hier wird die Berechnung gespeichert Bsp: calc = "Daryl"
				setVariableValue(Data, nameVar, 4, calc);
			}
			else
			{
				if (found != std::string::npos) // Es gibt eine Zuweisung in dem string. bsp: a = 5 * 2 ;
				{
					nameVar = calc.substr(0, found); // Name der Var wird hier gespeichert Bsp: nameVar = a
					calc = calc.substr(found + 1);  // Hier wird die Berechnung gespeichert Bsp: calc = 5 * 2

					if (!isVariableNameValid(nameVar))
					{
						cout << "\"" << nameVar << "\": Invalid variable name" << endl;
						goto Loop;
					}

					if (calc.find("frac") != std::string::npos)
					{
						std::string input = extractTextBetweenParentheses(calc);
						if (searchVariable(Data, input))
						{
							if (std::holds_alternative<double>(getVariableValue(Data, input).getValue()))
							{
								double value = get<double>(getVariableValue(Data, input).getValue());
								OpenFraction res = res.to_frac(value);
								setVariableValue(Data, nameVar, 9, res);
							}

						}
						else if (stod(input))
						{
							OpenFraction res = res.to_frac(stod(input));
							setVariableValue(Data, nameVar, 9, res);
						}
						goto Loop;
					}

					expression.register_symbol_table(symbol_table);

					if (!parser.compile(calc, expression))
					{
						rpn = toRPN(calc, Data);

						if (rpn.size() == 0)
						{
							std::cout << "Invalid input !" << std::endl;
							goto Loop;
						}

					}

				}
				else // Es gibt keine Zuweisung Bsp: 5 + 2 * 3 oder a
				{
					if (searchVariable(Data, calc.substr(0, calc.size() - 1))) // Wenn der Anwender nach einem bestimmten Variable fragt
					{
						OpmlaborVariable res = getVariableValue(Data, calc.substr(0, calc.size() - 1));
						displayVar(res);
					}
					else if (calc.find("frac") != std::string::npos)
					{
						std::string input = extractTextBetweenParentheses(calc);
						if (searchVariable(Data, input))
						{
							if (std::holds_alternative<double>(getVariableValue(Data, input).getValue()))
							{
								double value = get<double>(getVariableValue(Data, input).getValue());
								OpenFraction res = res.to_frac(value);
								setVariableValue(Data, nameVar, 9, res);
							}

						}
						else if (stod(input)) {
							OpenFraction res = res.to_frac(stod(input));
							setVariableValue(Data, nameVar, 9, res);
						}
						goto Loop;
					}
					else
					{
						expression.register_symbol_table(symbol_table);
						if (!parser.compile(calc, expression))
						{
							rpn = toRPN(calc, Data);
							if (rpn.size() == 0)
							{
								std::cout << "Invalid input !" << std::endl;
								goto Loop;
							}
						}
					}


				}

				if (parser.compile(calc, expression) || !rpn.empty())
				{
					if (!rpn.empty())
					{
						result = evalRPN(rpn);
					}
					else
					{
						result = expression.value();
					}

					int _type = isInteger(result);

					if (found != std::string::npos)
					{
						switch (_type)
						{
						case 1:
							setVariableValue(Data, nameVar, 1, result);
							break;
						case 2:
							setVariableValue(Data, nameVar, 2, result);
							break;
						case 3:
							setVariableValue(Data, nameVar, 3, result);
							break;
						default:
							setVariableValue(Data, nameVar, 10, result);
							break;
						}

					}
					else
					{
						switch (_type)
						{
						case 1:
							setVariableValue(Data, "ans", 1, result);
							break;
						case 2:
							setVariableValue(Data, "ans", 2, result);
							break;
						case 3:
							setVariableValue(Data, "ans", 3, result);
							break;
						default:
							setVariableValue(Data, "ans", 10, result);
							break;
						}

					}

				}
			}

		}
		else
		{
			if (calc.find("\"") != std::string::npos) // Es gibt eine Zuweisung in dem string. bsp: a = "Daryl" ;
			{
				nameVar = calc.substr(0, found); // Name der Var wird hier gespeichert Bsp: nameVar = a
				calc = calc.substr(found + 1);  // Hier wird die Berechnung gespeichert Bsp: calc = "Daryl"
				setVariableValue(Data, nameVar, 4, calc);
				cout << nameVar << " = " << calc << endl;
			}
			else
			{
				if (found != std::string::npos) // Es gibt eine Zuweisung in dem string. bsp: a = 5 * 2
				{
					nameVar = expr.substr(0, found); // Name der Var wird hier gespeichert Bsp: nameVar = a
					calc = expr.substr(found + 1);  // Hier wird die Berechnung gespeichert Bsp: calc = 5 * 2

					if (!isVariableNameValid(nameVar))
					{
						cout << "\"" << nameVar << "\": Invalid variable name" << endl;
						goto Loop;
					}
					else if (calc.find("frac") != std::string::npos)
					{
						std::string input = extractTextBetweenParentheses(calc);
						if (searchVariable(Data, input))
						{
							if (std::holds_alternative<double>(getVariableValue(Data, input).getValue()))
							{
								double value = get<double>(getVariableValue(Data, input).getValue());
								OpenFraction res = res.to_frac(value);
								setVariableValue(Data, nameVar, 9, res);
								std::cout << nameVar << " = ";
								displayValue(res);

							}

						}
						else if (stod(input)) {
							OpenFraction res = res.to_frac(stod(input));
							setVariableValue(Data, nameVar, 9, res);
							std::cout << nameVar << " = ";
							displayValue(res);
						}
						goto Loop;
					}
					else
					{
						expression.register_symbol_table(symbol_table);
						if (!parser.compile(calc, expression))
						{
							rpn = toRPN(calc, Data);
							if (rpn.size() == 0)
							{
								std::cout << "Invalid input !" << std::endl;
								goto Loop;
							}

						}

					}

				}
				else // Es gibt keine Zuweisung Bsp: 5 + 2 * 3
				{
					if (searchVariable(Data, calc)) // Wenn der Anwender nach einem bestimmten Variable nachfragt
					{
						OpmlaborVariable res = getVariableValue(Data, calc);
						displayVar(res);
						goto Loop;
					}
					else if (calc.find("frac") != std::string::npos)
					{
						std::string input = extractTextBetweenParentheses(calc);
						if (searchVariable(Data, input))
						{
							if (std::holds_alternative<double>(getVariableValue(Data, input).getValue()))
							{
								double value = get<double>(getVariableValue(Data, input).getValue());
								OpenFraction res = res.to_frac(value);
								setVariableValue(Data, nameVar, 9, res);
								std::cout << nameVar << " = ";
								displayValue(res);

							}

						}
						else if (stod(input)) {
							OpenFraction res = res.to_frac(stod(input));
							setVariableValue(Data, nameVar, 9, res);
							std::cout << nameVar << " = ";
							displayValue(res);
						}
						goto Loop;
					}
					else
						// Hier wird der Ausdruck umgewandelt.Bsp: a + 3 = > a = value(a) + 3 falls a bereits gespeichert wurde.
					{
						expression.register_symbol_table(symbol_table);
						if (!parser.compile(calc, expression))
						{
							rpn = toRPN(calc, Data);
							if (rpn.size() == 0)
							{
								std::cout << "Invalid input !" << std::endl;
								goto Loop;
							}

						}
					}
				}
				//std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> result = expression.value(); //evalRPN(rpn);
				if (parser.compile(calc, expression) || (!rpn.empty()))  //Dann hat der Anwender nach einem bestimmten Variable nachgefragt.Nichts muss weiter gemacht werden. Wurde schon behandelt
				{
					if (!rpn.empty())
					{
						result = evalRPN(rpn);
					}
					else
					{
						result = expression.value();
					}

					int _type = isInteger(result);
					if (found != std::string::npos)
					{
						switch (_type)
						{
						case 1:
							setVariableValue(Data, nameVar, 1, result);
							std::cout << nameVar << " = ";
							displayValue(result);
							break;
						case 2:
							setVariableValue(Data, nameVar, 2, result);
							std::cout << nameVar << " = ";
							displayValue(result);
							break;
						case 3:
							setVariableValue(Data, nameVar, 3, result);
							std::cout << nameVar << " = ";
							displayValue(result);
							break;
						default:
							setVariableValue(Data, nameVar, 10, result);
							std::cout << nameVar << " = ";
							displayValue(result);
							break;
						}



					}


					else
					{
						switch (_type)
						{
						case 1:
							setVariableValue(Data, "ans", 1, result);
							std::cout << "ans = ";
							displayValue(result);
							break;
						case 2:
							setVariableValue(Data, "ans", 2, result);
							std::cout << "ans = ";
							displayValue(result);
							break;
						case 3:
							setVariableValue(Data, "ans", 3, result);
							std::cout << "ans = ";
							displayValue(result);
							break;
						default:
							setVariableValue(Data, "ans", 10, result);
							std::cout << "ans = ";
							displayValue(result);
							break;
						}
					}

				}
			}

		}

	}


}

// Définissez le reste des fonctions membres de la classe Calculator ici

void calculator::setVariableValue(vector<OpmlaborVariable>& variables, std::string name, int _Typ, std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> _value)
{
	bool newVar = true;

	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].getName() == name)
		{
			variables[i].setValue(_value);
			variables[i].setType(_Typ);
			newVar = false;
			if (std::holds_alternative<double>(_value) || std::holds_alternative<int>(_value))
			{
				symbol_table.add_variable(name, get<double>(_value));
				symbol_table.add_constants();
			}

		}
	}
	// Wenn die Variable nicht gefunden wurde, füge sie hinzu
	if (newVar)
	{
		OpmlaborVariable var;
		var.setValue(_value);
		var.setName(name);
		var.setType(_Typ);
		variables.push_back(var);
		if (std::holds_alternative<double>(_value) || std::holds_alternative<int>(_value))
		{
			symbol_table.add_variable(name, get<double>(_value));
			symbol_table.add_constants();
		}
	}

}

OpmlaborVariable calculator::getVariableValue(vector<OpmlaborVariable>& variables, string name)
{
	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].getName() == name)
		{
			return variables[i];
		}
	}

	cout << "Fehler: Variable " << name << "wurde nicht gefunden." << endl;
	return  OpmlaborVariable();
	// exit(EXIT_FAILURE);
}

bool calculator::searchVariable(vector<OpmlaborVariable>& variables, std::string _name)
{
	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].getName() == _name)
		{
			return true;
		}
	}
	return false;
}

bool calculator::isOperator(string c) {
	return c == "+" || c == "-" || c == "*" || c == "/";
}

int calculator::precedence(char op) {
	switch (op) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return 0;
	}
}

std::vector<string> calculator::toRPN(const std::string& expr, vector<OpmlaborVariable> Data)
{
	std::stack<string> s;
	std::vector<string> output;
	vector<string> tokens;
	//if (expr.find("i") != std::string::npos) tokens.push_back("OpenComplex");
	//std::regex term_regex("(([-]?[0-9]*\\.?[0-9]+)?i?)|[+*/]");
	std::regex term_regex("([-]?\\d+(\\.\\d+)?[ ]?[-][-]?\\d+(\\.\\d+)?i)|([-]?\\d+(\\.\\d+)?i)|([-]?\\d+(\\.\\d+)?)|([+*/()])|([-]?[a-zA-Z_][a-zA-Z0-9_]*)|[-]");
	//std::regex term_regex("([-]?\\d+(\\.\\d+)?[ ]?[-][-]?\\d+(\\.\\d+)?i)|([-]?\\d+(\\.\\d+)?i)|([-]?\\d+(\\.\\d+)?)|([+*/()])|([-]?[a-zA-Z_][a-zA-Z0-9_]*)");
	std::sregex_token_iterator iter(expr.begin(), expr.end(), term_regex);
	std::sregex_token_iterator end;

	for (; iter != end; ++iter)
	{
		std::string token = iter->str();
		if (!tokens.empty() && token[0] == '-' && (!isOperator(tokens.back())) && tokens.back() != "(" && tokens.back() != ")")
		{
			tokens.push_back("-");
			tokens.push_back(token.substr(1));
		}
		else if (token == "") { continue; }
		else
		{
			tokens.push_back(token);
		}
	}

	for (std::string token : tokens)
	{

		if (!isOperator(token) && token != "(" && token != ")")
		{
			if (containsAlphabetLetter(token)) // entweder Complex oder gespeicherte Variable oder error
			{
				if (token[0] == '-')
				{
					string cer = token;
					token = token.substr(1);
					if (searchVariable(Data, token))
					{      // gespeicherte Variable
						std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> value = getVariableValue(Data, token).getValue();
						if (std::holds_alternative<int>(value))
							output.push_back(to_string((-1) * get<int>(value)));
						else if (std::holds_alternative<float>(value))
							output.push_back(to_string((-1) * get<float>(value)));
						else if (std::holds_alternative<double>(value))
							output.push_back(to_string((-1) * get<float>(value)));
						else if (std::holds_alternative<OpenComplex>(value))
						{
							OpenComplex tmp = OpenComplex(-1) * get<OpenComplex>(value);
							string cplx = complexToString(tmp);
							output.push_back(cplx);
						}

					}
					else if (isComplexNumber(token))
					{
						token = "-" + token;
						output.push_back(token);
					}
					else
					{
						cout << "'" << cer << "': " << "unknown variable oder invalid input" << endl;
						return std::vector<string>();
					}
				}
				else
				{
					if (searchVariable(Data, token))
					{
						std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> value = getVariableValue(Data, token).getValue();
						if (std::holds_alternative<int>(value))
							output.push_back(to_string(get<int>(value)));
						else if (std::holds_alternative<float>(value))
							output.push_back(to_string(get<float>(value)));
						else if (std::holds_alternative<double>(value))
							output.push_back(to_string(get<double>(value)));
						else if (std::holds_alternative<OpenComplex>(value))
						{
							OpenComplex tmp = get<OpenComplex>(value);
							string cplx = complexToString(tmp);
							output.push_back(cplx);
						}

					}
					else if (isComplexNumber(token))
					{
						output.push_back(token);
					}
					else if (token == "") { continue; }
					else
					{
						cout << "'" << token << "' invalid input or variable nicht gefunden." << endl;
						return std::vector<string>();
					}

				}

			}
			else
			{
				try
				{
					if (token == "")continue;
					else
					{
						double value = stod(token);
						output.push_back(token);
					}

				}
				catch (const std::exception& e)
				{
					cout << e.what() << endl;
					cout << token << " variable nicht gefunden or invalid input" << endl;
					return std::vector<string>();
				}
			}

		}
		else if (isOperator(token)) {
			while (!s.empty() && precedence(s.top()[0]) >= precedence(token[0])) {
				output.push_back(s.top());
				s.pop();
			}
			s.push(token);
		}
		else if (token == "") { continue; }
		else if (token == "(") {
			s.push(token);
		}
		else if (token == ")") {
			while (!s.empty() && s.top() != "(") {
				output.push_back(s.top());
				s.pop();
			}
			if (!s.empty() && s.top() == "(") {
				s.pop(); // Pop the opening parenthesis
			}
		}
	}

	while (!s.empty()) {
		output.push_back(s.top());
		s.pop();
	}

	return output;
}

std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex > calculator::evalRPN(const std::vector<string>& rpn) {
	std::stack<OpenComplex> s;
	for (string c : rpn)
	{
		if (isOperator(c))
		{
			OpenComplex b = s.top();
			s.pop();
			OpenComplex a = s.top();
			s.pop();
			char op = c[0];
			switch (op) {
			case '+':
				s.push(a + b);
				break;
			case '-':
				s.push(a - b);
				break;
			case '*':
				s.push(a * b);
				break;
			case '/':
				s.push(a / b);
				break;
			}
		}
		else if (c == "") { continue; }
		else
		{
			OpenComplex tmp;
			tmp.strtocmplx(c);
			s.push(tmp);
		}
	}
	if (s.top().get_imag_as_double() == 0.0)
	{
		if (std::holds_alternative<int>(s.top().get_real()))
			return get<int>(s.top().get_real());
		if (std::holds_alternative<float>(s.top().get_real()))
			return get<float>(s.top().get_real());
		if (std::holds_alternative<double>(s.top().get_real()))
			return get<double>(s.top().get_real());
	}
	else if (s.top().get_real_as_double() == 0.0)
	{
		if (std::holds_alternative<int>(s.top().get_imag()))
			return OpenComplex(0, get<int>(s.top().get_imag()));
		if (std::holds_alternative<float>(s.top().get_imag()))
			return OpenComplex(0, get<float>(s.top().get_imag()));
		if (std::holds_alternative<double>(s.top().get_imag()))
			return OpenComplex(0, get<double>(s.top().get_imag()));
	}
	else
	{
		if (std::holds_alternative<int>(s.top().get_real()) && std::holds_alternative<int>(s.top().get_imag()))
			return OpenComplex(get<int>(s.top().get_real()), get<int>(s.top().get_imag()));
		else if (std::holds_alternative<float>(s.top().get_real()) && std::holds_alternative<float>(s.top().get_imag()))
			return OpenComplex(get<float>(s.top().get_real()), get<float>(s.top().get_imag()));
		else if (std::holds_alternative<double>(s.top().get_real()) && std::holds_alternative<double>(s.top().get_imag()))
			return OpenComplex(get<double>(s.top().get_real()), get<double>(s.top().get_imag()));
		else
			return s.top();
	}

}

std::string calculator::removeSpacesAndEOL(const std::string& input) {
	std::string result;

	for (char c : input) {
		if (c != '\n' && c != '\r') {
			result += c;
		}
	}

	return result;
}

int calculator::isInteger(std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> number) {
	if (std::holds_alternative<int>(number)) {
		return 1;
	}
	else if (std::holds_alternative<float>(number)) {
		return 2;
	}
	else if (std::holds_alternative<double>(number)) {
		return 3;
	}
	else if (std::holds_alternative<OpenFraction>(number))
	{
		return 9;
	}
	else {
		return 10;
	}
}

std::string calculator::removeSpaces(const std::string& input) {
	std::string result;
	for (char c : input) {
		if (c != ' ') {
			result += c;
		}
	}
	return result;
}

bool calculator::containsAlphabetLetter(const std::string& input) {
	for (char c : input) {
		if (std::isalpha(c)) {
			return true; // Si un caractère est une lettre, retourner vrai.
		}
	}
	return false; // Aucune lettre de l'alphabet trouvée.
}

bool calculator::isVariableNameValid(const std::string& name) {
	// Un nom de variable doit commencer par une lettre ou un soulignement.
	if (!isalpha(name[0]) && name[0] != '_') {
		return false;
	}

	// Vérification des caractères suivants : lettres, chiffres ou soulignements.
	for (char c : name) {
		if (!isalnum(c) && c != '_') {
			return false;
		}
	}

	return true;
}

std::string calculator::typeToString(OpmlaborVariable::Type type) {
	switch (type)
	{
	case OpmlaborVariable::INT: return "INT";
	case OpmlaborVariable::FLOAT: return "FLOAT";
	case OpmlaborVariable::DOUBLE: return "DOUBLE";
	case OpmlaborVariable::STRING: return "STRING";
	case OpmlaborVariable::NONE: return "NONE";
	case OpmlaborVariable::OPenCVMat: return "OPenCVMat";
	case OpmlaborVariable::Openm: return "OpenMatrix";
	case OpmlaborVariable::OpenE: return "OpenEquation";
	case OpmlaborVariable::OpenF: return "OpenFraction";
	case OpmlaborVariable::OpenC: return "OpenComplex";

	default: return "UNKNOWN";
	}
}

void calculator::displayVar(const OpmlaborVariable& var) {
	const auto& value = var.getValue();
	std::cout << "Name: " << var.getName() << endl << "Type: " << typeToString(var.getType()) << endl << "Value: ";
	if (auto intValue = std::get_if<int>(&value)) {
		std::cout << *intValue;
	}
	else if (auto floatValue = std::get_if<float>(&value)) {
		std::cout << *floatValue;
	}
	else if (auto doubleValue = std::get_if<double>(&value)) {
		std::cout << *doubleValue;
	}
	else if (auto stringValue = std::get_if<std::string>(&value)) {
		std::cout << *stringValue;
	}

	else if (auto matValue = std::get_if<cv::Mat>(&value)) {
		std::cout << matValue->rows << "x" << matValue->cols << ", type=" << matValue->type() << std::endl;

		std::cout << *matValue << std::endl;
	}

	else if (auto opentest = std::get_if<OpenMatrix>(&value)) {

		OpenMatrix temp = *opentest;
		std::cout << std::string(temp.get_mat());
	}

	else if (auto opentest = std::get_if<OpenEquation>(&value)) {

		OpenEquation temp = *opentest;
		std::cout << std::string(temp.get());
	}
	else if (auto opentest = std::get_if<OpenFraction>(&value)) {

		OpenFraction temp = *opentest;
		std::cout << temp;
	}
	else if (auto opentest = std::get_if<OpenComplex>(&value)) {

		OpenComplex temp = *opentest;
		std::cout << temp;
	}


	std::cout << std::endl;
}

void calculator::displayValue(const std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> var) {
	const auto& value = var;

	if (auto intValue = std::get_if<int>(&value)) {
		std::cout << *intValue;
	}
	else if (auto floatValue = std::get_if<float>(&value)) {
		std::cout << *floatValue;
	}
	else if (auto doubleValue = std::get_if<double>(&value)) {
		std::cout << *doubleValue;
	}
	else if (auto stringValue = std::get_if<std::string>(&value)) {
		std::cout << *stringValue;
	}

	else if (auto matValue = std::get_if<cv::Mat>(&value)) {
		std::cout << matValue->rows << "x" << matValue->cols << ", type=" << matValue->type() << std::endl;

		std::cout << *matValue << std::endl;
	}

	else if (auto opentest = std::get_if<OpenMatrix>(&value)) {

		OpenMatrix temp = *opentest;
		std::cout << std::string(temp.get_mat());
	}

	else if (auto opentest = std::get_if<OpenEquation>(&value)) {

		OpenEquation temp = *opentest;
		std::cout << std::string(temp.get());
	}
	else if (auto opentest = std::get_if<OpenFraction>(&value)) {

		OpenFraction temp = *opentest;
		std::cout << temp;
	}
	else if (auto opentest = std::get_if<OpenComplex>(&value)) {

		OpenComplex temp = *opentest;
		std::cout << temp;
	}
}

std::string calculator::complexToString(const OpenComplex& complex) {
	// Convertir les parties réelle et imaginaire en chaînes de caractères
	std::string realStr, imagStr;

	if (std::holds_alternative<int>(complex.get_real())) {
		realStr = std::to_string(std::get<int>(complex.get_real()));
	}
	else if (std::holds_alternative<float>(complex.get_real())) {
		realStr = std::to_string(std::get<float>(complex.get_real()));
	}
	else if (std::holds_alternative<double>(complex.get_real())) {
		realStr = std::to_string(std::get<double>(complex.get_real()));
	}

	if (std::holds_alternative<int>(complex.get_imag())) {
		int imagValue = std::get<int>(complex.get_imag());
		if (imagValue >= 0) {
			imagStr = "+ " + std::to_string(imagValue) + "i";
		}
		else {
			imagStr = "- " + std::to_string(-imagValue) + "i";
		}
	}
	else if (std::holds_alternative<float>(complex.get_imag())) {
		float imagValue = std::get<float>(complex.get_imag());
		if (imagValue >= 0) {
			imagStr = "+ " + std::to_string(imagValue) + "i";
		}
		else {
			imagStr = "- " + std::to_string(-imagValue) + "i";
		}
	}
	else if (std::holds_alternative<double>(complex.get_imag())) {
		double imagValue = std::get<double>(complex.get_imag());
		if (imagValue >= 0) {
			imagStr = "+ " + std::to_string(imagValue) + "i";
		}
		else {
			imagStr = "- " + std::to_string(-imagValue) + "i";
		}
	}

	// Construire la chaîne résultante au format "a + bi" ou "a - bi"
	std::string result = realStr + " " + imagStr;

	return result;
}

bool calculator::isComplexNumber(const std::string& input) {
	// Expression régulière pour correspondre à un nombre complexe de la forme (a+bi) ou (bi)
	std::regex complex_regex("\\(\\s*[-+]?\\s*\\d*(\\.\\d+)?\\s*([-+])\\s*\\d*(\\.\\d+)?i\\s*\\)|\\b[-+]?\\d*(\\.\\d+)?i\\b");

	return std::regex_search(input, complex_regex);
}

void calculator::DisplayAllVariables(const vector <OpmlaborVariable> var)
{
	for (OpmlaborVariable data : var)
	{
		displayVar(data);
		cout << endl;
	}

}

std::string calculator::extractTextBetweenParentheses(const std::string& input) {
	std::size_t startPos = input.find("(");
	std::size_t endPos = input.find(")");

	if (startPos != std::string::npos && endPos != std::string::npos && endPos > startPos) {
		std::string extractedText = input.substr(startPos + 1, endPos - startPos - 1);
		return extractedText;
	}
	else {
		// Parentheses not found or in the wrong order
		return "";
	}
}
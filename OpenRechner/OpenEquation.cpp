#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stdio.h>
#include <algorithm>
#include "OpenEquation.h"
#pragma warning (disable: 4996)

using namespace std;

double safeAtof(const char* str)
{
    char* endptr;
    double result = strtod(str, &endptr);

    // Check if the entire string was parsed, and if not, return 0.0
    if (*endptr != '\0') {
        result = 0.0;
    }

    return result;
}

vector<double> OpenEquation::transform()
{
    string _equation = this->equation;
    string equation;

    //retirer espace inutile
    for (char caractere : _equation) {
        // Vérifie si le caractère n'est ni un espace ni un caractère EOF
        if (!std::isspace(caractere) && caractere != EOF) { equation += caractere; }
    }
    // une expression régulière pour capturer les termes
    std::regex term_regex("[-+]?\\d*\\.?\\d*\\*?x\\^?\\d*|[-+]?\\d*");

    // un vecteur pour stocker les tokens
    std::vector<std::string> tokens;

    // un sregex_iterator pour extraire les termes
    std::sregex_token_iterator iter(equation.begin(), equation.end(), term_regex);
    std::sregex_token_iterator end;

    for (; iter != end; ++iter)
    {
        std::string token = iter->str();
        // Supprimez les espaces inutiles
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
        if (!tokens.empty() && token[0] == '-' && (tokens.back() == "-" || tokens.back() == "+"))
        {
            tokens.back() += token;
        }
        else { tokens.push_back(token); }
    }

    //ajouter 1 devant chaque x sans coefficient

    for (std::string& token : tokens) {
        if ((token[0] == 'x') || (token[0] == '-' && token[1] == 'x') || (token[0] == '+' && token[1] == 'x')) {
            if (token[0] == '-' || token[0] == '+') { token.insert(1, "1"); }
            else { token.insert(0, "1"); }
        }
    }

    //Extraction coefficients et exposants

    vector <double> coef;
    vector <int> exp;

    // transformer chaque x en x^1 et ajouter x^0 si necessaire

    for (string& token : tokens)
    {
        char* tmp = (char*)token.c_str();
        if (tmp[strlen(tmp) - 1] == 'x') { token.append("^1"); }
        if (safeAtof(tmp) != 0.0) { token.append("x^0"); }
    }

    //retirer espace inutile
    tokens.erase(remove_if(tokens.begin(), tokens.end(), [](string x) { return x == ""; }), tokens.end());

    //extraire coef et exponent

    for (string& token : tokens)
    {
        if (token == "0") continue;
        else
        {
            char* _token = (char*)token.c_str();
            char* tmp = strtok(_token, "x^");
            coef.push_back(strtod(tmp, NULL));
            tmp = strtok(NULL, "x^");
            exp.push_back(strtod(tmp, NULL));
        }

    }

    auto max = max_element(exp.begin(), exp.end());
    int maxVal = (int)*max;

    vector<double> coefficients(maxVal + 1, 0.0);

    // vecteur finale avec les coef
    for (int i = 0; i < coef.size(); i++)
    {
        coefficients[exp[i]] = coef[i];
    }

    reverse(coefficients.begin(), coefficients.end());

    return coefficients;
}

ostream& operator<<(ostream& out, OpenEquation equ)
{
    out << equ.equation ;
    return out;
}

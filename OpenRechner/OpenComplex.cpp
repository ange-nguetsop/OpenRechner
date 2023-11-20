#define _USE_MATH_DEFINES

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <variant>
#include <regex>
#include <cmath>
#include <iomanip>
#include <vector>
#include <ctype.h> // Pour isspace
#include "OpenComplex.h"
#pragma warning (disable: 4996)

using namespace std;

string retirerEspaces(const string& chaine);

std::ostream& operator<<(std::ostream& out, const OpenComplex& z) 
{
    auto printValueImag = [](std::ostream& os, const auto& value) {
        os << std::fixed << std::setprecision(3);
        if (std::holds_alternative<int>(value)) {
            if (get<int>(value) < 0)
                os << (-1) * std::get<int>(value);
            else
            os << std::get<int>(value);
        }
        else if (std::holds_alternative<float>(value)) {
            if (get<float>(value) < 0.0f)
                os << (-1) * std::get<float>(value);
            else
                os << std::get<float>(value);
        }
        else {
            if (get<double>(value) < 0.0)
                os << (-1) * std::get<double>(value);
            else
                os << std::get<double>(value);
        }
        };

    auto printValueReal = [](std::ostream& os, const auto& value) {
        os << std::fixed << std::setprecision(3);
        if (std::holds_alternative<int>(value)) {
                os << std::get<int>(value);
        }
        else if (std::holds_alternative<float>(value)) {
                os << std::get<float>(value);
        }
        else {

                os << std::get<double>(value);
        }
        };

    printValueReal(out, z.get_real());
    auto Value = z.get_imag();

    if (std::holds_alternative<int>(Value))
        if (get<int>(Value) < 0)
        {
            out << " - ";
            printValueImag(out, z.get_imag());
            out << "i" << endl;
        }
        else
        {
            out << " + ";
            printValueImag(out, z.get_imag());
            out << "i" << endl;
        }
      
    if (std::holds_alternative<float>(Value))
        if (get<float>(Value) < 0.0f)
        {
        out << " - ";
        printValueImag(out, z.get_imag());
        out << "i" << endl;
        }
        else
        {
            out << " + ";
            printValueImag(out, z.get_imag());
            out << "i" << endl;
        }
    if (std::holds_alternative<double>(Value))
        if (get<double>(Value) < 0.0)
        {
            out << " - ";
            printValueImag(out, z.get_imag());
            out << "i" << endl;
        }
        else
        {
            out << " + ";
            printValueImag(out, z.get_imag());
            out << "i" << endl;
        }

    return out;
}

void OpenComplex::set_imag(const char* _imag)
{
    this->real = 0;
    int len = strlen(_imag);
    char* tmp = new char[len + 1];
    strcpy(tmp, _imag);
    char* token = strtok(tmp, "ji");
    this->imag = strtod(token, NULL);
    delete[] tmp;
}

//void OpenComplex::strtocmplx(const string& _cmplx) 
//{
//    double real = 0, imag = 0;
//    string _cplx = retirerEspaces(_cmplx);
//    string expr;
//    for (char c : _cplx)
//    {
//        if (c == '(' || c == ')') continue;
//        else
//            expr += c;
//    }
//    vector<string> tokens;
//    std::regex term_regex("(([-]?\\b-?\\w+\\d*(\\.\\d+)?\\b|\\d+|[^a-zA-Z0-9]))");
//    std::sregex_token_iterator iter(expr.begin(), expr.end(), term_regex);
//    std::sregex_token_iterator end;
//
//    for (; iter != end; ++iter)
//    {
//        std::string token = iter->str();
//        tokens.push_back(token);
//    }
//
//    for (string value : tokens)
//    {
//        if (value.find("i") != std::string::npos)
//        {
//            try{ imag = stod(value.substr(0,value.size() - 1)); }
//            catch (const std::exception& e)
//            {
//                cerr << endl << e.what() << endl;
//                cout << endl << "'" << _cmplx << "'" << " invalid input" << endl;
//            }   
//        }
//        else
//        {
//            try {
//                real = stod(value);
//            }
//            catch (const std::exception& e)
//            {
//                cerr<<endl << e.what() << endl;
//                cout << endl << "'" << _cmplx << "'" << " invalid input" << endl;
//            }
//        }
//
//    }
//
//    this->real = real;
//    this->imag = imag;
//}

string retirerEspaces(const string& chaine)
{
    string nouvelleChaine;

    for (char caractere : chaine) {
        if (!isspace(caractere)) {
            nouvelleChaine += caractere;
        }
    }

    return nouvelleChaine;
}

//void OpenComplex::ausgabe()
//{
//    if (imag < 0)
//        printf("%.3lf - j%.3lf\n", real, -imag);
//    else
//        printf("%.3lf + j%.3lf\n", real, imag);
//}

void OpenComplex:: strtocmplx(const std::string& _cmplx) {
    std::variant<int, float, double> real = 0, imag = 0;
    std::string _cplx = retirerEspaces(_cmplx);
    std::string expr;

    for (char c : _cplx) {
        if (c == '(' || c == ')') continue;
        else
            expr += c;
    }

    std::vector<std::string> tokens;
    std::regex re("([-+]?[0-9]*\\.?[0-9]+)?i?");
    std::sregex_token_iterator iter(expr.begin(), expr.end(), re);
    std::sregex_token_iterator end;

    for (; iter != end; ++iter) {
        std::string token = iter->str();
        tokens.push_back(token);
    }

    for (std::string value : tokens) {
        if (value.find("i") != std::string::npos) {
            
                if (value.find(".") != std::string::npos)
                    imag = std::stod(value.substr(0, value.size() - 1));
                else
                    imag = std::stoi(value.substr(0, value.size() - 1));

        }
        else if (value == "") { continue; }
        else
        {

            if (value.find(".") != std::string::npos)
                real = std::stod(value);
            else
                real = std::stoi(value);
        }        
    }

    this->real = std::variant<int, float, double>(real);
    this->imag = std::variant<int, float, double>(imag);
}

void OpenComplex::ausgabe() {
    auto real_value = get_real();
    auto imag_value = get_imag();

    auto printValue = [](const auto& value) {
        std::cout << std::fixed << std::setprecision(3);
        if (std::holds_alternative<int>(value)) {
            std::cout << std::get<int>(value);
        }
        else if (std::holds_alternative<float>(value)) {
            std::cout << std::get<float>(value);
        }
        else {
            std::cout << std::get<double>(value);
        }
        };

    if (std::holds_alternative<int>(real_value) || std::holds_alternative<float>(real_value)) {
        printValue(real_value);
    }
    else {
        std::cout << std::get<double>(real_value);
    }

    if (std::holds_alternative<int>(imag_value) || std::holds_alternative<float>(imag_value)) {
        if (std::get<double>(imag_value) < 0) {
            std::cout << " - " << -std::get<double>(imag_value) << "i";
        }
        else {
            std::cout << " + " << std::get<double>(imag_value) << "i";
        }
    }
    else {
        if (std::get<double>(imag_value) < 0) {
            std::cout << " - " << -std::get<double>(imag_value) << "i";
        }
        else {
            std::cout << " + " << std::get<double>(imag_value) << "i";
        }
    }
    std::cout << std::endl;
}

OpenComplex operator+(const OpenComplex& z1, const OpenComplex& z2) 
{
    std::variant<int,float,double> res_imag, res_real= 0;

    std::visit([&res_real](auto&& val1, auto&& val2) {
        res_real = val1 + val2;
        }, z1.real, z2.real);

    std::visit([&res_imag](auto&& val1, auto&& val2) {
        res_imag = val1 + val2;
        }, z1.imag, z2.imag);

    return OpenComplex(res_real, res_imag); 
}

OpenComplex operator-(const OpenComplex& z1, const OpenComplex& z2) 
{
    std::variant<int, float, double> res_imag, res_real = 0;

    std::visit([&res_real](auto&& val1, auto&& val2) {
        res_real = val1 - val2;
        }, z1.real, z2.real);

    std::visit([&res_imag](auto&& val1, auto&& val2) {
        res_imag = val1 - val2;
        }, z1.imag, z2.imag);

    return OpenComplex(res_real, res_imag);
}

OpenComplex operator*(const OpenComplex& z1, const OpenComplex& z2) {
    std::variant<int, float, double> res_imag, res_real;

    std::visit([&res_real](auto&& val1, auto&& val2, auto&& val3, auto&& val4) {
        res_real = (val1 * val2) - (val3 * val4);
        }, z1.real, z2.real, z1.imag, z2.imag);

    std::visit([&res_imag](auto&& val1, auto&& val2, auto&& val3, auto&& val4) {
        res_imag = (val1 * val2) + (val3 * val4);
        }, z1.real, z2.imag, z1.imag, z2.real);

    // Remplacer -0 par 0
    std::variant<int, float, double> x = -0.0;
    if (res_real == x) {
        res_real = 0;
    }
    if (res_imag == x) {
        res_imag = 0;
    }

    return OpenComplex(res_real, res_imag);
}

//OpenComplex& OpenComplex::operator+=(const OpenComplex& z)
//{
//    this->real = this->real + z.real;
//    this->imag = this->imag + z.imag;
//    return *this;
//}

OpenComplex& OpenComplex::operator+=(const OpenComplex& z)
{
    std::visit([&](auto&& r, auto&& i) {
        if constexpr (std::is_same_v<decltype(r), int> && std::is_same_v<decltype(i), int>) {
            std::get<int>(this->real) += std::get<int>(z.real);
            std::get<int>(this->imag) += std::get<int>(z.imag);
        }
        else if constexpr (std::is_same_v<decltype(r), double> && std::is_same_v<decltype(i), double>) {
            std::get<double>(this->real) += std::get<double>(z.real);
            std::get<double>(this->imag) += std::get<double>(z.imag);
        }
        else if constexpr (std::is_same_v<decltype(r), float> && std::is_same_v<decltype(i), float>) {
            std::get<float>(this->real) += std::get<float>(z.real);
            std::get<float>(this->imag) += std::get<float>(z.imag);
        }
        }, this->real, this->imag);

    return *this;
}

//OpenComplex& OpenComplex::operator-=(const OpenComplex& z)
//{
//    this->real = this->real - z.real;
//    this->imag = this->imag - z.imag;
//    return *this;
//}

OpenComplex& OpenComplex::operator-=(const OpenComplex& z)
{
    std::visit([&](auto&& r, auto&& i) {
        if constexpr (std::is_same_v<decltype(r), int> && std::is_same_v<decltype(i), int>) {
            std::get<int>(this->real) -= std::get<int>(z.real);
            std::get<int>(this->imag) -= std::get<int>(z.imag);
        }
        else if constexpr (std::is_same_v<decltype(r), double> && std::is_same_v<decltype(i), double>) {
            std::get<double>(this->real) -= std::get<double>(z.real);
            std::get<double>(this->imag) -= std::get<double>(z.imag);
        }
        else if constexpr (std::is_same_v<decltype(r), float> && std::is_same_v<decltype(i), float>) {
            std::get<float>(this->real) -= std::get<float>(z.real);
            std::get<float>(this->imag) -= std::get<float>(z.imag);
        }
        }, this->real, this->imag);

    return *this;
}

//OpenComplex& OpenComplex::operator*=(const OpenComplex& z)
//{
//    this->real = this->real * z.real - this->imag * z.imag;
//    this->imag = this->real * z.imag + this->imag * z.real;
//    return *this;
//}

OpenComplex& OpenComplex::operator*=(const OpenComplex& z)
{
    std::visit([&](auto&& r1, auto&& i1, auto&& r2, auto&& i2) {
        if constexpr (std::is_same_v<decltype(r1), int> && std::is_same_v<decltype(i1), int> &&
            std::is_same_v<decltype(r2), int> && std::is_same_v<decltype(i2), int>) {
            std::get<int>(this->real) = std::get<int>(r1) * std::get<int>(r2) - std::get<int>(i1) * std::get<int>(i2);
            std::get<int>(this->imag) = std::get<int>(r1) * std::get<int>(i2) + std::get<int>(i1) * std::get<int>(r2);
        }
        else if constexpr (std::is_same_v<decltype(r1), double> && std::is_same_v<decltype(i1), double> &&
            std::is_same_v<decltype(r2), double> && std::is_same_v<decltype(i2), double>) {
            std::get<double>(this->real) = std::get<double>(r1) * std::get<double>(r2) - std::get<double>(i1) * std::get<double>(i2);
            std::get<double>(this->imag) = std::get<double>(r1) * std::get<double>(i2) + std::get<double>(i1) * std::get<double>(r2);
        }
        else if constexpr (std::is_same_v<decltype(r1), float> && std::is_same_v<decltype(i1), float> &&
            std::is_same_v<decltype(r2), float> && std::is_same_v<decltype(i2), float>) {
            std::get<float>(this->real) = std::get<float>(r1) * std::get<float>(r2) - std::get<float>(i1) * std::get<float>(i2);
            std::get<float>(this->imag) = std::get<float>(r1) * std::get<float>(i2) + std::get<float>(i1) * std::get<float>(r2);
        }
        else {
            throw std::runtime_error("Incompatible types for multiplication.");
        }
        }, this->real, this->imag, z.real, z.imag);

    return *this;
}


//OpenComplex& OpenComplex::operator/=(const OpenComplex& z)
//{
//    std::variant<int,float,double> nenner = (z.real * z.real) + (z.imag * z.imag);
//    this->real = (this->real * z.real + this->imag * z.imag) / nenner;
//    this->imag = (this->imag * z.real - this->real * z.imag) / nenner;
//    return *this;
//}

OpenComplex& OpenComplex::operator/=(const OpenComplex& z)
{
    // Berechnung des Nenners
    std::variant<int, float, double> nenner;

    std::visit([&nenner](auto&& r1, auto&& i1, auto&& r2, auto&& i2) {
        if constexpr (std::is_same_v<decltype(r1), int> && std::is_same_v<decltype(i1), int> &&
            std::is_same_v<decltype(r2), int> && std::is_same_v<decltype(i2), int>) {
            std::get<int>(nenner) = (std::get<int>(r2) * std::get<int>(r2) + std::get<int>(i2) * std::get<int>(i2));
        }
        else if constexpr (std::is_same_v<decltype(r1), double> && std::is_same_v<decltype(i1), double> &&
            std::is_same_v<decltype(r2), double> && std::is_same_v<decltype(i2), double>) {
            std::get<double>(nenner) = (std::get<double>(r2) * std::get<double>(r2) + std::get<double>(i2) * std::get<double>(i2));
        }
        else if constexpr (std::is_same_v<decltype(r1), float> && std::is_same_v<decltype(i1), float> &&
            std::is_same_v<decltype(r2), float> && std::is_same_v<decltype(i2), float>) {
            std::get<float>(nenner) = (std::get<float>(r2) * std::get<float>(r2) + std::get<float>(i2) * std::get<float>(i2));
        }
        else {
            throw std::runtime_error("Incompatible types for division.");
        }
        }, this->real, this->imag, z.real, z.imag);

    // Durchführung der Division
    std::visit([&nenner](auto&& r1, auto&& i1, auto&& n) {
        if constexpr (std::is_same_v<decltype(r1), int> && std::is_same_v<decltype(i1), int>) {
            std::get<int>(r1) = (std::get<int>(r1) * std::get<decltype(n)>(n)) / std::get<int>(n);
            std::get<int>(i1) = (std::get<int>(i1) * std::get<decltype(n)>(n)) / std::get<int>(n);
        }
        else if constexpr (std::is_same_v<decltype(r1), double> && std::is_same_v<decltype(i1), double>) {
            std::get<double>(r1) = (std::get<double>(r1) * std::get<decltype(n)>(n)) / std::get<double>(n);
            std::get<double>(i1) = (std::get<double>(i1) * std::get<decltype(n)>(n)) / std::get<double>(n);
        }
        else if constexpr (std::is_same_v<decltype(r1), float> && std::is_same_v<decltype(i1), float>) {
            std::get<float>(r1) = (std::get<float>(r1) * std::get<decltype(n)>(n)) / std::get<float>(n);
            std::get<float>(i1) = (std::get<float>(i1) * std::get<decltype(n)>(n)) / std::get<float>(n);
        }
        else {
            throw std::runtime_error("Incompatible types for division.");
        }
        }, this->real, this->imag, nenner);

    return *this;
}

//OpenComplex& OpenComplex::operator++()
//{
//    this->real = this->real + 1;
//    return *this;
//}

OpenComplex& OpenComplex::operator++()
{
    std::visit([](auto&& r) {
        if constexpr (std::is_same_v<decltype(r), int>) {
            std::get<int>(r) += 1;
        }
        else if constexpr (std::is_same_v<decltype(r), double>) {
            std::get<double>(r) += 1.0;
        }
        else if constexpr (std::is_same_v<decltype(r), float>) {
            std::get<float>(r) += 1.0f;
        }
        }, this->real);

    return *this;
}

//OpenComplex& OpenComplex::operator++(int)
//{
//    this->imag = this->imag + 1;
//    return *this;
//}

OpenComplex& OpenComplex::operator++(int)
{
    std::visit([](auto&& i) {
        if constexpr (std::is_same_v<decltype(i), int>) {
            std::get<int>(i) += 1;
        }
        else if constexpr (std::is_same_v<decltype(i), double>) {
            std::get<double>(i) += 1.0;
        }
        else if constexpr (std::is_same_v<decltype(i), float>) {
            std::get<float>(i) += 1.0f;
        }
        }, this->imag);

    return *this; // Rückgabe der temporären Kopie des vorherigen Zustands
}


//OpenComplex& OpenComplex::operator--()
//{
//    this->real = this->real - 1;
//    return *this;
//}

OpenComplex& OpenComplex::operator--()
{
    std::visit([](auto&& r) {
        if constexpr (std::is_same_v<decltype(r), int>) {
            std::get<int>(r) -= 1;
        }
        else if constexpr (std::is_same_v<decltype(r), double>) {
            std::get<double>(r) -= 1.0;
        }
        else if constexpr (std::is_same_v<decltype(r), float>) {
            std::get<float>(r) -= 1.0f;
        }
        }, this->real);

    return *this;
}


//OpenComplex& OpenComplex::operator--(int)
//{
//    this->imag = this->imag - 1;
//    return *this;
//}

OpenComplex& OpenComplex::operator--(int)
{
    std::visit([](auto&& i) {
        if constexpr (std::is_same_v<decltype(i), int>) {
            std::get<int>(i) -= 1;
        }
        else if constexpr (std::is_same_v<decltype(i), double>) {
            std::get<double>(i) -= 1.0;
        }
        else if constexpr (std::is_same_v<decltype(i), float>) {
            std::get<float>(i) -= 1.0f;
        }
        }, this->imag);

    return *this; // Rückgabe des aktualisierten Objekts
}

bool OpenComplex::operator==(const OpenComplex& z)
{
    if (this->real == z.real && this->imag == z.imag) return true;
    else
        return false;
}

bool OpenComplex::operator!=(const OpenComplex& z)
{
    if (this->real != z.real || this->imag != z.imag) return true;
    else
        return false;
}

//void OpenComplex::polar()
//{
//    double betrag = sqrt(pow(this->real, 2) + pow(this->imag, 2));
//    double arg = 0.0;
//    if (this->real > 0 || this->imag != 0)
//    {
//        arg = 2 * atan2(this->imag, (betrag + this->real));
//    }
//    if (this->imag == 0 && this->real < 0)
//    {
//        arg = M_PI;
//    }
//
//    if (this->imag < 0)
//    {
//        printf("|"); printf("%.3lf - j%.3lf", real, -imag); printf("| = %.3lf\n", betrag);
//        printf("arg ("); printf("%.3lf - j%.3lf", real, -imag); printf(") = %.3lf rad\n", arg);
//        printf("arg ("); printf("%.3lf - j%.3lf", real, -imag); printf(") = %.3lf degrees\n", arg * (180 / M_PI));
//
//    }
//
//    else
//    {
//        printf("|"); printf("%.3lf + j%.3lf", this->real, this->imag); printf("| = %.3lf\n", betrag);
//        printf("arg ("); printf("%.3lf + j%.3lf", this->real, this->imag); printf(") = %.3lf rad\n", arg);
//        printf("arg ("); printf("%.3lf + j%.3lf", this->real, this->imag); printf(") = %.3lf degrees\n", arg * (180 / M_PI));
//    }
//
//}

void OpenComplex:: polar() {
    // Accédez à real et imag à l'aide des méthodes d'accès
    auto real_value = get_real();
    auto imag_value = get_imag();

    auto get_double = [](const auto& var) -> double {
        if (std::holds_alternative<int>(var)) {
            return static_cast<double>(std::get<int>(var));
        }
        else if (std::holds_alternative<float>(var)) {
            return static_cast<double>(std::get<float>(var));
        }
        else {
            return std::get<double>(var);
        }
        };

    double real_double = get_double(real_value);
    double imag_double = get_double(imag_value);

    double betrag = std::sqrt(std::pow(real_double, 2) + std::pow(imag_double, 2));
    double arg = std::atan2(imag_double, real_double);

    std::cout << "|" << std::fixed << std::setprecision(3) << real_double << " + j" << imag_double << "| = " << betrag << std::endl;
    std::cout << "arg (" << real_double << " + j" << imag_double << ") = " << arg << " rad" << std::endl;
    std::cout << "arg (" << real_double << " + j" << imag_double << ") = " << (arg * (180 / M_PI)) << " degrees" << std::endl;
}

//OpenComplex OpenComplex::operator*() { return OpenComplex(real, -imag); }

OpenComplex OpenComplex::operator*() {
    std::variant<int, float, double> conj_real;
    std::variant<int, float, double> conj_imag;

    std::visit([&conj_real, &conj_imag](auto&& r, auto&& i) {
        if constexpr (std::is_same_v<decltype(r), int>) {
            conj_real = std::get<int>(r);
            conj_imag = -std::get<int>(i);
        }
        else if constexpr (std::is_same_v<decltype(r), float>) {
            conj_real = std::get<float>(r);
            conj_imag = -std::get<float>(i);
        }
        else if constexpr (std::is_same_v<decltype(r), double>) {
            conj_real = std::get<double>(r);
            conj_imag = -std::get<double>(i);
        }
        }, real, imag);

    return OpenComplex(conj_real, conj_imag);
}

//std::variant<int, float, double> OpenComplex::betrag()
//{
//    double betrag = sqrt(pow(this->real, 2) + pow(this->imag, 2));
//    return betrag;
//}

std::variant<int, float, double> OpenComplex::betrag()
{
    auto get_double = [](const auto& var) -> double {
        if (std::holds_alternative<int>(var)) {
            return static_cast<double>(std::get<int>(var));
        }
        else if (std::holds_alternative<float>(var)) {
            return static_cast<double>(std::get<float>(var));
        }
        else {
            return std::get<double>(var);
        }
        };

    double real_double = get_double(real);
    double imag_double = get_double(imag);

    double betrag = sqrt(pow(real_double, 2) + pow(imag_double, 2));

    if (std::holds_alternative<int>(real) && std::holds_alternative<int>(imag)) {
        return static_cast<int>(betrag);
    }
    else if (std::holds_alternative<float>(real) || std::holds_alternative<float>(imag)) {
        return static_cast<float>(betrag);
    }
    else {
        return betrag;
    }
}

//float OpenComplex::winkel(bool art)
//{
//    double betrag = sqrt(pow(this->real, 2) + pow(this->imag, 2));
//    double arg = 0.0;
//    if (this->real > 0 || this->imag != 0)
//    {
//        arg = 2 * atan2(this->imag, (betrag + this->real));
//    }
//    if (this->imag == 0 && this->real < 0)
//    {
//        arg = M_PI;
//    }
//
//    if (art == true)
//    {
//        return (arg * (180 / M_PI));
//    }
//    else
//        return arg;
//}

std::variant<int, float, double> OpenComplex::winkel(bool art)
{
    auto get_double = [](const auto& var) -> double {
        if (std::holds_alternative<int>(var)) {
            return static_cast<double>(std::get<int>(var));
        }
        else if (std::holds_alternative<float>(var)) {
            return static_cast<double>(std::get<float>(var));
        }
        else {
            return std::get<double>(var);
        }
        };

    double real_double = get_double(real);
    double imag_double = get_double(imag);

    double betrag = sqrt(pow(real_double, 2) + pow(imag_double, 2));
    double arg = 0.0;

    if (real_double > 0 || imag_double != 0)
    {
        arg = 2 * atan2(imag_double, (betrag + real_double));
    }

    if (imag_double == 0 && real_double < 0)
    {
        arg = M_PI;
    }

    if (art)
    {
        return static_cast<float>(arg * (180.0 / M_PI));
    }
    else
    {
        return arg;
    }
}

//OpenComplex operator/(const OpenComplex& z1, const OpenComplex& z2)
//{
//    OpenComplex res;
//    std::variant<int,float,double> nenner = (z2.real * z2.real) + (z2.imag * z2.imag);
//    res.real = (z1.real * z2.real + z1.imag * z2.imag) / nenner;
//    res.imag = (z1.imag * z2.real - z1.real * z2.imag) / nenner;
//    return res;
//}

OpenComplex operator/(const OpenComplex& z1, const OpenComplex& z2)
{
    OpenComplex res;

    auto get_double = [](const auto& var) -> double {
        if (std::holds_alternative<int>(var)) {
            return static_cast<double>(std::get<int>(var));
        }
        else if (std::holds_alternative<float>(var)) {
            return static_cast<double>(std::get<float>(var));
        }
        else {
            return std::get<double>(var);
        }
        };

    double z1_real_double = get_double(z1.real);
    double z1_imag_double = get_double(z1.imag);
    double z2_real_double = get_double(z2.real);
    double z2_imag_double = get_double(z2.imag);
    
    double nenner = (z2_real_double * z2_real_double) + (z2_imag_double * z2_imag_double);
    if(nenner == 0.0)
        throw std::runtime_error("Division by 0 not authorized");
    res.real = (z1_real_double * z2_real_double + z1_imag_double * z2_imag_double) / nenner;
    res.imag = (z1_imag_double * z2_real_double - z1_real_double * z2_imag_double) / nenner;

    return res;

  
}

double OpenComplex:: get_imag_as_double() const 
{
    // Supposons que vous voulez obtenir la partie imaginaire comme un double
    // Vous pouvez adapter cette fonction pour obtenir le type souhaité (int, float, double)
    if (std::holds_alternative<int>(imag)) {
        return static_cast<double>(std::get<int>(imag));
    }
    else if (std::holds_alternative<float>(imag)) {
        return static_cast<double>(std::get<float>(imag));
    }
    else {
        return std::get<double>(imag);
    }
}

double OpenComplex::get_real_as_double() const
{
    // Supposons que vous voulez obtenir la partie imaginaire comme un double
    // Vous pouvez adapter cette fonction pour obtenir le type souhaité (int, float, double)
    if (std::holds_alternative<int>(real)) {
        return static_cast<double>(std::get<int>(real));
    }
    else if (std::holds_alternative<float>(real)) {
        return static_cast<double>(std::get<float>(real));
    }
    else {
        return std::get<double>(real);
    }
}


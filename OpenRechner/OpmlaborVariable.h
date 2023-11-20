#pragma once

class OpmlaborVariable
{
public:
    enum Type 
    {
        INT = 1, FLOAT, DOUBLE, STRING, NONE,OPenCVMat,Openm, OpenE, OpenF = 9, OpenC = 10
    };

    OpmlaborVariable()
        : type(NONE), value(0) {}

    OpmlaborVariable(std::string name, int v)
        : type(INT), value(v) ,varname(name){}

    OpmlaborVariable(std::string name,float v)
        : type(FLOAT), value(v), varname(name) {}

    OpmlaborVariable(std::string name,double v)
        : type(DOUBLE), value(v), varname(name) {}

    OpmlaborVariable(std::string name,const std::string& v)
        : type(STRING), value(v), varname(name) {}

    OpmlaborVariable(std::string name, cv::Mat v)
        : type(OPenCVMat), value(v), varname(name) {}

    OpmlaborVariable(std::string name, OpenMatrix v)
        : type(Openm), value(v), varname(name) {}

    OpmlaborVariable(std::string name, OpenEquation v)
        : type(OpenE), value(v), varname(name) {}

    OpmlaborVariable(std::string name, OpenFraction v)
        : type(OpenF), value(v), varname(name) {}

    OpmlaborVariable(std::string name, OpenComplex v)
        : type(OpenC), value(v), varname(name) {}

    Type getType() const {
        return type;
    }

    void setName(std::string _name)
    {
        varname = _name;
    }
    void setValue(std::variant<int, float, double, std::string, cv::Mat, OpenMatrix, OpenEquation, OpenFraction, OpenComplex> v)
    {
        value = v;
    }
    void setType(int t)
    {
       type = static_cast<Type>(t);
    }

    std::variant<int, float, double, std::string,cv::Mat,OpenMatrix,OpenEquation,OpenFraction,OpenComplex> getValue() const {
        return value;
    }

    std::string getName() const
    {
        return varname;
    }

private:
    Type type;
    std::variant<int, float, double, std::string,cv::Mat,OpenMatrix, OpenEquation,OpenFraction, OpenComplex> value;
    std::string varname; 
};


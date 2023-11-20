#include <iostream>
#include <map>
#include"stdafx.h"
#include "OpmlaborVariable.h"
#include "calculator.h"
#include <vector>
#include <cassert>


int main()
{
    try
    {
        calculator calculator;
        calculator.run();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception catch : " << e.what() << std::endl;
    }


}




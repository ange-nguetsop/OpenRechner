#include "stdafx.h"
#include "OpenMatrix.h"
#pragma warning (disable: 4996)

using namespace std;

void OpenMatrix::set_mat(string ma_Matrice) { mt = ma_Matrice; }

string OpenMatrix::get_mat() { return this->mt;}

vector<vector<int>> OpenMatrix::transformtoi()
{
    vector <vector<int>> your_Matrice;
    vector <int> data;
    vector <string> data_string;

    char* token = strtok((char*)mt.c_str(), "[;]");
    while (token != NULL)
    {

        data_string.push_back(token);
        token = strtok(NULL, "[;]");
    }

    for (int i = 0; i < data_string.size(); i++)
    {
        data.clear();
        char* token = strtok((char*)data_string[i].c_str(), " ");
        while (token != NULL)
        {
            data.push_back(atoi(token));
            token = strtok(NULL, " ");
        }

        your_Matrice.push_back(data);
    }
    return your_Matrice;
}

vector<vector<double>> OpenMatrix::transformtod()
{
    vector <vector<double>> your_Matrice;
    vector <double> data;
    vector <string> data_string;

    char* token = strtok((char*)mt.c_str(), "[;]");
    while (token != NULL)
    {

        data_string.push_back(token);
        token = strtok(NULL, "[;]");
    }

    for (int i = 0; i < data_string.size(); i++)
    {
        data.clear();
        char* token = strtok((char*)data_string[i].c_str(), " ");
        while (token != NULL)
        {
            data.push_back(strtod(token, NULL));
            token = strtok(NULL, " ");
        }

        your_Matrice.push_back(data);
    }
    return your_Matrice;
}

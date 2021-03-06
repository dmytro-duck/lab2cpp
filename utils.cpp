#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <cmath>

using namespace std;
namespace fs = filesystem;

string to_lowercase(string str)
{
    for (size_t i = 0; i < str.size(); i++)
        str[i] = tolower(str[i]);
    return str;
}

bool flag2bool(string flag)
{
    string f = to_lowercase(flag);
    if (f == "true" || f == "yes")
        return true;
    if (f == "false" || f == "no")
        return false;
    if (f[0] == '-')
    {
        for (size_t i = 0; i < f.size(); i++)
        {
            if (f[i] != '-')
            {
                throw invalid_argument("Невідоме булеве значення - \"" + flag + "\"");
            }
        }
    return false;
    }
    if (f[0] == '+')
    {
        for (size_t i = 0; i < f.size(); i++)
        {
            if (f[i] != '+')
            {
                throw invalid_argument("Невідоме булеве значення - \"" + flag + "\"");
            }
        }
    return true;
    }
}
vector<string> split(string str, char delim)
{
    vector<string> out;
    size_t start = 0, end;
    string line;

    do
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
        start = end + 1;
    } while (end != string::npos);

    return out;
}

vector<string> listFiles(string directory, string extension)
{
    vector<string> out;
    if (fs::exists(directory) && fs::is_directory(directory))
    {
        for (const auto &entry : fs::directory_iterator(directory))
            if (fs::path(entry).extension() == extension)
                out.push_back(entry.path().string());
    }
    else
        cerr << "Введеної директорії не існує - \"" + directory + "\"" << endl;

    return out;
}

double roundOff(double x, int precision)
{
    double power_of_10 = pow(10, precision);
    return double(round(x * power_of_10)) / power_of_10;
}
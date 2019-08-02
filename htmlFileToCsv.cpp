#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct database
{
    string name, timeIn, timeOut, purpose;
};

string
readfile(string filename)
{
    string result = "";
    ifstream src;
    src.open(filename);
    while (src.eof())
    {
        src >> result;
        result += "\n";
    }
    return result;
}
database getContentArray(string file)
{
    stringstream lines(readfile(file));
    string text, sc;
    lines >> sc;
    /* gets me to the beginning of the line that i need */
    while (sc.find("<textarea") != -1)
    {
        lines >> sc;
    }
}
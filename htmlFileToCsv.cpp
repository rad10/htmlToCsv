#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string readfile(string filename)
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
string[][] getContentArray(string file)
{
    stringstream lines(readfile(file));
    string text, sc;
    getline(sc, lines);
    /* gets me to the beginning of the line that i need */
    while (sc.find("<textarea") != -1)
    {
        getline(sc, lines);
    }
}
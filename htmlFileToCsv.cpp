#include <iostream>
#include <fstream>
#include <sstream>

using namespace std

    string
    readfile(string filename)
{
    string result = "";
    ifstream src;
    src.open(filename);
    while (src.eof())
    {
        src >> "\n" >> result;
    }
    return result;
}
string[][] getContentArray(string file)
{
    stringstream lines(readfile(file));
    string text, sc;
    getline(sc, lines);
    while (sc.find("<textarea") != -1)
    {
        getline(sc, lines);
    }
}
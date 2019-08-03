#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct database
{
    string firstname, lastname, timeIn, timeOut;
    int hours;
    string purpose;
};

bool Debug = true;

string readfile(string filename)
{
    string result, add;
    ifstream src(filename);
    while (getline(src, add))
    {
        result += add + "\n";
    }
    src.close();
    return result;
}
string getContentSource(string file)
{
    stringstream lines(readfile(file));
    string text, sc;
    getline(lines, sc);
    /* gets me to the beginning of the line that i need */
    while (sc.find("<textarea") == -1 && !lines.eof())
    {
        getline(lines, sc);
    }
    text = sc.substr(sc.find("<textarea") + 22, sc.length()) + "\n";
    getline(lines, sc);
    while (sc.find("</textarea>") == -1 && !lines.eof())
    {
        text += sc + "\n";
        getline(lines, sc);
    }
    text += sc.substr(0, sc.find("</textarea>"));
    return text;
}
void sourceToDictionary(string source)
{
}
int main()
{
    cout << getContentSource("sheet1.html");
}
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
database *dict;

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
/**
 * this function was made to simplify the bs tools c++ gives for string manipulation.
 */
int countlines(string src)
{
    stringstream s(src);
    string waste;
    int count = 0;
    while (getline(s, waste))
    {
        count++;
    }
    return count;
}
database *sourceToDictionary(string source)
{
    int size = countlines(source);
    database h[size]; // = new database[size];
{
    int size = count(source.begin(), source.end(), "\n") + 1;
    dict = new database[size];
}
int main()
{
    cout << getContentSource("sheet1.html");
}
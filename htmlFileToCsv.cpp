#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct database
{
    string name, timeIn, timeOut, purpose;
};

bool Debug = true;

string readfile(string filename)
{
    string result, add;
    ifstream src(filename);
    //cout << "file open: " << src.is_open() << "\nfileend: " << src.eof() << "\n";
    while (getline(src, add))
    {
        result += add + "\n";
    }
    /* if (Debug)
    {
        cout << result << "\n";
    } */
    src.close();
    return result;
}
string getContentArray(string file)
{
    //cout << readfile(file);
    stringstream lines(readfile(file));
    string text, sc;
    getline(lines, sc);
    /* gets me to the beginning of the line that i need */
    while (sc.find("<textarea") == -1 && !lines.eof())
    {
        getline(lines, sc);
        //cout << l << ". " << sc << " | " << sc.find("<textarea") << "\n";
    }
    /* if (Debug)
    {
        cout << sc << " | " << sc.find("<textarea") << "\n";
    } */
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
int main()
{
    cout << getContentArray("sheet1.html");
}
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

void debugProfile(database p)
{
    cout << p.firstname << " " << p.lastname << ", " << p.timeIn << ", " << p.timeOut << ", " << p.hours << ", " << p.purpose << "\n";
}
void debugDictionary(database d[], int size)
{
    for (int i = 0; i < size; i++)
    {
        debugProfile(d[i]);
    }
}
database *sourceToDictionary(string source)
{
    int size = countlines(source);
    database h[size]; // = new database[size];
    cout << source << "\n";
    stringstream src(source);
    int c = 0;
    string buffer;
    while (getline(src, buffer))
{
        stringstream line(buffer);
        //cout << c << " " << buffer << "\n";
        line >> h[c].firstname >> h[c].lastname >> h[c].timeIn >> h[c].timeOut >> h[c].hours >> h[c].purpose;
        //debugProfile(h[c]);
        c++;
    }
    //cout << c << "\n";
    dict = h;
    return dict;
}

/**
 * this function is meant to skip making the whole database part in my psuedocode. go from the raw data straight to CSV.
 */
string sourceToCsv(string source)
{
    stringstream src(source);
    string line;
    string result = "";
    string firstname, lastname, timein, timeout, hour, tpurpose;
    string purpose = "";
    int hours;

    stringstream buffer;
    while (getline(src, line))
    {
        buffer.str(line);
        buffer >> firstname >> lastname >> timein >> timeout >> hours >> purpose;
        while (buffer >> tpurpose)
        {
            purpose += " " + tpurpose;
        }
        //hour = hours;
        result += firstname + " " + lastname + "," + timein + "," + timeout + "," + to_string(hours) + "," + purpose + "\n";
        purpose = "";
        buffer.clear();
    }
    return result;
}

void outputCSV(string source)
{
    stringstream src(source);
    ofstream output("names.csv", ios::app);
    string buffer;
    while (getline(src, buffer))
    {
        output << buffer << "\n";
    }
    output << "\n";
}

int main()
{
    cout << getContentSource("sheet1.html");
}
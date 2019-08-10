#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool Debug = true;

/**
 * simple function designed just to open and output all the contents in the file specified.
 */
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

/**
 * works to extract the data we need from the HTML file.
 */
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

/**
 * places the final text into the file that we desire
 */
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
    string csv = sourceToCsv(getContentSource("sheet1.html"));
    outputCSV(csv);
}
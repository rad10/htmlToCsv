#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/* struct database
{
    string firstname, lastname, timeIn, timeOut;
    int hours;
    string purpose;
}; */

bool Debug = true;
// database *dict;

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
    while (sc.find("<textarea") == -1 && !lines.eof()) // throws out each line till it finds textarea in the line or stops once theres no more lines to search (aka dud)
    {
        getline(lines, sc);
    }
    /* adds the date that starts on the first line */
    text = sc.substr(sc.find("<textarea") + 22, sc.length()) + "\n";
    getline(lines, sc);
    /* keeps adding lines until it finds </textarea> or the file ends (aka dud) */
    while (sc.find("</textarea>") == -1 && !lines.eof())
    {
        text += sc + "\n";
        getline(lines, sc);
    }
    /* gets the final data that begins just before </textarea> */
    text += sc.substr(0, sc.find("</textarea>"));
    return text;
}

/**
 * this function was made to simplify the bs tools c++ gives for string manipulation.
 */
/* int countlines(string src)
{
    stringstream s(src);
    string waste;
    int count = 0;
    while (getline(s, waste))
    {
        count++;
    }
    return count;
} */

/* void debugProfile(database p)
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
} */

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
        buffer.str(line); // refreshes line to split into pieces
        buffer >> firstname >> lastname >> timein >> timeout >> hours >> purpose;
        while (buffer >> tpurpose) // anything that didnt fit into the line above gets combined into purpose via tpurpose
        {
            purpose += " " + tpurpose;
        }
        //hour = hours;
        result += firstname + " " + lastname + "," + timein + "," + timeout + "," + to_string(hours) + "," + purpose + "\n";
        purpose = "";
        buffer.clear(); // resets the buffer so that it doesnt restart at eof
    }
    return result + "\n";
}

/**
 * places the final text into the file that we desire
 */
void outputCSV(string source)
{
    stringstream src(source);
    ofstream output("names.csv", ios::app); // this line opens names.csv and itll append everything to the file automatically
    string buffer;
    while (getline(src, buffer))
    {
        output << buffer << "\n";
    }
}

int main()
{
    string csv = sourceToCsv(getContentSource("sheet1.html"));
    outputCSV(csv);
}
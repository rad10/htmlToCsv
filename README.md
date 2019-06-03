# htmlToCsv

This is a project to take data out of inkspaces bamboo paper and put it in database format. This project is made for intended use by STEMTech Neighborhood Academy.

The intended use for this project is to take names written on a sign up sheet including other values, process it through a writing to text machine, and put that information on an excel sheet for use in data manipulation other projects.

The task is to make a functional tool that can take html files taken from inkspace's website since they store their digital output on the HTML source code itself.
With that, this tool is intended to dig into each HTML file in its directory (or depending on the language can allow other places etc.) but most tools are suppossed to interact with HTML files in the same directory by activation without arguements.

The program is designed to open each HTML file and strip the data collected by inkspace from the rest of the HTML file. With this information, it will attempt to organize all the names of people as well as other stats as well as possible into a datasheet organized by people and their data values (which goes as full name, time in, time out, hours, and purpose of visit.)
With this dictionary of names, it then sets it up in a CSV format and either creates a names.csv file or adds it to a currently existing file. From here the information gets passed down via the CSV file to wherever it needs to be, particularly excel.

and that is the full intention of this program.

### C++

#### !!!Warning: this script is incomplete and does not work as intended yet!!!

This variant is mostly setup for windows environment but it is made to work for both windows and linux.

> Tested with *[MinGW32](https://http://www.mingw.org)*

All setting should be setup properly with this variant. If you choose to use a different compiler, you may need to edit settings for it to work (if youre using vscode that is).
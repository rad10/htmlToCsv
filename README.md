# htmlToCsv
This is a project to take data out of inkspaces bamboo paper and put it in database format. This project is made for intended use by STEMTech Neighborhood Academy.

The intended use for this project is to take names written on a sign up sheet including other values, process it through a writing to text machine, and put that information on an excel sheet for use in data manipulation other projects.

The taks is to make a functional tool that can take html files taken from inkspaces website since they store their digital output on the HTML source code itself.
With that this tool is intended to dig into each html file in its directory (or depending on the language can allow other places etc.) but most tools are suppossed to interact with HTML files in the same directory by activation without arguements.

The program is designed to open each HTML file and strip the data collected by inkspace from the rest of the HTML file. With this information, it will attempt to organize all the names of people as well as other stats as well as possible into a datasheet organized by people and their data values (which goes as full name, time in, time out, hours, and purpose of visit.)
With this dictionary of names, it then sets it up in a CSV format and either creates a names.csv file or adds it to a currently existing file. From here the information gets passed down via the CSV file to wherever it needs to be, particularly excel.

and that is the full intention of this program.

### Java

This variant takes advantage of Object Oriented Programming to better organize and control the manipulation of strings in the program.

This application should in theory work on both windows and linux, however it has not been tested on linux as of yet.

Full documentation of functions and use can be found in `/docs` if intended to be used as an api.
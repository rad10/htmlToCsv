#!/usr/bin/python
from sys import argv
from os import listdir, unlink
from shutil import rmtree
from bs4 import BeautifulSoup
# Functions
Debug = False


def debug(content):
    if Debug:
        print(content)


def readfile(dir):
    return open(dir, "r").read()


def exportToFile(dir, content):
    open(dir, "w").write(content)


def appendToFile(dir, content):
    try:
        inside = open(dir, "r").read()
        open(dir, "w").write(inside + content)
    except:
        open(dir, "w").write(content)


def isNum(num):
    try:
        return float(str(num)).is_integer()
    except:
        return False


def help():
    print(__file__, "[OPTION]", "[HTML File]")
    print("This program is intended to take data from inkspace HTML files and append it to a CSV file in the same directory.")
    print("INSTRUCTIONS: save inkspace output to an HTML file in the same directory as this program. Once done, run this program. Profit.")
    print("OPTIONS:")
    print("-h | --help\t\t\tPrints this help screen.")
    print("-d | --display\t\t\tPrints the output of the CSV into the console as well as into the file.")


# Generator
def htmlToSource(file):
    lines = readfile(file).split("\n")
    #debug(("lines:", lines))
    # all the content starts after the tag <textarea reeadonly="">
    text = lines[2][lines[2].find("<textarea")+22:]
    debug(("text", text))
    # all the content makes a new line in the html, so this adds every line after <textarea>
    for i in range(3, len(lines)):
        if (text.find("</textarea>") == -1):
            text = text + "\n" + lines[i]
            debug(text)
        else:
            break  # once line has a </textarea>, it stops adding lines, but includes the line with </textarea>
    # cuts out all info after </textarea>, then splits the new dictionary to define people and their attributes
    people = text[:text.find("</textarea>")].split("\n")
    debug(("people:", people))
    return people


def getContentArray(people):
    """the purpose of the function is to take all the content in the HTML and return a matrix array.
    file: a string containing the contents from a file given by readfile().
    return: a string[][] matrix with important data scraped from file.
    """
    directory = []  # the matrix used to store conent
    for i in people:
        # gets the attribute of each individual person and defines it by a space
        attr = i.split(" ")
        debug(("attr:", attr))
        if (len(attr) >= 5):  # a person cannot have any more than 5 attributes, and if they do, they all merge into the last attribute
            #                         FirstName, LastName, timeIn, timeOut, hours, purpose
            directory.append([str(attr[0]+" "+attr[1]), attr[2], attr[3],
                              attr[4], ''.join(str(x+" ") for x in attr[5:])])
            directory[-1][4] = directory[-1][4][:len(directory[-1][4])-1]
            # Comment top and uncomment bottom if you want first and last name separate
            #directory.append([attr[0], attr[1], attr[2], attr[3], attr[4], ''.join(str(x+" ") for x in attr[5:])])
            #directory[-1][5] = directory[-1][5][:len(directory[-1][5])-1]
        elif (len(attr) > 1):  # this is added to deal with first and last name being together, in case someone only puts down their name
            hold = []
            # this combines the first and last name
            hold.append(str(attr[0]+" "+attr[1]))
            if (len(attr) > 2):  # if they did put in more than just their name, its added to attributes
                for i in attr[2:]:
                    hold.append(i)
            # combines all the attributes into an array, then return to people array
            directory.append(hold)
        else:
            directory.append(attr)
        debug(("directory:", directory))
    return directory  # returns the matrix


def arrayToCsv(directory):
    """takes a matrix and returns a string in CSV format.
    var directory: a string[][] matrix that contains the information of people at the center.
    returns: a string that contains all the information in CSV format.
    """
    cvarray = ''
    for i in range(len(directory)):
        for e in range(len(directory[i])-1):
            if (isNum(directory[i][e])):
                cvarray += (directory[i][e]+", ")
            else:
                cvarray += (directory[i][e]+", ")
        cvarray += (directory[i][-1]+"\n")
        debug(("cvarray["+str(i)+"]:", cvarray))
    return (cvarray+"\n")


# Actual Script
def main():
    input = []
    display = False  # Option to display results of CSV in console as well as names.csv
    if len(argv) > 1:
        for i in argv[1:]:
            if (i == "/help" or i == "-help" or i == "==help" or i == "-h" or i == "/h"):
                help()
                return
            elif (i == "/d"or i == "-d"or i == "/display"or i == "-display"or i == "--display"):
                display = True
            if (i.split(".")[1].lower() == "html"):
                input.append(i)
        #debug("argv: " + str(input))
    if(len(input) == 0):
        for i in listdir():
            try:
                if (i.split(".")[1] == "html"):
                    input.append(i)
            except:
                continue
        #debug("listdir: " + str(input))
    if(len(input) == 0):
        print("ERROR: No HTML Files imported and none in current directory!")
        help()
        return
    output = ''
    for i in input:
        # debug(i+":"+i.split(".")[1].lower())
        output += arrayToCsv(getContentArray(i))
        try:
            # deletes the html used as to not accidentally add it to csv again
            unlink(i)
        except:
            True
        try:  # incase the folder already doesnt exist
            rmtree(str(i.split(".")[0] + "_files"))  # removes folder
        except:
            True
    # debug(("output:",output))
    if(display):
        print(output)
    appendToFile("names.csv", output)


main()

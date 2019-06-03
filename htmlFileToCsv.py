from sys import argv
from os import listdir, unlink
from shutil import rmtree
##Functions
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
    try: return float(str(num)).is_integer()
    except: return False


#Generator
def getContentArray(file): #the purpose of the function is to take all the content in the html and return a matrix array
    lines = readfile(file).split("\n")
    #debug(("lines:", lines))
    directory = [] #the matrix used to store conent
    text = lines[2][lines[2].find("<textarea")+22:] #all the content starts after the tag <textarea reeadonly="">
    debug(("text", text))
    for i in range(3,len(lines)): #all the content makes a new line in the html, so this adds every line after <textarea>
        if (text.find("</textarea>")==-1):
            text = text + "\n" + lines[i]
            debug(text)
        else: break #once line has a </textarea>, it stops adding lines, but includes the line with </textarea>
    people = text[:text.find("</textarea>")].split("\n") # cuts out all info after </textarea>, then splits the new dictionary to define people and their attributes
    debug(("people:", people))
    for i in people:
        attr = i.split(" ") #gets the attribute of each individual person and defines it by a space
        debug(("attr:", attr))
        if (len(attr)>=5): #a person cannot have any more than 5 attributes, and if they do, they all merge into the last attribute
#                         FirstName, LastName, timeIn, timeOut, hours, purpose
            directory.append([str(attr[0]+" "+attr[1]), attr[2], attr[3], attr[4], ''.join(str(x+" ") for x in attr[5:])])
            directory[-1][4] = directory[-1][4][:len(directory[-1][4])-1]
            #Comment top and uncomment bottom if you want first and last name separate
            #directory.append([attr[0], attr[1], attr[2], attr[3], attr[4], ''.join(str(x+" ") for x in attr[5:])])
            #directory[-1][5] = directory[-1][5][:len(directory[-1][5])-1]
        elif (len(attr) > 1): #this is added to deal with first and last name being together, in case someone only puts down their name
            hold = []
            hold.append(str(attr[0]+" "+attr[1])) #this combines the first and last name
            if (len(attr) > 2): #if they did put in more than just their name, its added to attributes
                for i in attr[2:]: hold.append(i)
            directory.append(hold) #combines all the attributes into an array, then return to people array
        else: directory.append(attr)
        debug(("directory:", directory))
    return directory # returns the matrix

def arrayToCsv(directory): #takes a matrix and returns a string in csv format
    cvarray = ''
    for i in range(len(directory)):
        for e in range(len(directory[i])-1):
            if (isNum(directory[i][e])):
                cvarray += (directory[i][e]+", ")
            else: cvarray += (directory[i][e]+", ")
        cvarray += (directory[i][-1]+"\n")
        debug(("cvarray["+str(i)+"]:", cvarray))
    return (cvarray+"\n")


#Actual Script
input = []
if len(argv) > 1:
    for i in argv[1:]:
        if (i.split(".")[1].lower() == "html"):
            input.append(i)
    #debug("argv: " + str(input))
else:
    for i in listdir():
        try:
            if (i.split(".")[1] == "html"):
                input.append(i)
        except: continue
    #debug("listdir: " + str(input))
output = ''
for i in input:
    #debug(i+":"+i.split(".")[1].lower())
    output += arrayToCsv(getContentArray(i))
    try: 
        unlink(i) #deletes the html used as to not accidentally add it to csv again
    except:
        True
    try: # incase the folder already doesnt exist
        rmtree(str(i.split(".")[0] + "_files")) #removes folder
    except:
        True
#debug(("output:",output))
appendToFile("names.csv", output)

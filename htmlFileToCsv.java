import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class htmlFileToCsv {
    private static boolean Debug = false;

    /**
     * I leave these debug commands in case anyone wants to place them anywhere
     * inside the code to output the results
     */
    private static void debug(String content) {
        if (Debug)
            System.out.println(content);
    }

    private static void debug(String content, Boolean debug) {
        if (debug)
            System.out.println(content);
    }

    private static void debug(String[] a) {
        if (Debug)
            for (String b : a)
                System.out.println(b);
    }

    private static void debug(String[] a, Boolean debug) {
        if (debug)
            for (String b : a)
                System.out.println(b);
    }

    private static void debug(List<String> a) {
        if (Debug)
            for (String b : a)
                System.out.println(b);
    }

    private static void debug(List<String> a, Boolean debug) {
        if (debug)
            for (String b : a)
                System.out.println(b);
    }

    private static void debug(String[][] a) {
        if (Debug)
            for (String[] b : a) {
                for (String c : b)
                    System.out.print(c + " ");
                System.out.println();
            }
    }

    private static void debug(String[][] a, Boolean debug) {
        if (debug)
            for (String[] b : a) {
                for (String c : b)
                    System.out.print(c + " ");
                System.out.println();
            }
    }

    /*
     * private static void debug(List<String[]> a) { if (Debug) for (String[] b : a)
     * { for (String c : b) System.out.print(c + " "); System.out.println(); } }
     * 
     * private static void debug(List<String[]> a, Boolean debug) { if (debug) for
     * (String[] b : a) { for (String c : b) System.out.print(c + " ");
     * System.out.println(); } }
     */

    /**
     * This command will take a string name for a file and attempt to output the
     * files contents in the form of a String array
     * 
     * @param file is the name of the file to read
     * @return is a String[] that contains each line in the file
     * 
     * @author Nick Cottrell
     * @version 1.0
     * @since 2019-03-08
     */
    private static String[] readFile(String file) {
        List<String> result = new ArrayList<String>();
        if (file.endsWith(".html")) {
            File html = new File(file);
            try {
                Scanner scfile = new Scanner(html);
                while (scfile.hasNextLine()) {
                    result.add(scfile.nextLine());
                }
                scfile.close();
                String[] fin = new String[result.size()];
                fin = result.toArray(fin);
                return fin;
            } catch (FileNotFoundException e) {
                return new String[1];
            }
        }
        return new String[1];
    }

    /**
     * This is the function that runs when no html files are added to the programs
     * arguements. it will search its current directory for html files to act on and
     * use them instead.
     * 
     * @return is a String[] which contains the names of all html files in current
     *         directory
     */
    private static String[] getFilesInDirectory() {
        int count = 0;
        File[] files = new File(".").listFiles();
        for (File a : files)
            if (a.getName().endsWith(".html"))
                count += 1;
        String[] names = new String[count];
        count = 0;
        for (int f = 0; f < files.length; f++) {
            if (files[f].getName().endsWith(".html")) {
                names[f] = files[count].getName();
                count += 1;
            }
        }
        return names;
    }

    /**
     * This function takes the lines given from a file and searches for specific
     * data that relates to peoples sign ins. it then converts the data into a data
     * matrix with each row specifying a person, and each column defining an
     * attribute of each person.
     * 
     * @param htmlContent the lines given by the file
     * @return a String[][] with each persons attributes
     * 
     * @author Nick COttrell
     * @version 1.0
     * @since 2019-03-08
     */
    public static String[][] getContentToArray(String[] htmlContent) {
        String text = htmlContent[2].substring(htmlContent[2].indexOf("<textarea") + 22);
        debug("Text: " + text);
        for (int i = 3; i < htmlContent.length; i++) {
            if (htmlContent[i].indexOf("</textarea>") == -1) {
                text += "\n" + htmlContent[i];
                // debug(text);
            } else { // once line has a </textarea>, it stops adding lines, but includes the line
                     // with </textarea>
                text += "\n" + htmlContent[i].substring(0, htmlContent[i].indexOf("</textarea>"));
                break;
            }
        }
        debug(text);

        /* Dictionary Creation */
        List<String[]> directory = new ArrayList<String[]>(); // the matrix that will be used to store content
        String[] people = text.split("\n");
        String[] attr;
        String[] hold = new String[5]; // there will only every be 5 attributes for anyone to have ever. that will only
                                       // change if we ever make first and last name seperate. in that case, wed need a
                                       // new function to account for that
        String purpose = "";
        for (String i : people) {
            attr = i.split(" ");
            purpose = "";
            if (attr.length >= 5) {
                for (int p = 5; p < attr.length - 1; p++)
                    purpose += attr[p] + " ";
                purpose += attr[attr.length - 1];
                hold = new String[] { (attr[0] + " " + attr[1]), attr[2], attr[3], attr[4], purpose };
                directory.add(hold);
            } else if (attr.length >= 1) {
                hold = new String[5];
                if (attr.length > 1) {
                    hold[0] = (attr[0] + " " + attr[1]);
                    for (int a = 2; a < attr.length; a++) {
                        hold[a - 1] = attr[a];
                    }
                } else {
                    hold[0] = attr[0];
                }
                for (int b = attr.length; b < hold.length; b++) {
                    hold[b] = " "; // since all the spots in the matrix length and width wise, i had to make the
                                   // attributes equals, no matter what. to combat this, i fill all empty slots
                                   // with spaces to be dealt with when converting to csv.
                }
                directory.add(hold);
            }
        }

        /* packing dictionary into matrix */
        String[][] result = new String[directory.size()][5];
        result = directory.toArray(result);

        /* double checking array to remove null values */
        for (int row = 0; row < result.length; row++)
            for (int col = 0; col < result[row].length; col++)
                if (result[row][col] == null) // if the value is outright null (could never figure out how), it will
                                              // replace it with a space.
                    result[row][col] = " ";
        return result;
    }

    /**
     * This function is depricated for a better output option. takes in a dictionary
     * matrix and converts it into a csv friendly string
     * 
     * @deprecated replaced by arrayToCsvList()
     * @param directroy is the matrix containing everyones information.
     * @return everyones information inside a string in csv format.
     * @see {@link htmlFileToCsv#arrayToCsvList(String[][])}
     * 
     * @author Nick COttrell
     * @version 1.0
     * @since 2019-03-08
     */
    public static String arrayToCsvString(String[][] directory) {
        String cvArray = "";
        for (String[] row : directory) {
            cvArray += row[0];
            for (int col = 1; col < row.length; col++) {
                debug("row[col]: " + row[col]);
                if (!row[col].equals(" "))
                    cvArray += ", " + row[col];
            }
            cvArray += "\n";
        }
        return cvArray + "\n";
    }

    /**
     * This function will take the database of peoples information and make it into
     * a string list in csv format to be used by an output function to a file
     * 
     * @param directory is a String[][] matrix that contains everyones attributes
     * @return a List<String> that containes each individual line in a csv format
     * 
     * @author Nick Cottrell
     * @version 1.0
     * @since 2019-03-08
     */
    public static List<String> arrayToCsvList(String[][] directory) {
        List<String> result = new ArrayList<String>();
        String cvArray = ""; // this line is used to add and organize all of the files contents
        for (String[] row : directory) {
            cvArray = row[0]; // immediately adds date/name. next line will add ", " so that it is never at
                              // the end of a line
            for (int col = 1; col < row.length; col++) {
                debug("row[col]: " + row[col], false);
                if (!row[col].equals(" ")) // if any values were null/empty, it will not categorize them into the file
                    cvArray += ", " + row[col];
            }
            result.add(cvArray);
        }
        return result;
    }

    public static void main(String args[]) {
        List<String> input = new ArrayList<String>();
        Boolean reveal = false; // remove when done with experiment
        if (args.length > 0) {
            for (String i : args) {
                if (i.endsWith(".html"))
                    input.add(i);
                else if ((new File(i + ".html")).exists())
                    input.add(i + ".html");
                else if (i.equals("/reveal"))
                    reveal = true;
            }
        } else {
            for (String i : getFilesInDirectory()) {
                if (i.endsWith(".html"))
                    input.add(i);
            }
        }
        debug(input);
        List<String> output = new ArrayList<String>(); // this is roughly the entire object since it holds all the
                                                       // information
        String[][] Database;
        File trash;
        for (String i : input) {
            output = arrayToCsvList(getContentToArray(readFile(i)));
            output.add(""); // this line helps separate multiple file scrapings for better organization
            Database = getContentToArray(readFile(i)); // this is the object that contains all the information on each
                                                       // person
            /* removing html file and baggage */
            trash = new File(i);
            if (trash.isDirectory()) {
                for (File e : trash.listFiles())
                    e.delete();
            }
            trash.delete();
            /*
             * Removing folder that normally goes along with html file, in fashion
             * %htmlFile%_files
             */
            String name = trash.getName();
            trash = new File(name.substring(0, name.indexOf(".html")) + "_files");
            if (trash.isDirectory()) {
                for (File e : trash.listFiles())
                    e.delete();
            }
            trash.delete();
        }
        debug(output, false);

        if (reveal) {
            debug(output, true);
        }
        /* outputing to file */
        try {
            Files.write(Paths.get("names.csv"), output, StandardCharsets.UTF_8, StandardOpenOption.APPEND);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
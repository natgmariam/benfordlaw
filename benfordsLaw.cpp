/*Name: Natnael Gebremariam, 5002150850, CS 202-1001, Assignment 1
Description: The program will use Io/File to read a file and 
using the first digit account for them, printing an outfile 
with * to show how many of that number are starters in the file
Input: The input file will be files ready, contaning number 
that will be read as ints and account for first number 
Output: the output is an outfile that will have how many 
times each number shows up in the form of an *. 
*/
#include <iostream>
#include <iomanip>
#include <math.h> //math library 
#include <string>
#include <cstring>
#include <fstream> //file library 
#include <sstream>
using namespace std;

/**
 * @brief findFirstDigit : Calculate the first digit of the given number
 * @param number
 */
//function to find the first digit 
int findFirstDigit(int number)
{
    while (number >= 10)
        number /= 10;
    return number; // return first digit
}

/**
 * @brief findHundreds : Read the value from t
 * he second parameter and calculate the
 * number of 100's of a given value
 *&param value- value passed from main() like the total count of 0's
 * in the given input file
 * &param ofstream &resultFile- 
 * print the number of asterisks(stars) based on the calculated value
 * and also return value to the output file
 */
//function to /=100, and print the * according to the result 
int findHundreds(ofstream &resultFile, double value)
{
    double hundereds;
    //to round down values belowe 100 as 0's 
    if (value < 100){
    hundereds =0; 
    
    }
    //to devid by 100 if value is greater than 100
    else {
    hundereds = round(value / 100);
    }
    resultFile << value << "|" << string(hundereds, '*')
              << "-" << hundereds << endl;
    

    return hundereds; 
    // return hundreds value; if value=220; then it should return 22
}

// argc = argument count
// argv = argument vector
int main(int argc, char *argv[])
{
    ifstream inFile;
    ofstream outFile;
    string file; // file retrvial
    string data; // read the file
    string arg1;
    string word; //string to hold 
    int number = 0;
    int count = 0;
    int firstCount[10] = {}; //array to hold 1-9 

    if (argc != 2)
    {
        cout << "Usage: ./benFordsLaw <base filename>.txt \n";
        return 0;
    }

    arg1 = argv[1];

    file = argv[1];

    inFile.open(file.c_str());

    //read file and checks for error in file entry 
    while (inFile.fail())
    {
        inFile.clear();
        inFile.ignore(100, '\n');
        cout << "Error: You entered " << file 
        << "\nplease re-enter valid filename:" << endl;
        cin >> file;
        inFile.open(file.c_str());
    }

    if (inFile.is_open())
    {
        //     //outfile << file << " is opned " << endl;
    }
    //to rename the outfile as a results file 
    string rawname = file.substr(0, file.find_last_of("."));
    outFile.open((rawname + "_results.txt"));

    //print statments 
    outFile << "CS 202 - Assignment #1" << endl;
    outFile << "Benford's Law Program" << endl;
    outFile << "File Name: " << file << endl;
    outFile << endl;
    outFile << "---------------------------------" << endl;
    outFile << "Benford's Law - Test Results: " << endl;

    //skiping the first 5 lines of the file 
    for (int i = 0; i < 5; i++)
    {
        getline(inFile, data);
    }

    //taking the data from the file 
    int value=0;
    while (!(inFile.eof()))
    {
        // reading the file
        getline(inFile, data);
        if (data == "")
            break;

        // trying to only read the ints
        istringstream line(data);

        // holder for the file data
        string holder;
        // to seprate the strings and int

        //accounts for spacing and - char 
        // and = 
        getline(line, holder, ' ');
        if (holder[0] == '-'){
            getline(line, holder, '-');
        }
        else if (holder[0] == '='){
            getline(line, holder,'='); 
        } 
        //stors the strings from the data
        word = holder;
        
        //to get the int untill the eof 
        while (getline(line, holder, ' '))
        {
        }
        getline(line, holder);

        //converting string to int 
        value = stoi(holder);

        //function call to get the first int value 
        ++firstCount[findFirstDigit(value)];

        ++count;
    }
    // prints out the total digits and data points 
    outFile << "Total Data Points: " << count << endl;
    outFile << "First Digit: " << endl;
    outFile << endl;

    //to print the proper table format and arrange them 
    for (int i = 0; i < 10; i++)
    {

       outFile << i << right << setw(9);
        findHundreds(outFile, firstCount[i]);
    }
        outFile << "---------------------------------" << endl;

    //close file 
    inFile.close();
    outFile.close();

    return 0;
}

This package allows for viewing the longest common subsequence between two strings. Included in this package is a bash script that allows for an easy-to-use interface (runProgram), the program that calculates the longest subsequence, and a DNA subsequence generator.

First time users should type:

bash runProgram

to build the programs and then give simple options to use the programs.




DNAGen.c
Builds with: make d

The DNA subsequence generator randomly generates strings consisting of the characters 'A', 'U', 'C', or 'G', with a length based on the first argument given. If a second argument is given, instead of outputting the result, it saves it to the file specified in the second argument.

Usage:

./dnagen 3020
Outputs a DNA sequence that is 3020 characters long and prints it to stdout.

./dnagen 34380 outputfile.txt
Outputs a DNA sequence that is 34380 characters long to the file "outputfile.txt"


lcs.c
Builds with: make

This program uses Dynamic Programming to determine the longest subsequence of characters within two strings. Strings can be inputted through files

Usage:

./lcs "String 1 was here" "String 2 is not here....srtinsfwasdkjd "
Result: "String  s here"

./lcs -f file1.txt file2.txt
Compares file1.txt and file2.txt and outputs the result to stdout.

./lcs -f file1.txt file2.txt resultfile.txt
Compares file1.txt and file2.txt and outputs the result to resultfile.txt

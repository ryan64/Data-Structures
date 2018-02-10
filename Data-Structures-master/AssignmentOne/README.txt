README File:

--The function of this code is to multiply a square matrix by itself. It will take a string argument as the input file and process the data into a matrix to be multiplied. The code will then output the result into a file specified by the user in the terminal.-- 

HOW TO COMPILE: 

1. In the terminal, run the following command: g++ -std=c++11 *.cpp -o densemult
--This command will compile the densemult.cpp file. 

2. Next, run the following command: ./densemult "A=inputFile.txt;C=outputFile.txt"
--inputFile.txt = the input file you're passing in as argument. 
--outputFile.txt = the output file you're writing to. 
--The input file is the name of the file you have in the directory, and the output file can be named whatever you wish. 

3. Now, you should see a output on the terminal showing "A: 'yourinputfilename.txt' \n C: 'youroutputfilename.txt'" assuming the input file exists, otherwise it will output a message stating "File is empty.... aborting". 

ERROR CHECKING: 
Error messages can be displayed in the terminal if one of the following errors occur >>

1. If the file does not exist. 
2. If there is no data in input file. 
3. if the Matrix is a rectangular matrix. 

Name: Ryan Gonzalez
PeopleSoft ID: 1330002

#include <SPI.h>
#include <SD.h>
#include <stdlib.h>
const int pinCS = 4; // change this to your pin

void setup () {
  Serial.begin (9600); // start serial communication
  pinMode (pinCS, OUTPUT); // set pinCS as output
  if (!SD.begin (pinCS)) { // initialize SD card
    Serial.println ("SD card initialization failed");
    return;
  }
  File myFile = SD.open ("prog.txt"); // open the file
  if (!myFile) { // check if the file exists
    Serial.println ("File not found");
    return;
  }

  String line; // to store each line
  int row = 0; // to keep track of the row index
  int col = 0; // to keep track of the column index
  unsigned long matrix [5] [3]; // to store the matrix, change the size as needed
  myFile = SD.open("prog.txt");
  while (myFile.available ()) { // while there is something to read
    line = myFile.readStringUntil ('\n'); // read a line until newline character
    //Serial.println (line); // print the line for debugging
    col = 0; // reset the column index for each line
    for (int i = 0; i < line.length (); i++) { // loop through each character in the line
      if (line.charAt (i) == ',') { // if a comma is found
        matrix [row] [col] = strtoul (line.substring (0, i).c_str (), NULL, 10); // convert the substring before the comma to an unsigned long and store it in the matrix
        line = line.substring (i + 1); // remove the substring before the comma from the line
        i = 0; // reset the index to start from the beginning of the new line
        col++; // increment the column index
      }
    }
    matrix [row] [col] = strtoul (line.c_str (), NULL, 10); // convert the remaining substring to an unsigned long and store it in the matrix
    row++; // increment the row index
  }
  myFile.close (); // close the file when done reading

  Serial.println("Imprimiendo matriz:");
  // print the matrix for debugging
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      Serial.print (matrix [i] [j], DEC); // print the matrix element in decimal format
      Serial.print (" ");
    }
    Serial.println ();
  }
}

void loop () {
  
}
#include <iostream>
#include <string>
#include "p2Table.h"

using namespace std;

int main()
{
   Table table;

   // TODO: read in the csv file
   string csvFile;
   cout << "Please enter the file name: ";
   cin >> csvFile;
   if (table.read(csvFile))
      cout << "File \"" << csvFile << "\" was read in successfully.";
   else exit(-1); // csvFile does not exist.
   cout << endl;

   string command;
   int col;

   // read and execute commands
   while (cin >> command) {
     if (command == "ADD") {
       table.add();
     } else if (command == "PRINT") {
       table.print();
     } else if (command == "SUM") {
       cin >> col;
       table.sum(col);
     } else if (command == "AVE") {
       cin >> col;
       table.avg(col);
     } else if (command == "MAX") {
       cin >> col;
       table.max(col);
     } else if (command == "MIN") {
       cin >> col;
       table.min(col);
     } else if (command == "DIST") {
       cin >> col;
       table.count(col);
     } else if (command == "EXIT") {
       break;
     } else {
       cout << endl;
     }
   }
}

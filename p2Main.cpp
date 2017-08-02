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
      cout << "File \"" << csvFile << "\" was read in successfully." << endl;
   else exit(-1); // csvFile does not exist.
   cout << endl;

   string command;
   int col;

   // read and execute commands
   cout << "Type Command:";
   while (cin >> command) {
     if (command == "ADD") {
       table.add();
       cout << "Type Command:";
     } else if (command == "PRINT") {
       table.print();
       cout << "Type Command:";
     } else if (command == "SUM") {
       cin >> col;
       table.sum(col);
       cout << "Type Command:";
     } else if (command == "AVE") {
       cin >> col;
       table.avg(col);
       cout << "Type Command:";
     } else if (command == "MAX") {
       cin >> col;
       table.max(col);
       cout << "Type Command:";
     } else if (command == "MIN") {
       cin >> col;
       table.min(col);
       cout << "Type Command:";
     } else if (command == "COUNT") {
       cin >> col;
       table.count(col);
       cout << "Type Command:";
     } else if (command == "EXIT") {
       break;
     } else {
       cout << endl;
       cout << "Type Command:";
     }
   }
}

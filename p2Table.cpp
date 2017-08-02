#include "p2Table.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Implement member functions of class Row and Table here

void
Row::setRowLength(int length)
{
  _data = new int[length];
}

void
Row::fillRow(int index, int num)
{
  _data[index] = num;
}

void
Row::printRow(int rowLength)
{
  for (int i = 0; i < rowLength; i++) {
    cout << _data[i] << ",";
  }
}

void
Table::print()
{
  for (int i = 0; i < rowCount; i++) {
    _rows[i].printRow(rowLength);
    cout << endl;
  }
}

bool
Table::read(const string& csvFile)
{
  fstream file(csvFile);

  // string csv = "1,2^M3,^M5,6^M,8^M";
  string csv = "100,,-2,^M,-33,49,57^M6,79,,8^M,-99,10,^M11,21,323,^M,,14,-5^M";
  int csvIndex = 0;
  rowCount = 0;
  rowLength = 1;
  bool checkRowLength = true;
  while (csvIndex < csv.length()) {
    if (csv[csvIndex] == '^') {
      checkRowLength = false;
      rowCount++;
    };
    if (checkRowLength && (csv[csvIndex] == ',')) {
      rowLength++;
    }
    csvIndex++;
  };

  int matrix[rowCount][rowLength];

  csvIndex = 0;
  int firstIndex = 0;
  int secondIndex = 0;
  string str;
  while(csvIndex < csv.length()) {
    if (csv[csvIndex] != ',' && csv[csvIndex] != '^' && csv[csvIndex] != '-') {
      if (csv[csvIndex+1] != ',' && csv[csvIndex+1] != '^') {
        if (csv[csvIndex+2] != ',' && csv[csvIndex+2] != '^') {
          if (csv[csvIndex+3] == ',') {
            // 100,
            str = csv.substr (csvIndex,3);
            matrix[firstIndex][secondIndex] = atoi(str.c_str());
            secondIndex++;
            csvIndex += 3;
          } else if (csv[csvIndex+3] == '^') {
            // 100^M
            str = csv.substr (csvIndex,3);
            matrix[firstIndex][secondIndex] = atoi(str.c_str());
            csvIndex += 3;
          }
        } else if (csv[csvIndex+2] == ',') {
          // 99,
          str = csv.substr (csvIndex,2);
          matrix[firstIndex][secondIndex] = atoi(str.c_str());
          secondIndex++;
          csvIndex += 2;
        } else if (csv[csvIndex+2] == '^') {
          // 99^M
          str = csv.substr (csvIndex,2);
          matrix[firstIndex][secondIndex] = atoi(str.c_str());
          csvIndex += 2;
        }
      } else if (csv[csvIndex+1] == ',') {
        // 5,
        str = csv.substr (csvIndex,1);
        matrix[firstIndex][secondIndex] = atoi(str.c_str());
        secondIndex++;
        csvIndex++;
      } else if (csv[csvIndex+1] == '^') {
        // 5^M
        str = csv.substr (csvIndex,1);
        matrix[firstIndex][secondIndex] = atoi(str.c_str());
        csvIndex++;
      }
    } else if (csv[csvIndex] == ',') {
      if (csv[csvIndex+1] != ',' && csv[csvIndex+1] != '^') {
        // ,1
        csvIndex++;
      } else if (csv[csvIndex+1] == ',') {
        // ,,
        matrix[firstIndex][secondIndex] = -500;
        secondIndex++;
        csvIndex++;
      } else if (csv[csvIndex+1] == '^') {
        // ,^M
        matrix[firstIndex][secondIndex] = -500;
        secondIndex++;
        csvIndex++;
      }
    } else if (csv[csvIndex] == '^') {
      if (csv[csvIndex+2] != ',') {
        // ^M5
        // ^M-4
        firstIndex++;
        secondIndex = 0;
        csvIndex += 2;
      } else if (csv[csvIndex+2] == ',') {
        // ^M,
        firstIndex++;
        matrix[firstIndex][0] = -500;
        secondIndex = 1;
        csvIndex += 2;
      }
    } else if (csv[csvIndex] == '-') {
      if (csv[csvIndex+1] != ',' && csv[csvIndex+1] != '^') {
        if (csv[csvIndex+2] != ',' && csv[csvIndex+2] != '^') {
          if (csv[csvIndex+3] == ',') {
            // -99,
            str = csv.substr (csvIndex,3);
            matrix[firstIndex][secondIndex] = atoi(str.c_str());
            secondIndex++;
            csvIndex += 3;
          } else if (csv[csvIndex+3] == '^') {
            // -99^M
            str = csv.substr (csvIndex,3);
            matrix[firstIndex][secondIndex] = atoi(str.c_str());
            secondIndex++;
            csvIndex += 3;
          }
        } else if (csv[csvIndex+2] == ',') {
          // -9,
          str = csv.substr (csvIndex,2);
          matrix[firstIndex][secondIndex] = atoi(str.c_str());
          secondIndex++;
          csvIndex += 2;
        } else if (csv[csvIndex+2] == '^') {
          // -9^M
          str = csv.substr (csvIndex,2);
          matrix[firstIndex][secondIndex] = atoi(str.c_str());
          secondIndex++;
          csvIndex += 2;
        }
      }
    }
  }

  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < rowLength; j++) {
      cout << matrix[i][j] << ',';
    }
    cout << endl;
  }

  Row *newRow = new Row[rowCount];

  for(int i = 0; i < rowCount; i++) {
    newRow[i].setRowLength(rowLength);
    for (int j = 0; j < rowLength; j++) {
      newRow[i].fillRow(j, matrix[i][j]);
    }
    _rows.push_back(newRow[i]);
  }

  delete[] newRow;

  return true; // TODO
}

#include "p2Table.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

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

int
Row::getIndex(int index)
{
  return _data[index];
}

const int
Row::operator[] (size_t i) const
{
  return _data[i];
}

int&
Row::operator[] (size_t i)
{
  int& data = _data[i];
  return data;
}

const Row&
Table::operator[] (size_t i) const
{
  return _rows[i];
}

Row&
Table::operator[] (size_t i)
{
  return _rows[i];
}

void
Table::print()
{
  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < rowLength; j++) {
      if (_rows[i][j] == -500) {
        cout << setw(4) << right << "";
      } else {
        cout << setw(4) << right << _rows[i][j];
      }
    }
    cout << endl;
  }
}

bool
Table::read(const string& csvFile)
{
	ifstream file(csvFile);
  if(!file.is_open())
  {
    cout << "Maybe the file doesn't exist." << endl;
    return false;
  } else {
    string buffer;
    string csv = "";
    while(!file.eof())
    {
      getline(file,buffer,'\r');
      if(!file.eof())
      csv += buffer;
      csv += "^M";
    }
    // cout << csv << endl;

    // string csv = "1,2^M3,^M5,6^M,8^M";
    // string csv = "100,,-2,^M,-33,49,57^M6,79,,8^M,-99,10,^M11,21,323,^M,,14,-5^M";
    int csvIndex = 0;
    rowCount = 0;
    rowLength = 1;
    bool checkRowLength = true;

    // check rowCount & rowLength
    while (csvIndex < csv.length()) {
      if (csv[csvIndex] == '^') {
        checkRowLength = false;
        if (csv[csvIndex+2] != '^') {
          rowCount++;
        }
      };
      if (checkRowLength && (csv[csvIndex] == ',')) {
        rowLength++;
      }
      csvIndex++;
    };

    // initial dynamic matrix array
    int** matrix = new int*[rowCount];
    for(int i = 0; i < rowCount; ++i) {
      matrix[i] = new int[rowLength];
    }

    // transform csv content into dynamic matrix array
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
        } else if (csv[csvIndex+2] == '^') {
          // ^M^M
          break;
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

    // put dynamic matrix array into Table
    Row *newRow = new Row[rowCount];

    for(int i = 0; i < rowCount; i++) {
      newRow[i].setRowLength(rowLength);
      for (int j = 0; j < rowLength; j++) {
        newRow[i].fillRow(j, matrix[i][j]);
      }
      _rows.push_back(newRow[i]);
    }

    delete[] newRow;
    return true;
  }
}

int
Table::sum(int col)
{
  int sum = 0;
  for (int i = 0; i < rowCount; i++) {
    if (_rows[i][col] != -500) {
      sum += _rows[i][col];
    }
  }
  cout << "The summation of data in column #" << col << " is " << sum << endl;
  return sum;
}

int
Table::max(int col)
{
  int max = -100;
  int temp = -500;
  for (int i = 0; i < rowCount; i++) {
    temp = _rows[i][col];
    if (max < temp) {
      max = temp;
    }
  }
  cout << "The maximum of data in column #" << col << " is " << max << endl;
  return max;
}

int
Table::min(int col)
{
  int min = 101;
  int temp = 500;
  for (int i = 0; i < rowCount; i++) {
    if (_rows[i][col] != -500) {
      temp = _rows[i][col];
    }
    if (min > temp) {
      min = temp;
    }
  }
  cout << "The minimum of data in column #" << col << " is " << min << endl;
  return min;
}

int
Table::count(int col)
{
  int count = 0;
  for (int i = 0; i < rowCount; i++) {
    if (_rows[i][col] != -500) {
      count++;
    }
  }
  cout << "The distinct count of data in column #" << col << " is " << count << endl;
  return count;
}

double
Table::avg(int col)
{
  double sumResult = 0;
  double countResult = 0;
  for (int i = 0; i < rowCount; i++) {
    if (_rows[i][col] != -500) {
      sumResult += (double)_rows[i][col];
      countResult++;
    }
  }
  double avg = sumResult / countResult;
  cout << fixed << setprecision(1) << "The average of data in column #" << col << " is " << avg << endl;
  return avg;
}

void
Table::add()
{
  Row tempRow;
  tempRow.setRowLength(rowLength);
  string inputNum;
  int num;
  for (int i = 0; i < rowLength; i++) {
    cin >> inputNum;
    if (inputNum != "-") {
      num = atoi(inputNum.c_str());
      tempRow.fillRow(i,num);
    } else {
      tempRow.fillRow(i, -500);
    }
  }
  _rows.push_back(tempRow);
  rowCount++;
}

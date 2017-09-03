#include "p2Table.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>

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
      if (_rows[i][j] == 2147483647) {
        cout << setw(4) << right << '.';
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
	ifstream fileM(csvFile);
  if(!fileM.is_open())
  {
    cout << "Maybe the file doesn't exist." << endl;
    return false;
  } else {
    string bufferM;
    string bufferJ;
    string csvM = "";
    string csvJ = "";
    int mCount = 0;
    int jCount = 0;
    while(!fileM.eof())
    {
      getline(fileM,bufferM,'\r');
      csvM += bufferM;
      csvM += "^M";
      mCount++;
    }

    ifstream fileJ(csvFile);
    if(!fileJ.is_open())
    {
      cout << "Maybe the file doesn't exist." << endl;
      return false;
    } else {
      while(!fileJ.eof())
      {
        getline(fileJ,bufferJ,'\n');
        csvJ += bufferJ;
        csvJ += "^M";
        jCount++;
      }
    }
    string csv = "";

    bool readJ = false;
    if (mCount >= jCount) {
      csvM.erase(std::remove(csvM.begin(), csvM.end(), '\n'), csvM.end());
      csv = csvM;
    } else {
      csv = csvJ;
      readJ = true;
    }
    int csvIndex = 0;
    rowCount = 0;
    rowLength = 1;
    bool checkRowLength = true;
    int length = csv.length();

    // check rowCount & rowLength
    while (csvIndex < length) {
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

    ifstream file(csvFile);
    if(!file.is_open())
    {
      cout << "Maybe the file doesn't exist." << endl;
      return false;
    } else {
      string buffer;
      while(!file.eof())
      {
        if (readJ) {
          getline(file,buffer,'\n');
        } else {
          getline(file,buffer,'\r');
          buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
        }
        istringstream templine(buffer);
        string data;
        while (getline(templine,data,','))
        {
          if (data.empty()) {
            matrix[firstIndex][secondIndex] = 2147483647;
            secondIndex += 1;
          } else {
            matrix[firstIndex][secondIndex] = atof(data.c_str());
            secondIndex += 1;
          }
        }
        if (secondIndex == rowLength - 1) {
          matrix[firstIndex][secondIndex] = 2147483647;
          secondIndex += 1;
        }
        firstIndex += 1;
        secondIndex = 0;
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
  bool nullcol = true;
  for (int i = 0; i < rowCount; i++) {
    if (_rows[i][col] != 2147483647) {
      sum += _rows[i][col];
      nullcol = false;
    }
  }
  if (nullcol)  {
    cout << "Error: This is a NULL column!!" << endl;
  } else {
    cout << "The summation of data in column #" << col << " is " << sum << "." << endl;
  }
  return sum;
}

int
Table::max(int col)
{
  int max = -2147483648;
  int temp = -2147483648;
  bool nullcol = true;
  for (int i = 0; i < rowCount; i++) {
    temp = _rows[i][col];
    if (max < temp && temp != 2147483647) {
      max = temp;
      nullcol = false;
    }
  }
  if (nullcol)  {
    cout << "Error: This is a NULL column!!" << endl;
  } else {
    cout << "The maximum of data in column #" << col << " is " << max << "." << endl;
  }
  return max;
}

int
Table::min(int col)
{
  int min = 2147483647;
  int temp = 2147483647;
  bool nullcol = true;
  for (int i = 0; i < rowCount; i++) {
    if (_rows[i][col] != 2147483647) {
      temp = _rows[i][col];
      if (min > temp) {
        min = temp;
        nullcol = false;
      }
    }
  }
  if (nullcol) {
    cout << "Error: This is a NULL column!!" << endl;
  } else {
    cout << "The minimum of data in column #" << col << " is " << min << "." << endl;
  }
  return min;
}

int
Table::count(int col)
{
  int count = 0;
  int dcount = 0;
  bool check = false;

  int *array = new int[rowCount];

  for (int i = 0; i < rowCount; i++) {
    if (_rows[i][col] != 2147483647) {
      array[count] = _rows[i][col];
      count++;
    }
  }

  if (count != 0) {
    dcount = count;
    for (int i = 0; i < count - 1; i++) {
      for (int j = count - 1; j > i; j--) {
        if (array[i] == array[j]) {
          check = true;
        };
      }
      if (check) {
        dcount -= 1;
        check = false;
      }
    }

    delete [] array;
  } else {
    dcount = count;
  }

  if (dcount == 0) {
    cout << "Error: This is a NULL column!!" << endl;
  } else {
    cout << "The distinct count of data in column #" << col << " is " << dcount << "."  << endl;
  }
  return dcount;
}

double
Table::avg(int col)
{
  double sumResult = 0;
  double countResult = 0;
  for (int i = 0; i < rowCount; i++) {
    if (_rows[i][col] != 2147483647) {
      sumResult += (double)_rows[i][col];
      countResult++;
    }
  }
  double avg = sumResult / countResult;
  if (countResult == 0) {
    cout << "Error: This is a NULL column!!" << endl;
  } else {
    cout << fixed << setprecision(1) << "The average of data in column #" << col << " is " << avg << "." << endl;
  }
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
    if (inputNum != ".") {
      num = atoi(inputNum.c_str());
      tempRow.fillRow(i,num);
    } else {
      tempRow.fillRow(i, 2147483647);
    }
  }
  _rows.push_back(tempRow);
  rowCount++;
}

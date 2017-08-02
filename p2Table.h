#ifndef P2_TABLE_H
#define P2_TABLE_H

#include <vector>
#include <string>

using namespace std;

class Row
{
public:
   void setRowLength(int);
   void fillRow(int, int);
   int getIndex(int);
   const int operator[] (size_t i) const;
   int& operator[] (size_t i);

private:
   int  *_data;
};

class Table
{
public:
   const Row& operator[] (size_t i) const;
   Row& operator[] (size_t i);

   void print();
   bool read(const string&);
   int sum(int);
   int max(int);
   int min(int);
   int count(int);
   double avg(int);
   void add();

private:
   vector<Row>  _rows;
   int rowCount;
   int rowLength;
};

#endif // P2_TABLE_H

/**
Step 1. g++ -std=c++11 -Wall -Werror -O2 -o test0 Matrix.cpp test0.cpp
Step 2. ./test0 > test0.out
Step 3. diff test0.out test0.sol
**/

#include <iostream>
#include <fstream>
#include "SMatrix.h"
using namespace std;
int main(void) {
  //ifstream inf("1.txt");
  //istream &is = inf;
  //  SMatrix m = SMatrix::identity(200);
  // m.setVal(0,1,1);
  // m.setVal(1,0,2);
  //  m.setVal(1,2,1);
  //  m.setVal(2,0,3);
  SMatrix m1(3,3);
  m1.setVal(0,0,1);
  m1.setVal(0,1,-1);
  m1.setVal(1,2,1);
 m1.setVal(1,1,1);
m1.setVal(1,0,2);
 m1.setVal(1,2,0);
  // cout<<m<<endl<<m1<<endl;

cout<<m1<<endl;

//cout<<m<<endl;
//~SMatrix(m);
//cout<<m<<endl;
//m1+=m;
//cout<<m1;



  return 0;

}

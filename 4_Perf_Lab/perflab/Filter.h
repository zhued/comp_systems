//-*-c++-*-
#ifndef _Filter_h_
#define _Filter_h_

using namespace std;

class Filter {
  int divisor;
  int dim;
  

public:
	int *data;
  Filter(int _dim);
  int get(int r, int c);
//  void getData(int* dataret);
  void set(int r, int c, int value);

  int getDivisor();
  void setDivisor(int value);

  int getSize();
};

#endif

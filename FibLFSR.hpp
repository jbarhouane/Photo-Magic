#ifndef FIBLFSR_H
#define FIBLFSR_H
#include <iostream>
#include <string>

using namespace std;

class FibLFSR 
{
public:
  FibLFSR();
  FibLFSR(string seed);
  int step();
  int generate(int k);
  int s_length(void);
  string get_seed(void);
  void set_bits(string seed);
  void set_n(int n);
  int get_n(void);
  friend ostream& operator<<(ostream&, const FibLFSR& lfsr);
private:
  string _seed;
  int _n;
};

#endif

#include <iostream>
#include <string>
#include <cmath>
#include "FibLFSR.hpp"

using namespace std;

FibLFSR::FibLFSR(string seed)
{
  _seed = seed;
  _n = seed.at(seed.length() - 1) % 2; 
}

int FibLFSR::step()
{
  int x;
  string old_bits = get_seed();
  string new_bits = "";
  for (int i = 1; i < s_length(); i++)
  {
    new_bits += old_bits.at(i);
  }
  for (int j = 0; j < s_length() / 2; j++)
  {
    char temp = old_bits.at(j);
    old_bits.at(j) = old_bits.at(s_length() - j - 1);
    old_bits.at(s_length() - j - 1) = temp;
  }
  x = old_bits.at(s_length() - 1) ^ old_bits.at(10) ^ old_bits.at(12) ^ old_bits.at(13);
  new_bits += to_string(x);
  set_bits(new_bits);
  set_n(x);
  return x;
}

int FibLFSR::generate(int k)
{
  int n = 0;
  for (int i = 0; i < k; i++)
  {
    step();
  }
  for (int j = 0; j < k; j++)
  {
    n += (get_seed().at(s_length() - j - 1) % 2) * pow(2, j);
  }
  set_n(n);
  return n;
}

int FibLFSR::s_length(void) 
{ 
  return _seed.length(); 
}

string FibLFSR::get_seed(void) 
{ 
  return _seed; 
}

void FibLFSR::set_bits(string seed) 
{ 
  _seed = seed; 
}

void FibLFSR::set_n(int n) 
{ 
  _n = n; 
}

int FibLFSR::get_n(void) 
{ 
  return _n; 
}


ostream& operator<<(ostream& output, const FibLFSR& lfsr)
{
  output << lfsr._seed << " " << lfsr._n;
  return output;
}

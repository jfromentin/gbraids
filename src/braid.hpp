#ifndef BRAID_HPP
#define BRAID_HPP

#include <iostream>
#include <cassert>
#include <fstream>
#include "config.hpp"
#include "memory.hpp"

using namespace std;

using uchar=unsigned char;

class Braid{
public:
  size_t l;
  char* tab;
public:
  static uchar code(char c);
  static char decode(uchar c);
  Braid();
  Braid(char i);
  Braid(char* buffer,size_t l);
  Braid(const Braid&);
  Braid(Braid&&);
  Braid(string str);
  ~Braid();
  Braid& operator=(const Braid&);
  Braid& operator=(Braid&&);
  Braid operator*(char i) const;
  bool can_freely_add(char i) const;
  bool operator<(const Braid&) const;
  static void disp_letter(int v);
  static void disp_list(EDList& l);
  void write(fstream& file) const;
  friend ostream& operator<<(ostream&,const Braid&);
};

inline
uchar
Braid::code(char c){
  return (c<0)?6+c:c-1;
}

inline
char
Braid::decode(uchar c){
  return (c<3)?c+1:(char)c-6;
}

inline
Braid::Braid(){
  l=0;
  tab=nullptr;
}

inline
Braid::Braid(char i){
  l=1;
  tab=new char[1];
  tab[0]=i;
}

inline
Braid::Braid(const Braid& b){
  l=b.l;
  tab=new char[l];
  for(size_t i=0;i<l;++i){
    tab[i]=b.tab[i];
  }
}
inline
Braid::Braid(Braid&& b){
  l=b.l;
  tab=b.tab;
  b.l=0;
  b.tab=nullptr;
}

inline
Braid::~Braid(){
  if(tab!=nullptr) delete[] tab;
}

inline Braid&
Braid::operator=(const Braid& b){
  if(tab!=nullptr) delete[] tab;
  l=b.l;
  tab=new char[l];
  for(size_t i=0;i<l;++i){
    tab[i]=b.tab[i];
  }
  return *this;
}
inline Braid&
Braid::operator=(Braid&& b){
  if(tab!=nullptr) delete[] tab;
  l=b.l;
  tab=b.tab;
  b.l=0;
  b.tab=nullptr;
  return *this;
}



inline Braid
Braid::operator*(char i) const{
  Braid res;
  res.l=l+1;
  res.tab=new char[l+1];
  for(size_t k=0;k<l;++k){
    res.tab[k]=tab[k];
  }
  res.tab[l]=i;
  return res;
}

inline bool
Braid::can_freely_add(char i) const{
  if(l==0) return true;
  return tab[l-1]!=-i;
}
#endif

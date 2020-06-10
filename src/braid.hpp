/*
* This file is part of Gbraids (https://github.com/jfromentin/gbraids).
* Copyright (c) 2020 Jean Fromentin (fromentin@math.cnrs.fr).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BRAID_HPP
#define BRAID_HPP

#include <iostream>
#include <cassert>
#include <fstream>
#include "config.hpp"
#include "permutation.hpp"

using namespace std;

using uchar=unsigned char;
using Int=int64_t;

extern Int amplitude;



class Braid{
private:
  union{
    struct{
      char tab[32];
    };
    struct{
      uint64_t tab64[4];
    };
  }; 
  size_t len;

public:
  static uchar code(char c);
  static char decode(uchar c);
  Braid();
  Braid(char i);
  Braid(char* buffer,size_t l);
  Braid(const Braid&);
  Braid(string str);
  ~Braid();
  size_t length() const;
  Braid& operator=(const Braid&);
  Braid operator*(char i) const;
  void operator*=(char i);
  int cmp(const Braid&) const; //-1 for <, 0 for == and 1 for >
  bool operator<(const Braid&) const;
  void write(fstream& file) const;
  void negate();
  void phi();
  static void disp_letter(int v);
  static void Dynnikov_action(char i,Int* a,Int* b);
  friend ostream& operator<<(ostream&,const Braid&);
};


void positive_Dynnikov_action(Int& x1,Int& y1,Int& x2,Int& y2);
void negative_Dynnikov_action(Int& x1,Int& y1,Int& x2,Int& y2);

inline uchar
Braid::code(char c){
  return (c<0)?6+c:c-1;
}

inline char
Braid::decode(uchar c){
  return (c<3)?c+1:(char)c-6;
}

inline
Braid::Braid(){
  tab64[0]=0;
  tab64[1]=0;
  tab64[2]=0;
  tab64[3]=0;
  len=0;
}

inline
Braid::Braid(const Braid& b){
  tab64[0]=b.tab64[0];
  tab64[1]=b.tab64[1];
  tab64[2]=b.tab64[2];
  tab64[3]=b.tab64[3];
  len=b.len;
}

inline
Braid::~Braid(){
}

inline Braid&
Braid::operator=(const Braid& b){
  tab64[0]=b.tab64[0];
  tab64[1]=b.tab64[1];
  tab64[2]=b.tab64[2];
  tab64[3]=b.tab64[3];
  len=b.len;
  return *this;
}

inline size_t
Braid::length() const{
  return len;
}

inline void
Braid::operator*=(char i){
  tab[len++]=i;
}

inline void
Braid::negate(){
  for(size_t i=0;i<len;++i) tab[i]*=-1;
}

inline void
Braid::phi(){
  for(size_t i=0;i<len;++i){
    char v=tab[i];
    tab[i]=(v>0)?4-v:-4-v;
  }
}

inline bool
Braid::operator<(const Braid& b) const{
  return cmp(b)==-1;
}

inline void
Braid::disp_letter(int v){
  if(v>0) cout<<char('a'+v-1);
  else cout<<char('A'-v-1);
}


inline void
Braid::Dynnikov_action(char i,Int* a,Int* b){
  if(i>0) positive_Dynnikov_action(a[i-1],b[i-1],a[i],b[i]);
  else negative_Dynnikov_action(a[-i-1],b[-i-1],a[-i],b[-i]);
}

inline Int pos(Int a){
  return (a<0)?0:a;
}

inline Int neg(Int a){
  return (a>0)?0:a;
}

#endif

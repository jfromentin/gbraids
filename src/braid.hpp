#ifndef BRAID_HPP
#define BRAID_HPP

#include <iostream>
#include <cassert>
#include <fstream>
#include "config.hpp"
#include "memory.hpp"
#include "permutation.hpp"

using namespace std;

using uchar=unsigned char;
using Int=int64_t;

extern Int amplitude;

class Invariant{
public:
  union{
    struct{
      char e13,e24,e14;
      char pad8=0;
      uint32_t pad32=0;
    };
    uint64_t val;
  };
  bool operator<(const Invariant& inv) const;
  bool operator==(const Invariant& inv) const;
  Invariant father(char p,char i) const;
};

ostream& operator<<(ostream& os,const Invariant& inv);

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
  static void Dynnikov_action(char i,Int* a,Int* b);
  static void positive_Dynnikov_action(Int& x1,Int& y1,Int& x2,Int& y2);
  static void negative_Dynnikov_action(Int& x1,Int& y1,Int& x2,Int& y2);
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
  Invariant invariant();
  static void disp_letter(int v);
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
    tab[i]=(v<0)?-STRANDS-v:STRANDS-v;
  }
}

inline bool
Braid::operator<(const Braid& b) const{
  return cmp(b)==-1;
}

inline bool
Invariant::operator<(const Invariant& inv) const{
  return val<inv.val;
}

inline bool
Invariant::operator==(const Invariant& inv) const{
  return val==inv.val;
}

inline ostream&
operator<<(ostream& os,const Invariant& inv){
  return os<<'['<<(int)inv.e13<<','<<(int)inv.e24<<','<<(int)inv.e14<<']';
}

inline Int pos(Int a){
  return (a<0)?0:a;
}

inline Int neg(Int a){
  return (a>0)?0:a;
}

inline void
Braid::Dynnikov_action(char i,Int* a,Int* b){
  if(i>0) positive_Dynnikov_action(a[i-1],b[i-1],a[i],b[i]);
  else negative_Dynnikov_action(a[-i-1],b[-i-1],a[-i],b[-i]);
}

#endif

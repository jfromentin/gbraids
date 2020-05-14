#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <set>
#include "permutation.hpp"

using namespace std;

class Signature{
private:
  char l;
  char p;
  char e12;
  char e23;
  char e34;
protected:
  string display(char sep) const;
public:
  Signature();
  Signature(char l,char p,char e12,char e23,char e34);
  Signature(string str);
  int get_l() const;
  int get_p() const;
  int get_e12() const;
  int get_e23() const;
  int get_e34() const;
  bool operator<(const Signature& s) const;
  bool operator==(const Signature& s) const;
  string csv() const;
  string filename() const;
  Signature son(char i) const;
  Signature comparison()const;
  Signature father(char i) const;
  bool is_negative() const;
  Signature negate() const;
  bool is_phi_reducible() const;
  Signature phi() const;
  int get_rank() const;
  friend ostream& operator<<(ostream& os,const Signature& bs);
};

void load(int l,set<Signature>&);
void next_signatures(const set<Signature>& src,set<Signature>& dst);
size_t number(const Signature& s);

inline
Signature::Signature(){
}

inline
Signature::Signature(char _l,char _p,char _e12,char _e23,char _e34):l(_l),p(_p),e12(_e12),e23(_e23),e34(_e34){
}

inline int
Signature::get_l() const{
  return l;
}

inline int
Signature::get_p() const{
  return p;
}

inline int
Signature::get_e12() const{
  return e12;
}

inline int
Signature::get_e23() const{
  return e23;
}

inline int
Signature::get_e34() const{
  return e34;
}
				 
inline bool
Signature::operator==(const Signature& s) const{
  return (l==s.l) and (p==s.p) and (e12==s.e12) and (e23==s.e23) and (e34==s.e34);
}

inline string
Signature::csv() const{
  return display(',');
}

inline string
Signature::filename() const{
  return display('_');
}

inline Signature
Signature::comparison() const{
  Signature s=*this;
  s.l=l-2;
  return s;
}

inline bool
Signature::is_negative() const{
  if(e12!=0) return e12<0;
  if(e23!=0) return e23<0;
  return e34<0;
}

inline Signature
Signature::negate() const{
  return Signature(l,p,-e12,-e23,-e34);
}

inline bool
Signature::is_phi_reducible() const{
  return phi_image[p]<p;
}

inline Signature
Signature::phi() const{
  return Signature(l,phi_image[p],e34,e23,e12);
}

inline int
Signature::get_rank() const{
  int r=(phi_image[p]==p)?1:2;
  if(e12==0 and e23==0 and e34==0) return r;
  return r*2;
}

inline ostream&
operator<<(ostream& os,const Signature& s){
  return os<<'['<<s.display(',')<<']';
}
#endif


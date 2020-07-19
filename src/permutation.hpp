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

#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include <iostream>

using namespace std;

//*********************
//* Class Permutation *
//*********************

//! A class for permutation of S4
//! - tab[i] is the image of i by the permutation.
//! - data contains the whole array tab
//! By convention tab[0] is 0.

class Permutation{
private:
  union{
    struct{
      char tab[5];
    };
    size_t data;
  };
public:
  //! Create identity permutation
  Permutation();
  
  //! Create a permutation from a char
  //! \param p a char containing tab[1]*1000+tab[2]*100+tab[3]*10+tab[4]
  Permutation(int p);
  
  //! Create a permutation from char
  //! \param p1 is for tab[1]
  //! \param p2 is for tab[2]
  //! \param p3 is for tab[3]
  //! \param p4 is for tab[4]
  Permutation(char p1,char p2,char p3,char p4);
  
  //! Multiply the current permutation on the right by s_i=(i i+1)
  //! \param i a char in {1,2,3}
  Permutation operator*(char i) const;

  //! Multiply the current permutation on the right by the permutation of ith dual generator
  //! \param i a char in {1,2,3,4,5,6}
  Permutation dual_prod(char i) const;

  Permutation inverse() const;
  
  //! The less operator
  //! \param p a permutation to compare with
  bool operator<(const Permutation& p) const;
  
  //! Not equal operator
  //! \param p a permutation to compare with
  bool operator!=(const Permutation& p) const;
  
  //! Evaluation operator
  //! \param i a char in {1,2,3}
  //! Return permutation(i)
  char operator()(char i) const;
  
  //! Return the image of permutation under the action of phi,
  //! which transform s_{i} in s_{n-i}
  Permutation phi() const;

  //! Return the image of permutation under the action of phi dual,
  //! which transform a_{i,j} in a_{i+1,j+1}
  Permutation phi_dual() const;
  
  //! Return a string of the window view of the permutation
  string to_string() const;
};

//********************
//* Inline functions *
//********************

inline
Permutation::Permutation(){
  data=0;
  for(size_t i=0;i<=4;++i) tab[i]=i;
}

inline
Permutation::Permutation(char a,char b,char c,char d){
  data=0;
  tab[0]=0;
  tab[1]=a;
  tab[2]=b;
  tab[3]=c;
  tab[4]=d;
}

inline
Permutation::Permutation(int p){
  data=0;
  tab[0]=0;
  tab[4]=p%10;
  p=p/10;
  tab[3]=p%10;
  p=p/10;
  tab[2]=p%10;
  p=p/10;
  tab[1]=p%10;
}

inline Permutation
Permutation::inverse() const{
  Permutation res;
  res.tab[0]=0;
  res.tab[tab[1]]=1;
  res.tab[tab[2]]=2;
  res.tab[tab[3]]=3;
  res.tab[tab[4]]=4;
  return res;
}

inline Permutation
Permutation::operator*(char i) const{
  Permutation res;
  res.data=data;
  swap(res.tab[i],res.tab[i+1]);
  return res;
}

inline bool
Permutation::operator<(const Permutation& p) const{
  return data<p.data;
}

inline bool
Permutation::operator!=(const Permutation& p) const{
  return data!=p.data;
}

inline char
Permutation::operator()(char i) const{
  return tab[i];
}

inline Permutation
Permutation::dual_prod(char i) const{
  Permutation res;
  res.data=data;
  switch(i){
  case 1:
    swap(res.tab[1],res.tab[2]);
    break;
  case 2:
    swap(res.tab[2],res.tab[3]);
    break;
  case 3:
    swap(res.tab[1],res.tab[3]);
    break;
  case 4:
    swap(res.tab[3],res.tab[4]);
    break;
  case 5:
    swap(res.tab[2],res.tab[4]);
    break;
  case 6:
    swap(res.tab[1],res.tab[4]);
    break;
  default:
    break;
  };
  return res;
}

inline Permutation
Permutation::phi() const{
  Permutation res;
  res.tab[0]=0;
#if STRANDS==3
  res.tab[1]=4-tab[3];
  res.tab[2]=4-tab[2];
  res.tab[3]=4-tab[1];
  res.tab[4]=tab[4];
#elif STRANDS==4
  res.tab[1]=5-tab[4];
  res.tab[2]=5-tab[3];
  res.tab[3]=5-tab[2];
  res.tab[4]=5-tab[1];
#else
#error "Bad value of STRANDS"
#endif
  return res;
}

inline Permutation
Permutation::phi_dual() const{
  Permutation res;
  res.tab[0]=0;
#if STRANDS==3
  char c=tab[3];
  res.tab[1]=(c==3)?1:c+1;
  c=tab[1];
  res.tab[2]=(c==3)?1:c+1;
  c=tab[2];
  res.tab[3]=(c==3)?1:c+1;
  res.tab[4]=tab[4];
#elif STRANDS==4
  char c=tab[4];
  res.tab[1]=(c==4)?1:c+1;
  c=tab[1];
  res.tab[2]=(c==4)?1:c+1;
  c=tab[2];
  res.tab[3]=(c==4)?1:c+1;
  c=tab[3];
  res.tab[4]=(c==4)?1:c+1;
#else
  #error "Bad value of STRANDS"
#endif
  return res;
}


inline string
Permutation::to_string() const{
  string str;
  str+=char('0'+tab[1]);
  str+=char('0'+tab[2]);
  str+=char('0'+tab[3]);
  str+=char('0'+tab[4]);
  return str;
}

#endif

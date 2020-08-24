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

#ifndef DYNNIKOV_HPP
#define DYNNIKOV_HPP
//#include <boost/multiprecision/cpp_int.hpp>
#include <cstddef>
#include <cstdint>


//**********
//* Macros *
//**********

using Int = __int128;//int128_t;
//using UInt = uint128_t;

//*********************
//* Class declaration *
//*********************

//---------------------
// DynnikovCoordinates
//---------------------

//! Class DynnikovCoordinates.
//! This class is used to represent Dynnikov's corrdinates of a braid
class DynnikovCoordinates{
private:
  //!Dynnikov's coordinates of a braid on 4 strands
  union{
    struct{
     Int a[4],b[4];
    };
    struct{
     Int c[8];
    };
  };
  
  //! Return max(0,a)
  static Int pos(Int a);

  //! Return min(0,a)
  static Int neg(Int a);

public:
  //! Empty constructor
  DynnikovCoordinates();
  
  //! Perform Dynnikov's action of g-th Artin's letter or its inverse
  void Artin_action(char g);
  
  //! Positive Artin's generator action
  static void positive_Artin_action(Int& x1,Int& y1,Int& x2,Int& y2);

  //! Negative Artin's generator action
  static void negative_Artin_action(Int& x1,Int& y1,Int& x2,Int& y2);

  //! Egality operator
  bool operator==(const DynnikovCoordinates& d) const;

  //! Comparison operator
  bool operator<(const DynnikovCoordinates& d) const;

  //! Hash function
  size_t hash() const;  
};

//---------------------
// DynnikovCoordinates 
//---------------------

inline
DynnikovCoordinates::DynnikovCoordinates(){
  a[0]=a[1]=a[2]=a[3]=0;
  b[0]=b[1]=b[2]=b[3]=1;
}

inline void
DynnikovCoordinates::Artin_action(char i){
  if(i>0) positive_Artin_action(a[i-1],b[i-1],a[i],b[i]);
  else negative_Artin_action(a[-i-1],b[-i-1],a[-i],b[-i]);
}

inline bool
DynnikovCoordinates::operator<(const DynnikovCoordinates& d) const{
  for(size_t k=0;k<8;++k){
    if(c[k]!=d.c[k]) return c[k]<d.c[k];
  }
  return false;
}

inline size_t
DynnikovCoordinates::hash() const{
  size_t res=0;
  for(size_t k=0;k<8;++k){
    size_t t=c[k];
    t=t%256;
    res=(res<<8)+t;
  }
  return res;
}

inline Int
DynnikovCoordinates::neg(Int a){
  return (a>0)?0:a;
}

inline bool
DynnikovCoordinates::operator==(const DynnikovCoordinates& d) const{
  for(size_t k=0;k<8;++k){
    if(c[k]!=d.c[k]) return false;
  }
  return true;
}

inline Int
DynnikovCoordinates::pos(Int a){
  return (a<0)?0:a;
}
#endif

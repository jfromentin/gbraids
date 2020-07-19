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
#include <cassert>
#include <iostream>
#include <fstream>
#include "config.hpp"
#include "dynnikov.hpp"
#include "permutation.hpp"
#include "signature.hpp"

using namespace std;

using uchar=unsigned char;

//***********
//* Classes *
//***********

//-----------
// BraidData 
//-----------

//! Class BraidData gathering common data and methods of Braid<Gen>.
//! BraidData is essentialy an array of char. The inverse of the g-th generator
//! is represented by -g. The max size of the braid is hardcoded to be 32.

class BraidData{
protected:
  union{
    struct{
      //! An array of char 
      char tab[32];
    };
    struct{
      //! The 32 length array of char can be sees an an 4 array of uint64
      uint64_t tab64[4];
    };
  };
  //! Length of the braid
  size_t len;
  
public:
  //! Empty constructor
  BraidData();
  
  //! Recopy constructor 
  BraidData(const BraidData&);

  //! Return he length of the braid
  size_t length() const;

  //! Assignement operator
  BraidData& operator=(const BraidData&);

  //! Multiply the braid inplace by a generator (or its inverse)
  //!  \param g index, or opposite index, of a generator 
  void operator*=(char i); 
};

template<Gen G> class Braid;

//--------------
// Braid<Artin> 
//--------------

//! Class Braid<Artin> representing Braid on Artin's generators
//! Artin's generator are indexed as follows : sig_i -> i
//! For the sequel a letter will be an integer {-3,-2,-1,1,2,3}
template<> class Braid<Artin>:public BraidData{
public:
  //! Code a letter as an integer in [0,5]
  static uchar code(char c);
  
  //! Decode an integer in [0,5] as a letter
  static char decode(uchar c);

  //! Empty constructor
  Braid();

  //! Construct a braid from an array of char; in compressed format
  //! \param buffer buffer of char
  //! \param l size of the buffer
  Braid(char* buffer,size_t l);

  //! Recopy constructor
  Braid(const Braid&);

  //! Apply action
  void apply(typename Signature<Artin>::Action& action);
  
  //! Return compressed size of a braid of length l
  static size_t compressed_size(size_t l);

  //! Return Dynnikov's coordinates of the braid
  DynnikovCoordinates coordinates() const;
  
  //! Negate the current braid, sending i to -i. Warning, the braid so obtained is not the inverse
  //! of the original one
  void negate();
  
  //! Affectation constructor
  Braid& operator=(const Braid&);
  
  //! Equality operator; use Dynnikov coordinates
  bool operator==(const Braid& b) const;
  
  //! Apply phi (Garside's automorphism) to the current braid 
  void phi();
  
  //! Write the current braid in a file using compressed representation
  //! \param file a file in which write the braid
  void write(fstream& file) const;

  //! Display operator
  friend ostream& operator<<(ostream&,const Braid&);
};

//-------------
// Braid<Dual> 
//-------------

//! Class Braid<Dual> representing Braid on dual generators
//! Dual generator are enumerate as follow : a12, a23, a13, a34, a24, a14
//! For the sequel a letter will be an integer {-6,-5,-4,-3,-2,-1,1,2,3,4,5,6}
template<> class Braid<Dual>:public BraidData{
private:
  static char phi(char g,int d);
public:
  //! Code a letter as an integer in [0,5]
  static uchar code(char c);
  
  //! Decode an integer in [0,5] as a letter
  static char decode(uchar c);

  //! Empty constructor
  Braid();

  //! Construct a braid from an array of char; in compressed format
  //! \param buffer buffer of char
  //! \param l size of the buffer
  Braid(char* buffer,size_t l);

  //! Recopy constructor
  Braid(const Braid&);

  //! Apply action
  void apply(const typename Signature<Dual>::Action& action);

  //! Return compressed size of a braid of length l
  static size_t compressed_size(size_t l);

  //! Return Dynnikov's coordinates of the braid
  DynnikovCoordinates coordinates() const;
  
  //! Affectation constructor
  Braid& operator=(const Braid&);
  
  //! Equality operator; use Dynnikov coordinates
  bool operator==(const Braid& b) const;
  
  //! Write the current braid in a file using compressed representation
  //! \param file a file in which write the braid
  void write(fstream& file) const;

  //! Display operator
  friend ostream& operator<<(ostream&,const Braid&);
};

//******************
//* Hash functions *
//******************

template<> struct std::hash<Braid<Artin>>{
  size_t operator()(const Braid<Artin>& b) const{
    return b.coordinates().hash();
  }
};

template<> struct std::hash<Braid<Dual>>{
  size_t operator()(const Braid<Dual>& b) const{
    return b.coordinates().hash();
  }
};

//********************
//* Inline functions * 
//********************

//-----------
// BraidData
//-----------

inline
BraidData::BraidData(){
  tab64[0]=0;
  tab64[1]=0;
  tab64[2]=0;
  tab64[3]=0;
  len=0;
}

inline
BraidData::BraidData(const BraidData& b){
  tab64[0]=b.tab64[0];
  tab64[1]=b.tab64[1];
  tab64[2]=b.tab64[2];
  tab64[3]=b.tab64[3];
  len=b.len;
}

inline size_t
BraidData::length() const{
  return len;
}

inline BraidData&
BraidData::operator=(const BraidData& b){
  tab64[0]=b.tab64[0];
  tab64[1]=b.tab64[1];
  tab64[2]=b.tab64[2];
  tab64[3]=b.tab64[3];
  len=b.len;
  return *this;
}

inline void
BraidData::operator*=(char i){
  tab[len++]=i;
}

//--------------
// Braid<Artin>
//--------------

inline
Braid<Artin>::Braid():BraidData(){
}

inline
Braid<Artin>::Braid(const Braid<Artin>& b):BraidData(b){
}

inline void
Braid<Artin>::apply(typename Signature<Artin>::Action& action){
  if(action.apply_phi) phi();
  if(action.apply_negation) negate();
}

inline uchar
Braid<Artin>::code(char c){
  return (c<0)?6+c:c-1;
}

inline size_t
Braid<Artin>::compressed_size(size_t l){
  return (l-1)/3+1;
}

inline DynnikovCoordinates
Braid<Artin>::coordinates() const{
  DynnikovCoordinates d;
  for(size_t i=0;i<len;++i){
    d.Artin_action(tab[i]);
  }
  return d;
}

inline char
Braid<Artin>::decode(uchar c){
  return (c<3)?c+1:(char)c-6;
}

inline void
Braid<Artin>::negate(){
  for(size_t i=0;i<len;++i) tab[i]*=-1;
}

inline void
Braid<Artin>::phi(){
  for(size_t i=0;i<len;++i){
    char v=tab[i];
    tab[i]=(v>0)?STRANDS-v:-STRANDS-v;
  }
}

inline bool
Braid<Artin>::operator==(const Braid<Artin>& b) const{
  return coordinates()==b.coordinates();
}

//-------------
// Braid<Dual>
//-------------

inline
Braid<Dual>::Braid():BraidData(){
}

inline
Braid<Dual>::Braid(const Braid<Dual>& b):BraidData(b){
}

inline uchar
Braid<Dual>::code(char c){
  return (c<0)?12+c:c-1;
}

inline size_t
Braid<Dual>::compressed_size(size_t l){
  return (l-1)/2+1;
}

inline char
Braid<Dual>::decode(uchar c){
  return (c<6)?c+1:(char)c-12;
}

inline bool
Braid<Dual>::operator==(const Braid<Dual>& b) const{
  return coordinates()==b.coordinates();
}
#endif

/*This file is part of Gbraids (https://github.com/jfromentin/gbraids).
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

#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP
#include <cassert>
#include <fstream>
#include <iostream>
#include <set>
#include <sys/stat.h> 
#include "config.hpp"
#include "permutation.hpp"
#include "stl.hpp"

using namespace std;

using Generator=char;


//*********************
//* Class declaration *
//*********************

//---------------
// SignatureData 
//---------------

//! Class SignatureData gathering datas and methods of Signature<Gen>
//! It is composed of :
//!  - interlacing numbers
//!  - the geodesic length of the braid
//!  - the permutation associated to the braid

class SignatureData{
protected:
  //! Interlacing numbers
  union{
    struct{
      char e12,e23,e34,e14,e13,e24;
    };
    struct{
      char e[6];
    };
    int64_t full_e;
  };
  
  //! Geodesic length ot the braid
  char length;
  
  //! Permutation associated to the braid
  Permutation permutation;

  static int dual_interlacing_number(char ag,char sg,char i,char j);
    
  //! Base function to obtain a Signature from a CSV entry (using comma)
  //! \param str CSV entry
  //! \param pos current position of the read cursor
  static int get_value(string str,size_t& pos);

  //! Update interlacing numbers of a signature obtain from ther right product of a signature
  //! by an Artin's generator i
  //! \param e interlacing numbers of the original Signature
  //! \param p permutation of the original Signature
  //! \param i Artin generator that multiply the original Signature on the right
  static void update_interlacing_Artin(char* e,Permutation p,Generator i);

  //! Update interlacing numbers of a signature obtain from ther right product of a signature
  //! by an Dual's generator i
  //! \param e interlacing numbers of the original Signature
  //! \param p permutation of the original Signature
  //! \param i Dual generator that multiply the original Signature on the right
  static void update_interlacing_Dual(char* e,Permutation p,Generator i);
  
protected:
  //! Display the Signature
  string display() const;
  
public:	
  //! Empty construcor 
  SignatureData();
  
  //! A constructor 
  SignatureData(char l,Permutation p,char e12,char e23,char e34,char e14,char e13,char e24);
  
  //! Construct a Signature form a string (obtain from a CSV file)
  //! \param str string source
  //! \param d degree of the Signature
  SignatureData(string str);

  //! Return braid length of the Signature
  size_t braid_length() const;

  //! Export the Signature to a CSV entry
  string csv() const;

  //! Obtain the dir associated to the Signature
  void makedir() const;
  
  //! Obtain a filename from the Signature
  string filename() const;

  //! Test if the Signature has length zero
  bool has_length_zero() const;
  
  //! Comparison operator
  //! \param s a Signature to compare with
  bool operator<(const SignatureData& s) const;
  
  //! Equality operator
  //! \param s a Signature to compare with
  bool operator==(const SignatureData& s) const;

  //! Equality operator
  //! \param s a Signature to compare with
  bool operator!=(const SignatureData& s) const;
};

//--------------
// Signature<G>
//--------------

//! Class Signature for braid's signature

template<Gen G> class Signature;

//------------------
// Signature<Artin> 
//------------------

//! Class Signature for Artin-braid's signature
template<> class Signature<Artin>:public SignatureData{
public:
  //! Information on how obtain the mimal signature from a current one
  struct Action{
    bool apply_phi;
    bool apply_negation;
  };
  static const char nbgen=3;
  
  //! Empty constructor
  Signature();
  
  //! Construct a Signature form a string (obtain from a CSV file)
  //! \param str string source
  //! \param d degree of the Signature
  Signature(string str);
  
  //! A constructor 
  Signature(char l,Permutation p,char e12,char e23,char e34,char e14,char e13,char e24);

  //! Return a Signature with same data except length which is length-2
  Signature comparison() const;
  
  //! Return the i-father of the Signature
  //! \param i generator to apply
  //! If a braid b has Signature S then it can be decomposed as c*i where c has Signature S.father(i).
  Signature father(Generator i) const;
  
  //! Test if the SignatureData is minimal (in its orbit)
  bool is_minimal() const;
  
  //! Return tne minimal Signature in the orbit of the current one plus information and how obtain it
  pair<Signature,Action> minimize() const;

  //! Return a negated version of the Signature
  Signature negate() const;
  
  //! Return the orbit of the current signature
  set<Signature> orbit() const;
  
  //! Apply phi to the Signature
  //! If b has signature S the phi(b) has signature S.phi()
  Signature phi() const;

  //! Return the rank of the Signature, namely number of Signatures associated to this one under
  //! the action of phi and negation.
  size_t rank() const;
  
  //! Return the i-son of the Signature
  //! \param i generator to apply
  //! If a braid b has Signature S then braid b*i has Signature S.son(i).
  Signature son(Generator i) const;

  //! Operator << for Signature
  template<Gen H> friend ostream& operator<<(ostream& os,const Signature<H>& bs);
};

//-----------------
// Signature<Dual> 
//-----------------

//! Class Signature for Dual-braid's signature
template<> class Signature<Dual>:public SignatureData{
public:
  //! Information on how obtain the mimal signature from a current one
  struct Action{
    int phi_degree;
  };
  static const char nbgen=6;
  //! Empty constructor
  Signature();
  
  //! Construct a Signature form a string (obtain from a CSV file)
  //! \param str string source
  //! \param d degree of the Signature
  Signature(string str);
  
  //! A constructor 
  Signature(char l,Permutation p,char e12,char e23,char e34,char e14,char e13,char e24);

  //! Return a Signature with same data except length which is length-2
  Signature comparison() const;
  
  //! Return the i-father of the Signature
  //! \param i generator to apply
  //! If a braid b has Signature S then it can be decomposed as c*i where c has Signature S.father(i).
  Signature father(Generator i) const;
  
  //! Test if the SignatureData is minimal (in its orbit)
  bool is_minimal() const;
  
  //! Return tne minimal Signature in the orbit of the current one plus information and how obtain it
  pair<Signature,Action> minimize() const;
 
  //! Return the orbit of the current signature
  set<Signature> orbit() const;
  
  //! Apply phi to the Signature
  //! If b has signature S the phi(b) has signature S.phi()
  Signature phi() const;

  //! Return the rank of the Signature, namely number of Signatures associated to this one under
  //! the action of phi and negation.
  size_t rank() const;
  
  //! Return the i-son of the Signature
  //! \param i generator to apply
  //! If a braid b has Signature S then braid b*i has Signature S.son(i).
  Signature son(Generator i) const;

  //! Operator << for Signature
  template<Gen H> friend ostream& operator<<(ostream& os,const Signature<H>& bs);
};

//*******************
//* Other functions *
//*******************

//! Load signature of length l from a CSV file
//! \param l length of Signature to load
//! \param signatures a set to strore loaded Signatures
//! Signatures is not cleared during the call of this function.
template<Gen G> void load(int l,set<Signature<G>>& signatures);

//! Determine which Signatures must be considered during the exploration of braids of length l+1
//! \param src the input set of all signatures of current length l
//! \param dst the output set, that will eventually contain all signatures of length l+1
void next_signatures(const set<Signature<Artin>>& src,set<Signature<Artin>>& dst);
void next_signatures(const set<Signature<Dual>>& src,set<Signature<Dual>>& dst);
//********************
//* Inline functions *
//********************

//---------------
// SignatureData
//---------------

inline
SignatureData::SignatureData(){
}
  
inline size_t
SignatureData::braid_length() const{
  return length;
}
inline string
SignatureData::csv() const{
  return display();
}

inline bool
SignatureData::has_length_zero() const{
  return length==0;
}

inline bool
SignatureData::operator!=(const SignatureData& s) const{
  if(length!=s.length) return true;
  if(permutation!=s.permutation) return true;
  if(full_e!=s.full_e) return true;
  return false;
}

//------------------
// Signature<Artin> 
//------------------

inline
Signature<Artin>::Signature():SignatureData(){
}

inline
Signature<Artin>::Signature(string str):SignatureData(str){
}

inline
Signature<Artin>::Signature(char l,Permutation p,char e1,char e2,char e3,char e4,char e5,char e6):
  SignatureData(l,p,e1,e2,e3,e4,e5,e6){
}

// Assume u is a geodesic word and v=u*i is not geodesic then the geodesic length of the
// braid represented by u is |v|-2. Hence to decide is a word is geodesic we have to compare
// it with reprensentative of braids with same signature plus "comparison signature", namely
// same signature expcept the length is decreased by 2.
inline Signature<Artin>
Signature<Artin>::comparison() const{
  Signature<Artin> s=*this;
  s.length=length-2;
  return s;
}

inline bool
Signature<Artin>::is_minimal() const{
  typename set<Signature<Artin>>::iterator it=orbit().begin();
  return *this==*it;
}

inline size_t
Signature<Artin>::rank() const{
  return orbit().size();
}

//-----------------
// Signature<Dual> 
//-----------------

inline 
Signature<Dual>::Signature():SignatureData(){
}

inline
Signature<Dual>::Signature(string str):SignatureData(str){
}

inline
Signature<Dual>::Signature(char l,Permutation p,char e1,char e2,char e3,char e4,char e5,char e6):
  SignatureData(l,p,e1,e2,e3,e4,e5,e6){
}

// Assume u is a geodesic word and v=u*i is not geodesic then the geodesic length of the
// braid represented by u is |v|-2. Hence to decide is a word is geodesic we have to compare
// it with reprensentative of braids with same signature plus "comparison signature", namely
// same signature expcept the length is decreased by 2.
inline Signature<Dual>
Signature<Dual>::comparison() const{
  Signature<Dual> s=*this;
  s.length=length-2;
  return s;
}

inline bool
Signature<Dual>::is_minimal() const{
  typename set<Signature<Dual>>::iterator it=orbit().begin();
  return *this==*it;
}

inline size_t
Signature<Dual>::rank() const{
  return orbit().size();
}

//-----------------
// Other functions
//-----------------

template<Gen G> inline ostream&
operator<<(ostream& os,const Signature<G>& s){
  return os<<'['<<s.display()<<']';
}

template<Gen G> void
load(int l,set<Signature<G>>& signatures){
  fstream file;
  file.open(DATA_DIR+to_string(l)+".csv",ios::in);
  string line;
  while(getline(file,line)){
    Signature<G> s(line);
    signatures.emplace(s);
  }
}
#endif


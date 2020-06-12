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

#ifndef STL_HPP
#define STL_HPP

#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

//! Insert an element of type in a set of type T
//! \param s set of type T
//! \param b element to insert in the set s
template<class T> void insert(set<T>& s,const T& b);

//! Insert an element of type in a vector of type T
//! \param s set of type T
//! \param b element to insert in the set s
template<class T> void insert(vector<T>& s,const T& b);

//! Overload of << operator
template<class T> ostream& operator<<(ostream& os,const set<T>& s);

//! Overload of << operator
template<class T> ostream& operator<<(ostream& os,const vector<T>& s);
//-----------------------
// Hash for Braid<Artin>
//-----------------------


//********************
//* Inline functions *
//********************

template<class T> inline void insert(set<T>& s,const T& b){
  s.insert(b);
}
template<class T> inline void insert(unordered_set<T>& s,const T& b){
  s.insert(b);
}
template<class T> inline void insert(vector<T>& v,const T& b){
  v.push_back(b);
}

template<class T> ostream&
operator<<(ostream& os,const set<T>& s){
  if(s.empty()) return os<<"{}";
  auto it=s.begin();
  os<<'{'<<*it;
  for(++it;it!=s.end();++it){
    os<<','<<*it;
  }
  return os<<'}';
}

template<class T> ostream&
operator<<(ostream& os,const vector<T>& s){
  if(s.empty()) return os<<"[]";
  auto it=s.begin();
  os<<'['<<*it;
  for(++it;it!=s.end();++it){
    os<<','<<*it;
  }
  return os<<']';
}
#endif

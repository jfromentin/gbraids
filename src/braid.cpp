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

#include "braid.hpp"
#include <cstring>
//****************
//* Braid<Artin> *
//****************

//---------------------
// Braid<Artin>::Braid 
//---------------------

Braid<Artin>::Braid(char* buffer,size_t l){
  memcpy(&geo,buffer,sizeof(size_t));
  size_t i=0;
  size_t j=sizeof(size_t);
  while(i<l){
    uchar c=buffer[j++];
    tab[i++]=decode(c%6);
    tab[i++]=decode((c%36)/6);
    tab[i++]=decode(c/36); 
  }
  len=l;
}

//---------------------
// Braid<Artin>::write
//---------------------

void
Braid<Artin>::write(fstream& file) const{
  file.write((const char*)&geo,sizeof(size_t));
  size_t size=(len-1)/3+1;
  char buffer[size];
  size_t i=0;
  size_t k=0;
  while(i<len){
    uchar c=code(tab[i++]);
    if(i<len) c+=(code(tab[i++])*6);
    if(i<len) c+=(code(tab[i++])*36);
    buffer[k++]=c;
  }
  file.write(buffer,size);
}

//***************
//* Braid<Dual> *
//***************

//---------------------
// Braid<Dual>::Braid 
//---------------------

Braid<Dual>::Braid(char* buffer,size_t l){
  memcpy(&geo,buffer,sizeof(size_t));
  size_t i=0;
  size_t j=sizeof(size_t);
  while(i<l){
    uchar c=buffer[j++];
    tab[i++]=decode(c%12);
    tab[i++]=decode(c/12); 
  }
  len=l;
}

//--------------------
// Braid<Dual>::apply
//--------------------

void
Braid<Dual>::apply(const typename Signature<Dual>::Action& action){
  for(size_t i=0;i<len;++i){
    char v=tab[i];
    if(v>0) tab[i]=phi(v,STRANDS-action.phi_degree);
    else tab[i]=-phi(-v,STRANDS-action.phi_degree);
  }
}

//--------------------------
// Braid<Dual>::coordinates 
//--------------------------

DynnikovCoordinates
Braid<Dual>::coordinates() const{
  DynnikovCoordinates d;
  for(size_t i=0;i<len;++i){
    char g=tab[i];
    char ag,sg;
    if(g<0){
      ag=-g;sg=-1;
    }
    else{
      ag=g;sg=1;
    }
    switch(ag){
    case 1: //a12 or A12
      d.Artin_action(sg);
      break;
    case 2: //a23 or A23
      d.Artin_action(sg*2);
      break;
    case 3: //a13 or A13
      d.Artin_action(1);
      d.Artin_action(sg*2);
      d.Artin_action(-1);
      break;
    case 4: //a34 or A34
      d.Artin_action(sg*3);
      break;
    case 5://a24 or A24
      d.Artin_action(2);
      d.Artin_action(sg*3);
      d.Artin_action(-2);
      break;
    case 6://a14 or A14
      d.Artin_action(1);
      d.Artin_action(2);
      d.Artin_action(sg*3);
      d.Artin_action(-2);
      d.Artin_action(-1);
      break;
    default:
      assert(false);
      break; 
    };
  }
  return d;
}

//------------------
// Braid<Dual>::phi
//------------------

char
Braid<Dual>::phi(char g,int d){
  switch(d){
  case 0:
    return g;
    break;
#if STRANDS == 3
  case 1:
    {
      char data[3]={2,3,1};
      return data[g-1];
    }
    break;
  case 2:
    {
      char data[3]={3,1,2};
      return data[g-1];
    }
    break;
#elif STRANDS ==4 
  case 1:
    {
      char data[6]={2,4,5,6,3,1};
      return data[g-1];
    }
    break;
  case 2:
    {
      char data[6]={4,6,3,1,5,2};
      return data[g-1];
    }
    break;
  case 3:
    {
      char data[6]={6,1,5,2,3,4};
      return data[g-1];
    }
    break;
#else
#error "Bad value of STRANDS"
#endif
  default:
    assert(false);
    break;
  };
  return g;
}

//--------------------
// Braid<Dual>::write
//--------------------

void
Braid<Dual>::write(fstream& file) const{
  file.write((const char*)&geo,sizeof(size_t));
  size_t size=(len-1)/2+1;
  char buffer[size];
  size_t i=0;
  size_t k=0;
  while(i<len){
    uchar c=code(tab[i++]);
    if(i<len) c+=(code(tab[i++])*12);
    buffer[k++]=c;
  }
  file.write(buffer,size);
}

//*******************
//* Other functions *
//*******************

ostream&
operator<<(ostream& os,const Braid<Artin>& b){
  if(b.len==0) return os<<'1';
  for(size_t i=0;i<b.len;++i){
    char c=b.tab[i];
    if(c>0) os<<char(c-1+'a');
    else os<<char(-c-1+'A');
  }
  return os;
}

ostream&
operator<<(ostream& os,const Braid<Dual>& b){
  if(b.len==0) return os<<'1';
  for(size_t i=0;i<b.len;++i){
    char c=b.tab[i];
    os<<(c<0?'A':'a');
    switch(abs(c)){
    case 1:
      os<<"12";
      break;
    case 2:
      os<<"23";
      break;
    case 3:
      os<<"13";
      break;
    case 4:
      os<<"34";
      break;
    case 5:
      os<<"24";
      break;
    case 6:
      os<<"14";
      break;
    default:
      break;
    };
  }
  return os;
}

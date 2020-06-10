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

Int amplitude=0;


void positive_Dynnikov_action(Int& x1,Int& y1,Int& x2,Int& y2){
  Int t=x1-neg(y1)-x2+pos(y2);
  Int r1=x1+pos(y1)+pos(pos(y2)-t);
  Int r2=y2-pos(t);
  Int r3=x2+neg(y2)+neg(neg(y1)+t);
  Int r4=y1+pos(t);
  x1=r1;
  y1=r2;
  x2=r3;
  y2=r4;
}

void negative_Dynnikov_action(Int& x1,Int& y1,Int& x2,Int& y2){
  Int t=x1+neg(y1)-x2-pos(y2);
  Int r1=x1-pos(y1)-pos(pos(y2)+t);
  Int r2=y2+neg(t);
  Int r3=x2-neg(y2)-neg(neg(y1)-t);
  Int r4=y1-neg(t);
  x1=r1;
  y1=r2;
  x2=r3;
  y2=r4;
}

Braid::Braid(char* buffer,size_t l){
  size_t i=0;
  size_t j=0;
  while(i<l){
    uchar c=buffer[j++];
    tab[i++]=decode(c%6);
    tab[i++]=decode((c%36)/6);
    tab[i++]=decode(c/36); 
  }
  len=l;
}

void
Braid::write(fstream& file) const{
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

int
Braid::cmp(const Braid& braid) const{
  Int a[4];
  Int b[4];
  a[0]=a[1]=a[2]=a[3]=0;
  b[0]=b[1]=b[2]=b[3]=1;
  for(size_t i=0;i<len;++i) Dynnikov_action(-tab[len-i-1],a,b);
  for(size_t i=0;i<braid.len;++i) Dynnikov_action(braid.tab[i],a,b);
  for(size_t i=0;i<4;++i){
    if(a[i]<0) return 1;
    if(a[i]>0) return -1;
  }
  return 0;
}

ostream&
operator<<(ostream& os,const Braid& b){
  if(b.len==0) return os<<'1';
  for(size_t i=0;i<b.len;++i){
    char c=b.tab[i];
    if(c>0) os<<char(c-1+'a');
    else os<<char(-c-1+'A');
  }
  return os;
}

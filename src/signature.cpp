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

#include "signature.hpp"

//*************************
//* Not inlined functions *
//*************************

//---------------
// SignatureData
//---------------

SignatureData::SignatureData(char l,Permutation p,char e1,char e2,char e3,char e4){
  length=l;
  permutation=p;
  e[0]=e1;
  e[1]=e2;
  e[2]=e3;
  e[3]=e4;
}

SignatureData::SignatureData(string line){
  size_t pos=0;
  length=get_value(line,pos);
  int p=get_value(line,pos);
  permutation=p;
  for(size_t k=0;k<4;++k){
    e[k]=get_value(line,pos);
  }
}

string
SignatureData::display(char sep) const{
  string res=to_string(length);
  res+=sep;
  res+=permutation.to_string();
  for(size_t k=0;k<4;++k){
    res+=sep;
    res+=to_string(e[k]);
  }
  return res;
}

int
SignatureData::get_value(string str,size_t& pos){
  string res="";
  while(pos!=str.size() and str[pos]!=','){
    res+=str[pos++];
  }
  ++pos;
  return stoi(res);
}

// Two Signatures are equal if all its values are
bool
SignatureData::operator==(const SignatureData& s) const{
  if(length!=s.length) return false;
  if(permutation!=s.permutation) return false;
  for(size_t k=0;k<4;++k){
    if(e[k]!=s.e[k]) return false;
  }
  return true;
}

// Signature order is a lexicographic order of signature entries
bool
SignatureData::operator<(const SignatureData& s) const{
  if(length!=s.length) return length<s.length;
  if(permutation!=s.permutation) return permutation<s.permutation;
  for(size_t k=0;k<4;++k){
    if(e[k]!=s.e[k]) return e[k]<s.e[k];
  }
  return false;
}

void
SignatureData::update_interlacing_Artin(char* e,Permutation p,Generator i){
  char ai,si;
  if(i<0){
    ai=-i;si=-1;
  }
  else{
    ai=i;si=1;
  }
  char r=p(ai);
  char s=p(ai+1);
  if(r>s) swap(r,s);
  switch(10*r+s){
  case 12:
    e[0]+=si;
    break;
  case 23:
    e[1]+=si;
    break;
  case 34:
    e[2]+=si;
    break;
  case 14:
    e[3]+=si;
    break;
  default:
    assert(false);
    break;
  }
}

//------------------
// Signature<Artin>
//------------------

// Assume a geodesic word w1 is expressed w2*i where w2 is geoseic then
// len(w1)=len(w2)+1, hence len(w2)=len(w1)-1
// perm(w1)=perm(w2)*perm(abs(i)), i.e. perm(w2)=perm(w1)*perm(abs(i)) since perms(wi) is a transposition
// values of interlacing numbers depends of perm(w2).
// The father signature is then the signature of w2.
Signature<Artin>
Signature<Artin>::father(Generator i) const{
  Signature res;
  res.length=length-1;
  res.permutation=permutation*abs(i);
  res.full_e=full_e;
  update_interlacing_Artin(res.e,res.permutation,-i);
  return res;
}

pair<Signature<Artin>,Signature<Artin>::Action>
Signature<Artin>::minimize() const{
  pair<Signature<Artin>,Signature<Artin>::Action> res;
  Signature<Artin> p=phi();
  Signature<Artin> n=negate();
  Signature<Artin> np=p.negate();
  res.first=*this;
  res.second.apply_phi=false;
  res.second.apply_negation=false;
  if(p<res.first){
    res.first=p;
    res.second.apply_phi=true;
    res.second.apply_negation=false;
  }
  if(n<res.first){
    res.first=n;
    res.second.apply_phi=false;
    res.second.apply_negation=true;
  }
  if(np<res.first){
    res.first=np;
    res.second.apply_phi=true;
    res.second.apply_negation=true;
  }
  return res;
}

Signature<Artin>
Signature<Artin>::negate() const{
  Signature<Artin> res;
  res.length=length;
  res.permutation=permutation;
  res.full_e=full_e;
  for(size_t k=0;k<4;++k){
    res.e[k]*=-1;
  }
  return res;
}

set<Signature<Artin>>
Signature<Artin>::orbit() const{
  set<Signature<Artin>> res;
  res.insert(*this);
  Signature<Artin> p=phi();
  res.insert(p);
  res.insert(negate());
  res.insert(p.negate());
  return res;
}

Signature<Artin>
Signature<Artin>::phi() const{
  Signature res;
  res.length=length;
  res.permutation=permutation.phi();
  res.e12=e34;
  res.e23=e23;
  res.e34=e12;
  res.e14=e14;
  return res;
}

// Assume a geodesic word w2 is expressed w1*i where w1 is geoseic then
// len(w2)=len(w1)+1
// perm(w2)=perm(w1)*perm(abs(i))
// values of interlacing numbers depends of perm(w1).
// The father signature is then the signature of w2
Signature<Artin>
Signature<Artin>::son(Generator i) const{
  Signature<Artin> res;
  res.length=length+1;
  res.permutation=permutation*abs(i);
  res.full_e=full_e;
  update_interlacing_Artin(res.e,permutation,i);
  return res;
}

//-----------------
// Other functions
//-----------------

void
next_signatures(const set<Signature<Artin>>& src,set<Signature<Artin>>& dst){
  for(auto it=src.begin();it!=src.end();++it){
    Signature<Artin> s=*it;
    Signature<Artin> s_phi=s.phi();
    Signature<Artin> s_neg=s.negate();
    Signature<Artin> s_phi_neg=s_phi.negate();
    for(Generator i=-3;i<=3;++i){
      if(i!=0){
	Signature<Artin> son=s.son(i);
	if(son.is_minimal()) dst.insert(son);
	son=s_phi.son(i);
	if(son.is_minimal()) dst.insert(son);
	son=s_neg.son(i);
	if(son.is_minimal()) dst.insert(son);
	son=s_phi_neg.son(i);
	if(son.is_minimal()) dst.insert(son);
      }
    }
  }
}

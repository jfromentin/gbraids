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

SignatureData::SignatureData(char l,Permutation p,char e1,char e2,char e3,char e4,char e5,char e6){
  length=l;
  permutation=p;
  e[0]=e1;
  e[1]=e2;
  e[2]=e3;
  e[3]=e4;
  e[4]=e5;
  e[5]=e6;
}

SignatureData::SignatureData(string line){
  size_t pos=0;
  length=get_value(line,pos);
  int p=get_value(line,pos);
  permutation=p;
  for(size_t k=0;k<6;++k){
    e[k]=get_value(line,pos);
  }
}

string
SignatureData::display() const{
  string res=to_string(length);
  res+=',';
  res+=permutation.to_string();
  for(size_t k=0;k<6;++k){
    res+=',';
    res+=to_string(e[k]);
  }
  return res;
}

int
SignatureData::dual_interlacing_number(char ag,char sg,char i,char j){
  if(i>j) swap(i,j);
  char r,s;
  switch(ag){
  case 1:
    r=1;s=2;
    break;
  case 2:
    r=2;s=3;
    break;
  case 3:
    r=1;s=3;
    break;
  case 4:
    r=3;s=4;
    break;
  case 5:
    r=2;s=4;
    break;
  case 6:
    r=1;s=4;
    break;
  default:
    break;
  };
  if(i==r and j<=s-1) return 1;
  if(i==r and j==s) return sg;
  if(r+1<=i and j==s) return -1;
  return 0;
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

string
SignatureData::filename() const{
  string res=to_string(length);
  res+='/';
  res+=permutation.to_string();
  res+='/';
  for(size_t k=0;k<6;++k){
    res+='_';
    res+=to_string(e[k]);
  }
  return res;
}

void
SignatureData::makedir() const{
  string res=DATA_DIR+to_string(length);
  mkdir(res.c_str(),0777);
  res+="/";
  res+=permutation.to_string();
  mkdir(res.c_str(),0777);
}

// Two Signatures are equal if all its values are
bool
SignatureData::operator==(const SignatureData& s) const{
  if(length!=s.length) return false;
  if(permutation!=s.permutation) return false;
  for(size_t k=0;k<6;++k){
    if(e[k]!=s.e[k]) return false;
  }
  return true;
}

// Signature order is a lexicographic order of signature entries
bool
SignatureData::operator<(const SignatureData& s) const{
  if(length!=s.length) return length<s.length;
  if(permutation!=s.permutation) return permutation<s.permutation;
  for(size_t k=0;k<6;++k){
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
  case 13:
    e[4]+=si;
    break;
  case 24:
    e[5]+=si;
    break;
  default:
    assert(false);
    break;
  }
}

void
SignatureData::update_interlacing_Dual(char* e,Permutation p,Generator g){
  char ag,sg;
  if(g<0){
    ag=-g;sg=-1;
  }
  else{
    ag=g;sg=1;
  }
  Permutation pi=p.inverse();
  e[0]+=dual_interlacing_number(ag,sg,pi(1),pi(2));
  e[1]+=dual_interlacing_number(ag,sg,pi(2),pi(3));
  e[2]+=dual_interlacing_number(ag,sg,pi(3),pi(4));
  e[3]+=dual_interlacing_number(ag,sg,pi(1),pi(4));
  e[4]+=dual_interlacing_number(ag,sg,pi(1),pi(3));
  e[5]+=dual_interlacing_number(ag,sg,pi(2),pi(4));
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
  for(size_t k=0;k<6;++k){
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
  res.e13=e24;
  res.e24=e13;
  //cout<<endl<<*this<<"->"<<res<<endl;
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
// Signature<Dual>
//-----------------

// Assume a geodesic word w1 is expressed w2*i where w2 is geoseic then
// len(w1)=len(w2)+1, hence len(w2)=len(w1)-1
// perm(w1)=perm(w2)*perm(abs(i)), i.e. perm(w2)=perm(w1)*perm(abs(i)) since perms(wi) is a transposition
// values of interlacing numbers depends of perm(w2).
// The father signature is then the signature of w2.
Signature<Dual>
Signature<Dual>::father(Generator i) const{
  Signature res=son(-i);
  res.length=length-1;
  return res;
}

pair<Signature<Dual>,Signature<Dual>::Action>
Signature<Dual>::minimize() const{
  pair<Signature<Dual>,Signature<Dual>::Action> res;
  Signature<Dual> s[4];
  s[0]=*this;
  s[1]=s[0].phi();
  s[2]=s[1].phi();
  s[3]=s[2].phi();
  Signature smin=s[0];
  int dmin=0;
  for(int d=1;d<4;++d){
    if(s[d]<smin){
      smin=s[d];
      dmin=d;
    }
  }
  res.first=smin;
  res.second.phi_degree=dmin;
  return res;      
}

set<Signature<Dual>>
Signature<Dual>::orbit() const{
  set<Signature<Dual>> res;
  res.insert(*this);
  Signature<Dual> p=phi();
  res.insert(p);
  p=p.phi();
  res.insert(p);
  p=p.phi();
  res.insert(p);
  return res;
}

Signature<Dual>
Signature<Dual>::phi() const{
  Signature res;
  res.length=length;
  res.permutation=permutation.phi_dual();
  res.e12=e14+1;
  res.e23=e12;
  res.e34=e23;
  res.e14=e34+1;
  res.e13=e24+1;
  res.e24=e13;
  char k=permutation(4);
  switch(k){
  case 1:
    res.e12-=1;
    res.e23-=1;
    res.e24-=1;
    break;
  case 2:
    res.e23-=1;
    res.e34-=1;
    res.e13-=1;
    break;
  case 3:
    res.e34-=1;
    res.e14-=1;
    res.e24-=1;
    break;
  case 4:
    res.e12-=1;
    res.e14-=1;
    res.e13-=1;
    break;
  default:
    break;
  }
  return res;
}

// Assume a geodesic word w2 is expressed w1*i where w1 is geoseic then
// len(w2)=len(w1)+1
// perm(w2)=perm(w1)*perm(abs(i))
// values of interlacing numbers depends of perm(w1).
// The father signature is then the signature of w2
Signature<Dual>
Signature<Dual>::son(Generator i) const{
  Signature<Dual> res;
  res.length=length+1;
  res.permutation=permutation.dual_prod(abs(i));
  res.full_e=full_e;
  update_interlacing_Dual(res.e,permutation,i);
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

void
next_signatures(const set<Signature<Dual>>& src,set<Signature<Dual>>& dst){
  for(auto it=src.begin();it!=src.end();++it){
    set<Signature<Dual>> orbit=it->orbit();
    for(auto it2=orbit.begin();it2!=orbit.end();++it2){
      for(Generator i=-6;i<=6;++i){
	if(i!=0){
	  Signature<Dual> son=it2->son(i);
	  if(son.is_minimal()) dst.insert(son);
	}
      }
    }
  }
}

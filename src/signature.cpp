#include "signature.hpp"

char get_value(string str,size_t& pos){
  string res="";
  while(pos!=str.size() and str[pos]!=','){
    res+=str[pos++];
  }
  ++pos;
  return stoi(res);
}

Signature::Signature(string line){
  size_t pos=0;
  l=get_value(line,pos);
  p=get_value(line,pos);
  e12=get_value(line,pos);
  e23=get_value(line,pos);
  e34=get_value(line,pos);
}

bool
Signature::operator<(const Signature& s) const{
  if(l!=s.l) return l<s.l;
  if(p!=s.p) return p<s.p;
  if(e12!=s.e12) return e12<s.e12;
  if(e23!=s.e23) return e23<s.e23;
  if(e34!=s.e34) return e34<s.e34;
  return false;
}

string
Signature::display(char sep) const{
  string res=to_string(get_l());
  res+=sep;
  res+=to_string(get_p());
  res+=sep;
  res+=to_string(get_e12());
  res+=sep;
  res+=to_string(get_e23());
  res+=sep;
  res+=to_string(get_e34());
  return res;
}

Signature
Signature::son(char i) const{
  Signature res;
  char ai,e;
  if(i<0){
    ai=-i;e=-1;
  }
  else{
    ai=i;e=1;
  }
  res.l=l+1;
  res.p=left_prod[ai][p];
  res.e12=e12;
  res.e23=e23;
  res.e34=e34;
  char r=eval_inv(p,ai);
  char s=eval_inv(p,ai+1);
  if(r>s) swap(r,s);
  if(r==1 and s==2) res.e12+=e;
  else if(r==2 and s==3) res.e23+=e;
  else if(r==3 and s==4) res.e34+=e;
  return res;
}

Signature
Signature::father(char i) const{
  Signature res;
  char ai,e;
  if(i<0){
    ai=-i;e=-1;
  }
  else{
    ai=i;e=1;
  }
  res.l=l-1;
  res.p=left_prod[ai][p];
  res.e12=e12;
  res.e23=e23;
  res.e34=e34;
  char r=eval_inv(res.p,ai);
  char s=eval_inv(res.p,ai+1);
  if(r>s) swap(r,s);
  if(r==1 and s==2) res.e12-=e;
  else if(r==2 and s==3) res.e23-=e;
  else if(r==3 and s==4) res.e34-=e;
  return res;
}

void
load(int l,set<Signature>& signature){
  fstream file;
  file.open(DATA_DIR+to_string(l)+".csv",ios::in);
  string line;
  while(getline(file,line)){
    signature.emplace(line);
  }
}

void
next_signatures(const set<Signature>& src,set<Signature>& dst){
  for(auto it=src.begin();it!=src.end();++it){
    Signature pos_s=*it;
    Signature phi_s=pos_s.phi();
    Signature neg_s=pos_s.negate();
    Signature neg_phi_s=phi_s.negate();
    for(char i=-NBGENS;i<=NBGENS;++i){
      if(i!=0){
        Signature son=pos_s.son(i);
        if(not son.is_negative() and not son.is_phi_reducible()) dst.insert(son);
        son=neg_s.son(i);
        if(not son.is_negative() and not son.is_phi_reducible()) dst.insert(son);
	son=phi_s.son(i);
        if(not son.is_negative() and not son.is_phi_reducible()) dst.insert(son);
	son=neg_phi_s.son(i);
        if(not son.is_negative() and not son.is_phi_reducible()) dst.insert(son);
      }
    }
  }
}

size_t
number(const Signature& s){
  if(s.get_l()==0) return 1;
  Signature ss=s;
  if(ss.is_phi_reducible()) ss=ss.phi();
  if(ss.is_negative()) ss=ss.negate();
  string filename=DATA_DIR+ss.filename();
  struct stat sb;
  if(stat(filename.c_str(),&sb)==0){
    size_t b_size=(ss.get_l()-1)/3+1;
    return sb.st_size/b_size;
  }
  return 0;
}

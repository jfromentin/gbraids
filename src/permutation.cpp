#include "permutation.hpp"

int Permutation::read_int(string s,size_t& offset){
  int v=0;
  while(offset<s.size()){
    char c=s[offset];
    if('0'<=c and c<='9'){
      v=v*10+(c-'0');
    }
    else if(c==',') return v;
    else{
      cerr<<"Syntax error : "<<c<<" unexpected"<<endl;
      exit(-1);
    }
    ++offset;
  }
  return v;
}

	 
Permutation::Permutation(string s){
  bool done[STRANDS+1];
  for(size_t i=0;i<=STRANDS;++i){
    done[i]=false;
  }
  if(s.size()!=STRANDS){
    cerr<<"Syntax error : permutation string has size "<<s.size()<<" instead of "<<STRANDS<<endl;
    exit(-1);
  }
  for(size_t i=0;i<STRANDS;++i){
    int v=s[i]-'a'+1;
    if(done[v]){
      cerr<<"Syntax error : "<<v<<" appear at least two times in permutation string"<<endl;
    }
    else{
      done[v]=true;
      data[i+1]=v;
    }
  }
}

Permutation Permutation::operator*(int i) const{
  assert(1<=i and i<=STRANDS-1);
  Permutation res;
  for(int k=1;k<=STRANDS;++k){
    if(k==i) res.data[i]=data[i+1];
    else if(k==i+1) res.data[i+1]=data[i];
    else res.data[k]=data[k];
  }
  return res;
}

string to_string(const Permutation& P){
  string res;
  for(int i=1;i<=STRANDS;++i){
    res+=char('a'+P(i)-1);
  }
  return res;
}

ostream& operator<<(ostream& os,const Permutation& P){
  return os<<to_string(P);
}

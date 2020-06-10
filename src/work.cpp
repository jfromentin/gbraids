#include "work.hpp"

void
output(const Signature<Artin>& s,const set<Braid>& braids){
  string filename=s.filename();
  fstream file;
  char l=s.braid_length();
  file.open(DATA_DIR+filename.c_str(),ios::out|ios::app);
  for(auto it=braids.begin();it!=braids.end();++it){
    if(it->length()==l) it->write(file);
  }
  file.close();
}

size_t
work(const Signature<Artin>& s_out){
  //cout<<endl<<"====> "<<s_out<<" <===="<<endl;
  Signature<Artin> s_cmp=s_out.comparison();
  set<Braid> cmp;
  //cout<<"s_cmp = "<<s_cmp<<endl;
  load(s_cmp,cmp);
  size_t n=0;
  for(char i=-3;i<=3;++i){
    if(i!=0){
      Signature<Artin> s_src=s_out.father(i);
      //cout<<"--> "<<i<<" : "<<s_src<<" => "<<src<<endl; 
      vector<Braid> src;
  
      load(s_src,src);
      //cout<<"--> "<<(int)i<<" : "<<s_src<<" => "<<src<<endl; 
      size_t nsrc=src.size();
      for(size_t k=0;k<nsrc;++k){
	Braid b=src[k];
	b*=i;
	//cout<<b<<endl;
	auto p_ins=cmp.insert(b);
	if(p_ins.second){
	  Braid c=b;
	  ++n;
	}
      }
    }
  }
  if(n!=0) output(s_out,cmp);
  return n;
}

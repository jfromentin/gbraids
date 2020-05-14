#include "work.hpp"

void
output(const Signature& s,const SetBraid& braids){
  string filename=s.filename();
  fstream file;
  char l=s.get_l();
  file.open(DATA_DIR+filename.c_str(),ios::out|ios::app);
  for(auto it=braids.begin();it!=braids.end();++it){
    if(it->length()==l){
      it->write(file);
    }
  }
  file.close();
}


size_t
work(const Signature& s_out){
  Signature s_cmp=s_out.comparison();

  size_t sc=number(s_cmp);
  if(sc>=SPLIT) return work_split(s_out);
  
  SetBraid cmp;
  load(s_cmp,cmp);
  size_t n=0;
    for(char i=-NBGENS;i<=NBGENS;++i){
    if(i!=0){
      Signature s_src=s_out.father(i);
      VectorBraid src;
      load(s_src,src);
      size_t nsrc=src.size();
      for(size_t k=0;k<nsrc;++k){
	Braid b=src[k];
	b*=i;
	auto p_ins=cmp.insert(b);
	if(p_ins.second) ++n;
      }
    }
  }
  if(n!=0) output(s_out,cmp);
  return n;
}

void
invariants(const Signature& s_out,set<Invariant>& invs){
  for(char i=-NBGENS;i<=NBGENS;++i){
    if(i!=0){
      Signature s_src=s_out.father(i);
      SetBraid src;
      load(s_src,src);
      for(auto it=src.begin();it!=src.end();++it){
        Braid b=*it;
	b*=i;
	invs.insert(b.invariant());
      }
    }
  }
}

size_t
work_split(const Signature& s_out){
  set<Invariant> invs;
  invariants(s_out,invs);
  Signature s_cmp=s_out.comparison();
  size_t n=0;
  size_t m=0;
  for(auto it_inv=invs.begin();it_inv!=invs.end();++it_inv){
    Invariant inv=*it_inv;
    SetBraid cmp;
    load(s_cmp,cmp,&inv);
    size_t nt=0;
    for(char i=-NBGENS;i<=NBGENS;++i){
      if(i!=0){
	Signature s_src=s_out.father(i);
	Invariant inv_src=inv.father(s_src.get_p(),i);
	VectorBraid src;
	load(s_src,src,&inv_src);
	size_t nsrc=src.size();
	for(size_t k=0;k<nsrc;++k){
	  Braid b=src[k];
	  b*=i;
	  if(b.invariant()==*it_inv){
	    auto p_ins=cmp.insert(b);
	    if(p_ins.second) ++nt;
	  }
	}
      }
    }
    if(nt!=0) output(s_out,cmp);
    n+=nt;
    m=max(m,nt);
  }
  return n;
}

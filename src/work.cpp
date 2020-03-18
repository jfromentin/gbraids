 #include "work.hpp"

size_t work(int l,Permutation& P,int a){
  char r;
  fstream fin[STRANDS];
  size_t size[STRANDS];
  string filenameout;
  filenameout=DATA_DIR+to_string(l)+to_string(P)+to_string(a);
  fstream fileout;
  set<Braid> all;
  string line;
  size_t n=0;
  for(int i=-STRANDS+1;i<STRANDS;++i){
    if(i!=0){
      Permutation Q=P*abs(i);
      int b=a+(i<0?1:-1);
      string filename=DATA_DIR+to_string(l-1)+to_string(Q)+to_string(b);
      fstream filesrc;
      filesrc.open(filename.c_str(),ios::in);
      filename=DATA_DIR+to_string(l-2)+to_string(P)+to_string(a);
      fstream filecomp;
      filecomp.open(filename.c_str(),ios::in);
      if(filecomp.is_open()){
	if(l==2){
	  Braid b;
	  all.insert(b);
	}
	else{
	  size_t bsize=(l-3)/3+1;
	  char buffer[bsize];
	  while(true){
	    filecomp.read(buffer,bsize);
	    if(filecomp.gcount()==0) break;
	    Braid b(buffer,l-2);
	    all.insert(b);
	  }
	}
	filecomp.close();
      }
      if(filesrc.is_open()){
	size_t bsize=(l-2)/3+1;
	char buffer[bsize];
	while(true){
	  filesrc.read(buffer,bsize);
	  if(filesrc.gcount()==0) break;
	  Braid b(buffer,l-1);
	  if(b.can_freely_add(i)){
	    Braid c=b*i;
	    auto res=all.insert(c);
	    if(res.second) ++n;
	  }
	}
	filesrc.close();
      }
    }
  }
  if(n>0){
    fileout.open(filenameout.c_str(),ios::out);
    for(auto it=all.begin();it!=all.end();++it){
      if(it->l==l){
	it->write(fileout);
      }
    }
    if(fopen) fileout.close();
  }
  return n;		      
}

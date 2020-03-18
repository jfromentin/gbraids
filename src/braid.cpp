#include "braid.hpp"

void
Braid::disp_letter(int v){
  if(v>0) cout<<char('a'+v-1);
  else cout<<char('A'-v-1);
}

Braid::Braid(string str){
  l=str.size();
  tab=new char[l];
  for(size_t i=0;i<l;++i){
    char c=str[i];
    if('a'<=c and c<='d'){
      tab[i]=c-'a'+1;
    }
    else if('A'<=c and c<='D'){
      tab[i]=-(c-'A'+1);
    }
    else{
      assert(false);
    }
  }
}

Braid::Braid(char* buffer,size_t ll){
  l=ll;
  tab=new char[l];
  size_t i=0;
  size_t j=0;
  while(i<l){
    uchar c=buffer[j++];
    tab[i++]=decode(c%6);
    if(i<l) tab[i++]=decode((c%36)/6);
    if(i<l) tab[i++]=decode(c/36); 
  }
}

void
Braid::write(fstream& file) const{
  size_t size=(l-1)/3+1;
  char buffer[size];
  size_t i=0;
  size_t k=0;
  while(i<l){
    uchar c=code(tab[i++]);
    if(i<l) c+=(code(tab[i++])*6);
    if(i<l) c+=(code(tab[i++])*36);
    buffer[k++]=c;
  }
  file.write(buffer,size);
}

bool
Braid::operator<(const Braid& b) const{
  //Init list
  EDList list;
  list.clear();
  if(l>0){
    for(size_t i=0;i<l;++i) list.push_front(-tab[i]);
  }
  if(b.l>0){
    for(size_t i=0;i<b.l;++i) list.push_back(b.tab[i]);
  }

  bool handle_reduced;
  int handles[STRANDS];
  //p=handles[i] contains the position of the last occurence of sigma_i^e; p has the sign of e
  //if we read a letter sigma_j^{+-1} with j<i then handles[i] is set to 0
  do{
    handle_reduced=false;
    for(size_t i=1;i<STRANDS;++i) handles[i]=0;
    uint16_t p=list.first();
    do{
      int v=list.get(p);
      int av,sv;
      if(v>0){av=v;sv=1;}
      else{av=-v;sv=-1;}
      for(size_t j=av+1;j<STRANDS;++j) handles[j]=0;
      int& info=handles[av];
      if(info*v>=0) info=sv*p;
      else{
	int16_t t=list.next(abs(info));
	while(t!=p){
	  int w=list.get(t);
	  int aw,sw;
	  if(w>0){aw=w;sw=1;}
	  else{aw=-w;sw=-1;}
	  if(aw==av+1){
	    list.insert_before(t,sv*aw);
	    list.set(t,sw*av);
	    t=list.insert_after(t,-sv*aw);
	  }
	  t=list.next(t);
	};
	list.erase(p);
	p=list.get_prev(abs(info));
	list.erase(abs(info));
	handle_reduced=true;
	break;
      }
      p=list.next(p);
    }while(p!=0);
  }while(handle_reduced);
  
  for(size_t i=1;i<STRANDS;++i){
    if(handles[i]!=0){
      return handles[i]>0;
    }
  }
  return false;
}

void
Braid::disp_list(EDList& l){
  uint16_t p=l.first();
  do{
    disp_letter(l.get(p));
    p=l.next(p);
  }while(p!=0);
  cout<<endl;
}

ostream& operator<<(ostream& os,const Braid& b){
  if(b.l==0) return os<<"empty braid";
  for(size_t i=0;i<b.l;++i){
    char c=b.tab[i];
    if(c>0){
      os<<char(c-1+'a');
    }
    else{
      os<<char(-c-1+'A');
    }
  }
  return os;
}

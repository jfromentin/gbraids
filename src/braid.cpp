#include "braid.hpp"

Int amplitude=0;

Invariant
Invariant::father(char p,char i) const{
  char ai,e;
  if(i<0){
    ai=-i;e=-1;
  }
  else{
    ai=i;e=1;
  }
  char r=eval_inv(p,ai);
  char s=eval_inv(p,ai+1);
  Invariant res;
  res.e13=e13;
  res.e24=e24;
  res.e14=e14;
  if(r>s) swap(r,s);
  if(r==1 and s==3) res.e13-=e;
  else if(r==2 and s==4) res.e24-=e;
  else if(r==1 and s==4) res.e14-=e;
  return res;
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

void Braid::positive_Dynnikov_action(Int& x1,Int& y1,Int& x2,Int& y2){
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

void Braid::negative_Dynnikov_action(Int& x1,Int& y1,Int& x2,Int& y2){
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

Invariant
Braid::invariant(){
  Invariant res;
  res.e13=0;
  res.e24=0;
  res.e14=0;
  char p=0;
  size_t k;
  while(k<len){
    char i=tab[k];
    char ai,e;
    if(i<0){
      ai=-i;
      e=-1;
    }
    else{
      ai=i;
      e=1;
    }
    char r=eval_inv(p,ai);
    char s=eval_inv(p,ai+1);
    if(r>s) swap(r,s);
    if(r==1 and s==3) res.e13+=e;
    else if(r==2 and s==4) res.e24+=e;
    else if(r==1 and s==4) res.e14+=e;
    p=left_prod[ai][p];
    ++k;
  }
  return res;
}

void
Braid::disp_letter(int v){
  if(v>0) cout<<char('a'+v-1);
  else cout<<char('A'-v-1);
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

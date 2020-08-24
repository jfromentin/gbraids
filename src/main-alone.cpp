#include "config.hpp"
#include "init.hpp"
#include "work.hpp"
#include "signature.hpp"
#include <omp.h>
#include <unordered_set>
using namespace std;

int main(int argc,char** argv){
  cout<<"***************************"<<endl;
  cout<<"* Gbraids - Artin - Alone *"<<endl;
  cout<<"***************************"<<endl;
  fstream file_bilan;
  file_bilan.open(DATA_DIR+"bilan.csv",ios::out);
  file_bilan<<"length,tasks,computed braids,braids,geodesics"<<endl;
  cout<<"-> Init ";
  init<GEN,STRANDS>();
  cout<<"... done."<<endl;
  set<Signature<GEN>> prec,cur;
  load(1,prec);
  cout<<"Prec "<<prec<<endl;
  next_signatures(prec,cur);
  cout<<"Cur "<<cur<<endl;
  //exit(0);
  for(char l=2;l<=24;++l){
    
    cur.clear();
    cout<<"------------------------"<<endl;
    cout<<"Length : "<<(int)l<<endl;
    next_signatures(prec,cur);
    fstream file;
    file.open(DATA_DIR+to_string((int)l)+".csv",ios::out);
    uint64_t ns=0;
    uint64_t ng=0;
    uint64_t nb=0;
    for(auto it=cur.begin();it!=cur.end();++it){
      pair<uint64_t,uint64_t> res=work(*it);
      int rank=it->rank();
      nb+=res.first;
      ns+=rank*res.first;
      ng+=rank*res.second;
      if(res.first!=0) file<<it->csv()<<','<<rank<<','<<res.first<<','<<res.second<<endl;
    }
    file.close();
    file_bilan<<l<<','<<cur.size()<<','<<nb<<','<<ns<<','<<ng<<endl;
    cout<<"-> "<<ns<<" braids"<<endl;
    cout<<"-> "<<ng<<" geodesics"<<endl;
    swap(cur,prec);
  }
}

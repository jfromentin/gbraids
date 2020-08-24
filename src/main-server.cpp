#include <set>
#include "config.hpp"
#include "../dist/server.hpp"
#include "init.hpp"
#include "work.hpp"
#include "gtask.hpp"
#include <algorithm>
using namespace std;

int main(int argc,char** argv){
  int l=1;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd<0){
    cerr<<"[Error] Can not open socket"<<endl;
    exit(-1);
  }
  if(GEN==Artin){
    cout<<"****************************"<<endl;
    cout<<"* Gbraids - Server - Artin *"<<endl;
    cout<<"****************************"<<endl;
  }
  else{
    cout<<"***************************"<<endl;
    cout<<"* Gbraids - Server - dual *"<<endl;
    cout<<"***************************"<<endl;
  }
  cout<<"Number of strands : "<<STRANDS<<endl;
  cout<<"Combinatorics type : ";
#ifdef SPHERICAL
  cout<<"spherical";
#else
  cout<<"geodesic";
#endif
  cout<<"."<<endl;
  Task* tasks=nullptr;
  Server server(MAX_CLIENTS,SERVER_PORT);
  set<Signature<GEN>> prec,cur;
  if(l==1){
    init<GEN,STRANDS>();
    ++l;
  }
  load(l-1,prec);
  fstream file_bilan;
  file_bilan.open(DATA_DIR+"bilan.csv",ios::out);
  file_bilan<<"length,tasks,computed braids,braids,geodesics"<<endl;
<<<<<<< HEAD
  while(l<=25){
=======
  while(l<=2){
>>>>>>> e1c2d0179e8933165b0bfb4e90f20ec19575cf66
    cur.clear();
    cout<<"---------------------------"<<endl;
    cout<<"Length : "<<(int)l<<endl;
    next_signatures(prec,cur);
    Task* tasks=generate_gtask(cur);
    size_t nb_tasks=cur.size();
    cout<<"Number of tasks : "<<nb_tasks<<endl;
    server.set_tasks(tasks,nb_tasks);
    do{
      server.listen_for_new_clients();
      server.listen_clients();
      server.treat_messages();
      server.affect_tasks();
      usleep(10000);
    }while(server.has_unfinished_tasks());
    fstream file;
    file.open(DATA_DIR+to_string((int)l)+".csv",ios::out);
    uint64_t ns=0;
    uint64_t ng=0;
    uint64_t nb=0;
    file<<"length,permutation,l12,l23,l34,l14,rank,braids,geodesics"<<endl;
    for(size_t i=0;i<nb_tasks;++i){
      GTaskOutput& output=*((GTaskOutput*)tasks[i].get_output());
      GTaskInput& input=*((GTaskInput*)tasks[i].get_input());
      if(output.ns!=0){
	int rank=input.signature.rank();
	ns+=(output.ns*rank);
	ng+=(output.ng*rank);
	nb+=output.ns;
	file<<input.signature.csv()<<','<<rank<<','<<output.ns<<','<<output.ng<<endl;
      }
    }
    file.close();
    file_bilan<<l<<','<<nb_tasks<<','<<nb<<','<<ns<<','<<ng<<endl;
    cout<<"Spherical : "<<ns<<endl;
    cout<<"Geodesics : "<<ng<<endl;
    ++l;
    swap(cur,prec);
  }
  file_bilan.close();
}

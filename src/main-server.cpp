#include <set>
#include "tclap/CmdLine.h"
#include "config.hpp"
#include "../dist/server.hpp"
#include "init.hpp"
#include "work.hpp"
#include "gtask.hpp"

using namespace std;

int main(int argc,char** argv){
  int l;
  try{
    TCLAP::CmdLine cmd("Count Artin braids on "+to_string(STRANDS)+" strands with given geodesic length (server)",' ',"0.1");
    TCLAP::ValueArg<int> l_arg("l","length","geodesic length",true,0,"integer");
    cmd.add(l_arg);
    cmd.parse(argc,argv);
    l=l_arg.getValue();
  }
  catch(TCLAP::ArgException &e){
    cerr <<"[Error] "<<e.error()<<" for arg "<<e.argId()<<endl;
    exit(-1);
  }
  if(l<1){
    cerr<<"[Error] Length must be greater than 2"<<endl;
    exit(-1);
  }
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd<0){
    cerr<<"[Error] Can not open socket"<<endl;
    exit(-1);
  }
  cout<<"*************************"<<endl;
  cout<<"* Geodesic braid server *"<<endl;
  cout<<"*************************"<<endl;
  Task* tasks=nullptr;
  Server server(MAX_CLIENTS,SERVER_PORT);
  set<Signature<Artin>> prec,cur;
  if(l==1){
    init<Artin>();
    ++l;
  }
  load(l-1,prec);
  fstream file_bilan;
  file_bilan.open(DATA_DIR+"bilan.csv",ios::out);
  file_bilan<<"length,braids,tasks,duration"<<endl;
  size_t total_duration=0;
  while(l<=32){
    size_t duration=0;
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
    size_t n=0;
    size_t nb=0;
    file<<"length,permutation,e12,e23,e34,rank,number"<<endl;
    for(size_t i=0;i<nb_tasks;++i){
      GTaskOutput& output=*((GTaskOutput*)tasks[i].get_output());
      GTaskInput& input=*((GTaskInput*)tasks[i].get_input());
      size_t number=output.number;
      if(number!=0){
	int rank=input.signature.rank();
	n+=(number*rank);
	nb+=number;
      	file<<input.signature.csv()<<","<<rank<<","<<number<<endl;
      }
    }
    file.close();
    file_bilan<<l<<','<<nb<<','<<n<<','<<nb_tasks<<endl;
    cout<<"Number of braids : "<<n<<endl;
    ++l;
    swap(cur,prec);
  }
  file_bilan.close();
}

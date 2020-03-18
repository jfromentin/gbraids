#include "tclap/CmdLine.h"
#include "config.hpp"
#include "../dist/server.hpp"
#include "init.hpp"
using namespace std;

static const string even_permutations[]={"abcd","acdb","adbc","badc","bcad","bdca",
					 "cabd","cbda","cdab","dacb","dbac","dcba"};
static const string  odd_permutations[]={"abdc","acbd","adcb","bacd","bcda","bdac",
					 "cadb","cbad","cdba","dabc","dbca","dcab"};

struct TaskInput{
  char p[4];
  int l;
  int a;
};

void generate_tasks(int l,Task* tasks){
  TaskInput input;
  size_t t=0;
  string* perms=(l%2==0)?(string*)even_permutations:(string*)odd_permutations;
  for(size_t i=0;i<12;++i){
    for(int a=-(int)l;a<=(int)l;a+=2){
      input.p[0]=perms[i][0];
      input.p[1]=perms[i][1];
      input.p[2]=perms[i][2];
      input.p[3]=perms[i][3];
      input.l=l;
      input.a=a;
      tasks[t].set_input((char*)&input,sizeof(TaskInput));
      tasks[t].set_statut(Task::Unaffected);
      ++t;
    }
  } 
}

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
  cout<<"*******************"<<endl;
  cout<<"* Genbraid server *"<<endl;
  cout<<"*******************"<<endl;
  Task* tasks=nullptr;
  size_t nb_tasks=0;
  Server server(MAX_CLIENTS,SERVER_PORT);
  while(true){
    if(l==1) init();
    else{
      cout<<"ici"<<endl;
      nb_tasks=12*(l+1);
      if(tasks!=nullptr) delete[] tasks;
      tasks=new Task[nb_tasks];
      generate_tasks(l,tasks);
      server.set_tasks(tasks,nb_tasks);
      cout<<"----------------------------------------"<<endl;
      cout<<" Length = "<<l<<endl;
      cout<<" Number of tasks = "<<nb_tasks<<endl;
      do{
	server.listen_for_new_clients();
	server.listen_clients();
	server.treat_messages();
	server.affect_tasks();
	usleep(10000);
      }while(server.has_unfinished_tasks());
      size_t n=0;
      string filename="data/"+to_string(l)+".csv";
      fstream fcsv;
      fcsv.open(filename.c_str(),ios::out);
      for(size_t i=0;i<nb_tasks;++i){
	size_t output;
	TaskInput input;
	memcpy(&output,tasks[i].get_output(),sizeof(size_t));
	memcpy(&input,tasks[i].get_input(),sizeof(TaskInput));
	n+=output;
	if(output>0){
	  fcsv<<input.l<<','<<input.p[0]<<input.p[1]<<input.p[2]<<input.p[3]<<','<<input.a<<','<<output<<endl;
	}
      }
      fcsv.close();
      cout<<" Number of braids : "<<n<<endl;
    }
    ++l;
  }
}

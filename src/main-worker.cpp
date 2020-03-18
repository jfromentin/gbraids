#include <set>
#include <stack>
#include <fstream>
#include <tclap/CmdLine.h>
#include <cstdlib>
#include "../dist/worker.hpp"
#include "work.hpp"

struct TaskInput{
  char p[4];
  int l;
  int a;
};

using namespace std;

int main(int argc,char** argv){
  Worker worker(SERVER_IP,SERVER_PORT);
  while(true){
    Task task=worker.get_task();
    const TaskInput* input=( const TaskInput* )task.get_input();
    string s="";
    s+=input->p[0];s+=input->p[1];s+=input->p[2];s+=input->p[3];
    Permutation P(s);
    /*cout<<"========= Get task ========="<<endl;
    cout<<" l = "<<input->l<<endl;
    cout<<" P = "<<P<<endl;
    cout<<" a = "<<input->a<<endl;*/
    size_t n=work(input->l,P,input->a);
    //cout<<" ---> done"<<endl;
    task.set_output((char*)&n,sizeof(size_t));
    worker.send_task(task);
  }
}
 

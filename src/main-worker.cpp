#include <set>
#include <stack>
#include <fstream>
#include <tclap/CmdLine.h>
#include <cstdlib>
#include <chrono>
#include "../dist/worker.hpp"
#include "work.hpp"
#include "gtask.hpp"

using namespace std;

int main(int argc,char** argv){
  Worker worker(SERVER_IP,SERVER_PORT);
  while(true){
    Task task=worker.get_task();
    const GTaskInput* input=(const GTaskInput*)task.get_input();
    const Signature& signature=input->signature;
    size_t estimation=input->estimation;
    GTaskOutput output;
    auto start = std::chrono::system_clock::now();
    size_t n;
    if(estimation>SPLIT){
      n=work_split(signature);
    }
    else{
      n=work(signature);
    }
    auto end = std::chrono::system_clock::now();
    size_t duration=std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    output.number=n;
    output.duration=duration;
    task.set_output((char*)&output,sizeof(output));
    worker.send_task(task);
  }
}
 

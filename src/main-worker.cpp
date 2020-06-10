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
    const Signature<Artin>& signature=input->signature;
    GTaskOutput output;
    auto start = std::chrono::system_clock::now();
    size_t n=work(signature);
    output.number=n;
    task.set_output((char*)&output,sizeof(output));
    worker.send_task(task);
  }
}
 

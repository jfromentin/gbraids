#include <set>
#include <stack>
#include <fstream>
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
    const Signature<GEN>& signature=input->signature;
    GTaskOutput output;
    auto start = std::chrono::system_clock::now();
    pair<size_t,size_t> p=work(signature);
    output.ns=p.first;
    output.ng=p.second;
    task.set_output((char*)&output,sizeof(output));
    worker.send_task(task);
  }
}
 

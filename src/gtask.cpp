#include "gtask.hpp"

bool
compare_gtask(const Task& t1,const Task& t2){
  GTaskInput* i1=(GTaskInput*)t1.get_input();
  GTaskInput* i2=(GTaskInput*)t2.get_input();
  return i1->signature<i2->signature;
}

Task*
generate_gtask(set<Signature<GEN>>& signatures){
  size_t size=signatures.size();
  Task* tasks=new Task[size];
  auto it=signatures.begin();
  for(size_t i=0;i<size;++i){
    GTaskInput input;
    input.signature=*it;
    Signature<GEN> s_cmp=it->comparison();
    tasks[i].set_input((char*)&input,sizeof(input));
    tasks[i].set_statut(Task::Unaffected);
    ++it;
  }
  sort(&tasks[0],&tasks[size],compare_gtask);
  return tasks;
}

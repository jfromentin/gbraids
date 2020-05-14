#ifndef TASK_HPP
#define TASK_HPP
#include <cassert>
#include <cstring>

class Task{
public:
  struct Data;
  enum Statut{Undefined,Unaffected,Affected,Done};
protected:
  char *input,*output;
  size_t input_size,output_size;
  Statut statut;
public:
  Task();
  Task(const Task& task);
  Task(Task&& task);
  ~Task();
  Task& operator=(const Task& task);
  Task& operator=(Task&& task);
  Statut get_statut() const;
  void set_statut(Statut s);
  const char* get_input() const;
  const char* get_output() const;
  size_t get_input_size() const;
  size_t get_output_size() const;
  void set_input(char* buffer,size_t s);
  void set_output(char* buffer,size_t s);
};

struct Task::Data{
  char* buffer;
  size_t size;
};

inline
Task::Task(){
  input=nullptr;
  output=nullptr;
  statut=Undefined;
}

inline
Task::Task(const Task& task){
  input_size=task.input_size;
  output_size=task.output_size;
  if(task.input!=nullptr){
    memcpy(input,task.input,input_size);
  }
  if(task.output!=nullptr){
    memcpy(output,task.output,output_size);
  }
  statut=task.statut;
}

inline
Task::Task(Task&& task){
  input_size=task.input_size;
  output_size=task.output_size;
  input=task.input;
  output=task.output;
  task.input=nullptr;
  task.output=nullptr;
  statut=task.statut;
}

inline
Task::~Task(){
  if(input!=nullptr) delete[] input;
  if(output!=nullptr) delete[] output;
}

inline Task&
Task::operator=(const Task& task){
  input_size=task.input_size;
  output_size=task.output_size;
  if(input==nullptr) delete[] input;
  if(output==nullptr) delete[] output;
  if(task.input!=nullptr){
    memcpy(input,task.input,input_size);
  }
  if(task.output!=nullptr){
    memcpy(output,task.output,output_size);
  }
  statut=task.statut;
  return *this;
}

inline
Task& Task::operator=(Task&& task){
  input_size=task.input_size;
  output_size=task.output_size;
  input=task.input;
  output=task.output;
  task.input=nullptr;
  task.output=nullptr;
  statut=task.statut;
  return *this;
}

inline
Task::Statut
Task::get_statut() const{
  return statut;
}

inline
void 
Task::set_statut(Statut s){
  statut=s;
}

inline
const char*
Task::get_input() const{
  return input;
}

inline
const char*
Task::get_output() const{
  return output;
}

inline
size_t
Task::get_input_size() const{
  return input_size;
}

inline
size_t
Task::get_output_size() const{
  return output_size;
}

inline
void
Task::set_input(char* buffer,size_t s){
  assert(input==nullptr);
  input_size=s;
  input=new char[s];
  memcpy(input,buffer,s);
}

inline
void
Task::set_output(char* buffer,size_t s){
  assert(output==nullptr);
  output_size=s;
  output=new char[s];
  memcpy(output,buffer,s);
}
#endif

#include "worker.hpp"

Task
Worker::get_task(){
  Task task;
  while(true){
    listen();
    if(has_message){
      has_message=false;
      switch(message.get_type()){
      case DATA:
	task.set_input(message.get_data_buffer(),message.get_data_size());
	return task;
	break;
      case CODE:
	if(message.get_code()=='K'){
	  cout<<"I quit !"<<endl;
	  exit(0);
	}
	cerr<<"[Error] Receive unexpected code "<<message.get_code()<<endl;
	exit(-1);
	break;
      default:
	cerr<<"[Error] Receive unexpected message"<<endl;
	break;
      }
    }
  }
  return task;
}

void
Worker::send_task(Task& task){
  Message msg;
  msg.set_data(task.get_output(),task.get_output_size());
  send_message(msg);
}

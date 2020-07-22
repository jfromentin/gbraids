#ifndef WORKER_HPP
#define WORKER_HPP

#include "client.hpp"
#include "task.hpp"

class Worker:public Client{
public:
  Worker(string ip,int port);
  Task get_task();
  void send_task(Task& task);
};

inline
Worker::Worker(string ip,int port):Client(ip,port){
  send_code('W');
}


#endif

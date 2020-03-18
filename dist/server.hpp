#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include "message.hpp"
#include "task.hpp"

using namespace std;

struct ClientInformation{
  int socket;
  bool has_message;
  Message message;
  void* data;
  bool is_worker;
  Task* current_task;
};

class Server{
private:
  void send_message(size_t c,Message& msg);
public:
  size_t nb_clients;
  size_t max_clients;
  size_t nb_workers;
  Task* tasks;
  size_t nb_tasks;
  size_t nb_finished_tasks;
  ClientInformation* clients;
  int connection_socket;
  char Buffer[MAX_MSG_SIZE];
  Server(size_t max_clients,int port);
  ~Server();
  void listen_for_new_clients();
  void listen_clients();
  void remove_client(size_t c);
  void get_message(size_t c);
  void send_code(size_t c,char code);
  void send_string(size_t c,string str);
  void treat_messages();
  void treat_message(size_t c);
  void send_informations(size_t c);
  void affect_task(size_t c);
  void affect_tasks();
  void get_task(size_t c);
  bool has_unfinished_tasks();
  void set_tasks(Task* tasks,size_t nb_tasks);
};

inline void
Server::send_message(size_t c,Message& msg){
  send(clients[c].socket,msg.buffer,msg.size,0);
}

inline void
Server::send_code(size_t c,char code){
  Message msg;
  msg.set_code(code);
  send_message(c,msg);
}

inline void
Server::treat_messages(){
  for(size_t c=0;c<nb_clients;++c){
    if(clients[c].has_message){
      treat_message(c);
    }
  }			 
}

inline bool
Server::has_unfinished_tasks(){
  return nb_finished_tasks<nb_tasks;
}
#endif

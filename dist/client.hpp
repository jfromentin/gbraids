#ifndef DIST_CLIENT_HPP
#define DIST_CLIENT_HPP
#include <iostream>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include "message.hpp"

using namespace std;

class Client{
protected:
   void send_message(Message& msg);
  bool has_message;
  Message message;
 public:
  char Buffer[MAX_MSG_SIZE];
  int socket_fd;
  Client(string server_ip,int server_port);
  ~Client();
  void send_code(char l);
  void send_string(string str);
  void listen();
  void get_message();
};

inline
Client::~Client(){
  close(socket_fd);
}

inline void
Client::send_message(Message& msg){
  send(socket_fd,msg.buffer,msg.size,0);
}

inline void
Client::send_code(char c){
  Message msg;
  msg.set_code(c);
  send_message(msg);
}
#endif

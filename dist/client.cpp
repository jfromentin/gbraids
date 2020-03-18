#include "client.hpp"

Client::Client(string server_ip,int server_port){
  socket_fd=socket(AF_INET, SOCK_STREAM, 0);
  if(socket_fd<0){
    cerr<<"[Error] I can't open socket"<<endl;
    exit(-1);
  }
  sockaddr_in serv_addr;
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
  serv_addr.sin_port = htons(server_port);
  if(connect(socket_fd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0){
    cerr<<"[Error] I can't connect socket"<<endl;
    cout<<errno<<endl;
    exit(-1);
  }
  has_message=false;
}

void Client::listen(){
  char buffer;
  int l=recv(socket_fd,&buffer,1,MSG_PEEK);
  if(l>0){
    get_message();
  }
  if(l==0){
    cerr<<"[Error] Server was done"<<endl;
    exit(-1);
  }
}

void
Client::get_message(){
  char buffer;
  message.clear();
  do{
    recv(socket_fd,&buffer,1,0);
  }while(message.add(buffer));
  has_message=true;
}

void
Client::send_string(string str){
  size_t offset=0;
  Message msg;
  while(offset<str.size()){
    size_t len=min((size_t)(MAX_MSG_SIZE-3),str.size()-offset);
    msg.set_string(str.substr(offset,len));
    send_message(msg);
    offset+=len;
  }
}

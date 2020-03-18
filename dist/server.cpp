#include "server.hpp"

Server::Server(size_t _max_clients,int port){
  //--------------------------
  // Create connection socket
  //--------------------------
  connection_socket=socket(AF_INET, SOCK_STREAM, 0);
  if(connection_socket<0){
    cerr<<"[Error] Can not open socket"<<endl;
    exit(-1);
  }
  //Set socket for nonblocking
  if(fcntl(connection_socket, F_SETFL, O_NONBLOCK)<0){
    cerr<<"[Error] Can not set socket for unblocking"<<endl;
    exit(-1);
  }
  sockaddr_in serv_addr;
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  if(bind(connection_socket,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
    cerr<<"[Error] Can not bind socket"<<endl;
    exit(-1);
  }
  listen(connection_socket,5);
  //---------
  // Clients
  //---------
  max_clients=_max_clients;
  nb_clients=0;
  clients=new ClientInformation[max_clients];
  //---------
  // Tasks
  //---------
  tasks=nullptr;
  nb_tasks=0;
  nb_finished_tasks=0;
  nb_workers=0;
}

void Server::set_tasks(Task* _tasks,size_t _nb_tasks){
  tasks=_tasks;
  nb_tasks=_nb_tasks;
  nb_finished_tasks=0;
}

Server::~Server(){
  cout<<" Close server."<<endl;
  for(size_t c=0;c<nb_clients;++c){
    close(clients[c].socket);
  }
  delete[] clients;
  close(connection_socket);
}

void
Server::listen_for_new_clients(){
  int socket=accept(connection_socket, NULL, NULL);
  if(socket>=0){
    //Set socket for nonblocking
    fcntl(socket, F_SETFL, O_NONBLOCK);
    clients[nb_clients].socket=socket;
    clients[nb_clients].has_message=false;
    clients[nb_clients].is_worker=false;
    clients[nb_clients].current_task=nullptr;
    ++nb_clients;
  }
}

void Server::listen_clients(){
  char buffer;
  for(size_t c=0;c<nb_clients;++c){
    int l=recv(clients[c].socket,&buffer,1,MSG_PEEK);
    if(l>0){
      if(not clients[c].has_message){
	get_message(c);
      }
    }
    if(l==0) remove_client(c);
  }
}

void Server::remove_client(size_t c){
  ClientInformation& client=clients[c];
  if(client.is_worker){
    Task* task=client.current_task;
    if(task!=nullptr){
      if(task->get_statut()!=Task::Done){
	task->set_statut(Task::Unaffected);
      }
    }
    --nb_workers;
  }
  --nb_clients;
  for(size_t i=c;i<nb_clients;++i){
    clients[i]=clients[i+1];
  }
}

void
Server::get_message(size_t c){
  char buffer;
  Message& message=clients[c].message;
  message.clear();
  do{
    recv(clients[c].socket,&buffer,1,0);
  }while(message.add(buffer));
  clients[c].has_message=true;
}

void
Server::send_string(size_t c,string str){
  size_t offset=0;
  Message msg;
  while(offset<str.size()){
    size_t len=min((size_t)(MAX_MSG_SIZE-3),str.size()-offset);
    msg.set_string(str.substr(offset,len));
    send_message(c,msg);
    offset+=len;
  }
}

void
Server::treat_message(size_t c){
  Message& message=clients[c].message;
  switch(message.get_type()){
  case CODE:
    switch(message.get_code()){
    case 'I':
      send_informations(c);
      break;
    case 'K':
      for(size_t c=0;c<nb_clients;++c){
	send_code(c,'K');
      }
      exit(0);
      break;
    case 'W':
      clients[c].is_worker=true;
      clients[c].current_task=nullptr;
      ++nb_workers;
      break;
    default:
      cerr<<"[Error] Receive unexpected code "<<message.get_code()<<" from client "<<c<<endl;
      break;
    };
    break;
  case DATA:
    get_task(c);
    clients[c].current_task=nullptr;
    break;
  default:
    cerr<<"[Error] Receive unexpected message from client "<<c<<" with type "<<message.get_type()<<endl;
    break;
  }
  clients[c].has_message=false;
}

void
Server::send_informations(size_t c){
  send_string(c,"Tasks : "+to_string(nb_tasks));
  send_string(c,"Tasks done : "+to_string(nb_finished_tasks));
  send_string(c,"Clients : "+to_string(nb_clients));
  send_string(c,"Workers : "+to_string(nb_workers));
  send_code(c,'E');
}

void
Server::affect_tasks(){
  for(size_t c=0;c<nb_clients;++c){
    if(clients[c].is_worker and clients[c].current_task==nullptr){
      affect_task(c);
    }
  }								    
}

void
Server::affect_task(size_t c){
  //Find first unafected task
  for(size_t i=0;i<nb_tasks;++i){
    if(tasks[i].get_statut()==Task::Unaffected){
      //Affect task i
      clients[c].current_task=&tasks[i];
      tasks[i].set_statut(Task::Affected);
      Message msg;
      msg.set_data(tasks[i].get_input(),tasks[i].get_input_size());
      send_message(c,msg);
      return;
    }
  }
}

void
Server::get_task(size_t c){
  Task* task=clients[c].current_task;
  Message& message=clients[c].message;
  task->set_output(message.get_data_buffer(),message.get_data_size());
  task->set_statut(Task::Done);
  ++nb_finished_tasks;
}

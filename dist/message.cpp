#include "message.hpp"

void
Message::set_string(string s){
  size=s.size()+3;
  assert(size<=MAX_MSG_SIZE);
  buffer[0]=STRING;
  uint16_t u=s.size();
  memcpy(&buffer[1],(char*)&u,2);
  memcpy(&buffer[3],s.c_str(),s.size());
}

void
Message::set_integer(Integer i){
  size=1+sizeof(Integer);
  buffer[0]=INTEGER;
  memcpy(&buffer[1],(char*)&i,sizeof(Integer));
}

void
Message::set_data(const char* data_buffer,size_t data_size){
  size=1+sizeof(size_t)+data_size;
  buffer[0]=DATA;
  size_t offset=1;
  memcpy(&buffer[1],&data_size,sizeof(size_t));
  memcpy(&buffer[1+sizeof(size_t)],data_buffer,data_size);
}

bool
Message::add(char l){
  if(csize==0){
    csize=1;
    buffer[0]=l;
    switch(l){
    case CODE:
      size=2;
      break;
    case INTEGER:
      size=1+sizeof(Integer);
      break;
    case STRING:
    case DATA:
      break;
    default:
      cerr<<"[Error] Message type unkown ("<<l<<')'<<endl;
      return false;
      break;
    }
    return true;
  }
  switch(buffer[0]){
  case CODE:
    return add_to_code(l);
    break;
  case STRING:
    return add_to_string(l);
    break;
  case INTEGER:
    return add_to_integer(l);
    break;
  case DATA:
    return add_to_data(l);
    break;
  default:
    cerr<<"[Error] Message type unkown"<<endl;
    return false;
    break;
  }
  return false;  
}

bool
Message::add_to_code(char l){
  csize=2;
  buffer[1]=l;
  return false;
}

bool
Message::add_to_string(char l){
  if(csize==1){
    buffer[csize++]=l;
    return true;
  }
  if(csize==2){
    buffer[csize++]=l;
    uint16_t s;
    memcpy(&s,&buffer[1],2);
    size=s+3;
    return true;
  }
  buffer[csize++]=l;
  return csize<size; 
}

bool
Message::add_to_integer(char l){
  buffer[csize++]=l;
  return csize<size;
}

bool
Message::add_to_data(char l){
  if(csize==1+sizeof(size_t)){
    size_t s;
    memcpy(&s,&buffer[1],sizeof(size_t));
    size=csize+s;
  }
  buffer[csize++]=l;
  return csize<max(2+sizeof(size_t),size);
}

size_t
Message::get_data_size(){
  assert(buffer[0]==DATA);
  size_t data_size;
  memcpy(&data_size,&buffer[1],sizeof(size_t));
  return data_size;  
}

char*
Message::get_data_buffer(){
  assert(buffer[0]==DATA);
  return &buffer[1+sizeof(size_t)];  
}

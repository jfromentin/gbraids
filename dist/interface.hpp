#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "client.hpp"

class Interface:public Client{
public:
  Interface(string ip,int port);
  void get_informations();
};

inline
Interface::Interface(string ip,int port):Client(ip,port){
}
#endif

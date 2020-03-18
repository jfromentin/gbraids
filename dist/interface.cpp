#include "interface.hpp"

void
Interface::get_informations(){
  cout<<endl<<"========= Informations ========="<<endl;
  while(true){
    listen();
    if(has_message){
      has_message=false;
      switch(message.get_type()){
      case STRING:
	cout<<message.get_string()<<endl;
	break;
      case CODE:
	if(message.get_code()=='E') return;
	cerr<<"[Error] Receive unexpected code "<<message.get_code()<<endl;
	return;
	break;
      default:
	cerr<<"[Error] Receive unexpected message"<<endl;
	return;
	break;
      }
    }
    else usleep(10000);
  }
  cout<<"================================"<<endl;
}

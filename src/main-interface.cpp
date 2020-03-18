#include "../dist/interface.hpp"
#include "config.hpp"

using namespace std;
int main(int argc,char** argv){
  cout<<"*****************************"<<endl;
  cout<<"* Genbraid interface client *"<<endl;
  cout<<"*****************************"<<endl;
  Interface interface(SERVER_IP,SERVER_PORT);
  bool quit=false;
  while(not quit){
    cout<<endl;
    cout<<"---------- Menu ----------"<<endl;
    cout<<endl;
    cout<<"   i > get informations"<<endl;
    cout<<"   k > kill server"<<endl;
    cout<<"   q > quit"<<endl;
    cout<<endl;
    cout<<" choice ? ";
    char rep;
    cin>>rep;
    switch(rep){
    case 'i':
      interface.send_code('I');
      interface.get_informations();
      break;
    case 'k':
      interface.send_code('K');
      quit=true;
      break;
    case 'q':
      quit=true;
      break;
    default:
      break;     
    }
  }
  return 0;
}

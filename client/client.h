#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<error.h>
using namespace std;
class udp_client
{
public:
  udp_client(const string& _ip,const short&_port);
  ~udp_client();
  void init_client();
  bool send_data(const string& _data);
  bool recv_data(string& _out);
private:
   string remote_ip;
   short remote_port;
   int sock;
};

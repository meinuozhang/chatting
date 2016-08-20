#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<string>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<error.h>
#include<stdlib.h>
#include<stdio.h>
#include<map>
#include"data_pool.h"
using namespace std;
class udp_server
{
public:
   udp_server(const string &_ip,const short& _port);
   ~udp_server();
   void init_server(const string& _ip,const short& _port);
   bool recv_data(string &_out);
   void broadcast_data();
private:
   string ip;
   short port;
   int sock;
   data_pool pool;
   map<string,struct sockaddr_in> online_user;
   bool send_data(string &_data,struct sockaddr& _client,socklen_t _len);
  bool add_user(const struct sockaddr_in& _client);
  bool del_user(const string& _ip);
};

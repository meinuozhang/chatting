#include"server.h"
udp_server::udp_server(const string& _ip,const short& _port)
	:ip(_ip)
	,port(_port)
	,sock(-1)
{}
udp_server::~udp_server()
{
	if(this->sock>0)
	{
		close(sock);
	}
}
void udp_server:: init_server(const string& _ip,const short& _port)
{
  this->sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock==-1)
  {
	  perror("socket");
	  exit(1);
  }
  struct sockaddr_in local;
  local.sin_family=AF_INET;
  local.sin_port=htons(_port);
  if(_ip=="")
  {
   local.sin_addr.s_addr=htonl(INADDR_ANY);
  }
  else
  {
    local.sin_addr.s_addr=inet_addr(_ip.c_str());
  }
  if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
  {
	  perror("bind");
	  exit(2);
  }
}
bool udp_server:: recv_data(string &_out)
{
   char buf[1024];
   memset(buf,'\0',sizeof(buf));

   struct sockaddr_in client;
   socklen_t len=sizeof(client);
 while(1)
 {
   ssize_t _size=recvfrom(this->sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
   if(_size==0)
   {
    cout<<"client close"<<endl;
	continue;
   }
   else if(_size<0)
   {
	   close(sock);
   }
   else
   {
	   _out=buf;
   }
   return true;
 }
}

bool udp_server:: send_data(string &_data,struct sockaddr& _client,socklen_t _len)
{
  while(1)
  {
	ssize_t _size=sendto(this->sock,_data.c_str(),_data.size(),0,(struct sockaddr*)&_client,_len);
    if(_size<0)
	{
		perror("sendto");
        continue;
	}
	return true;
  }
} 

bool add_user(const struct sockaddr_in& _client)
{
     string _ip=inet_ntoa(_client.sin_addr);//将一个IP转化为标准的网络点分格式的字符串
	 map<string,struct sockaddr_in>::iterator _iter=online_user.find(_ip);
	 if(_iter!=online_user.end())
	 {
		 return false;//user already exit
	 }
	 else//add user success
	 {
		 online_user.insert(pair<string,struct sockaddr_in>(_ip,_client));
	 }
}

bool del_user(const string& _ip)
{
      this->ip=_ip;
	  map<string,struct sockaddr_in>::inerator _iter=online_user.begin();
	  for(;_iter!=online_user.end();_iter++)
	  {
		  if(_iter->first==ip)
		  {
			  online_user.erase(_iter++);
		  }
		  else
		  {
			  ++_iter;
		  }
	  }
}

void udp_server::broadcast_data()//put data broad to everyuser
{
    string _out;
	pool.get_data(_out);
	map<string,struct sockaddr_in>::iterator _iter;
    for(_iter=online_user.begin();_iter!=online_user.end();_iter++)
	{
		send_data(_out,&(_iter->second),sizeof(_iter->second));
	}
}

void* recv_handler(void* arg)
{
    udp_server *recv_server=(udp_server*)arg;
	string client_info;
    bool done=false;
	while(!done)
	{
		recv_server->recv_data(client_info);
	}
}
/*void* send_handler(void* arg)
{
   udp_server *broadcast_server=(udp_server*)arg;
   bool done=false;
   while(!done)
   {
	   broadcast_server->broadcast_data();
   }

}*/
void usage(char* _proc)
{
	cout<<_proc<<"[ip][port]"<<endl;
}
int main(int argc,char* argv[])
{
	if(argc<3)
	{
      usage(argv[0]);
	}
	string _ip=argv[1];
    short _port=atoi(argv[2]);
    udp_server ser(_ip,_port);
	ser.init_server(_ip,_port);
/*
    pthread_t recv_pthread;
	pthread_t send_pthread;
    pthread_create(&recv_pthread,NULL,recv_hander,(void *)&ser);
	pthread_create(&send_pthread,NULL,broadcast_hander,(void*)&ser);
    pthread_join(recv_pthread,NULL);
	pthread_join(send_pthread,NULL);
*/

	string _out;
	bool done=true;
	while(done)
	{
		ser.recv_data(_out);
		sleep(1);
		cout<<_out<<endl;
	}
	return 0;
}

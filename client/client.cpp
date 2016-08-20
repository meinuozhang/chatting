#include"client.h"
udp_client::udp_client(const string& _ip,const short& _port)
	:remote_ip(_ip)
	,remote_port(_port)
	,sock(-1)
{}
udp_client::~udp_client()
{
	if(this->sock>0)
	{
		close(sock);
	}
}
void udp_client::init_client()
{
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("socket");
		exit(1);
	}
}
bool udp_client::send_data(const string& _data)
{
   struct sockaddr_in remote;
   remote.sin_family=AF_INET;
   remote.sin_port=htons(remote_port);
   remote.sin_addr.s_addr=inet_addr(remote_ip.c_str());
   socklen_t len=sizeof(remote);
while(1)
{
   ssize_t _size=sendto(sock,_data.c_str(),_data.size(),0,(struct sockaddr*)&remote,len);
  if(_size<0)
  {
	  perror("sendto");
	  continue;
  }
  return true;
}
}
bool udp_client::recv_data(string &_out)
{

}
const void usage(char* _proc)
{
	cout<<_proc<<"[ip][port]"<<endl;
}


udp_client *client=NULL;
int main(int argc,char* argv[])
{
   if(argc<3)
   {
	   usage(argv[0]);
	   return -1;
   }
   string _ip=argv[1];
   short _port=atoi(argv[2]);
   udp_client cli(_ip,_port);
   cli.init_client();
   client=&cli;
   /*string _out="hello";
   bool done=true;
   while(done)
   {
   cli.send_data(_out);
   sleep(1);
   cout<<_out<<endl;
   }*/
   return 0;
}

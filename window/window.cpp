#include"window.h"
window::window()
	:header(NULL)
	,output(NULL)
	,input(NULL)
	,friends_list(NULL)
{
    initscr();//init screen
	curs_set(0);//cancel cursor
}
void window::put_str_to_win(WINDOW* _win,int _y,int _x, string& _msg)
{
	mvwaddstr(_win,_y,_x,_msg.c_str());
}
void window::get_input_msg(WINDOW*_in,string& _out)
{
    char buf[1024];
	memset(buf,'\0',sizeof(buf));
	wgetnstr(_in,buf,sizeof(buf)-1);
	_out=buf;
}
void window::draw_header(int msg_y,int msg_x,string& _msg)
{
    int _y=0;
	int _x=0;
	int _high=LINES/5;
	int _width=COLS;
	this->header=newwin(_high,_width,_y,_x);
	box(this->header,0,0);
	if(msg_y!=-1 ||msg_y!=-1)
	{
	 put_str_to_win(this->header,msg_y,msg_x,_msg);
	}
	 wrefresh(this->header);
}
void window::draw_input()
{
    int _y=(LINES*4)/5;
	int _x=0;
	int _high=LINES/5;
	int _width=COLS;
	this->input=newwin(_high,_width,_y,_x);
	box(this->input,0,0);
	int _str_y=0;
	int _str_x=0;
	string _str="please enter:";
 	put_str_to_win(this->input,_str_y,_str_x,_str);
	wrefresh(this->input);
}
void window::draw_output(int msg_y,int msg_x,string& _msg)
{
    int _y=LINES/5;
	int _x=0;
	int _high=(LINES*3)/5;
	int _width=(COLS*3)/4;
	if(msg_y==-1 && msg_x==-1)
	{	 
	this->output=newwin(_high,_width,_y,_x);
	box(this->output,0,0);
	}
	else
	{
	box(this->output,0,0);
	put_str_to_win(output,_y,_x,_msg);
	}
	wrefresh(this->output);
}
void window::draw_friends_list()
{
    int _y=LINES/5;
	int _x=(COLS*3)/4;
	int _high=(LINES*3)/5;
	int _width=COLS/4;
	this->friends_list=newwin(_high,_width,_y,_x);
	box(this->friends_list,0,0);
	wrefresh(this->friends_list);
}
void window:: clear_win_line(WINDOW* _win,int begin,int lines)
{
	while(lines-->0)
	{
	wmove(_win,begin++,0);
	wclrtoeol(_win);
	}
}
void* head(void* arg)
{
	window *_win=(window*)arg;
	bool done=false;
	int high_y=0;
	int width_x=0;
	int msg_x=1;
	int msg_y=LINES/10;
	string _msg="welcome change bit";
	_win->draw_header(-1,-1,_msg);
	WINDOW *header_win=_win->getheader();
	while(!done)
	{
	 getmaxyx(header_win,high_y,width_x);//have no value,is define
   	 msg_y=high_y/2;
	_win->draw_header(msg_x,msg_y,_msg);
	sleep(1);
	_win->clear_win_line(header_win,msg_y,1);
	msg_x++;
	msg_x%=width_x;
	}
	return NULL;
}
void* output(void* arg)
{
	window *_win=(window*)arg;
	bool done=false;
	int _high=(LINES*3)/5;
	int _width=(COLS*3)/4;
	string msg="hhhh";
	while(!done)
	{
	_win->draw_output(_high,_width,msg);
	_win->draw_friends_list();
	WINDOW *friend_list_win=_win->getflist();
	int y,x;
	getmaxyx(friend_list_win,y,x);
	}
	return NULL;
}
void* input(void* arg)
{
	window *_win=(window*)arg;
	WINDOW * input_win=_win->getinput();
	string msg;
	bool done=false;
	while(!done)
	{
	_win->draw_input();
	_win->get_input_msg(input_win,msg);
	_win->draw_input();
	sleep(1);
	}
	return NULL;
}
window::~window()
{
	delwin(this->header);
	delwin(this->output);
	delwin(this->friends_list);
	delwin(this->input);
	endwin();
}
#ifdef _DEBUG_
int main()
{

	window _w;
/*	int x=1;
	int y=1;
	string str="hello";
	_w.draw_header(y,x,str);
	sleep(1);
	//_w.draw_output();
	//sleep(1);
	_w.draw_input();
	sleep(1);
	_w.draw_friends_list();
	sleep(1);
*/
	pthread_t tid1,tid2,tid3;
	pthread_create(&tid1,NULL,head,(void*)&_w);
	pthread_create(&tid2,NULL,output,(void*)&_w);
	pthread_create(&tid3,NULL,input,(void*)&_w);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

	return 0;
}
#endif

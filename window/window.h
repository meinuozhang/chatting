#pragma once
#include<iostream>
#include<ncurses.h>
#include<string>
#include<string.h>
#include<pthread.h>
using namespace std;
class window
{
public:
	window();
	~window();
    void draw_header(int msg_y,int msg_x,string& _msg);
    void draw_output(int msg_y,int msg_x,string& _msg);
	void draw_input();
	void draw_friends_list();
    void put_str_to_win(WINDOW* _win,int _y,int _x,string& _msg);
    void get_input_msg(WINDOW*_in,string& _out);
	void clear_win_line(WINDOW* _win,int begin,int lines);
	WINDOW* getheader(){return header;}
	WINDOW* getoutput(){return output;}
	WINDOW* getinput() {return input;}
	WINDOW* getflist(){return friends_list;}
private:
    WINDOW *header;
	WINDOW *output;
	WINDOW *input;
	WINDOW *friends_list;
};

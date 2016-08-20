#pragma once
#include<iostream>
#include<string>
#include"json_comm.h"
class udp_data
{
public:
	udp_data();
	~udp_data();
	void set_name(const string& _s){name=_s;}
	void set_school(const string& _s){school=_s;}
	void set_msg(const string& _s){msg=_s;}
	void set_cmd(const string& _s){cmd=_s;}
	void serialize(string& _out);//序列化

	void deserialize(string& _in);//反序列化

	void get_name(string& _out){name=_out;}
	void get_school(string& _out){school=_out;}
	void get_msg(string& _out){msg=_out;}
	void get_cmd(string& _out){cmd=_out;}
private:
	string name;
	string school;
	string msg;
    string cmd;
};

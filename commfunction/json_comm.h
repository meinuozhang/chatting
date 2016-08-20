#pragma once
#include<iostream>
#include<string>
#include<json/json.h>
using namespace std;
class json_comm
{
public:
    json_comm();
	~json_comm();
	bool set_val(const Json::Value& _val);
	bool val_to_str();
	bool get_val(const Json::Value& _outval);

	bool set_str(const string& _str);
	bool str_to_val();
	bool get_str(string& _outstr);
private:
    Json::Value val;
	string str;
};

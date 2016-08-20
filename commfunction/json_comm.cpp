#include"json_comm.h"
json_comm::json_comm()
{}
json_comm::~json_comm()
{}
bool json_comm::val_to_str()
{
  #ifdef _FAST_JSON_
	Json::Fastwriter _writer;
  #else
	Json::Styledwrite _writer;
  #endif
	this->str=_writer.write(this->val);
	return true;
}
bool json_comm::str_to_val()
{
	Json::Reader _read;
	if(_read.parse(this->str,this->val,false))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool json_comm::set_val(const Json::Value& _val)
{
	this->val=_val;
}
bool json_comm::get_val(Json::Value& _outval)
{
	_outval=this->val;
}
bool json_comm::set_str(const string& _str)
{
	this->str=_str;
}
bool json_comm::get_str(string& _outstr)
{
	_outstr=this->str;
}
//#ifdef _DEBUG_
int main()
{
  json_comm _json;
  string _out_str;
  Json::Value root;
  root["name"]="meinuo";
  root["school"]="xatu";
  root["msg"]="hello";
  root["cmd"]="none";
  _json.set_val(root);
  _json.val_to_str();
  _json.get_val(_out_str);
  cout<<root<<endl;
   return 0;
}

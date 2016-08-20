#include"udp_data.h"
void serialize(string& _out)
{
	Json::Value _value;
	_value["name"]=this->name;
	_value["school"]=this->school;
    _value["msg"]=this->msg;
	_value["cmd"]=this->cmd;
	json_comm _json;
	_json.set_val(_value);
	_json.val_to_str();
	_json.get_str(_out);

}
void deserialize(string& _in)
{
	Json::Value _value;
	json_comm _json;
    _json.set_str(_value);
	_json.str_to_val();
	_json.get_val(_in);

	this->name=_value["name"].asString();
    this->school=_value["school"].asString();
    this->msg=_value["msg"].asString();
	this->cmd=_value["cmd"].asString();
}
#ifdef _DEBUG_
int main()
{
  string _out;
  udp_data _data;
  _data.set_name("meinuo");
  _data.set.school("xatu");
  _data.set.msg("hello");
  _data.set.cmd("none");
  _data.serialize(_out);
  cout<<_out<<endl;
 return 0;
}
#endif

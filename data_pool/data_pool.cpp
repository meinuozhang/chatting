#include"data_pool.h"
data_pool::data_pool(int _size)
	:capacity(_size)
	,pool(_size)
	,product_step(0) 
	,consumer_step(0)
{
	sem_init(&product_sem,0,_size);
	sem_init(&consumer_sem,0,0);
}
data_pool::~data_pool()
{
    sem_destroy(&product_sem);
	sem_destroy(&consumer_sem);
}
bool data_pool::get_data(string& _out)
{
	sem_wait(&consumer_sem);
	_out=pool[consumer_step];
//	cout<<_out<<endl;
	consumer_step++;
	consumer_step%=capacity;
	sem_post(&product_sem);
}
bool data_pool::post_data(string& _in)
{
    sem_wait(&product_sem);
	pool[product_step]=_in;
	//cout<<pool[product_step]<<endl;
	product_step++;
	product_step%=capacity;
    sem_post(&consumer_sem);
}
/*
int main()
{
    data_pool pool(20);
    string msg="hello";
	bool done=false;
	while(!done)
	{
		pool.post_data(msg);
		pool.get_data(msg);	
	}
	return 0;
}*/

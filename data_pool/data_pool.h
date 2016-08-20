#pragma once
#include<iostream>
#include<vector>
#include<semaphore.h>
using namespace std;
class data_pool
{
public:
	data_pool(int _size);
	~data_pool();
	bool get_data(string& _out);
    bool post_data(string& _in);
private:
	vector<string> pool;
	int capacity;
	int product_step;
	int consumer_step;
    sem_t product_sem;
	sem_t consumer_sem;
};

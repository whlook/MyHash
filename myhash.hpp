#pragma once
#include <iostream>
using namespace std;

template<typename map_t>
class MyHash
{
public:
	MyHash() :size(1000)
	{
		store = new data[size];
	}
	MyHash(size_t s) :size(s)
	{
		store = new data[size];
	}
	~MyHash()
	{
		delete[]store;
	}
public:
	bool insert(size_t key, map_t val);
	bool find(size_t key, map_t & val);
	bool erase(size_t key);
	void print();

private:
	size_t size;
	struct data
	{
		size_t key;
		map_t content;
		bool isEmpty;
		data * next;
		data() :isEmpty(true), next(nullptr){}
	};
	
	data * store;
	size_t hash(size_t key);
};


template<typename map_t>
bool MyHash<map_t>::insert(size_t key, map_t val)
{
	size_t t_k = hash(key);
	if (t_k >= size || t_k < 0)
		return false;
	if (!store[t_k].isEmpty)
	{
		data * temp_ptr = & store[t_k];
		while (temp_ptr->next!=nullptr)
		{
			temp_ptr = temp_ptr->next;
			if (temp_ptr->key == key)
			{
				temp_ptr->content = val;
				return true;
			}
		}
		data *new_ = new data;

		new_->key = key;
		new_->content = val;
		new_->isEmpty = false;
		new_->next = nullptr;
		temp_ptr->next = new_;

		return true;
	}

	data* new_ = new data;
	new_->key = key;
	new_->content = val;
	new_->isEmpty = false;
	new_->next = nullptr;

	store[t_k].next = new_;
	store[t_k].isEmpty = false;
	

	return true;
}
template<typename map_t>
bool MyHash<map_t>::find(size_t key, map_t& val)
{
	size_t t_k = hash(key);
	if (t_k >= size || t_k < 0)
		return false;
	
		data * temp_ptr = &store[t_k];
		while (temp_ptr->next != nullptr)
		{
			temp_ptr = temp_ptr->next;
			if (temp_ptr->key == key)
			{
				val = temp_ptr->content;
				return true;
			}
		}
		return false;
}
template<typename map_t>
bool MyHash<map_t>::erase(size_t key)
{
	size_t t_k = hash(key);
	if (t_k >= size || t_k < 0 || store[t_k].isEmpty)
		return false;

	data * temp_ptr = &store[t_k];
	data * temp_ptr_ = &store[t_k];
	while (temp_ptr->next!=nullptr)
	{
		temp_ptr_ = temp_ptr;
		temp_ptr = temp_ptr->next;
		if (temp_ptr->key == key)
		{
			temp_ptr_->next = temp_ptr->next;
			delete temp_ptr;
			return true;
		}
	}

	return false;
}
template<typename map_t>
void MyHash<map_t>::print()
{
	for (int i = 0; i < size; ++i)
	{
		if (!store[i].isEmpty)
		{
			cout << i << "  : ";

			data * temp_ptr = &store[i];
			while (temp_ptr->next != nullptr)
			{
				temp_ptr = temp_ptr->next;
				cout << " - " << temp_ptr->content;
			}
			cout << endl;
		}
	}
}

template<typename map_t>
size_t MyHash<map_t>::hash(size_t key)
{
	return key%size;
}
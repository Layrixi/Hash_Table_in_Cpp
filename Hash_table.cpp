#include <iostream>
#include <string>
#include "dynamic_arr.h"
#include "lista_dwukierunkowa.h"

using namespace std;
//pomysl na hashowanie innych danych niż string: wyliczanie z bitów czegoś
template <typename T>
class Hash_table {
public:
	linked_list<T>* arr;//tymczasowe rozwiazanie, nie jestem w stanie zrobic tego na tablicy dynamicznej
	//dynamic_arr<linked_list<T>*> arr;
	bool add(string key, T* obj);//przed dodaniem sprawdzić zapełnienie, jeśli jest pełne to rehashować
	bool remove(string key);
	T* find(string key);
	int hash_fun(string key);
	void print();
	void rehash();
	void clear();
	Hash_table()
	{
		arr = new linked_list<T>[31];
	}
};

template <typename T> void Hash_table<T>::clear()
{
	for (int i = 0; i < 31; i++)
	{
		arr[i].clear();
	}
}
//template <typename T> void Hash_table<T>::clear()
//{
//	for (int i = 0; i < arr.size; i++)
//		delete arr[i];
//	
//	//arr.clear();
//}

template <typename T> void Hash_table<T>::print()
{
	for (int i = 0; i < 31; i++)
	{
		cout << "arr [" << i << "] ";
		arr[i].print_list();
	}
}

template <typename T> int Hash_table<T>::hash_fun(string key)
{
	unsigned int ASCII_sum = 0;
	for (int i = 0; i < key.length(); i++)
	{
		ASCII_sum += (int)key[i];
	}
	return ASCII_sum % 31;
	//return ASCII_sum % arr.size_max;
}

template <typename T> void Hash_table<T>::rehash()
{
	//stworz tablice pomocnicza, przepisz do niej tablice zahashowaną, wyzeruj elementy w tablicy zahashowanej, zahashuj wartości z tablicy pomocniczej do nowej hashujacej
	dynamic_arr<linked_list<T>*> pom = arr;
	cout << "";
}

template <typename T> bool Hash_table<T>::add(string key, T* obj)
{
	//if (arr.check_fulfill() == 1)
		//rehash();
	unsigned int index = hash_fun(key);
	//linked_list<T>* lista = arr[index];
	/*if(arr[index]==NULL)
	{
		arr[index] = new linked_list<T>;
	}*/
	arr[index].add_tail(obj);
	//arr.size++;

	return true;
}

template <typename T> T* Hash_table<T>::find(string key)
{
	if (arr[hash_fun(key)].find_by_key(key) != NULL)
		return arr[hash_fun(key)].find_by_key(key)->obj;
	return NULL;
}

template <typename T> bool Hash_table<T>::remove(string key) {
	T* object = find(key);
	if(object != NULL)
		return arr[hash_fun(key)].remove_obj(object);
	return false;
}

class test_class {
public:
	string key;
	friend bool operator>(const test_class& klasa1, const test_class& klasa2)
	{
		return klasa1.key > klasa2.key;
	}
	friend bool operator<(const test_class& klasa1, const test_class& klasa2)
	{
		return klasa1.key < klasa2.key;
	}
	friend bool operator==(const test_class& klasa1, const test_class& klasa2)
	{
		return klasa1.key == klasa2.key;
	}

	friend ostream& operator<<(ostream& os, const test_class klasa1)//TODO: fix when calling << of NULL object
	{
		
		os << klasa1.key;
		return os;
	}
	test_class(string i)
	{
		key = i;
	}
	string gen_random(const int len) {
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";//tablica ze znakami do generowania losowych stringow
		string temp;
		temp.reserve(len);

		for (int i = 0; i < len; ++i) {
			temp += alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		return temp;
	}
	test_class()
	{
		key = gen_random(10);
	}
};

int main()
{
	Hash_table<test_class>* tab = new Hash_table<test_class>;
	
	for (int i = 0; i < 100; i++)
	{
		test_class* test = new test_class();
		tab->add(test->key, test);
	}//dodawanie działa  na szywno
	
	test_class* test = new test_class("Los Capibaras");
	tab->add(test->key, test);
	tab->add(test->key, test);
	tab->add(test->key, test);
	tab->add(test->key, test);
	tab->print();
	if ((tab->find(test->key) == NULL))
	{
		cout << "\nNot found\n";
	}
	else
		cout << (*(tab->find(test->key)));
	tab->remove(test->key);
	tab->clear();
	tab->print();
}


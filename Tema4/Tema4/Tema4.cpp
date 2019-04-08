#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

//verified
#pragma  region value

#pragma region Definition
template <class T>
class value
{
protected:
	T value_;
public:
	explicit value();
	explicit value(const T val);
	value(const value& old_val);
	T get_value() const;
	template <typename T> friend std::istream& operator>>(std::istream& input, value<T>& val);
	template <typename T> friend std::ostream& operator<<(std::ostream& output, const value<T>& val);
	value<T>& operator = (const value<T> &val1);
};
#pragma endregion 

#pragma region Implementation
template <class T>
::value<T>::value()
{
	value_ = *new T();
}

template <class T>
::value<T>::value(const T val)
{
	value_ = val;
}

template <class T>
::value<T>::value(const value& old_val)
{
	value_ = old_val.value_;
}

template <class T>
T value<T>::get_value() const
{
	return  value_;
}

template <class T>
inline istream& operator>>(istream& input, value<T>& val)
{
	T val_float;
	try
	{
		input >> val_float;
		val = *new value<T>(val_float);
	}
	catch (_exception e)
	{
		cout << "Error while reading a value object!";
	}
	return input;
}

template <class T>
inline ostream& operator<<(ostream& output, const value<T>& val)
{
	output << val.get_value() << " ";
	return output;
}

template <class T>
inline bool operator == (const value<T> &val1, const value<T> &val2)
{
	return val1.get_value() == val2.get_value();
}

template <class T>
value<T> & value<T>::operator = (const value<T> &val1)
{
	value_ = val1.value_;
	return *this;
}
#pragma endregion 

#pragma  endregion 


#pragma  region node_single

#pragma region Definition
template <class T>
class node_single : public value<T>
{
protected:
	value<T> value_;
	node_single *next_nod_;
public:
	explicit node_single();
	explicit node_single(T& val);
	explicit node_single(value<T> &value);
	explicit node_single(node_single<T> &value);
	value<T> get_value() const;
	node_single<T>* get_next_nod() const;
	void set_next_nod(node_single<T>* p);
	template <typename T> friend std::istream& operator>>(std::istream& input, node_single<T>& val);
	~node_single();
};
#pragma endregion 

#pragma region Implementation
template <class T>
::node_single<T>::node_single()
{
	value_ = *new value<T>();
	next_nod_ = nullptr;
}
template <class T>
::node_single<T>::node_single(T& val)
{
	value_ = *new value<T>(val);
	next_nod_ = nullptr;
}

template <class T>
::node_single<T>::node_single(value<T>& value)
{
	value_ = value;
	next_nod_ = nullptr;
}

template <class T>
::node_single<T>::node_single(node_single<T>& value)
{
	value_ = value.value_;
	next_nod_ = value.next_nod_;
}

template <class T>
value<T> node_single<T>::get_value() const
{
	return value_;
}

template <class T>
node_single<T>* node_single<T>::get_next_nod() const
{
	return next_nod_;
}

template <class T>
void node_single<T>::set_next_nod(node_single<T>* p)
{
	next_nod_ = p;
}

template <class T>
inline istream& operator>>(istream& input, node_single<T>& val)
{
	input >> val.value_;
	return input;
}

template <class T>
inline ostream& operator<<(ostream& output, const node_single<T>& val)
{
	output << val.get_value() << " ";
	return output;
}

template <class T>
node_single<T>::~node_single()
{
	delete this->next_nod_;
}

#pragma endregion 

#pragma  endregion 

//end verified

#pragma  region node_double

#pragma region Definition
template <class T>
class node_double : public node_single<T>
{
protected:
	node_double<T> *next_nod_;
	node_double<T> *prev_nod_;
public:
	explicit node_double();
	explicit node_double(T& value);
	explicit node_double(value<T> &value);
	explicit node_double(node_single<T> &value);
	explicit node_double(node_double<T> &value);

	template <typename T> friend std::istream& operator>>(std::istream& input, node_double<T>& val);

	node_double<T>* get_prev_nod();
	node_double<T>* get_next_nod();
	void set_prev_nod(node_double<T>* p);

	template <typename T> friend class list_double;
	~node_double();
};
#pragma endregion 

#pragma region Implementation
template <class T>
::node_double<T>::node_double() : node_single<T>()
{
	this->prev_nod_ = nullptr;
}

template <class T>
::node_double<T>::node_double(node_double<T>& value) : node_single<T>(value)
{
	this->prev_nod_ = value.prev_nod_;
}

template <class T>
::node_double<T>::node_double(T& value) : node_single<T>(value)
{
	this->prev_nod_ = nullptr;
}

template <class T>
::node_double<T>::node_double(value<T>& value) : node_single<T>(value)
{
	this->prev_nod_ = nullptr;
}

template <class T>
::node_double<T>::node_double(node_single<T>& value) : node_single<T>(value)
{
	this->prev_nod_ = nullptr;
}


template <class T>
node_double<T>* node_double<T>::get_prev_nod()
{
	return  (node_double<T>*)this->prev_nod_;
}

template <class T>
node_double<T>* node_double<T>::get_next_nod()
{
	return (node_double<T>*)this->next_nod_;;
}

template <class T>
void node_double<T>::set_prev_nod(node_double<T>* p)
{
	this->prev_nod_ = p;
}

template <class T>
node_double<T>::~node_double()
{
	delete this->prev_nod_;
}


#pragma endregion 

#pragma  endregion 

#pragma  region node_double_priority

#pragma region Definition
template <class T>
class node_double_priority : public node_double<T>
{
	int priority_;
public:
	explicit node_double_priority(value<T> &value);
	friend class lista;
	int get_priority() const;
};
#pragma endregion 

#pragma region Implementation
template <class T>
::node_double_priority<T>::node_double_priority(value<T>& value) : node_double<T>(value)
{
	priority_ = 0;
}

template <class T>
int node_double_priority<T>::get_priority() const
{
	return  priority_;
}
#pragma endregion 

#pragma  endregion 



//verified
#pragma  region list_single

#pragma region Definition
template <class T>
class list_single
{
protected:
	node_single<T>* start_elem_;
	void remove_end();
	void remove_start();
public:
	list_single();
	list_single(list_single<T>& list);
	bool is_empty() const;
	node_single<T> get_item(int i);
	void add_end(T& val);
	void add_end(value<T>& val);
	void add_end(node_single<T>& val);
	void add_start(T& val);
	void add_start(value<T>& val);
	void add_start(node_single<T>& val);
	void remove(int i);
	void remove_step(int step);
	int Length();
	template <typename T> friend std::istream& operator>>(std::istream& input, list_single<T>& val);
	template <typename T> friend std::ostream& operator<<(std::ostream& output, const list_single<T>& val);

	~list_single();
};

#pragma endregion 

#pragma region Implementation
template <class T>
list_single<T>::list_single()
{
	start_elem_ = nullptr;
}

template <class T>
list_single<T>::list_single(list_single<T>& list)
{
	for (int i = 0; i < list.Length(); i++)
	{
		this->add_end(list.get_item(i).get_value());
	}
}

template <class T>
node_single<T> list_single<T>::get_item(int i)
{
	node_single<T> p = this->start_elem_;
	int count = 0;
	while (p != nullptr)
	{
		count++;
		if (count == i)
			return p;
		p = p.get_next_nod();
	}
	return NULL;
}


template <class T>
int list_single<T>::Length()
{
	if (is_empty())
		return  0;

	node_single<T>* p = this->start_elem_;
	int count = 0;
	while (p != nullptr)
	{
		count++;
		p = p->get_next_nod();
	}
	return count;
}


template <class T>
bool list_single<T>::is_empty() const
{
	return start_elem_ == nullptr;
}

template <class T>
void list_single<T>::add_end(value<T>& val)
{
	const auto d = new node_single<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		return;
	}
	auto p = this->start_elem_;
	while (p->get_next_nod() != nullptr)
		p = p->get_next_nod();

	p->set_next_nod(d);
}

template <class T>
void list_single<T>::add_end(T& val)
{
	const auto d = new node_single<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		return;
	}
	auto p = this->start_elem_;
	while (p->get_next_nod() != nullptr)
		p = p->get_next_nod();

	p->set_next_nod(d);
}

template <class T>
void list_single<T>::add_end(node_single<T>& val)
{
	const auto d = new node_single<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		return;
	}
	auto p = this->start_elem_;
	while (p->get_next_nod() != nullptr)
		p = p->get_next_nod();

	p->set_next_nod(d);
}

template <class T>
void list_single<T>::add_start(value<T>& val)
{
	const auto d = new node_single<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		return;
	}
	auto p = this->start_elem_;
	d->set_next_nod(p);
	start_elem_ = d;
}

template <class T>
void list_single<T>::add_start(T& val)
{
	const auto d = new node_single<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		return;
	}
	auto p = this->start_elem_;
	d->set_next_nod(p);
	start_elem_ = d;
}

template <class T>
void list_single<T>::add_start(node_single<T>& val)
{
	const auto d = new node_single<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		return;
	}
	auto p = this->start_elem_;
	d->set_next_nod(p);
	start_elem_ = d;
}

template <class T>
void list_single<T>::remove_end()
{
	if (is_empty())
	{
		return;
	}

	if (this->start_elem_->get_next_nod() == nullptr)
	{
		delete start_elem_;
		start_elem_ = nullptr;
		return;
	}

	node_single<T>* p = this->start_elem_;
	while (p->get_next_nod()->get_next_nod() != nullptr)
		p = p->get_next_nod();
	delete p->get_next_nod();
	p->set_next_nod(nullptr);
}

template <class T>
void list_single<T>::remove_start()
{
	if (is_empty())
	{
		return;
	}

	if (this->start_elem_->get_next_nod() == nullptr)
	{
		delete start_elem_;
		start_elem_ = nullptr;
		return;
	}

	node_single<T>* p = this->start_elem_;
	this->start_elem_ = start_elem_->get_next_nod();
	p->set_next_nod(nullptr);
	delete p;
}

template <class T>
void list_single<T>::remove_step(int step)
{
	int a = step - 1;
	while (a < Length())
	{
		remove(a);
		a += step - 1;
	}
}


template <class T>
void list_single<T>::remove(int i)
{
	if (is_empty())
		return;

	if (i >= Length())
		return;

	if (i == Length() - 1)
	{
		remove_end();
		return;
	}
	if (i == 0)
	{
		remove_start();
		return;
	}

	node_single<T>* p = this->start_elem_;
	int count = 0;
	while (p != nullptr)
	{
		count++;
		if (count == i)
			break;
		p = p->get_next_nod();
	}
	auto val = p->get_next_nod();

	p->set_next_nod(p->get_next_nod()->get_next_nod());
	val->set_next_nod(nullptr);
	delete val;
}

template <class T>
inline istream& operator>>(istream& input, list_single<T>& val)
{
	node_single<T> a;
	while (input >> a)
	{
		val.add_end(a);
	}
	return input;
}

template <class T>
inline ostream& operator<<(ostream& output, const list_single<T>& val)
{
	node_single<T>* p = val.start_elem_;
	while (p != nullptr)
	{
		output << *p;
		p = p->get_next_nod();
	}
	return output;
}

template <class T>
list_single<T>::~list_single()
{
	while (Length() > 0)
	{
		remove_end();
	}
}

#pragma endregion 

#pragma  endregion 

//end verified


#pragma  region list_double

#pragma region Definition
template <class T>
class list_double : public ::list_single<T>
{
	node_double<T>* start_elem_;
	node_double<T>* element_final_;

	list_double<T> create_copy() const;

	void delete_nod(node_double<T> * elem);

public:
	list_double()
	{
		element_final_ = nullptr;
		start_elem_ = nullptr;
	}
	void add_end(value<T> val);
	void add_end(T& val);
	void add_front(value<T> val);
	void add_front(T val);

	bool is_empty() const;
	int get_count() const;

	void delete_front();
	void delete_end();
	void delete_index(int index);
	void delete_value(const value<T>& val);
	void delete_jump(const int step);
	template <typename T> friend std::istream& operator>>(std::istream& input, list_double<T>& val);
	template <typename T> friend std::ostream& operator<<(std::ostream& output, const list_double<T>& val);

	list_double<T> operator+(list_double<T>& l) const;
	~list_double();
};

#pragma endregion 

#pragma region Implementation

template <class T>
list_double<T> list_double<T>::create_copy() const
{
	list_double l;
	auto p = this->start_elem_;
	while (p != nullptr)
	{
		l.add_end(p->value_);
		p = p->next_nod_;
	}
	return l;
}

template <class T>
void list_double<T>::delete_nod(node_double<T>* elem)
{
	if (elem->next_nod_ == nullptr)
	{
		delete_end();
		return;
	}
	if (elem->prev_nod_ == nullptr)
	{
		delete_front();
		return;
	}
	elem->prev_nod_->next_nod_ = elem->next_nod_;
	elem->next_nod_->prev_nod_ = elem->prev_nod_;
	elem->next_nod_ = nullptr;
	elem->prev_nod_ = nullptr;
	delete elem;
}

template <class T>
void list_double<T>::delete_index(int index)
{
	if (is_empty())
		return;

	if (index >= get_count())
		return;

	if (index == get_count() - 1)
	{
		delete_end();
		return;
	}
	if (index == 0)
	{
		delete_front();
		return;
	}
	int count = 0;
	auto p = start_elem_;
	while (p != nullptr)
	{
		count++;
		if (count == index)
		{
			delete_nod(p);
			break;
		}
		p = p->get_next_nod();
	}
}

template <class T>
void list_double<T>::add_end(value<T> val)
{
	const auto d = new node_double<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		element_final_ = d;
		return;
	}
	this->element_final_->next_nod_ = d;
	d->prev_nod_ = element_final_;
	this->element_final_ = d;
}

template <class T>
void list_double<T>::add_end(T& val)
{
	const auto d = new node_double<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		element_final_ = d;
		return;
	}
	element_final_->next_nod_ = d;
	d->prev_nod_ = element_final_;
	element_final_ = d;
}

template <class T>
void list_double<T>::add_front(value<T> val)
{
	const auto d = new node_double<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		element_final_ = d;
		return;
	}
	start_elem_->prev_nod_ = d;
	d->next_nod_ = start_elem_;
	start_elem_ = d;
}

template <class T>
void list_double<T>::add_front(T val)
{
	const auto d = new node_double<T>(val);
	if (is_empty())
	{
		start_elem_ = d;
		element_final_ = d;
		return;
	}
	start_elem_->prev_nod_ = d;
	d->next_nod_ = start_elem_;
	start_elem_ = d;
}

template <class T>
bool list_double<T>::is_empty() const
{
	return this->start_elem_ == nullptr;
}

template <class T>
int list_double<T>::get_count() const
{
	auto p = start_elem_;
	auto s = 0;
	while (p != nullptr)
	{
		s++;
		p = p->next_nod_;
	}
	return s;
}

template <class T>
void list_double<T>::delete_front()
{
	if (element_final_ == start_elem_)
	{
		element_final_ = nullptr;
		start_elem_ = nullptr;
		return;
	}
	const auto p = start_elem_;
	start_elem_ = start_elem_->next_nod_;
	start_elem_->prev_nod_ = nullptr;
	p->next_nod_ = nullptr;
	delete(p);
}

template <class T>
void list_double<T>::delete_end()
{
	if (element_final_ == start_elem_)
	{
		element_final_ = nullptr;
		start_elem_ = nullptr;
		return;
	}
	node_double<T> *p = element_final_;
	element_final_ = element_final_->prev_nod_;
	element_final_->next_nod_ = nullptr;
	p->prev_nod_ = nullptr;
	delete(p);
}

template <class T>
void list_double<T>::delete_value(const value<T>& val)
{
	while (start_elem_->value_ == val)
		delete_front();
	while (element_final_->value_ == val)
		delete_end();
	if (is_empty())
		return;
	auto p = start_elem_->next_nod_;
	while (p != nullptr)
	{
		if (p->value_ == val)
		{
			p = p->prev_nod_;
			delete_nod(p->next_nod_);
		}
		p = p->next_nod_;
	}
}

template <class T>
void list_double<T>::delete_jump(const int step)
{
	int a = step - 1;
	while (a < get_count())
	{
		remove(a);
		a += step - 1;
	}
}

template <class T>
list_double<T> list_double<T>::operator+(list_double<T>& l) const
{
	auto lista_n = this->create_copy();
	auto p = l.start_elem_;
	while (p != nullptr)
	{
		lista_n.add_end(p->value_);
		p = p->next_nod_;
	}
	return lista_n;
}

template <class T>
list_double<T>::~list_double()
{
	while (this->get_count() > 0)
	{
		delete_end();
	}
}

template <typename T>
std::istream& operator>>(std::istream& input, list_double<T>& val)
{
	value<T> l;
	while (input >> l)
		val.add_end(l);
	return input;
}

template <typename T>
std::ostream& operator<<(std::ostream& output, const list_double<T>& val)
{
	node_double<T> *p = val.start_elem_;
	while (p != nullptr)
	{
		output << p->get_value() << " ";
		p = p->get_next_nod();
	}
	output << std::endl;
	p = val.element_final_;
	while (p != nullptr)
	{
		output << p->get_value() << " ";
		p = p->get_prev_nod();
	}
	output << std::endl;
	return output;
}
#pragma endregion 

#pragma  endregion 
//
//#pragma  region list_double_priority - NOT IMPLEMENTED
//
//#pragma region Definition
//
//#pragma endregion 
//
//#pragma region Implementation
//
//#pragma endregion 
//
//#pragma  endregion 






int main()
{
	ifstream f("date1.in");
	list_double<float> a;
	f >> a;
	float s = 4.7;
	a.add_front(s);
	cout << a;
	a.delete_index(2);
	cout << a.get_count() << endl;

	cout << a;
	f.close();

	ifstream f1("date2.in");
	list_double<float> b;
	f1 >> b;
	float d = 4.7;
	b.add_front(d);
	cout << b;
	b.delete_index(2);
	cout << b.get_count() << endl;

	cout << b;
	f.close();

}

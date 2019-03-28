#include "pch.h"
#include <iostream>
#include <fstream>
#include "Value.h"

using namespace std;

class list_single
{
protected:
	node_single* start_elem_;
public:
	list_single()
	{
		start_elem_ = nullptr;
	}

	bool is_empty() const
	{
		return start_elem_ == nullptr;
	}

	void add(value &val)
	{
		const auto d = new node_single(val);
		if (is_empty())
		{
			start_elem_ = d;
			return;
		}
		auto p = this->start_elem_;
		while (p->get_next_nod() != nullptr)
			p = p->get_next_nod();

		p = d;
	}
};



class lista
{
	nod_double* start_elem_;
	nod_double* element_final_;
	lista create_copy() const;
	void delete_nod(nod_double * elem);
public:
	lista()
	{
		start_elem_ = nullptr;
		element_final_ = nullptr;
	}
	void add_end(value val);
	void add_front(value val);
	bool is_empty() const;
	int get_count() const;
	void delete_front();
	void delete_end();
	void delete_value(const value& val);
	void delete_jump(const int step);
	friend ostream& operator<<(ostream& output, lista& l);
	lista operator+(lista l) const;
};

bool lista::is_empty() const
{
	return this->start_elem_ == nullptr;
}

int lista::get_count() const
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



lista lista::create_copy() const
{
	lista l;
	auto p = this->start_elem_;
	while (p != nullptr)
	{
		l.add_end(p->value_);
		p = p->next_nod_;
	}
	return l;
}

void lista::add_end(value val)
{
	const auto d = new nod_double(val);
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

void lista::add_front(value val)
{
	const auto d = new nod_double(val);
	if (is_empty())
	{
		start_elem_ = d;
		element_final_ = d;
		return;
	}
	start_elem_->prev_nod_ = d;
	d->next_nod_ = element_final_;
	element_final_ = d;
}

istream& operator>>(istream& input, lista& l)
{
	value val;
	while (input >> val)
		l.add_end(val);
	return input;
}

ostream& operator<<(ostream& output, lista& l)
{
	nod_double *p = l.start_elem_;
	while (p != nullptr)
	{
		output << p->get_value() << " ";
		p = p->get_next_nod();
	}
	cout << endl;
	p = l.element_final_;
	while (p != nullptr)
	{
		output << p->get_value() << " ";
		p = p->get_prev_nod();
	}
	cout << endl;
	return output;
}

void lista::delete_end()
{
	if (element_final_ == start_elem_)
	{
		element_final_ = nullptr;
		start_elem_ = nullptr;
		return;
	}
	nod_double *p = element_final_;
	element_final_ = element_final_->prev_nod_;
	element_final_->next_nod_ = nullptr;
	delete(p);
}

void lista::delete_nod(nod_double* elem)
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

	delete elem;
}

void lista::delete_value(const value& val)
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

void lista::delete_jump(const int step)
{
	if (is_empty() || step <= 0 || step > get_count())
		return;
	if (step == get_count())
	{
		delete_end();
		return;
	}
	auto step_count = 0;
	auto p = start_elem_;
	while (p != nullptr)
	{
		step_count++;
		if (step_count == step)
		{
			p = p->prev_nod_;
			delete_nod(p->next_nod_);
			step_count = 0;
		}
		p = p->next_nod_;
	}
}

void lista::delete_front()
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
	delete(p);
}

lista lista::operator+(const lista l) const
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

int main()
{
	ifstream f1("date1.in");
	lista l1;
	f1 >> l1;

	cout << l1;
	f1.close();
	cout << endl << endl;
	ifstream f2("date2.in");
	lista l2;
	f2 >> l2;
	cout << l2;
	f2.close();
	cout << endl << endl;

	lista l = l2 + l1;
	cout << l << endl;

	/*
	//test value function
	l.delete_value(3);
	l.delete_value(1);
	l.delete_value(2);*/

	l.delete_jump(5);
	cout << l.get_count() << " - ";
	cout << l << endl;

	// delete din k in k elemente
}
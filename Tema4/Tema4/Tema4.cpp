#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

class Nod
{
private:
	Nod *prev_nod_;
	float valoare_;
	Nod *next_nod_;
public:
	Nod(float value);
	friend class lista;
	float get_valoare() { return valoare_; }
	Nod* get_next_nod() { return next_nod_; }
	Nod* get_prev_nod() { return prev_nod_; }
};

class lista
{
	Nod* element_start_;
	Nod* element_final_;
	lista create_copy();
	void delete_nod(Nod * elem);


public:
	lista()
	{
		element_start_ = NULL;
		element_final_ = NULL;
	}
	void add_end(float value);
	void add_end(float values[]);
	void add_front(float value);
	void add_front(float values[]);
	bool is_empty();
	int get_count();
	void delete_front();
	void delete_end();
	void delete_value(const float value);
	void delete_jump(const int step);
	friend ostream& operator<<(ostream& output, lista& l);
	lista operator+(lista l);
};

Nod::Nod(float value)
{
	prev_nod_ = NULL;
	valoare_ = value;
	next_nod_ = NULL;
}

bool lista::is_empty()
{
	return this->element_start_ == NULL;
}

int lista::get_count()
{
	Nod *p = element_start_;
	int s = 0;
	while (p != NULL)
	{
		s++;
		p = p->next_nod_;
	}
	return s;
}

lista lista::create_copy()
{
	lista l;
	Nod *p = this->element_start_;
	while (p != NULL)
	{
		l.add_end(p->valoare_);
		p = p->next_nod_;
	}
	return l;
}

void lista::add_end(float value)
{
	Nod* d = new Nod(value);
	if (is_empty())
	{
		element_start_ = d;
		element_final_ = d;
		return;
	}
	element_final_->next_nod_ = d;
	d->prev_nod_ = element_final_;
	element_final_ = d;
}

void lista::add_end(float values[])
{
	const int length = sizeof(values) / sizeof(float);
	for (int i = 0; i < length; i++)
		add_end(values[i]);
}

void lista::add_front(float value)
{
	Nod* d = new Nod(value);
	if (is_empty())
	{
		element_start_ = d;
		element_final_ = d;
		return;
	}
	element_start_->prev_nod_ = d;
	d->next_nod_ = element_final_;
	element_final_ = d;
}

void lista::add_front(float values[])
{
	const int length = sizeof(values) / sizeof(float);
	for (int i = 0; i < length; i++)
		add_front(values[i]);
}

istream& operator>>(istream& input, lista& l)
{
	float val;
	while (input >> val)
		l.add_end(val);
	return input;
}

ostream& operator<<(ostream& output, lista& l)
{
	Nod *p = l.element_start_;
	while (p != NULL)
	{
		output << p->get_valoare() << " ";
		p = p->get_next_nod();
	}
	cout << endl;
	p = l.element_final_;
	while (p != NULL)
	{
		output << p->get_valoare() << " ";
		p = p->get_prev_nod();
	}
	cout << endl;
	return output;
}

void lista::delete_end()
{
	if (element_final_ == element_start_)
	{
		element_final_ = NULL;
		element_start_ = NULL;
		return;
	}
	Nod *p = element_final_;
	element_final_ = element_final_->prev_nod_;
	element_final_->next_nod_ = NULL;
	delete(p);
}

void lista::delete_nod(Nod* elem)
{
	if (elem->next_nod_ == NULL)
	{
		delete_end();
		return;
	}
	if (elem->prev_nod_ == NULL)
	{
		delete_front();
		return;
	}
	elem->prev_nod_->next_nod_ = elem->next_nod_;
	elem->next_nod_->prev_nod_ = elem->prev_nod_;

	delete elem;
}

void lista::delete_value(const float value)
{
	while (element_start_->valoare_ == value)
		delete_front();
	while (element_final_->valoare_ == value)
		delete_end();
	if (is_empty())
		return;
	Nod *p = element_start_->next_nod_;
	while (p != NULL)
	{
		if (p->valoare_ == value)
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
	int step_count = 0;
	Nod *p = element_start_;
	while (p != NULL)
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
	if (element_final_ == element_start_)
	{
		element_final_ = NULL;
		element_start_ = NULL;
		return;
	}
	Nod *p = element_start_;
	element_start_ = element_start_->next_nod_;
	element_start_->prev_nod_ = NULL;
	delete(p);
}

lista lista::operator+(lista l)
{
	lista lista_n = this->create_copy();
	Nod *p = l.element_start_;
	while (p != NULL)
	{
		lista_n.add_end(p->valoare_);
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
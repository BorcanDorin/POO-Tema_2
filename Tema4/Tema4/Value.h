#pragma once

#pragma region Value
class value
{
	float float_value_;
public:
	explicit value(const float val = 0);
	value(const value& old_val);
	float get_float_value() const;
	friend std::istream& operator>>(std::istream& input, value& val);
};

inline value::value(const float val)
{
	float_value_ = val;
}

inline value::value(const value& old_val)
{
	float_value_ = old_val.float_value_;
}

inline float value::get_float_value() const
{
	return float_value_;
}

inline std::istream& operator>>(std::istream& input, value& val)
{
	float val_float;
	try
	{
		input >> val_float;
		val.float_value_ = val_float;
	}
	catch (_exception e)
	{
		std::cout << "Error while reading a value object!";
	}
	return input;
}

inline std::ostream& operator<<(std::ostream& output, const value& val)
{
    output << val.get_float_value();
	return output;
}

inline bool operator == (const value &val1 , const value &val2)
{
	return val1.get_float_value() == val1.get_float_value();
}
#pragma endregion 



#pragma region Nod single
class node_single
{
protected:
	value value_;
	node_single *next_nod_;
public:
	explicit node_single(value &value);
	friend class lista;
	value get_value() const;
	node_single* get_next_nod() const;
};

inline node_single::node_single(value &value)
{
	value_ = value;
	next_nod_ = nullptr;
}

inline value node_single::get_value() const
{
	return value_;
}

inline node_single* node_single::get_next_nod() const
{
	return next_nod_;
}
#pragma endregion 



#pragma region Nod double
class nod_double : public node_single
{
protected:
	node_single *prev_nod_;
public:
	explicit nod_double(value &value);
	friend class lista;
	node_single* get_prev_nod() const;
};

inline nod_double::nod_double(value &value): node_single(value)
{
	prev_nod_ = nullptr;
}

inline node_single* nod_double::get_prev_nod() const
{
	return prev_nod_;
}

#pragma endregion 



#pragma region Nod double priority
class nod_double_priority : public nod_double
{
	int priority_;
public:
	explicit nod_double_priority(value &value);
	friend class lista;
	int get_priority() const;
};

inline nod_double_priority::nod_double_priority(value &value) : nod_double(value)
{
	priority_ = 0;
}

inline int nod_double_priority::get_priority() const
{
	return priority_;
}

#pragma endregion 

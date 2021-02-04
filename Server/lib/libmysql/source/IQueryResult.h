#pragma once
#include<string>

class IQueryResult
{
public:
	virtual int Get_row_count()=0;
	virtual int Get_field_count() = 0;
	virtual bool Read() = 0;
	virtual void SetToBegin() = 0;
	virtual std::string field_name(int index) = 0;
	virtual int length(int n) = 0;

	virtual int get_data(int index,char *p) = 0;
	virtual int get_int(int index) = 0;
	virtual float get_float(int n)=0;
	virtual double get_double(int n)=0;
	virtual std::string  get_string(int index) = 0;
};
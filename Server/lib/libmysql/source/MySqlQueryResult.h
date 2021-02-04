#pragma once
#include<mysql.h>
#include<string>
#include<IQueryResult.h>

class MySqlQueryResult:public IQueryResult
{
public:
	MySqlQueryResult(MYSQL_RES *res, int rowcount, int fieldcount)
	{
		_mysql_res = res;
		row_count = rowcount;
		field_count = fieldcount;
		_begin = mysql_row_tell(_mysql_res);
	}
	~MySqlQueryResult()
	{

	}
	int Get_row_count()override
	{
		return row_count;
	}

	int Get_field_count()override
	{
		return field_count;
	}

	bool Read()override
	{
		_row = mysql_fetch_row(_mysql_res);
		if (_row)
		{
			mysql_fetch_lengths(_mysql_res);
			return true;
		}
		return false;
	}
	void SetToBegin()override
	{
		mysql_row_seek(_mysql_res, _begin);
	}

	std::string field_name(int n)override
	{
		return _mysql_res->fields[n].name;
	}

	int length(int n)override
	{
		return _mysql_res->lengths[n];
	}

	int get_data(int n, char *data)override
	{
		memcpy(data, _row[n], length(n));
		return length(n);
	}

	int get_int(int n)override
	{
		return _row[n] ? strtol(_row[n], 0, 10) : 0;
	}

	float get_float(int n)override
	{
		return _row[n] ? (float)atof(_row[n]) : 0;
	}

	double get_double(int n)override
	{
		return _row[n] ? atof(_row[n]) : 0;
	}

	std::string get_string(int n)override
	{
		return _row[n] ? _row[n] : "";
	}

private:
	int row_count;
	int field_count;

	MYSQL_ROW _row;
	MYSQL_ROW_OFFSET _begin;
	MYSQL_RES *_mysql_res;
};
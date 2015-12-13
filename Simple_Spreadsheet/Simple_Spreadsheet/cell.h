#include<iostream>
#include<string>
#include<limits>
#include"list.h"

#ifndef __CELL_H__
#define __CELL_H__

//Definition of class cell
class Cell{

public:
	static unsigned c;
	virtual std::string toString();
	Cell(){
		++c;
	}
	~Cell(){
		--c;
	}


};

//Definition of class NumericCell
//Derived class of Cell
class NumericCell :public Cell{
public:
	double val = 0;
	NumericCell();
	NumericCell(double v);
	std::string toString();
	double getValue();
	~NumericCell(){};

};

//Definition of class StringCell
//Derived class of Cell
class StringCell :public Cell{

public:
	std::string str;
	StringCell(std::string s);
	std::string toString();
	~StringCell(){};
};

//Definition of class FunctionCell
//Derived class of NumericCell
class FunctionCell :public NumericCell{

public:
	int offset_1, offset_2, rows, col, row;
	LList<LList<Cell*>>(*pass);
	std::string op;
	double value;
	std::string toString();

	FunctionCell(int c, int r, int row_ip, int of1, int of2, std::string type, LList<LList<Cell*>>(*sheet));

	FunctionCell(double v, int c, int r, int row_ip, int of1, int of2, std::string type);

	FunctionCell(double v);

	double mean = 0, max = 0, min = 0, sum = 0, maxh = 0, minh = 0;
	int h = 0, n = 0, w = 0, a = 0;

	void MMM(LList<LList<Cell*>>(*pass));
	~FunctionCell(){};
};

#endif
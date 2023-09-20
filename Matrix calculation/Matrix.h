#ifndef MATRIX_H
#define MATRIX_H

#include <mutex> 

class Matrix
{
private:
	int** array;
	int rows;
	int columns;
	std::mutex mtx;
public:
	Matrix();
	Matrix(int rows, int columns);
	void check_size(int rows, int columns);
	void Print_array(int rows, int columns);
	void swap_rows(int rows, int size, int sw1, int sw2);
	void swap_columns(int rows, int size, int sw1, int sw2);
	void Delete(int rows, int columns);
	int CalculateSum(int numThreads);
	~Matrix();

};




#endif

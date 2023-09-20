#include <iostream>
#include <vector>
#include <thread>
#include "Matrix.h"
#include <mutex>


	Matrix::Matrix() {
		std::cout << "2D Matrix is created: " << std::endl;
	}
	Matrix::Matrix(int rows, int columns)
	{
		this->rows = rows;
		this->columns = columns;

		array = new int* [rows];
		for (int i = 0; i < rows; ++i)
		{
			array[i] = new int[columns];
			{
				for (int j = 0; j < columns; ++j)
				{
					array[i][j] =  rand() % 110;
				}
			}
		}
	}
	void Matrix::check_size(int rows, int columns)
	{

		if (rows <= 0 || columns <= 0)
		{
			std::cout << std::endl << "The size of the rows and columns can't be under 0!!!!";
			exit(1);
		}

	}
	void Matrix::Print_array(int rows, int columns)
	{
		if (array == nullptr)
		{
			std::cout << "The array is empty!!! ";
			return;
		}
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				std::cout << array[i][j] << ' ';
			}
			std::cout << std::endl;
		}
	}
	void Matrix::swap_rows(int rows, int size, int sw1, int sw2)
	{
		if (sw1 >= rows || sw2 >= rows)
		{
			std::cout << std::endl << "You have crossed the boundaries of the matrix !!! ";
			exit(1);
		}
		else if (sw1 < 0 || sw2 < 0)
		{
			std::cout << std::endl << "You have crossed the boundaries of the matrix !!! ";
			exit(1);
		}
		std::cout << "New matrix with swappes rows is:_ " << std::endl;

		for (int j = 0; j < columns; ++j)
		{
			int temp = array[sw1][j];
			array[sw1][j] = array[sw2][j];
			array[sw2][j] = temp;
		}
		Print_array(rows, columns);

	}

	void Matrix::swap_columns(int rows, int size, int sw1, int sw2)
	{

		if (sw1 >= columns || sw2 >= columns)
		{
			std::cout << std::endl << "You have crossed the boundaries of the matrix !!! ";
			exit(1);
		}
		else if (sw1 < 0 || sw2 < 0)
		{
			std::cout << std::endl << "You have crossed the boundaries of the matrix !!! ";
			exit(1);
		}
		std::cout << "New matrix with swappes columns is:_ " << std::endl;

		for (int i = 0; i < rows; ++i)
		{
			int temp = array[i][sw1];
			array[i][sw1] = array[i][sw2];
			array[i][sw2] = temp;
		}
		Print_array(rows, columns);
	}

	void Matrix::Delete(int rows, int columns)
	{
		for (int i = 0; i < rows; ++i)
		{
			delete[] array[i];
		}
		delete[] array;
		array = nullptr;
	}
	Matrix::~Matrix()
	{
		std::cout << "Destructor is called:_ ";
		Delete(rows, columns);
	}

	int Matrix::CalculateSum(int numThreads)
	{
		std::vector<std::thread> m_threads(numThreads);
		std::vector<int>PartialSum(numThreads, -1);
		auto calcPartialSum = [&](int thread_index) {
			int startRow = thread_index * (rows / numThreads);
			int endRow = (thread_index == numThreads - 1) ? rows : (thread_index + 1) * (rows / numThreads);
			int Psum = 0;
			for (int i = startRow; i < endRow; ++i) {
				for (int j = 0; j < columns; ++j) {
					Psum += array[i][j];

					std::lock_guard<std::mutex> lock(mtx);
					PartialSum[thread_index] = Psum;
				}
			}
		};

		for (int i = 0; i < numThreads; ++i) {
			m_threads[i] = std::thread(calcPartialSum, i);
		}
		for (int i = 0; i < numThreads; ++i) {
			m_threads[i].join();
		}
		int totalSum = 0;
		for (int sum : PartialSum) {
			totalSum += sum;
		}
		return totalSum;
	};
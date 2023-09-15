#include <iostream>
#include <thread>

unsigned int Fib(int n)
{
	if (n <= 1)
	{
		return 1;
	}
	else
	{
		return Fib(n - 1) + Fib(n - 2);
	}
}
unsigned int Factorial(int n)
{
	if (n <= 1)
	{
		return 1;
	}
	else
	{
		return Factorial(n - 1) * n;
	}
}

void calculate(int n)
{
	unsigned int fibonachi = Fib(n);
	unsigned int factorial = Factorial(n);
	std::cout << "Factorial(" << n << ")=" << factorial<<std::endl;
	std::cout << "Fibonachi(" << n << ")=" << fibonachi <<std::endl;

}
int main(int argc, char** argv)
{
	int number;
	std::cout << "Kindly enter the number _";
	std::cin >> number;
	std::cout << std::endl;

	std::thread calcThread(calculate, number);
	calcThread.join();
	return 0;

}
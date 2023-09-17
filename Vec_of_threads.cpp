#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <mutex>

std::mutex printMutex;

unsigned int Fibonachi(int a) {
	if (a <= 1) {
		return a;
	}
	else {
		unsigned int k = 0, b = 1;
		for (int i = 2; i <= a; ++i) {
			unsigned int temp = k + b;
			k = b;
			b = temp;
		}
		return b;
	}
}
void calculate(int n)
{
	unsigned int fibonachi = Fibonachi(n);
	printMutex.lock();
	std::cout << "Fibonachi(" << n << ")=" << fibonachi << std::endl;
	printMutex.unlock();

}

int main(int argc, char** argv)
{
	int threads_num = 20;
	std::vector<std::thread>thread_vec;
	for (int i = 0; i < threads_num; ++i)
	{
		int number = std::rand() % 101;
		thread_vec.push_back(std::thread(calculate, number));
		
	}
	
	for (auto& thread : thread_vec)
	{
		thread.join();
	}

	return 0;
}
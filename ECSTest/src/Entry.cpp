#include <iostream>
#include "Example.h"
int main(int argc, char *argv[])
{
	Example exec(800, 600); //224x288
	exec.Run();
	std::cin.get();
	return 0;
}
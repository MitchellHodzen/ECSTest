#include <iostream>
#include "kecs/KECS.h"
#include "Example.h"
int main(int argc, char *argv[])
{
	KECS ecs;
	Example exec(800, 600);
	exec.Run();
	std::cin.get();
	return 0;
}
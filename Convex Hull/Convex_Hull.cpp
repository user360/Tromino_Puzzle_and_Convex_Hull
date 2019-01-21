#include "QuickHull.h"

#include <stdlib.h>
#include <algorithm>

int main(int argc, char*argv[])
{
	if (argc != 2)
	{
		printf("Wrong number of arguments\n");
		return -1;
	}
	FILE *f = NULL;
	f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("File does not exist!\n");
		return -2;
	}

	std::vector<Point> input;
	size_t size;
	fscanf(f, "%zd", &size);


	for (size_t i = 0; i < size; i++)
	{
		Point p;
		p.color = 0;
		fscanf(f, "%f", &p.x);
		fscanf(f, "%f", &p.y);
		input.push_back(p);
	}
	fclose(f);

	std::sort(input.begin(), input.end());

	QuickHull qh(input);
	qh.run();

	return 0;
}
#include <stdlib.h>

#include "TrominoPuzzle.h"

int main(int argc, char*argv[])
{
	if (argc != 4)
	{
		printf("Wrong number of arguments!\n");
		return 1;
	}

	int N = atoi(argv[1]);
	int r = atoi(argv[2]);
	int c = atoi(argv[3]);

	TrominoPuzzle puzzle(N, c, r);
	puzzle.print();
	puzzle.solve();
	puzzle.print();
	return 0;
}

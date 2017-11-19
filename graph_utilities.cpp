#include <stdio.h>
#include <vector>
#include <algorithm>

class node
{
public:
	vector<edge> neighbors;
}

class edge
{
public:
	bool is_directed;
	int weight;
}

class graph
{
public:
	int size;
	vector<node> nodes;
}

int main()
{
	printf("Hello world\n");
	return 0;
}
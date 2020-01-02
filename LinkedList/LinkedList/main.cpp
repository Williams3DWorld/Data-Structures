#include "LinkedList.h"
#include <string>
using namespace ds;


int main(int argc, char* argv[])
{
	/* Basic node struct */
	struct node
	{
		int		data;
	};

	stack::stack_array<int> sa(6);

	sa.push( 0 );
	sa.push( 2 );
	sa.push( 3 );
	sa.push( 4 );
	sa.push( 7 );
	sa.push( 20 );

	sa.pop();

	for (unsigned i = 0; i < sa.size(); ++i)
		std::cout << sa.at(i) << "\n";

	system("PAUSE");

	return EXIT_SUCCESS;
}
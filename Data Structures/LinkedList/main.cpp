#include "DataStructures.h"
#include <string>


using namespace data_structures;


// Main entry point
int main(int argc, char* argv[])
{
	/* Basic node struct */
	struct node
	{
		int	data;
	};

	stack<node*> sa;

	sa.push_stack(new node{ 0 });
	sa.push_stack(new node{ 1 });
	sa.push_stack(new node{ 2 });
	sa.push_stack(new node{ 3 });
	sa.push_stack(new node{ 4 });

	for (unsigned i = 0; i < sa.size(); ++i)
		std::cout << sa.at(i)->data << "\n";

	sa.clear();

	sa.push_stack(new node{ 2 });
	sa.push_stack(new node{ 3 });
	sa.pop_stack();

	for (unsigned i = 0; i < sa.size(); ++i)
		std::cout << sa.at(i)->data << "\n";

	std::cout << "Size of array: " << sa.size() << "\n\n";

	system("PAUSE");

	return EXIT_SUCCESS;
}
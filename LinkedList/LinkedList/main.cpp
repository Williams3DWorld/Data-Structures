#include "LinkedList.h"

int main(int argc, char* argv[])
{
	/* Basic node struct */
	struct node
	{
		int		data;
		node*	next;
	};

	list::linkedlist_s<node> list;

	list.emplace_back(1);
	list.emplace_back(36);
	list.emplace_back(42);

	list.display();
	std::cout << "\nSize: " << list.size() << "\n";

	system("PAUSE");

	return EXIT_SUCCESS;
}
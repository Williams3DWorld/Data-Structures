#include "LinkedList.h"

int main(int argc, char* argv[])
{
	/* Basic node struct */
	struct node_s
	{
		int		data;
		node_s*	next;
	};

	/* Basic node struct */
	struct node_d
	{
		int		data;
		node_d* next;
		node_d* prev;
	};

	list::linkedlist_d<node_d> list;

	list.emplace_front(new node_d{ 4, nullptr, nullptr });
	list.emplace_front(new node_d{ 6, nullptr, nullptr });
	list.emplace_front(new node_d{ 8, nullptr, nullptr });

	list.make_circular();

	std::cout << "Tail next: " << list.get(2)->next->data << "\n";
	std::cout << "Head prev: " << list.get(0)->prev->data << "\n";

	list.display(true);
	std::cout << "\nSize: " << list.size() << "\n";

	system("PAUSE");

	return EXIT_SUCCESS;
}
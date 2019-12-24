#include <iostream>


struct node
{
	int data;
	node* next;
};

class llist
{
private:
	node *head, *tail;

public:
	llist()
	{
		head = nullptr;
		tail = nullptr;
	}

	void emplace_back(int value)
	{
		node* temp = new node;
		temp->data = value;
		temp->next = nullptr;

		if (head == nullptr)
		{
			head = temp;
			tail = temp;
			temp = nullptr;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}

	void display()
	{
		if (!head)
			return;

		node* temp(head);
		while (temp != nullptr)
		{
			std::cout << temp->data << "\t";
			temp = temp->next;
		}

		std::cout << "\n";
	}
};

int main(int argc, char* argv[])
{
	llist list;

	list.emplace_back(1);
	list.emplace_back(36);
	list.emplace_back(3);
	list.emplace_back(27);

	list.display();


	system("PAUSE");

	return EXIT_SUCCESS;
}
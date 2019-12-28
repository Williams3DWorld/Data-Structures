#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <iostream>

namespace list
{
	/* A singly linked list data structure */
	template <class T>
	class linkedlist_s
	{
	private:
		size_t	_size;
		T*		_head;
		T*		_tail;

	public:
		linkedlist_s() 
		{
			_size = 0;
			_head = nullptr;
			_tail = nullptr;
		}

		~linkedlist_s()
		{
			for (unsigned i = 0; i < _size; ++i)
				pop_back();
		}

		/* Emplace a new node to the front of list */
		void emplace_front(int value)
		{
			T* temp = new T;	// Create temp node
			temp->data = value;		// Assign data to new node
			temp->next = _head;		// Assign temp's next node to _head
			_head = temp;			// Assign _head to temp

			++_size;				// Increment size of container
		}

		/* Emplace a new node to the back of list */
		void emplace_back(int value)
		{
			T* temp = new T;	// Create temp node
			temp->data = value;		// Assign parsed data to new node
			temp->next = nullptr;	// Assign nullptr to the last node

			if (_head == nullptr)	// Check if _head node doesn't exist
			{
				_head = temp;		// Assign _head to temp
				_tail = temp;		// Assign _tail to temp
				temp = nullptr;		// Set temp to nullptr
			}
			else					// If _head node DOES exist
			{
				_tail->next = temp;	// Set _tail's next to temp (as we currently have more than one node)
				_tail = temp;		// Position _tail to temp in the list
			}

			++_size;				// Increment size of container
		}

		/* Insert between start + 1, and end - 1 */
		void insert(unsigned pos, int value)
		{
			if (pos >= _size)		// If position index is greater than size of container...
			{
				emplace_back(value);	// Assign node to the back of list
				return;
			}
			else if (pos <= 0)		// Else if position index is less / equal to zero...
			{
				emplace_front(value);	// Assign node to the front of container
				return;
			}

			T* pre = new T;			// Previous node
			T* cur = new T;			// Current node
			T* temp = new T;		// Temporary node

			cur = _head;				// Assign current node to the _head before traversing
			for (unsigned i = 0; i < pos; ++i)
			{
				pre = cur;			// Assign previous node to current to keep track of last node
				cur = cur->next;	// Assign current node to current's next node to create a gap
			}

			temp->data = value;		// Assign parsed data to temp node
			pre->next = temp;		// Assign previous's next node to temp, creating the first link
			temp->next = cur;		// Assign temp's next node to current to create the second link

			++_size;				// Increment size of container
		}

		/* Deletes the first node in the list */
		void pop_front()
		{
			if (!_head)				// Check if head is equal to null
				return;
			else if (_size == 1)	// If size is equal to 1
			{
				_head = nullptr;	// Set head node to nullptr
				--_size;			// Decrement container size
				return;
			}

			T* temp = new T;	// Create a temp node
			temp = _head;			// Assign temp to head (the first node in list)
			_head = _head->next;	// Shift the head up to the next position in list
			delete temp;			// Delete the first node in list

			--_size;				// Decrement size of container
		}

		/* Deletes the last node in the list */
		void pop_back()
		{
			if (!_head)				// Check if head is equal to null
				return;
			else if (_size == 1)	// If size is equal to 1
			{
				_head = nullptr;	// Set head to be nullptr
				--_size;			// Decrement container size
				return;
			}

			T* cur = new T;	// Create a current node
			T* pre = new T;	// Create a previous node

			cur = _head;			// Assign current to head (ready for traversing)
			while (cur->next != nullptr)
			{
				pre = cur;			// Assign previous node to current
				cur = cur->next;	// Assign current to one node ahead in list
			}

			_tail = pre;			// Assign tail node to the previous node
			pre->next = nullptr;	// Assign previous's next node to null as it's the end of list
			delete cur;				// Delete current (originally pointed to the last node)

			--_size;				// Decrement size of container
		}

		/* Deletes a node between positions: start + 1 and end - 1 */
		void erase(unsigned pos)
		{
			if (!_head)				// Check if head is equal to null
				return;
			else if (pos <= 0)		// If position is less or equal to first element
			{
				pop_front();		// pop front as normal
				return;
			}
			else if (pos >= _size)	// If position is greater or equal to last element
			{
				pop_back();			// pop back as normal
				return;
			}

			T* cur = new T;			// Create current node
			T* pre = new T;			// Create previous node

			cur = _head;			// Assign current to the head node

			for (unsigned i = 0; i < pos; ++i)
			{
				pre = cur;			// Assign previous node to the current node
				cur = cur->next;	// Assign current node to the current's next node to get next in position
			}

			pre->next = cur->next;	// Assign previous's next node to the current's next node, automatically eliminating the node in-between
			delete cur;				// Delete current (originally pointed to the last node)

			--_size;				// Decrement size of container
		}

		/* Returns a node from list using a position index */
		T* get(unsigned pos)
		{
			if (!_head)
				return nullptr;
			else if (pos <= 0)
				return _head;
			else if (pos >= _size)
				return _tail;

			T* cur = _head;

			for (unsigned i = 0; i < pos; ++i)
				cur = cur->next;

			return cur;
		}

		T* head() { return _head; }
		T* tail() { return _tail; }
		size_t& size() { return _size; }

		void display()
		{
			if (!_head)
				return;

			T* temp(_head);
			while (temp != nullptr)
			{
				printf("%d\t", temp->data);
				temp = temp->next;
			}
		}
	};
}

#endif
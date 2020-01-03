#ifndef __DATA_STRUCTURE_H__
#define __DATA_STRUCTURE_H__

#include <iostream>

/* Data structure namespace */
namespace data_structures
{
	/* A stack class that stores an array in LIFO order */
	template <class T>
	class stack
	{
	private:
		size_t	_size;
		T* _array;

	public:
		stack() : _size(0), _array(nullptr) {}
		stack(unsigned size, T* data)
		{
			_size = size;
			_array = (T*)realloc(_array, sizeof(T) * _size);

			for (unsigned i = 0; i < size; ++i)
				_array[i] = data;
		}

		~stack()
		{
			if (_array)
				delete _array;
		}

		size_t& size() { return _size; }

		inline void push_stack(T data)
		{
			++_size;
			_array = (T*)realloc(_array, sizeof(T) * _size);
			_array[_size - 1] = data;

		}

		inline void pop_stack()
		{
			if (_array)
			{
				--_size;
				_array = (T*)realloc(_array, sizeof(T) * _size);
			}
		}

		inline void clear()
		{
			_size = 0;
			if (_array)
			{
				delete _array;
				_array = nullptr;
			}
		}

		inline T at(unsigned id)
		{
			return _array[id];
		}
	};

	namespace linkedlist
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

			linkedlist_s(unsigned size, T** nodes)
			{
				if (!nodes[0] || size <= 0)
				{
					printf("LINKEDLIST_S ERROR::NODE ARRAY IS EQUAL TO NULL!\n");
					return;
				}

				_size = size;

				/* Assign head and tail to first node */
				_head = nodes[0];		// Assign _head to temp
				_tail = nodes[0];		// Assign _tail to temp
				nodes[0] = nullptr;		// Set temp to nullptr (as head and tail already points to buffer)

				/* Emplace back the rest of nodes */
				for (unsigned i = 1; i < _size; ++i)	// Start from 1 as we've already already initialised head node
				{
					nodes[i]->next = nullptr;	// Assign nullptr to the last node
					_tail->next = nodes[i];		// Set _tail's next to temp (as we currently have more than one node)
					_tail = nodes[i];			// Reposition _tail to temp in the list
				}
			}

			~linkedlist_s()
			{
				if (_head)
				{
					T* temp = _head;
					while (temp != _tail)
						temp = temp->next;

					temp->next = nullptr;	// Detach loop (if there is one)

					for (unsigned i = 0; i < _size; ++i)
						pop_back();
				}
			}

			/* Emplace a new node to the front of list */
			void emplace_front(T* node)
			{
				node->next = _head;		// Assign temp's next node to _head
				_head = node;			// Assign _head to temp

				T* temp = _head;
				while (temp->next != nullptr)
					temp = temp->next;

				_tail = temp;

				++_size;				// Increment size of container
			}

			/* Emplace a new node to the back of list */
			void emplace_back(T* node)
			{
				node->next = nullptr;	// Assign nullptr to the last node

				if (_head == nullptr)	// Check if _head node doesn't exist
				{
					_head = node;		// Assign _head to temp
					_tail = node;		// Assign _tail to temp
					node = nullptr;		// Set temp to nullptr
				}
				else					// If _head node DOES exist
				{
					_tail->next = node;	// Set _tail's next to temp (as we currently have more than one node)
					_tail = node;		// Position _tail to temp in the list
				}

				++_size;				// Increment size of container
			}

			/* Insert between start + 1, and end - 1 */
			void insert(unsigned pos, T* node)
			{
				if (pos >= _size)		// If position index is greater than size of container...
				{
					emplace_back(node);	// Assign node to the back of list
					return;
				}
				else if (pos <= 0)		// Else if position index is less / equal to zero...
				{
					emplace_front(node);	// Assign node to the front of container
					return;
				}

				T* pre = new T;			// Previous node
				T* cur = new T;			// Current node

				cur = _head;				// Assign current node to the _head before traversing
				for (unsigned i = 0; i < pos; ++i)
				{
					pre = cur;			// Assign previous node to current to keep track of last node
					cur = cur->next;	// Assign current node to current's next node to create a gap
				}

				pre->next = node;		// Assign previous's next node to temp, creating the first link
				node->next = cur;		// Assign temp's next node to current to create the second link

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

			/* Make circular singly linked list */
			void make_loop()
			{
				_tail->next = _head;
			}

			/* Revert back to an singly linked list with a terminal end point */
			void detach_loop()
			{
				_tail->next = nullptr;
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

			void display(bool loop)
			{
				if (!_head)
					return;

				T* temp(_head);

				if (loop)
				{
					do
					{
						printf("%d\t", temp->data);
						temp = temp->next;
					} while (temp != _head);
				}
				else
				{
					while (temp != nullptr)
					{
						printf("%d\t", temp->data);
						temp = temp->next;
					}
				}
			}
		};

		/* A doubly linked list data structure */
		template <class T>
		class linkedlist_d
		{
		private:
			size_t	_size;
			T* _head;
			T* _tail;

		public:
			linkedlist_d()
			{
				_size = 0;
				_head = nullptr;
				_tail = nullptr;
			}

			linkedlist_d(unsigned size, T** nodes)
			{
				if (!nodes[0] || size <= 0)
				{
					printf("LINKEDLIST_D ERROR::NODE ARRAY IS EQUAL TO NULL!\n");
					return;
				}

				_size = size;

				/* Assign head and tail to first node */
				_head = nodes[0];		// Assign _head to temp
				_tail = nodes[0];		// Assign _tail to temp
				nodes[0] = nullptr;		// Set temp to nullptr (as head and tail already points to buffer)

				/* Emplace back the rest of nodes */
				for (unsigned i = 1; i < _size; ++i)	// Start from 1 as we've already already initialised head node
				{
					nodes[i]->next = nullptr;	// Assign nullptr to the last node
					_tail->next = nodes[i];		// Set _tail's next to temp (as we currently have more than one node)
					nodes[i]->prev = _tail;		// Assign new node's previous to the last node (tail's original position)
					_tail = nodes[i];			// Reposition _tail to temp in the list
				}
			}

			~linkedlist_d()
			{
				if (_head)
				{
					T* temp = _head;
					while (temp != _tail)
						temp = temp->next;

					temp->next = nullptr;	// Detach loop (if there is one)

					for (unsigned i = 0; i < _size; ++i)
						pop_back();
				}
			}

			/* Emplace a new node to the front of list */
			void emplace_front(T* node)
			{
				if (_head)
					_head->prev = node;		// Assign head's previous to new node

				node->next = _head;		// Assign new node's next node to _head (as we're attaching to the front)
				_head = node;			// Assign _head to new node (as this is now our new node)

				T* temp = _head;
				while (temp->next != nullptr)
					temp = temp->next;

				_tail = temp;

				++_size;				// Increment size of container
			}

			/* Emplace a new node to the back of list */
			void emplace_back(T* node)
			{
				node->next = nullptr;	// Assign nullptr to the last node

				if (_head == nullptr)	// Check if _head node doesn't exist
				{
					_head = node;		// Assign _head to temp
					_tail = node;		// Assign _tail to temp
					node = nullptr;		// Set temp to nullptr
				}
				else					// If _head node DOES exist
				{
					_tail->next = node;	// Set _tail's next to temp (as we currently have more than one node)
					node->prev = _tail; // Assign new node's previous to the last node
					_tail = node;		// Position _tail to temp in the list
				}

				++_size;				// Increment size of container
			}

			/* Insert between start + 1, and end - 1 */
			void insert(unsigned pos, T* node)
			{
				if (pos >= _size)		// If position index is greater than size of container...
				{
					emplace_back(node);	// Assign node to the back of list
					return;
				}
				else if (pos <= 0)		// Else if position index is less / equal to zero...
				{
					emplace_front(node);	// Assign node to the front of container
					return;
				}

				T* pre = new T;			// Previous node
				T* cur = new T;			// Current node

				cur = _head;				// Assign current node to the _head before traversing
				for (unsigned i = 0; i < pos; ++i)
				{
					pre = cur;			// Assign previous node to current to keep track of last node
					cur = cur->next;	// Assign current node to current's next node to create a gap
				}

				node->prev = pre;
				pre->next = node;		// Assign previous's next node to temp, creating the first link
				node->next = cur;		// Assign temp's next node to current to create the second link

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

				T* temp = new T;		// Create a temp node
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

				cur->prev = pre->next;	// Assign current's previous node to the previous's next node
				pre->next = cur->next;	// Assign previous's next node to the current's next node, automatically eliminating the node in-between
				delete cur;				// Delete current (originally pointed to the last node)

				--_size;				// Decrement size of container
			}

			/* Creates a circular doubly list by attaching the tail's next node to the head */
			void make_circular()
			{
				_tail->next = _head;
				_head->prev = _tail;
			}

			/* Make circular doubly linked list */
			void make_loop()
			{
				_tail->next = _head;
			}

			/* Revert back to an doubly linked list with a terminal end point */
			void detach_loop()
			{
				_tail->next = nullptr;
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

			void display(bool loop)
			{
				if (!_head)
					return;

				T* temp(_head);

				if (loop)
				{
					do
					{
						printf("%d\t", temp->data);
						temp = temp->next;
					} while (temp != _head);
				}
				else
				{
					while (temp != nullptr)
					{
						printf("%d\t", temp->data);
						temp = temp->next;
					}
				}
			}
		};
	}
}

#endif
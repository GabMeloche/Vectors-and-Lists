#ifndef __LIST__
#define __LIST__
#include <Iterator.h>


template <typename T, class Allocator>
class List
{
public:
	struct t_listData
	{
		T* m_data;
		t_listData* next;
		t_listData* prev;
		t_listData() 
		{
			m_data = nullptr;
			next = nullptr;
			prev = nullptr;
		}
	};
private:
	t_listData* head;
	t_listData* tail;
	size_t m_size;
public:

	List()
	{
		head = nullptr;
		tail = nullptr;
		m_size = 0;
	}

	~List() 
	{
		t_listData* currData = head;
		while (currData->next != nullptr)
		{
			//delete currData->prev;
			Allocator().deallocate(currData->m_data, 1);
			currData = currData->next;
		}
		Allocator().deallocate(tail->m_data, 1);
	}

	List(const List& other) {}

	void push_back(const T& newElement)
	{
		t_listData* newData = new t_listData();
		newData->m_data = Allocator().allocate(1);
		Allocator().construct(newData->m_data + m_size, newElement);
		
		if (head == nullptr && tail == nullptr)
		{
			head = newData;
			tail = newData;
		}
		else
		{
			tail->next = newData;
			newData->prev = tail;
			tail = newData;

		}
		++m_size;
	}

	size_t size() {return m_size;}

	t_listData* begin() {return head;}

	t_listData* end() {return tail;}
};

#endif

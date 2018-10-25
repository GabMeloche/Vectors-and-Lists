#ifndef __VECTOR__
#define __VECTOR__
#include <iostream>

template <typename T, class Allocator>
class Vector
{
private:
	Allocator m_allocator;
	T* m_data;
	int m_size;
	int m_capacity;
public:
	Vector()
	{
		m_data = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	~Vector()
	{
		m_allocator.deallocate(m_data, m_capacity);
	}
	Vector(const Vector& other)
	{
	}

	size_t capacity()
	{
		return m_capacity;
	}
	size_t size()
	{
		return m_size;
	}

	void push_back(const T& newElement)
	{
		T* new_data = m_data;

		if (m_capacity == 0)
		{
			++m_capacity;
			m_data = m_allocator.allocate(m_capacity);
			m_data[0] = newElement;
		}
		else
		{
			if (m_size % 2 != 1 || m_size == 1)
			{
				m_capacity *= 2;
				m_data = m_allocator.allocate(m_capacity);
				
				for (int i = 0; i < m_size; i++)
					m_data[i] = new_data[i];
				
				m_data[m_size] = newElement;
				m_allocator.deallocate(new_data, size());
			}
			else
			{
				m_data[m_size] = newElement;
			}
		}
		++m_size;
	}

	T& operator[](long int i)
	{
		return this->m_data[i];
	}
};

#endif

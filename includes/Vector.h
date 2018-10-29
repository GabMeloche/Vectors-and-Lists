#ifndef __VECTOR__
#define __VECTOR__
#include <iostream>
#include <cassert>

template <typename T, class Allocator>
class Vector
{
private:
	T* m_data;
	unsigned long int m_size;
	unsigned long int m_capacity;
public:
	Vector()
	{
		m_data = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	~Vector()
	{
		for (size_t i = 0; i < m_size; i++)
		{
			Allocator().destroy(m_data + i);
		}
		if (m_capacity != 0)
			Allocator().deallocate(m_data, m_capacity);
	}

	Vector(const Vector& other)
	{
		m_data = other.m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;
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
		if (m_capacity == 0)
		{
			++m_capacity;
			m_data = Allocator().allocate(m_capacity);
			Allocator().construct(m_data, newElement);
		}
		else if (m_capacity == m_size)
		{
			size_t oldCapacity = m_capacity;
			m_capacity *= 2;
			T* new_data; 
			Allocator().construct(&new_data, m_data);
			//Allocator().construct(new_data + m_size, newElement);
			new_data = Allocator().allocate(m_capacity);
			Allocator().construct(new_data + m_size, newElement);

			for (size_t i = 0; i < m_size; i++)
			{
				Allocator().construct(new_data + i, m_data[i]);
			}
			
			//Allocator().construct(m_data + m_size, newElement);

			for (size_t i = 0; i < m_size; i++)
			{
				Allocator().destroy(m_data + i);
			}
			Allocator().deallocate(m_data, oldCapacity);
			m_data = new_data;
		}
		else
			Allocator().construct(m_data + m_size, newElement);
		
		++m_size;
	}

	void reserve(unsigned long int n)
	{//max_size to do
		if (n > m_capacity)
		{
			m_capacity = n;		
			m_data = Allocator().allocate(n);
		}
	}

	T& operator[](long int i)
	{
		return this->m_data[i];
	}
};

#endif

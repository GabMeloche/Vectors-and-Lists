#ifndef __VECTOR__
#define __VECTOR__
#include <iostream>
#include <cassert>

template <typename T, class Allocator>
class Vector
{
private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;
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
		m_size = other.m_size;
		m_capacity = 0;
		reserve(other.m_capacity);
		for (size_t i = 0; i < m_capacity; i++)
			Allocator().construct(m_data + i, other.m_data[i]);
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
			new_data = Allocator().allocate(m_capacity);
			Allocator().construct(new_data + m_size, newElement);

			for (size_t i = 0; i < m_size; i++)
			{
				Allocator().construct(new_data + i, m_data[i]);
			}
			
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

	void reserve(size_t n)
	{
		if (n > m_capacity)
		{
			m_capacity = n;		
			m_data = Allocator().allocate(n);
		}
	}

	void clear()
	{
		for (size_t i = 0; i < m_size; i++)
		{
			Allocator().destroy(m_data + i);
		}
		m_size = 0;
	}

	void resize(size_t n, T* c_data = nullptr)
	{
		if (n == m_size)
			return;

		if (n > m_size)
		{
			reserve(n);
			if (c_data == nullptr)
			{
				for (size_t i = m_size; i < n; i++)
					Allocator().construct(m_data + i);
			}
			else
			{
				for (size_t i = m_size; i < n; i++)
                                        Allocator().construct(m_data + i, c_data[i]);
			}
		}
		else
		{
			for (size_t i = n; i < m_size; i++)
				Allocator().destroy(m_data + i);
		}
		m_size = n;
	}

	T& operator[](long int i)
	{
		return this->m_data[i];
	}

	Vector& operator=(const Vector& other)
	{
		clear();
		resize(other.m_size, other.m_data);
		return *this;
	}
};

#endif

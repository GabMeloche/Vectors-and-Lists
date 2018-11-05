#ifndef __ITERATOR__
#define __ITERATOR__

template<typename T>
class Iterator
{
private:
	T* m_data;
public:
	Iterator(T* data)
	{
		m_data = data;
	}
	~Iterator() = default;

	bool operator!=(T* other)
	{
		return m_data != other->m_data;
	}

	T& operator*() 
	{
		return *m_data;
	}

	Iterator& operator++(int)
	{
		++m_data;
		return *this;
	}


};

#endif

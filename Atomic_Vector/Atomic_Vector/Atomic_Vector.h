#ifndef __atomic_vector_h__
#define	__atomic_vector_h__

#include <thread>
#include <mutex>
#include <iostream>
using namespace std;

class Exceptions
{
protected:
	int num;
	char* str;
public:
	virtual void display() = 0;
	
};

class ExceptionsWithVectors : public Exceptions
{
public:
	ExceptionsWithVectors(int _num, char* _str)
	{
		this->num = _num;
		this->str = _str;
	}

	void display()
	{
		std::cout << "ExceptionsVector - #" << num << ": " << str << std::endl;
	}
};

template <class T> class AtomicVector
{
private:
	T* _begin; //указатель на начало вектора
	size_t _size; //размер вектора
	size_t _capacity; //вместимость выделенной области памяти
	std::recursive_mutex mutex;//mutex для блокировки чтения записи
	
public:
	AtomicVector() = default;
	AtomicVector(size_t _capacity) : _capacity(_capacity) 
	{
		_size = 0;
		_begin = new T[_capacity];
	};
	
	AtomicVector(const AtomicVector<T> &other)
	{
		_size = other._size;
		_capacity = other._capacity;
		_begin = new T[_capacity];
		for (size_t i = 0; i < _size; i++)
			_begin[i] = other._begin[i];
	}

	AtomicVector(AtomicVector<T> &&other)
	{
		swap(*this, other);
	}
	
	~AtomicVector()
	{
		delete[] _begin;
	}
	//получение указателя на первый элемент
	T* begin() 
	{
		return _begin;
	}
	//получение указателя на элемент после последнего
	T* end()
	{
		return (_begin == nullptr) ? (nullptr) : (_begin + _size);
	}

	size_t size()
	{
		return _size;
	}

	size_t capacity()
	{
		return _capacity;
	}
	//возвращает первый элемент вектора
	T front()
	{
		try
		{
			if (_begin == nullptr)
				throw ExceptionsWithVectors(2, (char*) "Vector did not initializing yet!");
			return *_begin;
		}

		catch (ExceptionsWithVectors exp)
		{
			exp.display();
		}
		
	}
	//возвращает последний элемент вектора
	T back()
	{
		try
		{
			if (end() == nullptr)
				throw ExceptionsWithVectors(2, (char*) "Vector did not initializing yet!");
			return *(end()-1);
		}
		catch (ExceptionsWithVectors exp) 
		{
			exp.display();
		}
	}

	bool empty()
	{
		return _size == NULL;
	}

	void push_back(T _data)
	{
		mutex.lock();
		if (_capacity <= _size)
			reserve(1);
		_begin[_size] = _data;
		_size++;
		mutex.unlock();

	}

	void pop_back()
	{
		resize(_size - 1);
	}

	void resize(size_t count)
	{
		mutex.lock();
		if (_capacity == count)
		{
			mutex.unlock();
			return;
		}
		AtomicVector<T> temp(count);
		for (size_t i = 0; i < count && i < _size; i++)
		{
			temp[i] = _begin[i];
		}
		swap(*this, temp);
		mutex.unlock();
	}

	void resize(size_t count, T _data)
	{
		mutex.lock();
		if (_capacity == count)
		{
			mutex.unlock();
			return;
		}
		AtomicVector<T> temp(count);
		temp.assign(_data);
		for (size_t i = 0; (i < count) && (i < _size); i++)
			temp[i] = _begin[i];
		swap(*this, temp);
		mutex.unlock();

	}

	void assign(T data)
	{
		mutex.lock();
		for (size_t i = 0; i < _capacity; i++) 
			_begin[i] = data;
		_size = _capacity;
		mutex.unlock();
	}

	void shrink_to_fit()
	{
		mutex.lock();
		resize(_size);
		mutex.unlock();
	}

	void reserve(size_t count)
	{
		mutex.lock();
		resize(_capacity + count);
		mutex.unlock();
	}

	AtomicVector<T> operator=(const AtomicVector<T>& other)
	{
		mutex.lock();
		AtomicVector<T> temp(other);
		swap(*this, temp);
		mutex.unlock();
		return *this;
	}

	AtomicVector<T> operator=(AtomicVector<T>&& other)
	{
		mutex.lock();
		if (_begin != nullptr)
			delete[] _begin;
		swap(*this, other);
		mutex.unlock();
		return *this;
	}

	T& operator[](size_t pos)
	{
		mutex.lock();
		try
		{
			if (_begin == nullptr)
			{
				mutex.unlock();
				throw ExceptionsWithVectors(2, (char*) "Vector did not initializing yet!");
			}
			if ((pos >= _size) && (pos < _capacity)) //увеличиваем размер если позволяет вместимость
				_size = pos + 1;
			mutex.unlock();
			return _begin[pos];
		}
		catch (ExceptionsWithVectors exp)
		{
			exp.display();
		}

	}

	T& at(size_t pos)
	{
		mutex.lock();
		try
		{
			if (_begin == nullptr)
			{
				mutex.unlock();
				throw ExceptionsWithVectors(2, (char*) "Vector did not initializing yet!");
			}
			if (pos >= _size)
			{
				mutex.unlock();
				throw ExceptionsWithVectors(1, (char*) "Out of range!");
			}
			mutex.unlock();
			return _begin[pos];
		}
		catch (ExceptionsWithVectors exp)
		{
			exp.display();
		}

	}

	friend void swap(AtomicVector<T>& first, AtomicVector<T>& second)
	{
		first.mutex.lock();
		size_t fsize = first._size;
		size_t fcapacity = first._capacity;
		T* fbegin = first._begin;
		second.mutex.lock();
		first._size = second._size;
		first._capacity = second._capacity;
		first._begin = second._begin;
		first.mutex.unlock();
		second._size = fsize;
		second._capacity = fcapacity;
		second._begin = fbegin;
		second.mutex.unlock();
	}
	
};

#endif __atomic_vector_h__

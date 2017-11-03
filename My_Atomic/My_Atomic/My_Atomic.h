#ifndef __my_atomic_h__
#define __my_atomic_h__

#include <thread>
#include <mutex>

template <class T> class MyAtomic {
private:
	T data;
	std::mutex mutex;
public:
	MyAtomic() = default;
	MyAtomic(const MyAtomic&) = delete;
	MyAtomic(T _data) : data(_data) {}
	~MyAtomic() {};
	MyAtomic& operator=(const MyAtomic&) = delete;

	T exchange(T _data = data)
	{
		mutex.lock();
		T temp;
		temp = data;
		data = _data;
		mutex.unlock();
		return temp;
	}
	T load() 
	{
		mutex.lock();
		T temp = data;
		mutex.unlock();
		return temp;
	}
	void store(T _data) 
	{
		mutex.lock();
		data = _data;
		mutex.unlock();
	}

	MyAtomic<T> &operator++()
	{
		mutex.lock();
		MyAtomic<T> oldvalue(data);
		data++;
		mutex.unlock();
		return oldvalue;
	}

	MyAtomic<T> &operator++(int)
	{
		mutex.lock();
		data++;
		mutex.unlock();
		return *this;

	}
};

#endif __my_atomic_h__

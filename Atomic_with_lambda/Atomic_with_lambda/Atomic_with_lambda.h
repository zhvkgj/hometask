#ifndef __my_atomic_h__
#define __my_atomic_h__

#include <thread>
#include <mutex>
#include <iostream>
#include <functional>

template <class T> class MyDigit {
protected:
	T number;
public:
	MyDigit() = default;
	MyDigit(T num) : number(num) {};
	//method number 0
	T doubling()
	{
		return (T) number * 2;
	}
	//method number 1
	T absValue()
	{
		return number < 0 ? number*(-1) : number;
	}
	//method number 2
	T powMyNum(int n)
	{
		if (n == 0) return 1;
		else
		{
			T k = number;
			while (n != 1)
			{
				k *= k;
				n--;
			}
			return k;
		}
	}

};


template <class T> class MyAtomic : MyDigit<T> {
private:
	std::recursive_mutex myMutex;
public:
	MyAtomic() = default;
	MyAtomic(T num) { number = num; };
	MyAtomic(const MyAtomic&) = delete;
	~MyAtomic() {};
	MyAtomic& operator=(const MyAtomic&) = delete;

	void atomicShell(int k, int n = 0)
	{
		myMutex.lock();
		std::function<void(int)> predicate;
		switch (k)
			{
				case 0: 
					predicate = [=](int a) {std::cout << doubling() << std::endl; };
					break;
				case 1:	
					predicate = [=](int a) {std::cout << absValue() << std::endl; };
					break;
				case 2: 
					predicate = [=](int a) {std::cout << powMyNum(a) << std::endl; };
					break;
			}
		predicate(n);
		myMutex.unlock();
	}

	T exchange(T tempData = number)
	{
		myMutex.lock();
		T temp;
		temp = number;
		number = tempData;
		myMutex.unlock();
		return temp;
	}

	T load()
	{
		myMutex.lock();
		T temp = number;
		myMutex.unlock();
		return temp;
	}
	void store(T tempData)
	{
		myMutex.lock();
		number = tempData;
		myMutex.unlock();
	}

	MyAtomic<T> &operator++()
	{
		myMutex.lock();
		MyAtomic<T> oldvalue(number);
		number++;
		myMutex.unlock();
		return oldvalue;
	}

	MyAtomic<T> &operator++(int)
	{
		myMutex.lock();
		number++;
		myMutex.unlock();
		return *this;

	}

	MyAtomic<T> &operator--()
	{
		myMutex.lock();
		MyAtomic<T> oldvalue(number);
		number--;
		myMutex.unlock();
		return oldvalue;
	}

	MyAtomic<T> &operator--(int)
	{
		myMutex.lock();
		number--;
		myMutex.unlock();
		return *this;
	}

	T operator= (T tempData)
	{
		myMutex.lock();
		number = tempData;
		myMutex.unlock();
		return number;
	}

};

#endif __my_atomic_h__
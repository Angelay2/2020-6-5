#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <string>

using std::cout;
using std::endl;
using std::string;

/* ����Ĵ��� iterator insert(iterator pos, int val)
	1. �����������pos������֮ǰ,
	2. ������������� ��Ҫͬʱ���µ�����pos��λ��

*/
class String
{
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
		cout << "String(const char*)" << endl;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
		cout << "~String()" << endl;
	}
private:
	char* _str;
};

template <class T>
class Vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;

	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}

	size_t size() const
	{
		return _finish - _start;
	}

	size_t capacity() const
	{
		return _endOfStorage - _start;
	}

	void pushBack(const T& val)
	{
		////�������
		//if (_finish == _endOfStorage)
		//{
		//	size_t newC = capacity() == 0 ? 1 : 2 * capacity();
		//	reserve(newC);
		//}
		////β�����
		//*_finish = val;
		//++_finish;
		insert(end(), val);
	}

	void reserve(size_t n)
	{
		if (n > capacity())
		{
			//��¼Ԫ�ظ���
			int sz = size();
			//���ռ�
			T* tmp = new T[n];
			if (_start != nullptr)  //(_start)
			{
				////��������:ǳ�������ᵼ�¶����ͷŵ�����
				//memcpy(tmp, _start, sizeof(T)* size());

				//���: ����T���͵ĸ�ֵ��������غ���
				for (int i = 0; i < sz; ++i)
				{
					tmp[i] = _start[i];
				}
				//�ͷ�ԭ�пռ�
				delete[] _start;
			}
			//����ָ��
			_start = tmp;
			_finish = _start + sz;
			_endOfStorage = _start + n;
		}
	}

	void resize(size_t n, const T& val = T())
	{
		if (n > capacity())
		{
			reserve(n);
		}
		if (n > size())
		{
			while (_finish != _start + n)
			{
				*_finish = val;
				++_finish;
			}
		}

		_finish = _start + n;
	}

	T& operator[](size_t pos)
	{
		if (pos < size())
			return _start[pos];
	}

	const T& operator[](size_t pos) const
	{
		if (pos < size())
			return _start[pos];
	}

	iterator begin()
	{
		//��һ��Ԫ�ص�λ��
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	const_iterator begin() const
	{
		return _start;
	}

	const_iterator end() const
	{
		return _finish;
	}

	void insert(iterator pos, const T& val)
	{
		if (pos >= _start && pos <= _finish)
		{
			//�������
			if (_finish == _endOfStorage)
			{
				//����֮ǰ����¼pos����ʼλ�õ�ƫ����
				int len = pos - _start;
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC);
				//������������ݣ������pos
				pos = _start + len;
			}
			//�ƶ�Ԫ��
			iterator end = _finish;
			while (end != pos)
			{
				*end = *(end - 1);
				--end;
			}
			//����Ԫ��
			*pos = val;
			//����size
			++_finish;
		}
	}
	//������һ��Ԫ�ص�λ��
	iterator erase(iterator pos)
	{
		if (pos >= begin() && pos < end())
		{
			iterator begin = pos + 1;
			//�ƶ�Ԫ��
			while (begin != _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}
			//����size
			--_finish;

			return pos;
		}
	}

	void pop_back()
	{
		if (size() > 0)
			erase(end() - 1);
	}

	Vector(const Vector<T>& v)
		:_start(new T[v.capacity()])
		, _finish(_start + v.size())
		, _endOfStorage(_start + v.capacity())
	{
		//����� ���ø�ֵ��������غ������
		for (int i = 0; i < v.size(); ++i)
		{
			_start[i] = v[i];
		}
	}

	//�ִ�д��
	Vector<T>& operator=(Vector<T> v)
	{
		Swap(v);
		return *this;
	}

	void Swap(Vector<T>& v)
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endOfStorage, v._endOfStorage);
	}

	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
	}

	template <class inputIterator>
	Vector(inputIterator first, inputIterator last)
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{
		while (first != last)
		{
			pushBack(*first);
			++first;
		}
	}

private:
	T* _start;
	T* _finish;
	T* _endOfStorage;
};

void test()
{
	Vector<int> v;
	int sz = v.size();
	int cap = v.capacity();

	v.pushBack(1);
	sz = v.size();
	cap = v.capacity();

	v.pushBack(2);
	sz = v.size();
	cap = v.capacity();

	for (int i = 0; i < 10000; ++i)
		v.pushBack(i);
}

void test2()
{
	Vector<string> v;
	string str1 = "123";
	string str2 = "456";
	string str3 = "789";
	string str4 = "1011";
	string str5 = "1213";

	v.pushBack(str1);

	v.pushBack(str2);

	v.pushBack(str3);

	v.pushBack(str4);

	v.pushBack(str5);

	v.pushBack(str1);

	v.pushBack(str2);

	v.pushBack(str3);

	v.pushBack(str4);

	v.pushBack(str5);

	v.pushBack(str1);

	v.pushBack(str2);

	v.pushBack(str3);

	v.pushBack(str4);

	v.pushBack(str5);

	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
		v[i] = "0";
	}

	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
		v[i] = "0";
	}
}

template <class T>
void printVector(const Vector<T>& vec)
{
	Vector<T>::const_iterator it = vec.begin();
	while (it != vec.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test3()
{
	Vector<int> v;
	v.pushBack(1);
	v.pushBack(2);
	v.pushBack(3);
	v.pushBack(4);
	v.pushBack(5);
	v.pushBack(6);

	Vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		*it = 100;
		++it;
	}
	cout << endl;

	printVector(v);

	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test4()
{
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.pushBack(i);

	printVector(v);
	v.resize(5);
	printVector(v);
	v.resize(8);
	printVector(v);
	v.resize(20, 50);
	printVector(v);
}

void test5()
{
	Vector<int> v;
	v.pushBack(1);
	v.insert(v.end(), 2);
	printVector(v);
	cout << endl;
	for (int i = 0; i < 100; ++i)
	{
		v.pushBack(i);
	}
	printVector(v);
	cout << endl;
}

void test6()
{
	Vector<int> v;
	v.pushBack(1);
	Vector<int>::iterator it = v.begin();
	cout << *it << endl;
	for (int i = 2; i <= 11; ++i)
		v.pushBack(i);
	//���»�ȡ������
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;
}

void test7()
{
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.pushBack(i);
	Vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 != 0)
			//ɾ��֮�����»�ȡ������
			it = v.erase(it);
		else
			++it;
	}
	printVector(v);
}

void test8()
{
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.pushBack(i);
	printVector(v);
	Vector<int> v2(v);
	printVector(v2);
	Vector<int> v3;
	for (int i = 10; i < 20; ++i)
	{
		v3.pushBack(i);
	}
	printVector(v3);
	v2 = v3;
	printVector(v2);

	Vector<int> v4(v3.begin(), v3.end());
	printVector(v4);

	int array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Vector<int> v5(array, array + 10);
}

//int main()
//{
//	//test();
//	//test2();
//	//test3();
//	//test4();
//	//test5();
//	//test6();
//	//test7();
//	test8();
//	return 0;
//}
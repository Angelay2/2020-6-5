#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>


using std::cout;
using std::endl; 
using std::list;
using std::string;
using std::vector;

/*
list������:
	���벻�ᵼ��list������ʧЧ,������ָ��û�з����仯, ����ռ�Ҳû���ͷ�
	ɾ���ᵼ�µ�����ʧЧ, ɾ��Ԫ��ʱ, �ռ��ͷ�, ָ��ʧЧ, ֻ��Ҫ���»�ȡ��ǰ��ɾ��λ�õ�����, �������������ᱻӰ��
	splice:�������, ����ֱ������Ҫƴ�ӵ�list��Ԫ��
	remove: ɾ��ָ����ֵ, ��ɾ������ָ��ֵ��Ԫ��, ���ָ����ֵ������, �������κβ���
	unique: ���ô˽ӿ�ǰ, ��Ҫ��֤listԪ������, ����֤������������
	merge: �������, ֱ������Ҫ�ϲ���list
*/
void t1()
{
	list<int> lst;

	list<int> lst2(10, 5);

	char charArr[] = "12345";

	string str = "6789";

	vector<char> vec(5, 'a');

	list<char> lst3(charArr, charArr + 6);

	list<char> lst4(str.begin(), str.end());

	list<char> lst5(vec.begin(), vec.end());

	//����������
	cout << "iterator" << endl;
	list<char>::iterator it = lst3.begin();
	while (it != lst3.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	cout << "for" << endl;
	for (const auto& ch : lst4)
	{
		cout << ch << " ";
	}
	cout << endl;

	it = lst5.begin();
	while (it != lst5.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void t2()
{
	list<int> lst;
	lst.push_back(1);
	lst.push_front(0);

	list<int>::iterator it = lst.begin();
	cout << *it << endl;

	lst.emplace_back(2);
	lst.emplace_front(-1);
	list<int>::iterator it2 = lst.begin();
	cout << *it << endl;
	cout << *it2 << endl;

	lst.insert(lst.begin(), -2);
	lst.emplace(lst.end(), 3);

	list<int>::iterator it3 = lst.begin();
	cout << *it << endl;
	cout << *it2 << endl;
	cout << *it3 << endl;

	cout << *it << endl;

	lst.erase(it);
	//cout << *it << endl;
	cout << *it2 << endl;
	cout << *it3 << endl;

}

void t3()
{
	list<int> lst1;
	list<int> lst2(3, 0);
	lst1.push_back(1);
	lst1.push_back(2);
	lst1.push_back(3);


	lst1.splice(++lst1.begin(), lst2, ++lst2.begin(), lst2.end());
	lst1.remove(10);
	lst1.push_back(0);
	lst1.push_back(1);
	lst1.push_back(2);
	lst1.push_back(3);
	lst1.sort();
	lst1.unique();
	for (const auto& e : lst1)
		cout << e << " ";
	cout << endl;

	for (const auto& e : lst2)
		cout << e << " ";
	cout << endl;

	list<int> lst3;
	lst3.push_back(1);
	lst3.merge(lst1);
	for (const auto& e : lst1)
		cout << e << " ";
	cout << endl;

	for (const auto& e : lst3)
		cout << e << " ";
	cout << endl;

	lst3.reverse();

	for (const auto& e : lst3)
		cout << e << " ";
	cout << endl;

}

int main()
{
	//t1();
	//t2();
	t3();
	return 0;
}
#include <iostream>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <functional>
#include <utility>
#include <vector>
#include <iomanip>
#include <Windows.h>

using namespace std;



void printVec(vector<int> & v, string name)
{
	cout << setw(5) << name << " : ";
	for_each(v.cbegin(), v.cend(), [](int i){cout << i << ' '; });
	cout << endl;
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// ��������
	// �����
	// negate
	// logical_not

	// �����
	// plus
	// minus
	// multiplies<T>   - ��������
	// divides<T> - ������
	// modulus<T> - ������ �� ������
	// equal_to
	// not_equal_to
	// greater
	// greater_equal
	// less
	// less_equal
	// logical_and
	// logical_or
	
	

	// ��� �������� ����� �������� ������� ���������� ����� �����:
	// template<typename Argument, typemane Result> struct unary_function {}
	// template<typename Argument1, typename Argument2, typemane Result> struct binary_function {}
	// ��������� class someFunctor : public unary_function<int,int> {...}
	
	// �������� �"����:
	// ������ � �������� �������� - �������, ����������� �������� �:
	// ������ �������� - bind1st(�������_�������, ��������) ��: bind1st(plus<int>(), 4);
	// ������ �������� - bind2nd(�������_�������, ��������) ��: bind1nd(plus<int>(), 4);

	// �������� (���������� ���������)
	// not1(unary_predicat)
	// not2(binary_predicat)

	//�������
	// ������� ����� ��� ��� �����
	// ptr_fun() - ������ � ����� ��������� �������� �� �������
	// cit = find_if(v.cbegin(), v.cend(), bind1st<less<int>>(less<int>(), 4));
	// cit = find_if(v.cbegin(), v.cend(), bind1st(ptr_fun(strcmp), 4));
	vector<int> v(10);
	vector<int>::const_iterator cit1 = find_if(v.cbegin(), v.cend(), bind1st(pointer_to_binary_function<int, int, int>(strcmp), 4));


	

	//vector<int> v(10);
	//fill_n(v.begin(), v.end(), 4);
	generate(v.begin(), v.end(), [](){ return rand() % 10; });
	printVec(v, "v");

	cout << "\n--------count------------------------------\n";
	cout << "count of 5 in v: " << count(v.cbegin(), v.cend(), 5) << endl;
	cout << "count of % 4 in v: " << count_if(v.cbegin(), v.cend(), [](int i) {if (i % 4) return false; return true; }) << endl;

	cout << "\n--------remove_copy------------------------------\n";
	// remove - ������ ��������, � ��������� ���������
	// remove_if - ������ ��������, � ��� ���� �������� � ��������
	// remove_copy - ����� �������� � result, � ��������� ���������
	// remove_if - ����� �������� � result, � ��� ���� �������� � ��������

	vector<int> v2(10);
	printVec(v, "v");
	printVec(v2, "v2");
	remove_copy(v.cbegin(), v.cend(), v2.begin(), 8);
	printVec(v, "v");
	printVec(v2, "v2");

	cout << "\n--------replace_copy------------------------------\n";
	// �� ���� �� remove, ����� ��� ����� �� ���� ��������

	fill(v2.begin(), v2.end(), 0);
	printVec(v, "v");
	printVec(v2, "v2");
	replace_copy(v.cbegin(), v.cend(), v2.begin(), 8, 1);
	printVec(v, "v");
	printVec(v2, "v2");

	cout << "\n--------reverse------------------------------\n";
	// ����� �����������
	// reverse_copy - + �����
	printVec(v, "v");
	reverse(v.begin() + 2, v.end() - 2);
	printVec(v, "v");

	cout << "\n--------adjacent_find-(����� �����.����.�������� + � ��.����.)----------\n";
	printVec(v, "v");
	
	typedef vector<int>::const_iterator vcit;
	typedef vector<int>::iterator vit;
	vcit cit = adjacent_find(v.cbegin(), v.cend());
	if (cit != v.cend())
	{
		cout << "adjacent_find: " << *cit << ',' << *(cit + 1) << endl;
	}

	cit = adjacent_find(v.cbegin(), v.cend(), [](int a, int b){if ((b - a) < 3) return 1; else return 0; });
	if (cit != v.cend())
	{
		cout << "adjacent_find (with BinPred): " << *cit << ',' << *(cit + 1) << endl;

	}

	cout << "\n--binary_search-(������� �����)--\n";
	cout << "\n--copy-(��������� �����������)--\n";
	cout << "\n--copy_backward-(������������ � ������.�������)--\n";
	cout << "\n--equal-(�� ����.�������� (+ � ��.����.))--\n";
	cout << "\n--equal_range-(������� ���� ����� �����. ���� ��� ����.�������)--\n";
	cout << "--equal_range-(��� ����� ���� �� ����������� �����!!!!)--\n";
	sort(v.begin(), v.end());
	printVec(v, "v");
	pair<vcit, vcit> p = equal_range(v.cbegin(), v.cend(), 4);
	cout << "equal_range(v.cbegin(), v.cend(), 4):\n";
	cout << "pair->first: " << *(p.first) << endl;
	cout << "pair->second: " << *(p.second) << endl;

	cout << "\n--fill / fill_n-(���������� �������� ���������)--\n";
	cout << "\n--find-(����� ��������)--\n";
	cout << "\n--find_end-(����� �������� � ������� :))--\n";
	cout << "\n--find_first_of-(������� ������ � ������ :))--\n";
	printVec(v, "v");
	printVec(v2, "v2");
	cit = find_first_of(v.cbegin(), v.cend(), v2.cbegin(), v2.cend());
	cout << "v2 �������� � v � �������: "  << cit - v.begin() << endl;
	cit = find_first_of(v2.cbegin(), v2.cend(), v.cbegin(), v.cend());
	cout << "v �������� � v2 � �������: " << cit - v2.begin() << endl;

	cout << "\n--find_if (����� ��������, �� ���������� ������� ����.)--\n";
	cit = find_if(v.cbegin(), v.cend(), bind1st<less<int>>(less<int>(), 4));
	printVec(v, "v");
	cout << "(1) �������� ����� 4 � ���: " << cit - v.cbegin() << " ��������: " << *cit << endl;
	
	cout << "\n--for_each--\n";
	cout << "\n--generate / genereate_n--\n";
	generate(v.begin(), v.end(), [](){return rand() % 100; });
	printVec(v, "v");
	
	cout << "\n--includes (find_first_of ����� ����� bool) --\n";
	
	cout << "\n--inplace_merge (2 ������ ��������, ���� �� �����->� ���� ������������)--\n";
	printVec(v, "v");
	sort(v.begin(), v.begin() + 5);
	sort(v.begin() + 6, v.end());
	printVec(v, "v");
	inplace_merge(v.begin(), v.begin() + 6, v.end());
	printVec(v, "v");

	cout << "\n--iter_swap (������ �������� 2-� ���������) --\n";
	cout << "\n--lexicographic_compare --\n";
	cout << "\n--lower_bound (��������� ������� �������� ����� >=val)--\n";
	printVec(v, "v");
	cit = lower_bound(v.cbegin(), v.cend(), 40);
	cout << "�������� >=40 �� �������: " << cit - v.cbegin() << " ���� ����: " << *cit << endl;
	
	cout << "\n--make_heap--\n";
	printVec(v, "v");
	make_heap(v.begin(), v.end());
	printVec(v, "v");

	cout << "\n--max (����������� � ���� ������� + ��� ���� �����)--\n";
	cout << "\n--max_element (����������� �������� � �������� + ��� ���� �����)--\n";
	
	cout << "\n-- merge--\n";
	// ��"���� �� ���������� ����������� � ����
	//generate(v.begin(), v.end(), [](){static int a = 0; a++; return a;});
	//generate(v2.begin(), v2.end(), [](){static int a = 19; a++; return a; });
	//printVec(v, "v");
	//printVec(v2,"v2");
	// v.resize(100);
	// merge(v.cbegin(), v.cend(), v2.cbegin(), v2.cend(), v.begin()); ��� � �� ������ ����!
	//cout << "after merge:\n";
	//printVec(v, "v");

	cout << "\n--min (�������� � ���� ������� + ��� ���� �����)--\n";
	cout << "\n--max_element (�������� �������� � �������� + ��� ���� �����)--\n";
	cout << "\n--mismatch (����� ����������� �� ����������)--\n";
	printVec(v, "v");
	printVec(v2,"v2");
	pair<vcit, vcit> p2 = mismatch(v.cbegin(), v.cend(), v2.cbegin());
	cout << "v1 pos mismatch: " << p2.first - v.cbegin() << " ���� ����: " << *p2.first << endl;
	cout << "v2 pos mismatch: " << p2.second - v2.cbegin() << " ���� ����: " << *p2.second << endl;

	cout << "\n--mismatch (����� ����������� �� ����������)--\n";
	// ������� ��������� ������������ ��������� �� ��������� ������������������ (�� ����� �������� ���)
	/*
	nth_element - ���������� ����������� �� ����������� start i end �������� ���� ����� ��������
	partial_sort - ���������� ���� �� ����������� start i end
	partial_sort_copy - �������������  ������������������,  ��������� ���  �����������  start�  end, �  
	   �����  ��������  �  ��������������  ������������������, ������������  �����������  res_start �  resjend, 
	   �������  ���������,  �������  ���  ����� ��������.  ��  ����������  ��������,  �������������  ��  ������� 
	   ��������������  ����� �������������,  �������  ���  ����������  ���������
	
	partition - �������������  ������������������,  ������������  �����������  start�  end. ���,  �����  ���  ��������, 
	   ���  ������� �������  ��������  pfn ���������  ��������,  ��������������  ���,  ���  �������  ����  ��������  
	   ����������  ������ ��������.

	pop_heap - ���� ������ ������ � ������� �������� �� ���������� ����

	prev_permutation - �������� ��������� ������������ (��� �� �� �������� :))
	push_heap - �������� ������� � ����� ����. ��� ����� ������� ��� �� ���� ��������� �����

	random_shuffle - ���������� �������� (����� ������ ���� ������� ���������� ���������� �����)
	


	
	
	*/



}
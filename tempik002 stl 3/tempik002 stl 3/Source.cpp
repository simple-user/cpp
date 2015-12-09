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
	// функтори
	// унарні
	// negate
	// logical_not

	// бінарні
	// plus
	// minus
	// multiplies<T>   - множення
	// divides<T> - ділення
	// modulus<T> - остача від ділення
	// equal_to
	// not_equal_to
	// greater
	// greater_equal
	// less
	// less_equal
	// logical_and
	// logical_or
	
	

	// при створенні свого функтора потрібно наслідувати базові класи:
	// template<typename Argument, typemane Result> struct unary_function {}
	// template<typename Argument1, typename Argument2, typemane Result> struct binary_function {}
	// наприклад class someFunctor : public unary_function<int,int> {...}
	
	// редактор з"язків:
	// робить з бінарного функтора - унарний, підставляючи значення в:
	// перший аргумент - bind1st(бінаринй_функтор, значення) пр: bind1st(plus<int>(), 4);
	// другий аргумент - bind2nd(бінаринй_функтор, значення) пр: bind1nd(plus<int>(), 4);

	// інвентор (возвращает отрицание)
	// not1(unary_predicat)
	// not2(binary_predicat)

	//адаптер
	// приклад такий собі але нехай
	// ptr_fun() - приймає у якості аргумента вказівник на функцію
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
	// remove - вдаляє елементи, з відповідним значенням
	// remove_if - вдаляє елементи, з для яких предикат є істинним
	// remove_copy - копіює елементи в result, з відповідним значенням
	// remove_if - копіює елементи в result, з для яких предикат є істинним

	vector<int> v2(10);
	printVec(v, "v");
	printVec(v2, "v2");
	remove_copy(v.cbegin(), v.cend(), v2.begin(), 8);
	printVec(v, "v");
	printVec(v2, "v2");

	cout << "\n--------replace_copy------------------------------\n";
	// те саме що remove, тільки тут заміна на інше значення

	fill(v2.begin(), v2.end(), 0);
	printVec(v, "v");
	printVec(v2, "v2");
	replace_copy(v.cbegin(), v.cend(), v2.begin(), 8, 1);
	printVec(v, "v");
	printVec(v2, "v2");

	cout << "\n--------reverse------------------------------\n";
	// змінює послідовність
	// reverse_copy - + копіює
	printVec(v, "v");
	reverse(v.begin() + 2, v.end() - 2);
	printVec(v, "v");

	cout << "\n--------adjacent_find-(пошук однак.сусід.елементів + з бін.пред.)----------\n";
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

	cout << "\n--binary_search-(бінарний пошук)--\n";
	cout << "\n--copy-(копіювання послідовності)--\n";
	cout << "\n--copy_backward-(вставляється у зворот.порядку)--\n";
	cout << "\n--equal-(чи співп.діапазони (+ з бін.пред.))--\n";
	cout << "\n--equal_range-(діапазон куди можна встав. знач без пруш.порядку)--\n";
	cout << "--equal_range-(при цьому якщо не відсортовано вилітає!!!!)--\n";
	sort(v.begin(), v.end());
	printVec(v, "v");
	pair<vcit, vcit> p = equal_range(v.cbegin(), v.cend(), 4);
	cout << "equal_range(v.cbegin(), v.cend(), 4):\n";
	cout << "pair->first: " << *(p.first) << endl;
	cout << "pair->second: " << *(p.second) << endl;

	cout << "\n--fill / fill_n-(заповнення діапазону значенням)--\n";
	cout << "\n--find-(пошук елемента)--\n";
	cout << "\n--find_end-(пошук діапазона в діапазоні :))--\n";
	cout << "\n--find_first_of-(згадуємо аналог у стрінга :))--\n";
	printVec(v, "v");
	printVec(v2, "v2");
	cit = find_first_of(v.cbegin(), v.cend(), v2.cbegin(), v2.cend());
	cout << "v2 знайдено в v в позиції: "  << cit - v.begin() << endl;
	cit = find_first_of(v2.cbegin(), v2.cend(), v.cbegin(), v.cend());
	cout << "v знайдено в v2 в позиції: " << cit - v2.begin() << endl;

	cout << "\n--find_if (пошук елемента, що задовільняє унарний пред.)--\n";
	cit = find_if(v.cbegin(), v.cend(), bind1st<less<int>>(less<int>(), 4));
	printVec(v, "v");
	cout << "(1) знайдено більше 4 в поз: " << cit - v.cbegin() << " значення: " << *cit << endl;
	
	cout << "\n--for_each--\n";
	cout << "\n--generate / genereate_n--\n";
	generate(v.begin(), v.end(), [](){return rand() % 100; });
	printVec(v, "v");
	
	cout << "\n--includes (find_first_of тільки вертає bool) --\n";
	
	cout << "\n--inplace_merge (2 відсорт діапазони, один за одним->в один відсортований)--\n";
	printVec(v, "v");
	sort(v.begin(), v.begin() + 5);
	sort(v.begin() + 6, v.end());
	printVec(v, "v");
	inplace_merge(v.begin(), v.begin() + 6, v.end());
	printVec(v, "v");

	cout << "\n--iter_swap (обмінює значення 2-х ітераторів) --\n";
	cout << "\n--lexicographic_compare --\n";
	cout << "\n--lower_bound (знаходить елемент значення якого >=val)--\n";
	printVec(v, "v");
	cit = lower_bound(v.cbegin(), v.cend(), 40);
	cout << "значення >=40 на позиції: " << cit - v.cbegin() << " його знач: " << *cit << endl;
	
	cout << "\n--make_heap--\n";
	printVec(v, "v");
	make_heap(v.begin(), v.end());
	printVec(v, "v");

	cout << "\n--max (максимальне з двох значень + свій пред порівн)--\n";
	cout << "\n--max_element (максимальне значення з даіпазону + свій пред порівн)--\n";
	
	cout << "\n-- merge--\n";
	// об"єднує дві відсортовані послідовності в одну
	//generate(v.begin(), v.end(), [](){static int a = 0; a++; return a;});
	//generate(v2.begin(), v2.end(), [](){static int a = 19; a++; return a; });
	//printVec(v, "v");
	//printVec(v2,"v2");
	// v.resize(100);
	// merge(v.cbegin(), v.cend(), v2.cbegin(), v2.cend(), v.begin()); так і не працює сука!
	//cout << "after merge:\n";
	//printVec(v, "v");

	cout << "\n--min (мінімальне з двох значень + свій пред порівн)--\n";
	cout << "\n--max_element (мінімальне значення з даіпазону + свій пред порівн)--\n";
	cout << "\n--mismatch (перше неспівпадіння між діапазонами)--\n";
	printVec(v, "v");
	printVec(v2,"v2");
	pair<vcit, vcit> p2 = mismatch(v.cbegin(), v.cend(), v2.cbegin());
	cout << "v1 pos mismatch: " << p2.first - v.cbegin() << " його знач: " << *p2.first << endl;
	cout << "v2 pos mismatch: " << p2.second - v2.cbegin() << " його знач: " << *p2.second << endl;

	cout << "\n--mismatch (перше неспівпадіння між діапазонами)--\n";
	// создает следующую перестановку состоящую из элементов последовательности (хз навіть тетстити лінь)
	/*
	nth_element - вопрядковує послідовність між ітераторами start i end значення яких менше елемента
	partial_sort - впорядковує лише між ітераторами start i end
	partial_sort_copy - упорядочивает  последовательность,  ограничен­ ную  итераторами  startи  end, а  
	   затем  копирует  в  результирующую  последовательность, определенную  итераторами  res_start и  resjend, 
	   столько  элементов,  сколько  она  может вместить.  Он  возвращает  итератор,  установленный  на  элемент 
	   результирующей  после довательности,  который  был  скопирован  последним
	
	partition - упорядочивает  последовательность,  ограниченную  итера­торами  startи  end. так,  чтобы  все  элементы, 
	   для  которых унарный  предикат  pfn явля­ется  истинным,  предшествовали  тем,  для  которых  этот  предикат  
	   возвращает  ложное значение.

	pop_heap - міняє місцями перший і останній елементи та перестраює кучу

	prev_permutation - відновлює попередню перестановку (щоб це не означало :))
	push_heap - вставляє елемент в кінець кучі. при цьому діапазон вже має бути коректною кучею

	random_shuffle - перетасовує елементи (можна задати свою вункцію генератора випадкових чисел)
	


	
	
	*/



}
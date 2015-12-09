//LINE 289

//*** Додаткове завдання(за бажанням) Дано вираз у рядку( можуть бути + - * / ()) .
//	Обчислити значення виразу, враховуючи дужки та пріоритет операцій.
//


#include <iostream>
using namespace std;

int find_brackets(char* str); //функція перевірки дужок
double expr(char* str); //функція додавання, віднімання
double mult(char* str, int& index); //функція множення, ділення
double number(char* str, int& index); //функція для витягування чисел 
char* extract(char* str, int& index); //функція для витягування підрядка (дужки) із загального виразу


int main()
{
	char expression[255] = { 0 }; //виділення памяті для виразу
	cout << endl << " Enter  expression (without spaces) to evaluate or 'exit'  for end\n\n";
	while (1)
	{
		cout << "=> ";
		cin >> expression;
		if (!strcmp(expression, "exit"))//вихід з програми 
			return 0;
		if (find_brackets(expression))//перевірка дужок
			continue;
		else
			cout << "Result : " << expr(expression) << "\n";
	}
}


char* extract(char* str, int& index){
	char buffer[255];       //память для фрагменту рядка
	char* p_str = 0;        //вказівник на новий рядок для повернення
	int numL = 0;           //лічильник знайдених лівих дужок
	int buf_index = index;  //для збереження початкового значенння index
	do{
		buffer[index - buf_index] = *(str + index); //копіюємо символ рядка в підрядок
		switch (buffer[index - buf_index]) //перевірка  символу
		{
		case ')':
			if (numL == 0){
				buffer[index - buf_index] = '\0'; //якщо лічильник дужок правильний, то кінець рядка
				++index;    //встановлюємо індекс на слідуючий за дужкою елемент
				p_str = new char[index - buf_index];
				strcpy(p_str, buffer); // копіюємо підрядок в нову память
				return p_str;
			}
			else
				numL--;     //зменшуємо лічильник дужок
			break;
		case '(':
			numL++;         //відповідно збільшуємо
			break;
		}
	} while (*(str + index++) != '\0');     //встановлюємо індекс в наступний елемент
	return p_str;
}



int find_brackets(char* str){
	int count_l_brack = 0; //ліві дужки
	int count_r_brack = 0; //праві дужки
	int j = strlen(str);
	for (int i = 0; i < j; i++){
		if (str[i] == '(')
			count_l_brack++;
		if (str[i] == ')')
			count_r_brack++;
		if (count_r_brack>count_l_brack){//закритих дужок більше ніж відкритих
			cout << " error brackets\n";
			return 1;
		}
	}
	if (count_r_brack != count_l_brack){//якщо кількість відкритих і закртих дужок не співпадає
		cout << " error brackets\n";
		return 1;
	}
	return 0;
}


double expr(char* str){
	double value = 0.0;         //змінна результату
	int index = 0;              //index символа з яким працюємо
	value = mult(str, index);   //отримуємо перше значенння 
	while (1){
		switch (*(str + index++)){
		case '\0':          //кінець рядка
			return value;
		case '+':
			value += mult(str, index);
			break;
		case '-':
			value -= mult(str, index);
			break;
		default:  cout << "error expression\n";  //якщо недопустимі символи то виходимо з 0 результатом
			return 0;
		}
	}
}

double mult(char* str, int& index){
	double value = 0.0;             //змінна результату
	value = number(str, index);      //отримуємо перше число виразу
	while ((*(str + index) == '*') || (*(str + index) == '/')){ //множимо і ділимо поки зустрічаються такі знаки 
		if (*(str + index) == '*')
			value *= number(str, ++index);
		if (*(str + index) == '/')
			value /= number(str, ++index);
	}
	return value;
}


double number(char* str, int& index){
	double value = 0.0;     //число яке будемо витягувати  із рядка           
	if (*(str + index) == '(')//якщо дужка тоді створюємо окремий рядок який будемо прораховувати як окремий вираз
	{
		char* p_substr = 0;
		p_substr = extract(str, ++index);
		value = expr(p_substr);
		delete[] p_substr;
		return value;
	}
	char * ptrEnd;
	value = strtod(str + index, &ptrEnd);// число з рядка 
	index = ptrEnd - str; //змінили індекс в рядку з якого далі будемо виконуватьи дії
	return value;
}
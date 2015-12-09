//LINE 289

//*** ��������� ��������(�� ��������) ���� ����� � �����( ������ ���� + - * / ()) .
//	��������� �������� ������, ���������� ����� �� �������� ��������.
//


#include <iostream>
using namespace std;

int find_brackets(char* str); //������� �������� �����
double expr(char* str); //������� ���������, ��������
double mult(char* str, int& index); //������� ��������, ������
double number(char* str, int& index); //������� ��� ����������� ����� 
char* extract(char* str, int& index); //������� ��� ����������� ������� (�����) �� ���������� ������


int main()
{
	char expression[255] = { 0 }; //�������� ����� ��� ������
	cout << endl << " Enter  expression (without spaces) to evaluate or 'exit'  for end\n\n";
	while (1)
	{
		cout << "=> ";
		cin >> expression;
		if (!strcmp(expression, "exit"))//����� � �������� 
			return 0;
		if (find_brackets(expression))//�������� �����
			continue;
		else
			cout << "Result : " << expr(expression) << "\n";
	}
}


char* extract(char* str, int& index){
	char buffer[255];       //������ ��� ��������� �����
	char* p_str = 0;        //�������� �� ����� ����� ��� ����������
	int numL = 0;           //�������� ��������� ���� �����
	int buf_index = index;  //��� ���������� ����������� ��������� index
	do{
		buffer[index - buf_index] = *(str + index); //������� ������ ����� � �������
		switch (buffer[index - buf_index]) //��������  �������
		{
		case ')':
			if (numL == 0){
				buffer[index - buf_index] = '\0'; //���� �������� ����� ����������, �� ����� �����
				++index;    //������������ ������ �� �������� �� ������ �������
				p_str = new char[index - buf_index];
				strcpy(p_str, buffer); // ������� ������� � ���� ������
				return p_str;
			}
			else
				numL--;     //�������� �������� �����
			break;
		case '(':
			numL++;         //�������� ��������
			break;
		}
	} while (*(str + index++) != '\0');     //������������ ������ � ��������� �������
	return p_str;
}



int find_brackets(char* str){
	int count_l_brack = 0; //�� �����
	int count_r_brack = 0; //���� �����
	int j = strlen(str);
	for (int i = 0; i < j; i++){
		if (str[i] == '(')
			count_l_brack++;
		if (str[i] == ')')
			count_r_brack++;
		if (count_r_brack>count_l_brack){//�������� ����� ����� �� ��������
			cout << " error brackets\n";
			return 1;
		}
	}
	if (count_r_brack != count_l_brack){//���� ������� �������� � ������� ����� �� �������
		cout << " error brackets\n";
		return 1;
	}
	return 0;
}


double expr(char* str){
	double value = 0.0;         //����� ����������
	int index = 0;              //index ������� � ���� ��������
	value = mult(str, index);   //�������� ����� ��������� 
	while (1){
		switch (*(str + index++)){
		case '\0':          //����� �����
			return value;
		case '+':
			value += mult(str, index);
			break;
		case '-':
			value -= mult(str, index);
			break;
		default:  cout << "error expression\n";  //���� ���������� ������� �� �������� � 0 �����������
			return 0;
		}
	}
}

double mult(char* str, int& index){
	double value = 0.0;             //����� ����������
	value = number(str, index);      //�������� ����� ����� ������
	while ((*(str + index) == '*') || (*(str + index) == '/')){ //������� � ����� ���� ������������ ��� ����� 
		if (*(str + index) == '*')
			value *= number(str, ++index);
		if (*(str + index) == '/')
			value /= number(str, ++index);
	}
	return value;
}


double number(char* str, int& index){
	double value = 0.0;     //����� ��� ������ ����������  �� �����           
	if (*(str + index) == '(')//���� ����� ��� ��������� ������� ����� ���� ������ ������������� �� ������� �����
	{
		char* p_substr = 0;
		p_substr = extract(str, ++index);
		value = expr(p_substr);
		delete[] p_substr;
		return value;
	}
	char * ptrEnd;
	value = strtod(str + index, &ptrEnd);// ����� � ����� 
	index = ptrEnd - str; //������ ������ � ����� � ����� ��� ������ ����������� 䳿
	return value;
}
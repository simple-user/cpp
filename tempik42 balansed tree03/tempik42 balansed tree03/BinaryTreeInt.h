#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// зберігає string'и з цілими ключами
class BinaryTreeInt
{
	// вузол дерева
	struct Node
	{
		// службові поля -- зв'язки
		Node *	_parent;	// покажчик на батьківський (вищестоячий) елемент
		Node *	_less;		// покажчик на дочірній (нижчестоячий) елемент з МЕНШИМ  значенням ключа
		Node *	_more;		// покажчик на дочірній (нижчестоячий) елемент з БІЛЬШИМ значенням ключа


		// змістовні поля -- котрі зберігають корисну інформацію
		int		_key;		// ключ -- унікальний для кожного елемента, викор. для пошуку і впорядкування
		string	_val;		// значення, що зберігається і пов'язане з ключем


		Node( int key, const string & value );


	}; // struct Node



public:

	BinaryTreeInt();	// створює пусте дерево

	~BinaryTreeInt();


	void add( int key, const string & value );
	string * FindByKey( int key );					// повертає значення, асоційоване з ключем
	void RemoveByKey( int key );		// видаляє один елемент із зазначеним ключем (усі підпорядковані зберігає!)

	void clear();		// спорожнює дерево -- рекурсивно видаляє ноди



	////////////////////// з метою тестування ////////////////////////////
	friend ostream & operator << ( ostream & out, BinaryTreeInt & obj );

	//////////////////////////////////////////////////////////////////////


private:

	Node *	_root;		// покажчик на кореневий елемент


	friend ostream & operator << ( ostream & out, Node * node );	// рекурсивна ф-я виведення ноди

	Node * RecursiveFindByKey( int key, Node * node );
	Node * IterativeFindByKey( int key, Node * node );
	void RecursiveDeleteNode( Node * node );

	void CopyTree( Node * pSrc );	// копіює у this елементи піддерева pSrc

};




#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// ������ string'� � ������ �������
class BinaryTreeInt
{
	// ����� ������
	struct Node
	{
		// ������� ���� -- ��'����
		Node *	_parent;	// �������� �� ����������� (�����������) �������
		Node *	_less;		// �������� �� ������� (������������) ������� � ������  ��������� �����
		Node *	_more;		// �������� �� ������� (������������) ������� � ������� ��������� �����


		// ������� ���� -- ���� ��������� ������� ����������
		int		_key;		// ���� -- ��������� ��� ������� ��������, �����. ��� ������ � �������������
		string	_val;		// ��������, �� ���������� � ���'����� � ������


		Node( int key, const string & value );


	}; // struct Node



public:

	BinaryTreeInt();	// ������� ����� ������

	~BinaryTreeInt();


	void add( int key, const string & value );
	string * FindByKey( int key );					// ������� ��������, ����������� � ������
	void RemoveByKey( int key );		// ������� ���� ������� �� ���������� ������ (�� ������������ ������!)

	void clear();		// ��������� ������ -- ���������� ������� ����



	////////////////////// � ����� ���������� ////////////////////////////
	friend ostream & operator << ( ostream & out, BinaryTreeInt & obj );

	//////////////////////////////////////////////////////////////////////


private:

	Node *	_root;		// �������� �� ��������� �������


	friend ostream & operator << ( ostream & out, Node * node );	// ���������� �-� ��������� ����

	Node * RecursiveFindByKey( int key, Node * node );
	Node * IterativeFindByKey( int key, Node * node );
	void RecursiveDeleteNode( Node * node );

	void CopyTree( Node * pSrc );	// ����� � this �������� �������� pSrc

};




#include "BinaryTreeInt.h"

// ������� ����� ������
BinaryTreeInt::BinaryTreeInt()
	: _root( nullptr )
{}


BinaryTreeInt::Node::Node( int key, const string & value )
	: _parent( nullptr ), _less( nullptr ), _more( nullptr )	// ���� ����������� �� ��'����� � � ���
	, _key( key), _val( value ), height(1)							// ��� ������ ���� � ��������
{}


BinaryTreeInt::~BinaryTreeInt()
{
	this->RecursiveDeleteNode( this->_root );
	this->_root = nullptr;

}


void BinaryTreeInt::clear()
{
	this->RecursiveDeleteNode( this->_root );
	this->_root = nullptr;
}



void BinaryTreeInt::add( int key, const string & value )
{
	Node * pNewNode = new Node( key, value );		// ���� ���� ��� ���������

	// ���� ������ ����� -- ������� �� � �����
	if( this->_root == nullptr )
	{
		this->_root = pNewNode;
		return;
	}


	// ���� � ������ �� ����� -- ����� ������, ���� �� "���������" 
	// ���� ���������, �� ���� � ����� ������ ��� � -- ��� �������� exception

	// ����, ����������� ������
	Node * pCur = this->_root;		// �������� �� ������� ����
	while (pCur != nullptr)
	{
		// ����������� ������� ������ -- ����������
		if( pCur->_key == pNewNode->_key )
		{
			throw runtime_error(string("Key alredy exists: ") + std::to_string(key));
		}


		if( pNewNode->_key > pCur->_key )	// ���� ����� ���� ������� �� ��������� -- ����� � ������� ������ ������
		{
			if( pCur->_more != nullptr )// ���� � ������� � ������ ���������
			{
				pCur = pCur->_more;		// ���������� �� �����
			}
			else
			{
				// ���� ���� ������� � ������ ��������� -- ������ ����� �������
				pNewNode->_parent = pCur;	// �� ���������� ����� ���� �������
				pCur->_more = pNewNode;		// � ���� ����� � "�����" �������
				break;   // $$$ �������� � while, � ������ ���������� �������� ������
			}

		}
		else
		{
			// ���� ����� ���� ������ �� ��������� -- ����� � ������� ������ ������
			if( pCur->_less != nullptr )// ���� � ������� � ������ ��������� �����
			{
				pCur = pCur->_less;		// ���������� �� �����
			}
			else
			{
				// ���� ���� �������� � ������ ��������� ����� -- ������ ����� �������
				pNewNode->_parent = pCur;	// �� ���������� ����� ���� �������
				pCur->_less = pNewNode;		// � ���� ����� � "�����" �������
				break;   // $$$ �������� � while, � ������ ���������� �������� ������
			}
		}
	}

	// ������� � while
	// �������� ������
	// ���� �������� �� newNode - � ������ ��� �� ����� �����
	pCur = pNewNode;
	unsigned long t = _root->height;
	while (pCur != _root)
	{
		unsigned long hLess = height(pCur->_parent->_less);
		unsigned long hMore = height(pCur->_parent->_more);
	
		pCur->_parent->height = (hLess > hMore ? hLess : hMore) + 1;
		pCur = pCur->_parent;
	} // ����� ���


}// void BinaryTreeInt::add( int key, const string & value )


ostream & operator << ( ostream & out, BinaryTreeInt & obj )
{
	if( obj._root )
	{
		out << obj._root;		// �������� ������ ����������, ��������� � �������� ����
	}
	else
	{
		cout <<"tree is empty \n";
	}
	return out;
}

// ���������� �-� ��������� ����
ostream & operator << ( ostream & out, BinaryTreeInt::Node * node )
{
	if ( node == nullptr )
	{
		return out;		// �� ��������
	}

	out <<"Current node : key=" <<node->_key << " value=\"" <<node->_val <<"\" height=" << node->height << "\n";

	if( node->_less != nullptr )
	{
		out << "        less : key=" << node->_less->_key << " value=\"" << node->_less->_val << "\" height=" << node->height << "\n";
	}
	else
	{
		out <<"        less : empty\n";
	}

	if( node->_more != nullptr )
	{
		out << "        more : key=" << node->_more->_key << " value=\"" << node->_more->_val << "\" height=" << node->height << "\n";
	}
	else
	{
		out <<"        more : empty\n";
	}

	out <<"\n";

	// ���������� �������� ������ ����
	out << node->_less;
	out << node->_more;

	return out;
}


string * BinaryTreeInt::FindByKey( int key )
{
	//Node* res =  RecursiveFindByKey( key, this->_root );	// ���������� ������, ��������� � ������
	Node* res = IterativeFindByKey( key, this->_root );	// ���������� ������, ��������� � ������

	if( res != nullptr )
	{
		return &(res->_val);	// ������ �����
	}

	return nullptr;		// �������� �����

}


BinaryTreeInt::Node * BinaryTreeInt::RecursiveFindByKey( int key, Node * node )
{
	if( node == nullptr )
	{
		return nullptr;
	}

	// ������ ���
	if( key < node->_key )	
	{
		return RecursiveFindByKey( key, node->_less );		// ���������� ������ � ������� � ������� �������
	}

	if (key > node->_key)
	{
		return RecursiveFindByKey(key, node->_more);		// ���������� ������ � ������� � ������� �������
	}
	else
		return node;
}



void BinaryTreeInt::RecursiveDeleteNode( Node * node )
{
	if( node == nullptr )
	{
		return;
	}

	// ���� � ������ ���� -- ����� ���������� �� (��� �� �������� ���������)
	if( node->_less )
	{
		RecursiveDeleteNode( node->_less );
	}
	if( node->_more )
	{
		RecursiveDeleteNode( node->_more );
	}

	// � ����� ���� node ��� �� �� ������� ���

	// ���� �� ��������, �������� �������� ���������� ����
	if( node->_parent )		
	{
		if( node->_parent->_less == node )	// ���� ���� ����������� � ������� ����� ���������� ����
		{
			node->_parent->_less  = nullptr;	// ��������� ����� �����
		}
		else
		{
			node->_parent->_more = nullptr;		// ��������� ����� �����
		}
	}
	//else
	//{
	//	// � �������� ���� ���� _patent, �����, ������ ��� ������
	//	this->_root = nullptr;
	//}

	// ������ ����� �������� node
	// cout <<"Deleted node : _key=" <<node->_key <<"  _val=\"" <<node->_val <<endl;
	delete node;

}


BinaryTreeInt::Node * BinaryTreeInt::IterativeFindByKey( int key, Node * node )
{

	while( node != nullptr && node->_key != key )	// ������
	{
		node = key > node->_key ? node->_more : node->_less;
	}


	return node;	// ��������� ��, �� �������

}

// ������� ���� ������� �� ���������� ������ (�� ������������ ������!)
void BinaryTreeInt::RemoveByKey( int key )
{
	// �������� ������, �� ��������
	Node * pDel = IterativeFindByKey( key, this->_root );

	if( pDel == nullptr )	// ���� �� �������
	{
		return;				// ����� �� ������
	}


	// ��������� ���� pDel, � �� ������ �������� "���������" � ������� ������

	if( pDel->_parent == nullptr )		// ���� ��������� �������� ����
	{
		this->_root = nullptr;			// �� ��������� ������ ���� ������
	}
	else
	{
		// �������� ���� "��������"
		if( pDel->_parent->_less == pDel )
		{
			pDel->_parent->_less = nullptr;		// � _less ������������ �������� ����� ����� �� ����
		}
		else
		{
			pDel->_parent->_more = nullptr;		// � _more ������������ �������� ����� ����� �� ����
		}

	}

	// "����������" ����������� ��������
	this->CopyTree( pDel->_less );
	this->CopyTree( pDel->_more );

	RecursiveDeleteNode( pDel );	// ����� ��������� ��������, ��� ���������

}



// ����� � this �������� �������� pSrc
void BinaryTreeInt::CopyTree( Node * pSrc )
{
	if( pSrc == nullptr )
	{
		return;
	}

	this->add( pSrc->_key, pSrc->_val);	//������� � this ������� ����

	// ������� � this ������� ������� ����
	this->CopyTree( pSrc->_less );
	this->CopyTree( pSrc->_more );

}





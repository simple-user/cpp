#include "BinaryTreeInt.h"

// створює пусте дерево
BinaryTreeInt::BinaryTreeInt()
	: _root( nullptr )
{}


BinaryTreeInt::Node::Node( int key, const string & value )
	: _parent( nullptr ), _less( nullptr ), _more( nullptr )	// нода створюється не зв'язана ні з ким
	, _key( key), _val( value ), height(1)							// але містить ключ і значення
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
	Node * pNewNode = new Node( key, value );		// нова нода для зберігання

	// якщо дерево пусте -- ставимо її в корінь
	if( this->_root == nullptr )
	{
		this->_root = pNewNode;
		return;
	}


	// якщо ж дерево НЕ пусте -- треба знайти, куди її "приткнути" 
	// може трапитися, що нода з таким ключем уже є -- тоді викидаємо exception

	// отже, переглядаємо дерево
	Node * pCur = this->_root;		// покажчик на поточну ноду
	while (pCur != nullptr)
	{
		// неприпустимі повтори ключів -- виключення
		if( pCur->_key == pNewNode->_key )
		{
			throw runtime_error(string("Key alredy exists: ") + std::to_string(key));
		}


		if( pNewNode->_key > pCur->_key )	// якщо новий ключ БІЛЬШИЙ від поточного -- ідемо в сторону більших ключів
		{
			if( pCur->_more != nullptr )// якщо є елемент з більшим значенням
			{
				pCur = pCur->_more;		// переходимо до нього
			}
			else
			{
				// якщо нема елемент з більшим значенням -- додаємо новий елемент
				pNewNode->_parent = pCur;	// її батькіською нодою буде поточна
				pCur->_more = pNewNode;		// а вона стане у "більшу" сторону
				break;   // $$$ виходимо з while, і будемо коригувати значення висоти
			}

		}
		else
		{
			// якщо новий ключ МЕНШИЙ від поточного -- ідемо в сторону менших ключів
			if( pCur->_less != nullptr )// якщо є елемент з меншим значенням ключа
			{
				pCur = pCur->_less;		// переходимо до нього
			}
			else
			{
				// якщо нема елемента з меншим значенням ключа -- додаємо новий елемент
				pNewNode->_parent = pCur;	// її батькіською нодою буде поточна
				pCur->_less = pNewNode;		// а вона стане у "меншу" сторону
				break;   // $$$ виходимо з while, і будемо коригувати значення висоти
			}
		}
	}

	// вийщшли з while
	// корегуємо висоти
	// маємо вказівник на newNode - і будемо йти від нього вверх
	pCur = pNewNode;
	unsigned long t = _root->height;
	while (pCur != _root)
	{
		unsigned long hLess = height(pCur->_parent->_less);
		unsigned long hMore = height(pCur->_parent->_more);
	
		pCur->_parent->height = (hLess > hMore ? hLess : hMore) + 1;
		pCur = pCur->_parent;
	} // вродь все


}// void BinaryTreeInt::add( int key, const string & value )


ostream & operator << ( ostream & out, BinaryTreeInt & obj )
{
	if( obj._root )
	{
		out << obj._root;		// виводить дерево рекурсивно, починаючи з кореневої ноди
	}
	else
	{
		cout <<"tree is empty \n";
	}
	return out;
}

// рекурсивна ф-я виведення ноди
ostream & operator << ( ostream & out, BinaryTreeInt::Node * node )
{
	if ( node == nullptr )
	{
		return out;		// не виводимо
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

	// рекурсивно виводимо дочірні ноди
	out << node->_less;
	out << node->_more;

	return out;
}


string * BinaryTreeInt::FindByKey( int key )
{
	//Node* res =  RecursiveFindByKey( key, this->_root );	// рекурсивно шукаємо, починаючи з кореня
	Node* res = IterativeFindByKey( key, this->_root );	// ітеративно шукаємо, починаючи з кореня

	if( res != nullptr )
	{
		return &(res->_val);	// вдалий пошук
	}

	return nullptr;		// невдалий пошук

}


BinaryTreeInt::Node * BinaryTreeInt::RecursiveFindByKey( int key, Node * node )
{
	if( node == nullptr )
	{
		return nullptr;
	}

	// шукаємо далі
	if( key < node->_key )	
	{
		return RecursiveFindByKey( key, node->_less );		// рекурсивно шукаємо у піддереві з меншими ключами
	}

	if (key > node->_key)
	{
		return RecursiveFindByKey(key, node->_more);		// рекурсивно шукаємо у піддереві з більшими ключами
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

	// якщо є дочірні ноди -- перше повидаляти їх (щоб не втратити вказівники)
	if( node->_less )
	{
		RecursiveDeleteNode( node->_less );
	}
	if( node->_more )
	{
		RecursiveDeleteNode( node->_more );
	}

	// у цьому місці node уже не має дочірніх нод

	// перш ніж видаляти, занулимо покажчик батьківської ноди
	if( node->_parent )		
	{
		if( node->_parent->_less == node )	// якщо нода знаходиться у меншому плечі батьківської ноди
		{
			node->_parent->_less  = nullptr;	// зануляємо менше плече
		}
		else
		{
			node->_parent->_more = nullptr;		// зануляємо більше плече
		}
	}
	//else
	//{
	//	// у кореневої ноди нема _patent, тобто, дерево уже порожнє
	//	this->_root = nullptr;
	//}

	// нарешті можна видалити node
	// cout <<"Deleted node : _key=" <<node->_key <<"  _val=\"" <<node->_val <<endl;
	delete node;

}


BinaryTreeInt::Node * BinaryTreeInt::IterativeFindByKey( int key, Node * node )
{

	while( node != nullptr && node->_key != key )	// шукаємо
	{
		node = key > node->_key ? node->_more : node->_less;
	}


	return node;	// повертаємо те, що знайщли

}

// видаляє один елемент із зазначеним ключем (усі підпорядковані зберігає!)
void BinaryTreeInt::RemoveByKey( int key )
{
	// спочатку шукаємо, що видаляти
	Node * pDel = IterativeFindByKey( key, this->_root );

	if( pDel == nullptr )	// якщо не знайшли
	{
		return;				// нічого не робимо
	}


	// видаляємо лише pDel, а її дочірні елементи "передодємо" у основне дерево

	if( pDel->_parent == nullptr )		// якщо видаляємо кореневу ноду
	{
		this->_root = nullptr;			// то тимчасово дерево буде пустим
	}
	else
	{
		// вилучаємо ціле "піддерево"
		if( pDel->_parent->_less == pDel )
		{
			pDel->_parent->_less = nullptr;		// у _less батьківського елемента тепер нікого не буде
		}
		else
		{
			pDel->_parent->_more = nullptr;		// у _more батьківського елемента тепер нікого не буде
		}

	}

	// "передодаємо" нижчестоячі елементи
	this->CopyTree( pDel->_less );
	this->CopyTree( pDel->_more );

	RecursiveDeleteNode( pDel );	// тепер видаляємо піддерево, яке зкопіювали

}



// копіює у this елементи піддерева pSrc
void BinaryTreeInt::CopyTree( Node * pSrc )
{
	if( pSrc == nullptr )
	{
		return;
	}

	this->add( pSrc->_key, pSrc->_val);	//копіюємо у this поточну ноду

	// копіюємо у this нащадків поточної ноди
	this->CopyTree( pSrc->_less );
	this->CopyTree( pSrc->_more );

}





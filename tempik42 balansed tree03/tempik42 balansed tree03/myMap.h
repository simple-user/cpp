#pragma once
#include <utility>
#include <list>
#include <iomanip>
#include <string>
#include <exception>
#include <string>

template <typename typeKey, typename typeVal>
class myMap
{
private:
	struct node; 
public:
	typedef typename std::pair<typeKey, typeVal> val;

	myMap() : root(nullptr), size(0) {}
	~myMap() {} // € хз поки що :)


	void push(const typeKey &k, const typeVal &v)
	{
		root = insert(root, k, v);
		++size;
	}
	void push(const val &vPair)
	{
		root = insert(root, vPair.first, vPair.second);
		++size;
	}
	void pop(const typeKey &k)
	{
		root = remove(k, root);
		--size;
	}
	const val operator[](size_t index) const
	{
		if (index >= size)
			throw std::logic_error(std::string("logic error"));
		size_t curIndex = 0;
		node *t = indexator(curIndex, index, root);
		return std::make_pair(t->nodeKey, t->nodeVal);
	}
	const val * findByKey(const typeKey &k) const
	{
		node *res = find(root, k);
		val...

	}
	void showSortedTreeTest() const
	{
		showSortedTest(root);
		cout << endl;
	}
	void show() const 
	{
		if (!root)
			return;

		std::list<node*> l;
		node * t = root;
		l.push_back(root);
		unsigned char height = root->height;

		while (l.size())
		{
			t = l.front();
			l.pop_front();
			if (t) cout << "\tcurrent: " << t->nodeKey << " (" << static_cast<int>(t->height) << ")\n";
			if (t->left) cout << "left: " << t->left->nodeKey << " (" << static_cast<int>(t->left->height) << ")\t\t";
			if (t->right) cout << "right: " << t->right->nodeKey << " (" << static_cast<int>(t->right->height) << ")\n";
			cout << endl;

			if (t->left) l.push_back(t->left);
			if (t->right) l.push_back(t->right);
		}

	}
	size_t getSize() const
	{
		return size;
	}
	unsigned char height() const // повертаЇ висоту всього дерева. дл€ nullptr висота - 0
	{
		return root ? root->height : 0;
	}
	unsigned char height(node* p) const // повертаЇ висоту дл€ даного вузла. дл€ nullptr висота - 0
	{
		return p ? p->height : 0;
	}

private:
	struct node // структура дл€ представлени€ узлов дерева
	{
		typeKey nodeKey;
		typeVal nodeVal;
		unsigned char height;
		node* left;
		node* right;
		node(const typeKey &k, const typeVal &v) { nodeKey = k; nodeVal=v, left = right = 0; height = 1; }
	};


	node * indexator(size_t &curIndex, size_t index, node *n)
	{
		if (!n)
			return nullptr;

		node *res = nullptr;
		if (n->left && curIndex<=index) res = indexator(curIndex, index, n->left);
		++curIndex; //щоб дал≥ не йшли по дереву (+ в≥дпрацьовуЇмо даний вузол)
		if (curIndex == index+1) return n;
		if (n->right && curIndex <= index) res = indexator(curIndex, index, n->right);
		return res;
	}
	
	void showSortedTest(node *n) const // будемо л≥пити з цього ≥ндексатор :)
	{
		if (!n)
			return;
		if (n->left) showSortedTest(n->left);
		cout << n->nodeKey << ' ';
		if (n->right) showSortedTest(n->right);
	}

	int bfactor(node* p)   // серв≥сний метод. на ск≥льки висота правого плеча б≥льша за висоту л≥вого
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(node* p)  // серв≥сний метод. виправленн€ значенн€ висоти вузла п≥сл€ ман≥пул€ц≥й над ним.
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl>hr ? hl : hr) + 1;
	}

	node* rotateright(node* p) // правый поворот вокруг p
	{
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	node* rotateleft(node* q) // левый поворот вокруг q
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	node* balance(node* p) // балансировка узла p
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // балансировка не нужна
	}

	node* insert(node* p, const typeKey &k, const typeVal &v) // вставка ключа k в дерево с корнем p
	{
		if (!p) return new node(k,v);
		if (k<p->nodeKey)
			p->left = insert(p->left, k, v);
		else
			p->right = insert(p->right, k, v);
		return balance(p);
	}
	
	node* findmin(node* p) // поиск узла с минимальным ключом в дереве p (ой-йо...)
	{
		return p->left ? findmin(p->left) : p;
	}

	node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* remove(const typeKey &k, node* p) // удаление ключа k из дерева p
	{
		if (!p) return 0;
		if (k < p->nodeKey)
			p->left = remove(k, p->left);
		else if (k > p->nodeKey)
			p->right = remove(k, p->right);
		else //  k == p->key 
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	node* find(node *p, const typeKey &k) const 
	{
		if (!p)
			return nullptr;
		
		if (k < p->nodeKey) 
			find(p->left, k); 
		else if (k > p->nodeKey)
			find(p->right, k);
		else //k == p->nodeKey
			return n;
	}

	node *root;
	size_t size;


};


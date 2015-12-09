#pragma once
#include <utility>
#include <list>
#include <iomanip>
#include <string>

template <typename typeKey, typename typeVal>
class myMap
{
private:
	struct node; 
public:
	typedef typename std::pair<typeKey, typeVal> val;

	myMap() : root(nullptr) {}
	~myMap() {} // � �� ���� �� :)


	void push(const typeKey &k, const typeVal &v)
	{
	// node* insert(node* p, const typeKey &k, const typeVal &v) // ������� ����� k � ������ � ������ p
		root = insert(root, k, v);
	}

	void show()
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
	
	unsigned char height(node* p) // �������� �����, �� ������� ������ ��� ������ �����. ��� nullptr ������ - 0
	{							  // ������ ����� ������ ��������, ��� ��� �����...
		return p ? p->height : 0;
	}

private:
	struct node // ��������� ��� ������������� ����� ������
	{
		typeKey nodeKey;
		typeVal nodeVal;
		unsigned char height;
		node* left;
		node* right;
		node(const typeKey &k, const typeVal &v) { nodeKey = k; nodeVal=v, left = right = 0; height = 1; }
	};



	int bfactor(node* p)   // �������� �����. �� ������ ������ ������� ����� ����� �� ������ �����
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(node* p)  // �������� �����. ����������� �������� ������ ����� ���� ���������� ��� ���.
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl>hr ? hl : hr) + 1;
	}

	node* rotateright(node* p) // ������ ������� ������ p
	{
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	node* rotateleft(node* q) // ����� ������� ������ q
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	node* balance(node* p) // ������������ ���� p
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
		return p; // ������������ �� �����
	}

	//node* insert(const typeKey &k, const typeVal &v) // ������� ����� k � ������ � ������ p
	//{
	//	node* p = root;
	//	if (!p) return new node(k,v);
	//	if (k<p->nodeKey)
	//		p->left = insert(p->left, k, v);
	//	else
	//		p->right = insert(p->right, k, v);
	//	return balance(p);
	//}
	
	node* insert(node* p, const typeKey &k, const typeVal &v) // ������� ����� k � ������ � ������ p
	{
		if (!p) return new node(k,v);
		if (k<p->nodeKey)
			p->left = insert(p->left, k, v);
		else
			p->right = insert(p->right, k, v);
		return balance(p);
	}
	node* findmin(node* p) // ����� ���� � ����������� ������ � ������ p (��-��...)
	{
		return p->left ? findmin(p->left) : p;
	}

	node* removemin(node* p) // �������� ���� � ����������� ������ �� ������ p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* remove(const typeKey & k) // �������� ����� k �� ������ p
	{
		node* p = root;
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(k, p->left);
		else if (k > p->key)
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

	node* remove(const typeKey & k, node* p) // �������� ����� k �� ������ p
	{
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(k, p->left);
		else if (k > p->key)
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

	node *root;


};


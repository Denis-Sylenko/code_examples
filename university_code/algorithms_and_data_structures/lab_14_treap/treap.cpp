#include"pch.h"
#include <ctime> 
#include<iostream>
#include<string>


using namespace std;

template <typename TKey, typename TValue>
class Treap
{
private:
	template <typename TKey, typename TValue>
	struct Node;
public:
	Treap();
	~Treap();
	TKey get_minimum_key() const;
	TKey get_maximum_key() const;
	void add(const TKey& key, const TValue& data);
	void remove(const TKey& key);
	TValue& try_get_value(const TKey& key) const;
	Treap<TKey, TValue>& merge(const Treap<TKey, TValue>& another_treap);
	void split(const TKey& key, Treap<TKey, TValue>& left, Treap<TKey, TValue>& right);
	void print() const;
	void clear();
private:
	template <typename TKey, typename TValue>
	struct Node
	{
		TKey key;
		TValue data;
		double priority;

		Node* left;
		Node* right;

		double drand(void)
		{
			double ret = (double)rand() / ((double)rand() + 0.1);
			return ret - floor(ret);
		}

		Node(const TKey& _key = TKey(), const TValue& _data = TValue())
			: key(_key), data(_data), left(nullptr), right(nullptr)
		{
			priority = drand();
		}

		Node(const TKey& _key, const TValue& _data, double _priority, Node* _left = nullptr, Node* _right = nullptr)
			: key(_key), data(_data), priority(_priority), left(_left), right(_right)
		{ }

		~Node()
		{
			if (left) delete left;
			if (right) delete right;
		}
	};
	Node<TKey, TValue>* root;
	void _in_order_tree_walk(Node<TKey, TValue>* node) const;
	Node<TKey, TValue>* _get_copy(const Node<TKey, TValue>* const sub_tree) const;
	void _insert(Node<TKey, TValue>*& sub_tree_root, Node<TKey, TValue>* to_insert);
	void _delete(Node<TKey, TValue>*& sub_tree_root, const TKey& key);
	Node<TKey, TValue>* _search(Node<TKey, TValue>* node, const TKey& key) const;
	Node<TKey, TValue>* _merge(const Node<TKey, TValue>* const left, const Node<TKey, TValue>* const  right);
	void _split(const Node<TKey, TValue>* const source_tree_root, const TKey& key, Node<TKey, TValue>*& left, Node<TKey, TValue>*& right);
};

template<typename TKey, typename TValue>
Treap<TKey, TValue>::Treap()
	: root(nullptr)
{ }

template<typename TKey, typename TValue>
Treap<TKey, TValue>::~Treap()
{
	clear();
}

template<typename TKey, typename TValue>
TKey Treap<TKey, TValue>::get_minimum_key() const
{
	Node<TKey, TValue>* node = root;
	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node->key;
}

template<typename TKey, typename TValue>
 TKey Treap<TKey, TValue>::get_maximum_key() const
{
	Node<TKey, TValue>* node = root;
	while (node->right != nullptr)
	{
		node = node->right;
	}
	return node->key;
}

template<typename TKey, typename TValue>
 void Treap<TKey, TValue>::_insert(Node<TKey, TValue>*& sub_tree_root, Node<TKey, TValue>* to_insert)
{
	if (!sub_tree_root)
		sub_tree_root = to_insert;
	else if (to_insert->priority > sub_tree_root->priority)
		_split(sub_tree_root, to_insert->key, to_insert->left, to_insert->right), delete sub_tree_root, sub_tree_root = to_insert;
	else
		_insert(to_insert->key < sub_tree_root->key ? sub_tree_root->left : sub_tree_root->right, to_insert);
}

template<typename TKey, typename TValue>
 void Treap<TKey, TValue>::add(const TKey & key, const TValue & data)
{
	if (_search(root, key) != nullptr)
		return;
	Node<TKey, TValue>* to_insert = new Node<TKey, TValue>(key, data);
	_insert(root, to_insert);
}

template<typename TKey, typename TValue>
 void Treap<TKey, TValue>::_delete(Node<TKey, TValue>*& sub_tree_root, const TKey& key)
{
	if (sub_tree_root->key == key)
	{
		Node<TKey, TValue>* tmp = _merge(sub_tree_root->left, sub_tree_root->right);
		delete sub_tree_root;
		sub_tree_root = tmp;
	}
	else
	{
		_delete(key < sub_tree_root->key ? sub_tree_root->left : sub_tree_root->right, key);
	}
}

template<typename TKey, typename TValue>
 void Treap<TKey, TValue>::remove(const TKey & key)
{
	if (_search(root, key) == nullptr)
		return;
	_delete(root, key);
}

template<typename TKey, typename TValue>
 TValue & Treap<TKey, TValue>::try_get_value(const TKey & key) const
{
	Node<TKey, TValue>* node = _search(root, key);
	if (node != nullptr)
		return node->data;
	else
		throw runtime_error("");
}

template<typename TKey, typename TValue>
 Treap<TKey, TValue>& Treap<TKey, TValue>::merge(const Treap<TKey, TValue>& another_treap)
{
	if (get_maximum_key() < another_treap.get_minimum_key())
	{
		Treap<TKey, TValue>* new_treap = new Treap<TKey, TValue>();
		new_treap->root = _merge(root, another_treap.root);
		return *new_treap;
	}
	else
	{
		throw runtime_error("");
	}
}

template<typename TKey, typename TValue>
 Treap<TKey, TValue>::Node<TKey, TValue>* Treap<TKey, TValue>::_merge(const Node<TKey, TValue>* const left, const Node<TKey, TValue>* const right)
{
	if (left == nullptr) return _get_copy(right);
	if (right == nullptr) return _get_copy(left);

	if (left->priority > right->priority)
	{
		Node<TKey, TValue>* new_right = _merge(left->right, right);
		Node<TKey, TValue>* left_copy = _get_copy(left->left);
		return new Node<TKey, TValue>(left->key, left->data, left->priority, left_copy, new_right);
	}
	else
	{
		Node<TKey, TValue>* new_left = _merge(left, right->left);
		Node<TKey, TValue>* right_copy = _get_copy(right->right);
		return new Node<TKey, TValue>(right->key, right->data, right->priority, new_left, right_copy);
	}
}

template<typename TKey, typename TValue>
 void Treap<TKey, TValue>::split(const TKey& key, Treap<TKey, TValue>& left, Treap<TKey, TValue>& right)
{
	left.clear();
	right.clear();
	_split(root, key, left.root, right.root);
}

template<typename TKey, typename TValue>
 void Treap<TKey, TValue>::_split(const Node<TKey, TValue>* const source_tree_root, const TKey& key, Node<TKey, TValue>*& left, Node<TKey, TValue>*& right)
{
	if (source_tree_root == nullptr)
		return;

	Node<TKey, TValue>* new_subtree = nullptr;
	if (source_tree_root->key <= key)
	{
		if (source_tree_root->right == nullptr)
			right = nullptr;
		else
			_split(source_tree_root->right, key, new_subtree, right);
		Node<TKey, TValue>* left_copy = _get_copy(source_tree_root->left);
		left = new Node<TKey, TValue>(source_tree_root->key, source_tree_root->data, source_tree_root->priority, left_copy, new_subtree);
	}
	else
	{
		if (source_tree_root->left == nullptr)
			left = nullptr;
		else
			_split(source_tree_root->left, key, left, new_subtree);
		Node<TKey, TValue>* right_copy = _get_copy(source_tree_root->right);
		right = new Node<TKey, TValue>(source_tree_root->key, source_tree_root->data, source_tree_root->priority, new_subtree, right_copy);
	}
}

template<typename TKey, typename TValue>
 void Treap<TKey, TValue>::clear()
{
	delete root;
	root = nullptr;
}

template<typename TKey, typename TValue>
 void Treap<TKey, TValue>::print() const
{
	_in_order_tree_walk(root);
}

template<typename TKey, typename TValue>
 void Treap<TKey, TValue>::_in_order_tree_walk(Node<TKey, TValue>* node) const
{
	if (node != nullptr)
	{
		_in_order_tree_walk(node->left);
		std::cout << node->key << " : " << node->priority << " : " << node->data;
		std::cout << endl << "Left child: ";
		node->left ? std::cout << node->left->key << " : " << node->left->priority : std::cout << "nullptr";
		std::cout <<endl << "Right child: ";
		node->right ? std::cout << node->right->key << " : " << node->right->priority : std::cout << "nullptr";
		std::cout << endl;
		_in_order_tree_walk(node->right);
	}
}

template<typename TKey, typename TValue>
 Treap<TKey, TValue>::Node<TKey, TValue>* Treap<TKey, TValue>::_get_copy(const Node<TKey, TValue>* const sub_tree) const
{
	if (sub_tree == nullptr)
		return nullptr;

	Node<TKey, TValue>* newnode = new Node<TKey, TValue>(sub_tree->key, sub_tree->data, sub_tree->priority);
	newnode->left = _get_copy(sub_tree->left);
	newnode->right = _get_copy(sub_tree->right);

	return newnode;
}

template<typename TKey, typename TValue>
 Treap<TKey, TValue>::Node<TKey, TValue>* Treap<TKey, TValue>::_search(Node<TKey, TValue>* node, const TKey & key) const
{
	while (node != nullptr && key != node->key)
	{
		if (key < node->key)
			node = node->left;
		else node = node->right;
	}
	return node;
}

int main() {
	Treap<int, string> tr, tmp_left, tmp_right, tmp_tree;

	std::cout << "1 - Add element\n2 - Remove element\n3 - Split\n4 - Merge\n5 - Search\n6 - Print\n7 - Exit" << std::endl;
	int n, tmp = 0, tmp2 = 0;
	string tmp_string;
	bool exit = false;
	while (!exit) {
		std::cout << "Enter command: ";
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "Enter key and value: " <<  std::endl;
			cin >> tmp >> tmp_string;
			tr.add(tmp, tmp_string);
			std::cout << "Success! " << std::endl;
			break;
		case 2:
			std::cout << "Enter key: " << endl;
			cin >> tmp;
			tr.remove(tmp);
			break;
		case 3:
			tmp_left.clear();
			tmp_right.clear();
			cout << "Enter key" << endl;
			cin >> tmp;
			tr.split(tmp, tmp_left, tmp_right);
			cout << "Left tree:" << endl;
			tmp_left.print();
			cout << "Right tree:" << endl;
			tmp_right.print();
			break;
		case 4:
			tmp_left.clear();
			tmp_right.clear();
			cout << "Enter size of left tree:";
			cin >> tmp;
			for (int i = 0; i < tmp; ++i) {
				std::cout << "Enter key and value: " << std::endl;
				cin >> tmp2 >> tmp_string;
				tmp_left.add(tmp2, tmp_string);
			}
			cout << "Enter size of right tree:";
			cin >> tmp;
			for (int i = 0; i < tmp; ++i) {
				std::cout << "Enter key and value: " << std::endl;
				cin >> tmp2 >> tmp_string;
				tmp_right.add(tmp2, tmp_string);
			}
			tmp_left = tmp_left.merge(tmp_right);
			cout << "Merged tree:" << endl;
			tmp_left.print();
			break;
		case 5:
			std::cout << "Enter key: ";
			std::cin >> tmp;
			cout << tr.try_get_value(tmp) << endl;
			break;
		case 6:
			tr.print();
			break;
		case 7:
			exit = true;
			continue;
		default:
			std::cout << "Not in range!" << std::endl;
			break;
		}
	}

	return 0;
}
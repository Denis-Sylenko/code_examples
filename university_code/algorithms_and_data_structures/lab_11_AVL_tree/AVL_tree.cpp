// lab_sylenko.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

#pragma once
#include <string>

class KeyNotFoundException {};

template <typename TKey, typename TValue>
class AVLtree
{
public:
	AVLtree();
	AVLtree(const TKey& key, const TValue& data);
	AVLtree(const AVLtree<TKey, TValue>& anotherTree);
	~AVLtree();
	TValue& operator[](const TKey& key);
	AVLtree<TKey, TValue>& operator=(const AVLtree<TKey, TValue>& anotherTree);
	int get_size() { return size; }
	void Add(const TKey& key, const TValue& data);
	void Delete(const TKey& key);
	bool ContainsKey(const TKey& key);
	TValue& GetValue(const TKey& key);
	void print();
	void clear();
protected:
	template <typename TKey, typename TValue>
	struct Node
	{
		Node* left;
		Node* right;

		TKey key;
		TValue data;
		unsigned char height;

		Node(const TKey& _key = TKey(), const TValue& _data = TValue())
			: key(_key), data(_data)
		{
			left = nullptr;
			right = nullptr;
			height = 1;
		}

		~Node()
		{
			delete left;
			delete right;
		}
	};
	int size;
	Node<TKey, TValue>* root;
	void symetric(Node<TKey, TValue>* sub_tree);
	Node<TKey, TValue>* TreeSearch(Node<TKey, TValue>* sub_tree, const TKey& key);
	Node<TKey, TValue>* RemoveMin(Node<TKey, TValue>* sub_tree);
	Node<TKey, TValue>* MinimumKeyNode(Node<TKey, TValue>* node);
	Node<TKey, TValue>* GetCopy(Node<TKey, TValue>* sub_tree);

	unsigned char height(Node<TKey, TValue>* node);
	int balance_factor(Node<TKey, TValue>* node);
	void fix_height(Node<TKey, TValue>* node);
	Node<TKey, TValue>* rotate_right(Node<TKey, TValue>* node);
	Node<TKey, TValue>* rotate_left(Node<TKey, TValue>* node);
	Node<TKey, TValue>* balance(Node<TKey, TValue>* node);
	Node<TKey, TValue>* addition(Node<TKey, TValue>* sub_tree, const TKey& key, const TValue& data);
	Node<TKey, TValue>* deletion(Node<TKey, TValue>* sub_tree, const TKey& key);
};

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::AVLtree()
	: size(0), root(nullptr)
{ }

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::AVLtree(const TKey& rootKey, const TValue& rootData)
{
	size = 1;
	root = new Node<TKey, TValue>(rootKey, rootData);
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::AVLtree(const AVLtree<TKey, TValue>& anotherTree)
{
	size = anotherTree.size;
	root = GetCopy(anotherTree.root);
}

template<typename TKey, typename TValue>
inline AVLtree<TKey, TValue>::~AVLtree()
{
	clear();
}

template<typename TKey, typename TValue>
 TValue& AVLtree<TKey, TValue>::operator[](const TKey& key)
{
	return GetValue(key);
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>& AVLtree<TKey, TValue>::operator=(const AVLtree<TKey, TValue>& anotherTree)
{
	if (this != &anotherTree)
	{
		this->clear();
		size = anotherTree.size;
		root = GetCopy(anotherTree.root);
	}
	return *this;
}

template<typename TKey, typename TValue>
void AVLtree<TKey, TValue>::Add(const TKey& key, const TValue& data)
{
	root = addition(root, key, data);
}

template<typename TKey, typename TValue>
 void AVLtree<TKey, TValue>::Delete(const TKey & key)
{
	root = deletion(root, key);
}

template<typename TKey, typename TValue>
 bool AVLtree<TKey, TValue>::ContainsKey(const TKey& key)
{
	return TreeSearch(root, key) ? true : false;
}

template<typename TKey, typename TValue>
 TValue& AVLtree<TKey, TValue>::GetValue(const TKey& key)
{
	Node<TKey, TValue>* node = TreeSearch(root, key);
	if (node != nullptr)
		return node->data;
	else
		throw KeyNotFoundException();
}

template<typename TKey, typename TValue>
 void AVLtree<TKey, TValue>::print()
{
	 symetric(root);
}

template<typename TKey, typename TValue>
 void AVLtree<TKey, TValue>::clear()
{
	delete root;
}

template<typename TKey, typename TValue>
 void AVLtree<TKey, TValue>::symetric(Node<TKey, TValue>* sub_tree)
{
	if (sub_tree != nullptr)
	{
		std::cout << sub_tree->key << " : " << sub_tree->data << "\theight: " << (int)sub_tree->height << "\tbalance: " << balance_factor(sub_tree) << std::endl;

		symetric(sub_tree->left);
		symetric(sub_tree->right);
	}
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::Node<TKey, TValue>* AVLtree<TKey, TValue>::TreeSearch(Node<TKey, TValue>* sub_tree, const TKey& key)
{
	while (sub_tree != nullptr && key != sub_tree->key)
	{
		if (key < sub_tree->key)
			sub_tree = sub_tree->left;
		else sub_tree = sub_tree->right;
	}
	return sub_tree;
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::Node<TKey, TValue>* AVLtree<TKey, TValue>::RemoveMin(Node<TKey, TValue>* sub_tree)
{
	if (sub_tree->left == nullptr)
		return sub_tree->right;
	sub_tree->left = RemoveMin(sub_tree->left);
	return balance(sub_tree);
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::Node<TKey, TValue>* AVLtree<TKey, TValue>::MinimumKeyNode(Node<TKey, TValue>* node)
{
	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node;
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::Node<TKey, TValue>* AVLtree<TKey, TValue>::GetCopy(Node<TKey, TValue>* oldnode)
{
	if (oldnode == nullptr)
		return nullptr;

	Node<TKey, TValue>* newnode = new Node<TKey, TValue>(oldnode->key, oldnode->data);
	newnode->left = GetCopy(oldnode->left);
	newnode->right = GetCopy(oldnode->right);

	return newnode;
}

template<typename TKey, typename TValue>
 unsigned char AVLtree<TKey, TValue>::height(Node<TKey, TValue>* node)
{
	return node ? node->height : 0;
}

template<typename TKey, typename TValue>
 int AVLtree<TKey, TValue>::balance_factor(Node<TKey, TValue>* node)
{
	return height(node->right) - height(node->left);
}

template<typename TKey, typename TValue>
 void AVLtree<TKey, TValue>::fix_height(Node<TKey, TValue>* node)
{
	unsigned char height_left = height(node->left);
	unsigned char height_right = height(node->right);
	node->height = (height_left > height_right ? height_left : height_right) + 1;
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::Node<TKey, TValue>* AVLtree<TKey, TValue>::rotate_right(Node<TKey, TValue>* node)
{
	Node<TKey, TValue>* node_left = node->left;
	node->left = node_left->right;
	node_left->right = node;
	fix_height(node);
	fix_height(node_left);
	return node_left;
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::Node<TKey, TValue>* AVLtree<TKey, TValue>::rotate_left(Node<TKey, TValue>* node)
{
	Node<TKey, TValue>* node_right = node->right;
	node->right = node_right->left;
	node_right->left = node;

	fix_height(node);
	fix_height(node_right);
	return node_right;
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::Node<TKey, TValue>* AVLtree<TKey, TValue>::balance(Node<TKey, TValue>* node)
{
	fix_height(node);
	if (balance_factor(node) == 2)
	{
		if (balance_factor(node->right) < 0)
			node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	if (balance_factor(node) == -2)
	{
		if (balance_factor(node->left) > 0)
			node->left = rotate_left(node->left);
		return rotate_right(node);
	}
	return node;
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::Node<TKey, TValue>* AVLtree<TKey, TValue>::addition(Node<TKey, TValue>* sub_tree, const TKey& key, const TValue& data)
{
	if (!sub_tree)
	{
		size++;
		return new Node<TKey, TValue>(key, data);
	}
	if (key < sub_tree->key)
		sub_tree->left = addition(sub_tree->left, key, data);
	else
		if (key > sub_tree->key)
			sub_tree->right = addition(sub_tree->right, key, data);
		else
			sub_tree->data = data;
	return balance(sub_tree);
}

template<typename TKey, typename TValue>
 AVLtree<TKey, TValue>::Node<TKey, TValue>* AVLtree<TKey, TValue>::deletion(Node<TKey, TValue>* sub_tree, const TKey & key)
{
	if (!sub_tree) return nullptr;
	if (key < sub_tree->key)
		sub_tree->left = deletion(sub_tree->left, key);
	else if (key > sub_tree->key)
		sub_tree->right = deletion(sub_tree->right, key);
	else
	{
		Node<TKey, TValue>* left = sub_tree->left;
		Node<TKey, TValue>* right = sub_tree->right;
		sub_tree->left = nullptr;
		sub_tree->right = nullptr;
		delete sub_tree;
		size--;

		if (right == nullptr) return left;
		Node<TKey, TValue>* next_node = MinimumKeyNode(right);
		next_node->right = RemoveMin(right);
		next_node->left = left;
		return balance(next_node);
	}
	return balance(sub_tree);
}


int main()
{
	setlocale(LC_ALL, "rus");

	std::cout << " 1 - Добавить пару ключ-значение\n" << " 2 - Удалить пару ключ-значение\n"<< " 3 - Получить значение по ключу\n"
		<< " 4 - Проверить, содержит ли дерево данный ключ\n"<< " 5 - Получить количество узлов в дереве\n" 
		<< " 6 - Напечатать дерево\n"<< " 7 - Выход с программы\n";

	AVLtree<int, int> bt;
	int key;
	int value;
	int n;
	while (true)
	{
		std::cout << "\nВведите команду\n";
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "\nВведите пару ключ-значение: ";
			std::cin >> key >> value;
			bt.Add(key, value);
			std::cout << "\nУзел добавлен!\n";
			break;
		case 2:
			std::cout << "\nВведите ключ: ";
			std::cin >> key;
			bt.Delete(key);
			std::cout << "\nУзел удален!\n";
			break;
		case 3:
			std::cout << "\nВведите ключ: ";
			std::cin >> key;
			try
			{
				value = bt.GetValue(key);
				std::cout << "\nЗначение, хранящееся по ключу " << key << ": " << value << std::endl;
			}
			catch (KeyNotFoundException)
			{
				std::cout << "\nДанного ключа нет\n";
			}
			break;
		case 4:
			std::cout << "\nВведите ключ: ";
			std::cin >> key;
			if (bt.ContainsKey(key))
			{
				std::cout << "\nДерево содержит указанный ключ!\n";
			}
			else
			{
				std::cout << "\nДерево не содержит указанного ключа!\n";
			}
			break;
		case 5:
			std::cout << "\nКоличество узлов в дереве: " << bt.get_size() << std::endl;
			break;
		case 6:
			bt.print();
			break;
		case 7:
			exit(0);
			break;
		}
	}
}
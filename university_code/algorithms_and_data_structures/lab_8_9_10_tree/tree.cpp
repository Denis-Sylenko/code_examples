#include "pch.h"
#include <iostream>

class branch {
	public:
		branch(int new_data) {
			data = new_data;
			left_child = right_child = nullptr;
		}
	void add_node(branch*& _root, int new_data) {
	if (_root == nullptr) {
		_root = new branch(new_data);
		return;
	}

	if (new_data <= _root->data) {
		add_node(_root->left_child, new_data);
	}
	else if (new_data > _root->data) {
		add_node(_root->right_child, new_data);
	}
}

	void order_print(branch* root) {
	if (root == nullptr) { return;  }
	std::cout << root->data << std::endl;
	order_print(root->left_child);
	order_print(root->right_child);
}

	void inorder_print(branch* root) {
	if (root == nullptr) { return; }
	inorder_print(root->left_child);
	inorder_print(root->right_child);
	std::cout << root->data << std::endl;
}
	void symetric_print(branch* root) {
	if (root == nullptr) { return; }
	symetric_print(root->left_child);
	std::cout << root->data << std::endl;
	symetric_print(root->right_child);
	
}
	
	int get_node_data(branch* node) {
	return node->data;
}

	branch* search(branch* root, int key) {
	if (root == nullptr || root->data == key) {
		return root;
	}

	if (key < root->data) {
		return search(root->left_child, key);
	}
	else if (key > root->data) {
		return search(root->right_child, key);
	}
}

	branch* min_value_node(branch* root) {
	branch* current = root;

	while (current && current->left_child != nullptr) {
		current = current->left_child;
	}

	return current;
}

	branch* first_appear_order(branch* root, int key) {
	if (root == nullptr) { return root; }
	if (root->data == key) {
		return root;
	}
	first_appear_order(root->left_child, key);
	first_appear_order(root->right_child, key);
}

	branch* first_appear_inorder(branch* root, int key) {
	if (root == nullptr) { return root; }
	first_appear_inorder(root->left_child, key);
	first_appear_inorder(root->right_child, key);
	if (root->data == key) {
		return root;
	}
}

	int distance_order(branch* root, int key, int& counter, int& result) {
	if (root == nullptr) { return 0; }
	++counter;
	if (root->data == key) {
		result = counter;
		return counter;
	}
	distance_order(root->left_child, key, counter, result);
	distance_order(root->right_child, key, counter, result);
}

	int distance_inorder(branch* root, int key, int& counter,  int& result) {
	if (root == nullptr) { return 0; }
	
	distance_inorder(root->left_child, key, counter, result);
	distance_inorder(root->right_child, key, counter, result);

	++counter;
	if (root->data == key) {
		result = counter;
		return counter;
	}
}

	branch* delete_node(branch* root, int key) {
	if (root == nullptr) {
		return root;
	}

	if (key < root->data) {
		root->left_child = delete_node(root->left_child, key);
	}
	else if (key > root->data) {
		root->right_child = delete_node(root->right_child, key);
	}

	else {
		if (root->left_child == nullptr) {
			branch* tmp = root->right_child;
			delete root;
			return tmp;
		} else if (root->right_child == nullptr) {
			branch* tmp = root->left_child;
			delete root;
			return tmp;
		}

		branch* tmp = min_value_node(root->right_child);

		root->data = tmp->data;

		root->right_child = delete_node(root->right_child, tmp->data);
	}
	return root;

}
private:
	int data;
	branch* left_child;
	branch* right_child;
};

int main()
{
	std::cout << "Add root element" << std::endl;
	int root_element;
	std::cin >> root_element;
	branch* tree = new branch(root_element);
	branch* tmp_branch = tree;
	std::cout << "1 - Order print\n2 - Inorder print\n3 - Symetric print\n4 - Add element\n5 - Search\n6 - First appear order\n7 - First appear inorder\n8 - Distance order\n9 - Distance inorder\n10 - delete\n11 - Exit" << std::endl;
	int n, tmp = 0;
	bool exit = false;
	while (!exit) {
		int counter = -1, result = 0;
		std::cout << "Enter command: ";
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "Tree in order print version: " << std::endl;
			tree->order_print(tree);
			std::cout << std::endl;
			break;
		case 2:
			std::cout << "Tree in inorder print version: " << std::endl;
			tree->inorder_print(tree);
			std::cout << std::endl;
			break;
		case 3:
			std::cout << "Tree in symetric print version: " << std::endl;
			tree->symetric_print(tree);
			std::cout << std::endl;
			break;
		case 4:
			std::cout << "Enter element: ";
			std::cin >> tmp;
			tree->add_node(tree, tmp);
			std::cout << "Element was successfully added!";
			break;
		case 5:
			std::cout << "Enter key: ";
			std::cin >> tmp;
			tmp_branch = tree->search(tree, tmp);
			if (tmp_branch != nullptr) {
				std::cout << "Data: " << tmp_branch->get_node_data(tmp_branch) << " is stored by address " << tmp_branch << std::endl;
			}
			else {
				std::cout << "No such element in the tree" << std::endl;
			}
			break;
		case 6:
			std::cout << "Enter key: ";
			std::cin >> tmp;
			tmp_branch = tree->first_appear_order(tree, tmp);
			if (tmp_branch != nullptr) {
				std::cout << "Data: " << tmp_branch->get_node_data(tmp_branch) << " firstly appear by address " << tmp_branch << std::endl;
			}
			else {
				std::cout << "No such element in the tree" << std::endl;
			}
			break;
		case 7:
			std::cout << "Enter key: ";
			std::cin >> tmp;
			tmp_branch = tree->first_appear_inorder(tree, tmp);
			if (tmp_branch != nullptr) {
			std::cout << "Data: " << tmp_branch->get_node_data(tmp_branch) << " firstly appear by address " << tmp_branch << std::endl;
			}	
			else {
			std::cout << "No such element in the tree" << std::endl;
			}
			break;
		case 8:
			std::cout << "Enter key: ";
			std::cin >> tmp;
			tree->distance_order(tree, tmp, counter, result);
			std::cout << "Distance: " << result<< std::endl;
			break;
		case 9:
			std::cout << "Enter key: ";
			std::cin >> tmp;
			tree->distance_inorder(tree, tmp, counter, result);
			std::cout << "Distance: " << result << std::endl;
			break;
		case 10:
			std::cout << "Enter key: ";
			std::cin >> tmp;
			tree->delete_node(tree, tmp);
			std::cout << "Deleted" << std::endl;
			break;
		case 11:
			exit = true;
			continue;
		default:
			std::cout << "Not in range!" << std::endl;
			break;
		}
	}
	return 0;
}
#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <algorithm>
#include <list>
#include <stdexcept>
#include "doubly_linked_list.h"

template<typename T, template<typename > class Container = doubly_linked_list>
class avl_tree {
	using size_type = std::size_t;

private:
	struct node {
		node(const T& item) :
		_height(1), _left(nullptr), _right(nullptr), _item(item) {
		}

		size_type _height;
		node* _left;
		node* _right;
		T _item;
	};

	T& find(node* root, const T& item) {
		if (root != nullptr) {
			if (root->_item > item)
				return find(root->_left, item);
			if (root->_item < item)
				return find(root->_right, item);
			else {
				return root->_item;
			}
		}
		throw std::range_error("Item not found on the tree.");
	}

	size_type factor(node* root) const {
		return (root == nullptr) ?
		0 : height(root->_left) - height(root->_right);
	}

	size_type height(node* root) const {
		return (root == nullptr) ? 0 : root->_height;
	}

	node* insert(node* root, const T& item) {
		if (root == nullptr)
			return root = new node(item);

		else if (root->_item > item) {
			root->_left = insert(root->_left, item);

			if (factor(root) == 2) {

				if (factor(root->_left) == -1)
					root->_left = rotate_left(root->_left);

				root = rotate_right(root);
			}
		}

		else if (root->_item < item) {
			root->_right = insert(root->_right, item);

			if (factor(root) == -2) {

				if (factor(root->_right) == 1)
					root->_right = rotate_right(root->_right);

				root = rotate_left(root);
			}

		} else
		throw std::exception();

		root->_height = std::max(height(root->_left), height(root->_right)) + 1;
		return root;
	}

	node* rotate_left(node* root) {
		node* aux;
		aux = root->_right;
		root->_right = aux->_left;
		aux->_left = root;
		root->_height = std::max(height(root->_left), height(root->_right)) + 1;
		aux->_height = std::max(height(aux->_left), height(root)) + 1;
		return aux;
	}

	node* rotate_right(node* root) {
		node* aux;
		aux = root->_left;
		root->_left = aux->_right;
		aux->_right = root;
		root->_height = std::max(height(root->_left), height(root->_right)) + 1;
		aux->_height = std::max(height(aux->_left), height(root)) + 1;
		return aux;
	}

	node* remove(node* root, const T& item) {
		if (root == nullptr)
			throw std::exception();

		else if (root->_item > item) {
			root->_left = remove(root->_left, item);
			if (factor(root) == 2) {
				if (factor(root->_left) == -1)
					root = rotate_left(root->_left);
				root = rotate_right(root);
			}
		} else if (root->_item < item) {
			root->_right = remove(root->_right, item);

			if (factor(root) == -2) {
				if (factor(root->_right) == 1)
					root = rotate_right(root->_right);
				root = rotate_left(root);
			}
		}

		else {

			if (root->_left == nullptr && root->_right == nullptr) {
				delete root;
				return nullptr;
			}

			if (root->_left == nullptr) {
				node* aux = root->_right;
				delete root;
				return aux;
			}

			if (root->_right == nullptr) {
				node* aux = root->_left;
				delete root;
				return aux;
			}

			node* aux = root->_right;
			while (aux->_left != nullptr)
				aux = aux->_left;
			std::swap(root->_item, aux->_item);
			root->_right = remove(root->_right, item);
		}

		root->_height = std::max(height(root->_left), height(root->_right)) + 1;
		return root;
	}

	void in_order(node* root, Container<T>& container) const {
		if (root != nullptr) {
			in_order(root->_left, container);
			container.push_back(root->_item);
			in_order(root->_right, container);
		}
	}

	void pre_order(node* root, Container<T>& container) const {
		if (root != nullptr) {
			container.push_back(root->_item);
			pre_order(root->_left, container);
			pre_order(root->_right, container);
		}
	}

	void post_order(node* root, Container<T>& container) const {
		if (root != nullptr) {
			post_order(root->_left, container);
			post_order(root->_right, container);
			container.push_back(root->_item);
		}
	}

	node* recursive_copy(node* other_root) {
		node* aux = new node(other_root->_item);
		aux->_left = recursive_copy(other_root->_left);
		aux->_right = recursive_copy(other_root->_right);
		return aux;
	}

	void recursive_delete(node* root) {
		if (root != nullptr) {
			recursive_delete(root->_left);
			recursive_delete(root->_right);
			delete root;
		}
	}

	using self = avl_tree<T>;

public:
	avl_tree() :
	_size(0), _root(nullptr) {
	}

	avl_tree(const self& other) {
		_root = recursive_copy(other._root);
	}

	~avl_tree() {
		recursive_delete(_root);
	}

	T& find(const T& item) {
		return find(_root, item);
	}

	bool has(const T& item) {
		try {
			find(_root, item);
			return true;
		} catch (std::exception& e) {
			return false;
		}
	}

	size_type height() const {
		return height(_root);
	}

	size_type size() const {
		return _size;
	}

	void insert(const T& item) {
		_root = insert(_root, item);
		++_size;
	}

	void remove(const T& item) {
		_root = remove(_root, item);
		--_size;
	}

	Container<T> in_order() const {
		Container<T> container;
		in_order(_root, container);
		return container;
	}

	Container<T> pre_order() const {
		Container<T> container;
		pre_order(_root, container);
		return container;
	}

	Container<T> post_order() const {
		Container<T> container;
		post_order(_root, container);
		return container;
	}

private:
	size_type _size;
	node* _root;
};

#endif
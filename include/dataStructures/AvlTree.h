#ifndef _AvlTree_h_
#define _AvlTree_h_

#include <algorithm>
#include <list>
#include <stdexcept>

namespace dataStructures {

template<typename T>
class AvlTree {
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
		// If we find a null root, we found the right spot.
		if (root == nullptr)
			return root = new node(item);

		// If root's value is greater than inserted value, try to insert to the left.
		else if (root->_item > item) {
			root->_left = insert(root->_left, item);

			// If the factor of root unbalancing is 2, we have a left-left or left-right case.
			if (factor(root) == 2) {

				// If the factor of the left node is -1, we have a left-right case.
				if (factor(root->_left) == -1)
					root->_left = rotate_left(root->_left);

				// The tree is now guaranteedly a left-left case.
				root = rotate_right(root);
			}
		}

		// If root's value is lesser than inserted value, try to insert to the right.
		else if (root->_item < item) {
			root->_right = insert(root->_right, item);

			// If the factor of root unbalancing is -2, we have a right-left or right-right case.
			if (factor(root) == -2) {

				// If the factor of the right node is 1, we have a right-left case.
				if (factor(root->_right) == 1)
					root->_right = rotate_right(root->_right);

				// The tree is now guaranteedly a right-right case.
				root = rotate_left(root);
			}

			// If root's value is equal to inserted value, we have an exception.
			// TODO: find a better exception to throw.
		} else
			throw std::exception();

		// Recalculate the node height according to the insertion.
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
		// If we find a nullptr, the item does not exist in this tree.
		if (root == nullptr)
			throw std::exception();

		// The same of insertion works here. Find where the item must be, rebalance if needed.
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

		// If root's value is equal to removed value, we found the node to remove.
		else {

			// Leaf case: just delete the actual node.
			if (root->_left == nullptr && root->_right == nullptr) {
				delete root;
				return nullptr;
			}

			// If there is only right child, replace the to-be-deleted node and delete it.
			if (root->_left == nullptr) {
				node* aux = root->_right;
				delete root;
				return aux;
			}

			// If there is only left child, replace the to-be-deleted node and delete it.
			if (root->_right == nullptr) {
				node* aux = root->_left;
				delete root;
				return aux;
			}

			// If there are both children, find the immediately next value, swap and retry to remove.
			node* aux = root->_right;
			while (aux->_left != nullptr)
				aux = aux->_left;
			std::swap(root->_item, aux->_item);
			root->_right = remove(root->_right, item);
		}

		// Recalculate the node height according to the removal.
		root->_height = std::max(height(root->_left), height(root->_right)) + 1;
		return root;
	}	

	node* recursive_copy(node* other_root) {
		// To recursively copy, create a new node, recursively copy it's left and right child, then return it to be attached.
		node* aux = new node(other_root->_item);
		aux->_left = recursive_copy(other_root->_left);
		aux->_right = recursive_copy(other_root->_right);
		return aux;
	}

	void recursive_delete(node* root) {
		// To recursively delete, recursively delete both children if they exist, then delete.
		if (root != nullptr) {
			recursive_delete(root->_left);
			recursive_delete(root->_right);
			delete root;
		}
	}

	using self = AvlTree<T>;

public:
	AvlTree() :
			_size(0), _root(nullptr) {
	}

	AvlTree(const self& other) {
		_root = recursive_copy(other._root);
	}

	~AvlTree() {
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

	T** to_array() const {
		size_type _length = 1 << (height(_root) - 1);
		node** nodes = new node*[_length];
		T** items = new T*[_length];

		if (_size) {
			nodes[0] = _root;
			items[0] = new T(_root->_item);
			for (size_type i = 0, pos = 0; i < _length >> 1; ++i) {
				++pos;
				if (nodes[i] != nullptr) {
					nodes[pos] = nodes[i]->_left;
					items[pos] = new T(nodes[i]->_item);
					++pos;
					nodes[pos] = nodes[i]->_right;
					items[pos] = new T(nodes[i]->_item);
				} else {
					nodes[pos] = nullptr;
					items[pos] = nullptr;
					++pos;
					nodes[pos] = nullptr;
					items[pos] = nullptr;

				}
			}
		}
		delete[] nodes;

		return items;
	}

private:
	size_type _size;
	node* _root;
};
}
#endif
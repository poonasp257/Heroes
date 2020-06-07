#ifndef QUAD_TREE_H
#define QUAD_TREE_H

template<typename value_type>
class QuadTree {
private: 
	std::unique_ptr<QuadTreeNode<value_type>> rootNode;
	
public:
	QuadTree();
	~QuadTree();

	void insert(value_type value);
	void remove();
	void clear();
};

#include "QuadTree.hpp"

#endif
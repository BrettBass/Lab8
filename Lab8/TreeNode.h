#ifndef H_TreeNode
#define H_TreeNode

#include <queue>

enum{standard = 1, express, extreme};
struct Order {
	int qty;
	int shipping;
};

typedef struct TreeNode {
	std::queue<Order> Node;
	TreeNode* left, * right;
}TreeNode;
typedef struct TreeNode* BST_Tree;


BST_Tree buildTree();
void placeOrder(BST_Tree root);
void addOrder(TreeNode* root, Order input);

#endif
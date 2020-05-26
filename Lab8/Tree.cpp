#include "TreeNode.h"
#include "Helpers.h"

BST_Tree buildTree() {
	try {
		TreeNode* root = new TreeNode, * leftNode = new TreeNode, * rightNode = new TreeNode;
		root->left = leftNode; root->right = rightNode;
		return root;
	}
	catch (const std::bad_alloc&) {
		die("Memory leak: ");
	}

}

void placeOrder(BST_Tree root) {
	int amt, shipping;
	std::cout << "\nHow many Widgets would you like to order: ";
	amt = inputCheck(false, "bad input, Order amount must be a positive integer value above zero: ");
	std::cout << "Shipping Options\n\n[1]Extreme (50% markup)\n[2]BST_Tree (20% markup)\n[3]Standard (10% markup)\n____________________\n";
	shipping = inputCheck(true, "bad input, shipment options are 1,2, or 3 please try again: ");
	addOrder(root, Order{ amt, shipping });
}

void addOrder(TreeNode* root, Order input) {
	if (input.shipping == standard)
		root->Node.push(input);
	else if (input.shipping == extreme)
		root->left->Node.push(input);
	else //input.shipping == BST_Tree
		root->right->Node.push(input);
}
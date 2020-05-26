#include "WidgetStack.h"
#include "TreeNode.h"
#include "Helpers.h"





int main() {
	WidgetStack ISO;
	BST_Tree tree = buildTree();
	int choice;
	std::cout << "~~~~~Lab 8 Warehouse Lab Shipment Thingy~~~~~\n";
	do {
		choice = displayMenu();
		runMenu(choice, ISO, tree);
	} while (choice != 5);
}

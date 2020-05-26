#include "Helpers.h"
#include "TreeNode.h"

void processPriority(WidgetStack& ISO, BST_Tree root) {
	if (root->Node.empty()) return;
	processPriority(ISO, root->left);
	processPriority(ISO, root->right);
	processOrders(ISO, root->Node);
}

void processOrders(WidgetStack& widgets, std::queue<Order> tree) {
	int qty_shipped = 0, toBeShipped = 0;
	double warehouse_cost = 0;
	bool shipmentComplete = false;
	int markup;
	if (tree.front().shipping == standard) markup = 1.1;
	else if (tree.front().shipping == express) markup = 1.2;
	else markup = 1.5;
	for (bool new_order = true; !widgets.isEmpty() && !tree.empty();) {

		if (new_order) {
			shipmentHeader();
			qty_shipped = 0, warehouse_cost = 0, toBeShipped = tree.front().qty;
			shipmentComplete = false;
		}
		if (widgets.peek().qty >= toBeShipped) {
			qty_shipped += toBeShipped;
			warehouse_cost += widgets.peek().cost * toBeShipped;

			shipmentComplete = true; new_order = false;
			showDelivery(toBeShipped, widgets.peek().cost, markup);
			if (widgets.peek().qty == toBeShipped)
				widgets.pop();
			else {
				widgets.increaseInventory(-toBeShipped);
				widgets.peek().qty -= toBeShipped;
			}

		}

		else if (widgets.peek().qty < toBeShipped) {
			qty_shipped += widgets.peek().qty;
			toBeShipped -= widgets.peek().qty;
			warehouse_cost += widgets.peek().qty * widgets.peek().cost;
			showDelivery(widgets.peek().qty, widgets.peek().cost, markup);
			shipmentComplete = false;
			widgets.pop();
			new_order = false;
		}

		if (widgets.isEmpty() || shipmentComplete) {
			shipmentSummary(qty_shipped, toBeShipped, tree.front().qty, warehouse_cost, markup);
			new_order = true;
		}

		if (shipmentComplete) tree.pop();

	}
	if (widgets.isEmpty() && !tree.empty())
		std::cout << "\nEmpty Warehouse: " << tree.size() << " orders will be processed at a later date.\n";
	else if (!widgets.isEmpty() && tree.empty())
		std::cout << "\nAll orders have been processed, There are " << widgets.inventorySize() << " widgets available.\n";
}

void shipmentHeader() {
	using namespace std;
	cout << "\nSHIPMENT DETAILS\n"
		<< std::right << std::setw(15) << "Delivery #" << setw(15) << "QTY. SHIPPED" << setw(15) << "UNIT PRICE" << setw(20) << "COST TO WAREHOUSE" << setw(20) << "COST TO CUSTOMER\n";
}

void shipmentSummary(int qty, int toBeShipped, int order_qty, double w_cost, int markup) {
	using namespace std;
	bool incompleteOrder = order_qty > qty;
	static int orderNumber = 100, deliveryNumber = 600;
	cout << showpoint << fixed << setprecision(2);

	cout << "\nSHIPMENT SUMMARY" << "\nOrder Number" << right << setw(15) << orderNumber << '\n'
		<< "QTY. ORDERED" << setw(15) << order_qty << '\n'
		<< "QTY. SHIPPED" << setw(15) << qty << '\n'
		<< "QTY. TO BE SHIPPED" << setw(9) << (incompleteOrder ? order_qty - qty : 0) << '\n'
		<< "COST TO WAREHOUSE" << setw(10) << w_cost << '\n'
		<< "COST TO CUSTOMER" << setw(11) << w_cost * markup << '\n'
		<< "TOTAL PROFIT" << setw(15) << w_cost * (markup - 1) << '\n';
	if (!incompleteOrder) orderNumber++;
}

void showDelivery(int qty, double w_cost, int markup) {
	static int deliveryNumber = 600;
	double c_cost = w_cost * markup * qty;
	using namespace std;

	cout << showpoint << fixed << setprecision(2);
	cout << right << setw(15) << deliveryNumber++ << setw(15) << qty << setw(11) << '$' << w_cost << setw(16) << '$' << w_cost * qty << setw(15) << '$' << c_cost << '\n';

}

int displayMenu() {
	int choice;
	std::cout << "\n1. increase warehouse production.\n"
		"2. place order.\n"
		"3. Process orders.\n"
		"4. display inventory\n"
		"5. exit program\n\n";

	choice = inputCheck(false, "bad input, input must be an integer value 1-5: ");
	return choice;
}

void runMenu(int userInput, WidgetStack& ISO, BST_Tree tree) {
	static int orderNumber = 100;
	switch (userInput) {
	case 1:
		lineBreak;
		ISO.addWidgets();
		lineBreak;
		break;
	case 2:
		lineBreak;
		std::cout << "\norder #" << orderNumber++;
		placeOrder(tree);
		lineBreak;
		break;
	case 3:
		lineBreak;
		processPriority(ISO, tree);
		lineBreak;
		break;
	case 4:
		lineBreak;
		if (ISO.isEmpty()) std::cout << "There are no widgets left in our inventory\n\n";
		else ISO.inventoryReport();
		lineBreak;
		break;
	case 5:
		break;
	default:
		std::cout << "bad input, input must be an integer value 1-5: ";
	}
}

int inputCheck(const bool menu, const std::string& msg) {
	using namespace std;
	bool badInput; int input;
	do {
		badInput = false;
		cin >> input;
		if (!cin || menu && input > 3 || input < 1) {
			cout << msg;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			badInput = true;
		}
	} while (badInput);
	return input;
}

double dubCheck(const std::string& msg) {
	using namespace std;
	bool badInput; double input;
	do {
		badInput = false;
		cin >> input;
		if (!cin || input <= 0) {
			cout << msg;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			badInput = true;
		}
	} while (badInput);
	return input;
}

bool die(const std::string& msg) {
	std::cout << "error: " << msg << std::endl;
	exit(EXIT_FAILURE);
}
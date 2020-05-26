#include "WidgetStack.h"
#include "Helpers.h"

WidgetStack::~WidgetStack(){
	for (; top > -1; top--) 
		pop();
	
	inventory = 0; top = -1;
}

void WidgetStack::prepend(int qty, double cost) {
	stack[++top].qty = qty; inventory += qty;
	stack[top].cost = cost;
}

void WidgetStack::addWidgets() {
	int qty; double cost;

	std::cout << "\nWareHouse\nqty of Widgets: ";
	qty = inputCheck(false, "bad input, Production must be a positive value above zero: ");

	std::cout << "Cost: $";
	cost = dubCheck("bad input, qty must be a positive float/double value above zero: ");

	prepend(qty, cost);
}

void WidgetStack::pop() {
	if (top < 0)
		std::cout << "WidgetStack Underflow\n";
	else {
		inventory -= stack[top].qty;
		stack[top].qty = 0;
		stack[top--].cost = 0;
	}
}

void const WidgetStack::inventoryReport() {
	bool Order = stack[top].cost == 0;
	for (int i = top; i > -1; i--) {
		if (i < 100) {
				std::cout << "Widget price : $" << stack[i].cost << "\t" << "qty in stock: " << stack[i].qty << '\n';
		}
	}
	std::cout << "\n\n";
}

int inputCheck(const bool menu, const std::string& msg) {
	using namespace std;
	bool badInput; int input;
	do {
		badInput = false;
		cin >> input;
		if (!cin || menu && input > 5 || input <= 0) {
			cout << msg;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			badInput = true;
		}
	} while (badInput);
	return input;
}
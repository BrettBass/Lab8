#ifndef H_WidgetStack
#define H_WidgetStack

#include <iostream>


#define SIZE 100

struct Widget {
	int qty;
	double cost;
};

class WidgetStack {
private:
	Widget stack[SIZE];
	int top = -1, inventory = 0;
public:
	~WidgetStack();

	Widget& peek() { return stack[top]; }
	int getTop() { return top; }
	int inventorySize() { return inventory; }
	bool const isEmpty() { return top == -1; }

	void increaseInventory(int amt) { inventory += amt; }
	void prepend(int qty, double cost = 0);
	void addWidgets();
	void pop();
	void const inventoryReport();
};

#endif
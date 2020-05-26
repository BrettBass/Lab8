#ifndef H_Helpers
#define H_Helpers

#include <iostream>
#include <string>
#include <iomanip>
#include "WidgetStack.h"
#include "TreeNode.h"

#define lineBreak std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"

void processPriority(WidgetStack & ISO, BST_Tree root);
void processOrders(WidgetStack& widgets, std::queue<Order> tree);

void shipmentHeader();
void shipmentSummary(int qty, int toBeShipped, int order_qty, double w_cost, int markup);
void showDelivery(int qty, double w_cost, int markup);

int displayMenu();

void runMenu(int userInput, WidgetStack& ISO, BST_Tree tree);

double dubCheck(const std::string& msg);
int inputCheck(const bool menu, const std::string& msg);

bool die(const std::string& msg);

#endif
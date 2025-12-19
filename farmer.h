#ifndef FARMER_H
#define FARMER_H

#include<stdio.h>

#define PRODUCT_FILE "products.txt"
#define ORDER_FILE   "orders.txt"
#define NOTIFY_FILE  "notifications.txt"


#define CATEGORY_COUNT 9
#define UNIT_COUNT 4

static const char
*CATEGORIES[CATEGORY_COUNT] = {
    "Vegetable",
    "Fruit",
    "Rice & Grains",
    "Fish",
    "Meat",
    "Poultry",
    "Spices",
    "Dairy",
    "Others"
};

static const char
*UNITS[UNIT_COUNT] = {
    "kg",
    "g",
    "liter",
    "pcs"
};

typedef struct {
    int id;
    char name[100];
    char phonenum[20];
    char password[20];
    int type;
} Farmer;

typedef struct {
    int productID;
    int farmerID;
    char name[100];
    char category[40];
    char unit[10];
    float price;
    float quantity;
} Product;

typedef struct {
    int orderID;
    int productID;
    int farmerID;
    int consumerID;
    float quantity;
    float totalPrice;
    char status[15];
} Order;

typedef struct {
    int farmerID;
    int productID;
    char name[100];
    char msg[200];
} Notification;



void clearInputBuffer(void);
void removeNewLine(char *str);
int getNewProductID(void);


void addProduct(int farmerID);
void viewMyProducts(int farmerID);
void updateProduct(int farmerID);
void deleteProduct(int farmerID);


int updateProductQuantity(int productID, float orderedQty);
void notifyOutOfStock(int farmerID, const char *name, const char *msg);
void addNotification(int farmerID, int productID, const char *name, const char *msg);
void viewNotifications(int farmerID);


void viewOrders(int farmerID);
void approveOrder(int farmerID);
void markOrderDelivered(int farmerID);


void farmerDashboard(int farmerID);

#endif

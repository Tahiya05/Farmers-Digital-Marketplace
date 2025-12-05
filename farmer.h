#ifndef FARMER_H
#define FARMER_H

#define PRODUCT_FILE "products.txt"
#define ORDER_FILE   "orders.txt"
#define NOTIFY_FILE  "notifications.txt"


#define CATEGORY_COUNT 9
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

typedef struct {
    char name[100];
    char phone[20];
    char password[20];
} Farmer;

typedef struct {
    int productID;
    char productName[100];
    char category[40];
    float price;
    int quantity;
    int farmerID;
} Product;

typedef struct {
    int orderID;
    int productID;
    char productName[100];
    float price;
    int quantity;
    char consumerPhone[20];
    int farmerID;
} Order;

typedef struct {
    int farmerID;
    int productID;
    char productName[100];
    char message[200];
} Notification;



void clearInputBuffer(void);
void removeNewLine(char *str);
int getNewProductID(void);


void farmerDashboard(int farmerID);

void addProduct(int farmerID);
void viewMyProducts(int farmerID);
void updateProduct(int farmerID);
void deleteProduct(int farmerID);


void viewOrders(int farmerID);
int updateProductQuantity(int productID, int orderedQty);
void notifyOutOfStock(int farmerID, const char productName[]);

void addNotification(int farmerID, int productID, const char productName[], const char msg[]);
void viewNotifications(int farmerID);

#endif

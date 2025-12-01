#ifndef FARMER_H
#define FARMER_H

#define PRODUCT_FILE "products.txt"
#define ORDER_FILE   "orders.txt"



typedef struct {
    char name[50];
    char phone[20];
    char password[20];
} Farmer;

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
    char farmerPhone[20];
} Product;

typedef struct {
    int orderID;
    int productID;
    char productName[50];
    int quantity;
    char consumerPhone[20];
    char farmerPhone[20];
} Order;



void clearInputBuffer();
void removeNewLine(char *str);
int getNewProductID();


void addProduct(char farmerPhone[]);
void viewMyProducts(char farmerPhone[]);
void updateProduct(char farmerPhone[]);
void deleteProduct(char farmerPhone[]);
void viewOrders(char farmerPhone[]);

#endif

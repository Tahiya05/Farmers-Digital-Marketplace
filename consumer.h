#include<stdio.h>
#include<string.h>

#define MAX_CART 100
#define MAX_PRODUCTS 200

typedef struct{
  int id;
  char username[30];
  char password[30];
  char phonenum [30];
  int type;
}User;

typedef struct{
     int ProductID;
     int farmerID;
     char name[100];
     char category[40];
     char unit [10];
     float price;
     float quantity;
}Product;

typedef struct{
    char product[50];
    int quantity;
    float price;
}CartItem;

typedef struct {
    int orderID;
    int productID;
    int farmerID;
    int consumerID;
    char name[50];
    float quantity;
    float totalPrice;
    char status[15];
} Order;

typedef  struct{
    int ordrId;
    int productId;
    char product[50];
    int buyerId;
    char customer[50];
    int quantity;
    float price;
    float total;
}Transaction;

CartItem cart[MAX_CART];
int cartCount=0;

void consumerMenu();
void signup();
int consumerLogin();
void consumerDashboard(int consumerID);
void viewProducts(Product item[],int n);
void viewByCategory(Product item[],int n);
void searchProduct(Product item[],int n);
void addToCart(Product item[],int n);
int transactionID();
int placeOrder(int consumerID,Product item[],int n);
void orderHistory(int consumerID);
void feedback(int consumerID);

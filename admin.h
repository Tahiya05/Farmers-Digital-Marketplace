#ifndef ADMIN_H
#define ADMIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "user.h"

typedef struct {
    int productID;
    float quantitySold;
} Sale;

void adminDashboard();
void adminExistence();
int adminLogin();
void getMaskedPassword(char pass[]);
void logFailedAdminLogin(char username[]);
void viewFarmers();
void viewConsumers();
void viewProducts();
void viewTransactions();
void reportsMenu();
void viewFailedAdminLogins();
void viewTotalRevenue();
void recordSale(int productID, float quantity);
float getTotalSold(int productID);
void viewTopSellingProducts();
void topFarmers();
void topConsumers();
void systemStats();

#endif

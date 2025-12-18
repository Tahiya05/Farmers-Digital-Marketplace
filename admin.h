#ifndef ADMIN_H
#define ADMIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "user.h"

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
void viewTopSellingProducts();
void topFarmers();
void topConsumers();

#endif

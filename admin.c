#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<time.h>

#include "admin.h"

void adminDashboard()
{
    int choice;

    while(1){
        printf("\t====== ADMIN DASHBOARD ======\n");
        printf("1. View Farmers List\n");
        printf("2. View Consumers List\n");
        printf("3. View Products List\n");
        printf("4. View Transactions\n");
        printf("5. Generate Reports\n");
        printf("6. View Failed Login Logs\n");
        printf("7. Logout\n");
        printf("======================================\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                viewFarmers();
                break;
            case 2:
                viewConsumers();
                break;
            case 3:
                viewProducts();
                break;
            case 4:
                viewTransactions();
                break;
            case 5:
                reportsMenu();
                break;
            case 6:
                viewFailedAdminLogins();
                break;
            case 7:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Try again.\n");

        }
    }
}

void reportsMenu()
{
    int choice;

    while(1){
        printf("\t====== Reports ======\n");
        printf("1. Total Revenue\n");
        printf("2. Top Selling Products\n");
        printf("3. Top Performing Farmers\n");
        printf("4. Top Consumers\n");
        printf("5. Back\n");
        printf("======================================\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                viewTotalRevenue();
                break;
            case 2:
                viewTopSellingProducts();
                break;
            case 3:
                topFarmers();
                break;
            case 4:
                topConsumers();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void adminExistence()
{
    FILE *fp = fopen("users.dat","rb");
    if (fp==NULL) {
        fp=fopen("users.dat", "wb");
        if (!fp){
            printf("Error!\n");
            return;
        }
        user admin={1, "Admin", "01711234567", "admin@123", 0};
        fwrite(&admin, sizeof(user), 1, fp);

        fclose(fp);

        printf("Default admin created!\n");
        return;
    }
    fclose(fp);
}

void getMaskedPassword(char pass[])
{
    int i=0;
    char ch;

    while(1){
        ch=getch();

        if(ch==13){
            pass[i]='\0';
            break;
        }
        else if(ch==8){
            if(i>0){
                i--;
                printf("\b \b");
            }
        }
        else{
            pass[i++]=ch;
            printf("*");
        }
    }
}

void logFailedAdminLogin(char username[])
{
    FILE *fp;
    time_t t;
    struct tm *tm_info;
    char datetime[30];

    time(&t);
    tm_info=localtime(&t);
    strftime(datetime, 30, "%Y-%m-%d %H:%M:%S", tm_info);

    fp=fopen("admin_login_log.txt","a");
    if(fp==NULL) return;

    fprintf(fp,"[%s] FAILED Admin Login | Username: %s\n", datetime,username);

    fclose(fp);
}

int adminLogin()
{
    FILE *fp;
    user u;
    char username[30],pass[20];
    int attempt =0;
    int found;

    while(attempt<3){
        found=0;

        printf("\n===Admin Login (Attempt %d of 3)===\n",attempt+1);
        printf("Enter Admin Username: ");
        scanf("%s",username);
        printf("Enter Password: ");
        getMaskedPassword(pass);

        fp= fopen("users.dat", "rb");
        if(!fp){
        printf("File not found\n");
        return 1;
        }
        while (fread(&u, sizeof(user), 1, fp)){
            if (u.type==0 && strcmp(u.username, username)==0 && strcmp(u.password, pass)==0){
            found=1;
            break;
            }
        }

        fclose(fp);
        if(found){
            printf("\n\nLogin successful!\n");
            return 0;
        }
        else {
            printf("\nInvalid username or password.\n");
            logFailedAdminLogin(username);
        }
        attempt++;
    }

    printf("\nToo many failed attempts! Access Denied.\n");
    return 0;
}

void viewFarmers()
{
    FILE *fp=fopen("users.dat", "rb");
    if(fp==NULL){
        printf("Error opening file.\n");
        return;
    }
    user u;
    int found=0;

    printf("\t=====LIST OF FARMERS=====\n");

    while(fread(&u, sizeof(user), 1, fp)){
        if(u.type==1){
            found=1;
            printf("ID: %d\n", u.id);
            printf("Username: %s\n", u.username);
            printf("Phone Number: %s\n", u.phonenum);

            printf("\n-----------------------------------------\n");

        }
    }

    if(!found){
        printf("No farmers found.\n");
    }
    fclose(fp);
}

void viewConsumers()
{
    FILE *fp=fopen("users.dat", "rb");
    if(fp==NULL){
        printf("Error opening User File\n");
        return;
    }
    user u;
    int found=0;

    printf("\t=====LIST OF CONSUMERS=====\n");

    while(fread(&u, sizeof(user), 1, fp)){
        if(u.type==2){
            found=1;
            printf("ID: %d\n", u.id);
            printf("Username: %s\n", u.username);
            printf("Phone Number: %s\n", u.phonenum);

            printf("\n-----------------------------------------\n");

        }
    }

    if(!found){
        printf("No consumers found.\n");
    }
    fclose(fp);
}

void viewProducts()
{
    FILE *fp = fopen("products.txt","r");
    if(fp==NULL){
        printf("File missing\n.");
        return 1;
    }

    Product p;
    int found=0;

    printf("\t=====ALL PRODUCTS=====\n");
    printf("ID\tName\tPrice\tQuantity\tCategory\n");

    while(fscanf(fp, "%d \"%[^\"]\" %f %d \"%[^\"]\"",&p.productID, p.name, &p.price, &p.quantity, p.category)==5){
        found=1;
        printf"%d \t %s \t %.2f \t %d \t %s\n",p.productID, p.name, p.price, p.quantity, p.category);
    }
    if(!found){
        printf("\nNo products available!\n");
    }
    fclose(fp);
}

void viewTransactions()
{
    FILE *fp = fopen("transactions.txt", "r");
    if(fp==NULL){
        printf("Error opening Transactions file.\n");
        return;
    }

    int orderID, productID, buyerID, quantity;
    float total, price, revenue=0;
    char customer[50], product[50];
    int found=0;

    printf("\t======== All TRANSACTIONS ========\n");
    printf("OrderID\tProductID\tName\tBuyerID\tName\tQuantity\tPrice\tTotal\n");

    while(fscanf(fp, "%d %d \"%[^\"]\" %d \"%[^\"]\" %d %f %f",&orderID,&productID,product,&buyerID,customer,&quantity,&price,&total)==8){
        found=1;
        printf("%d\t%d\t%s\t%d\t%s\t%d\t%.2f\t%.2f",orderID,productID,product,buyerID,customer,quantity,price,total);
    }
    if(!found){
        printf("\nNo transactions done yet!\n");
    }
    fclose(fp);
}

void viewFailedAdminLogins()
{
    FILE *fp;
    char line[200];
    int empty=1;

    fp=fopen("admin_login_log.txt","r");
    if (fp==NULL){
        printf("\nNo failed login records found.\n");
        return;
    }

    printf("\n====FAILED ADMIN LOGIN ATTEMPTS====\n");

    while(fgets(line, sizeof(line),fp)){
        printf("%s",line);
        empty=0;
    }

    if(empty){
        printf("No failed login attempts recorded.\n");
    }

    fclose(fp);

    printf("\n==============================================\n");
}

void viewTotalRevenue()
{
    FILE *fp=fopen("transactions.txt", "r");
    if(fp==NULL){
        printf("No file found!\n");
        return;
    }

    int orderID, productID, buyerID, quantity;
    float total, price, revenue=0;
    char customer[50], product[50];

    while(fscanf(fp, "%d %d \"%[^\"]\" %d \"%[^\"]\" %d %f %f",&orderID,&productID,product,&buyerID,customer,&quantity,&price,&total)==8){
        revenue=revenue+total;
    }
    printf("Total Revenue: %.2f Tk\n",revenue);
    fclose(fp);
}

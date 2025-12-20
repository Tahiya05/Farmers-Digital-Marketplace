#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#define PRODUCT_FILE "products.txt"
#define ORDER_FILE   "orders.txt"
#define NOTIFY_FILE  "notifications.txt"


#define CATEGORY_COUNT 9
#define UNIT_COUNT 4
#define MAX_CART 100
#define MAX_PRODUCTS 200

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
    char username[50];
    char phonenum[50];
    char password[20];
    int type;
} User;

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
    char name[50];
    float quantity;
    float totalPrice;
    char status[15];
} Order;

typedef struct {
    int productID;
    float quantitySold;
} Sale;

typedef struct {
    int farmerID;
    int productID;
    char name[100];
    char msg[200];
} Notification;

typedef struct{
    int productID;
    int farmerID;
    char product[50];
    float quantity;
    float price;
}CartItem;

CartItem cart[MAX_CART];
int cartCount=0;

//Tahiya
void adminDashboard();
void adminExistence();
int adminLogin();
void getMaskedPassword(char pass[]);
void logFailedAdminLogin(char username[]);
void viewFarmers();
void viewConsumers();
int loadProducts(Product p[],int max);
void viewProductsAdmin();
void viewTransactions();
void reportsMenu();
void viewFailedAdminLogins();
void viewTotalRevenue();
void recordSale(int productID, float quantity);
float getTotalSold(int productID);
void topSellingProduct();
void topPerformingFarmer();
void systemStats();
void farmerRegister();
int farmerLogin();
void farmerMenu();

//Erfan
void clearInputBuffer(void);
void removeNewLine(char *str);
int getNewProductID(void);
void addProduct(int farmerID);
void viewMyProducts(int farmerID);
void updateProduct(int farmerID);
void deleteProduct(int farmerID);
int updateProductQuantity(int productID, float orderedQty);
void notifyOutOfStock(int farmerID, const char *name);
void addNotification(int farmerID, int productID, const char *name, const char *msg);
void viewNotifications(int farmerID);
void viewOrders(int farmerID);
void approveOrder(int farmerID);
void markOrderDelivered(int farmerID);
void farmerDashboard(int farmerID);

//Jasiya
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

int main()
{
    adminExistence();

    int choice;

    while(1){
        printf("\t\t\t\t\t============ FARMERS' DIGITAL MARKETPLACE ============\n");
        printf("WELCOME to the Marketplace!\n");
        printf("\nWho are you?\n");
        printf("1. Admin\n");
        printf("2. Farmer\n");
        printf("3. Consumer\n");
        printf("4. Exit\n");
        printf("======================================\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                adminLogin();
                break;
            case 2:
                farmerMenu();
                break;
            case 3:
                consumerMenu();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }

    }
    return 0;
}

void adminDashboard()
{
    int choice;

    while(1){
        printf("\n");
        printf("\t====== ADMIN DASHBOARD ======\n");
        printf("1. View Farmers List\n");
        printf("2. View Consumers List\n");
        printf("3. View Products List\n");
        printf("4. View Transactions\n");
        printf("5. Generate Reports\n");
        printf("6. View Failed Login Logs\n");
        printf("7. System Statistics\n");
        printf("8. Logout\n");
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
                viewProductsAdmin();
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
                systemStats();
                break;
            case 8:
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
        printf("\n");
        printf("\t====== Reports ======\n");
        printf("1. Total Revenue\n");
        printf("2. Top Selling Product\n");
        printf("3. Top Performing Farmer\n");
        printf("4. Top Consumer\n");
        printf("5. Back\n");
        printf("======================================\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                viewTotalRevenue();
                break;
            case 2:
                topSellingProduct();
                break;
            case 3:
                topPerformingFarmer();
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
    FILE *fp = fopen("admin.dat","rb");
    if (fp==NULL) {
        fp=fopen("admin.dat", "wb");
        if (!fp){
            printf("Error!\n");
            return;
        }
        User admin={1, "Admin", "01711234567", "admin@123", 0};
        fwrite(&admin, sizeof(User), 1, fp);

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
    User u;
    char username[30],pass[20];
    int attempt =0;
    int found;

    while(attempt<3){
        found=0;

        printf("\t==== Admin Login (Attempt %d of 3) ====\n",attempt+1);
        printf("Enter Admin Username: ");
        scanf("%s",username);
        printf("Enter Password: ");
        getMaskedPassword(pass);

        fp= fopen("admin.dat", "rb");
        if(!fp){
        printf("File not found\n");
        return 1;
        }
        while (fread(&u, sizeof(User), 1, fp)){
            if (u.type==0 && strcmp(u.username, username)==0 && strcmp(u.password, pass)==0){
            found=1;
            break;
            }
        }

        fclose(fp);
        if(found){
            printf("\n\nLogin successful!\n");
            adminDashboard();
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
    FILE *fp=fopen("farmers.dat", "rb");
    if(fp==NULL){
        printf("Error opening file.\n");
        return;
    }
    User u;
    int found=0;

    printf("\t===== LIST OF FARMERS =====\n");

    while(fread(&u, sizeof(User), 1, fp)){
        if(u.type==1){
            found=1;
            printf("ID: %d\n", u.id);
            printf("Name: %s\n", u.username);
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
    FILE *fp=fopen("consumers.dat", "rb");
    if(fp==NULL){
        printf("Error opening User File\n");
        return;
    }
    User u;
    int found=0;

    printf("\t===== LIST OF CONSUMERS =====\n");

    while(fread(&u, sizeof(User), 1, fp)){
        if(u.type==2){
            found=1;
            printf("ID: %d\n", u.id);
            printf("Name: %s\n", u.username);
            printf("Phone Number: %s\n", u.phonenum);

            printf("\n-----------------------------------------\n");

        }
    }

    if(!found){
        printf("No consumers found.\n");
    }
    fclose(fp);
}

int loadProducts(Product p[],int max)
{
    FILE *fp=fopen("products.txt","r");
    if(fp==NULL){
        printf("File missing.\n");
        return 0;
    }

    int count=0;
    char line[300];

    while(fgets(line,sizeof(line),fp)&& count<max){
        if(sscanf(line, "%d|%d|%99[^|]|%39[^|]|%9[^|]|%f|%f", &p[count].productID, &p[count].farmerID, p[count].name, p[count].category, p[count].unit,
           &p[count].price, &p[count].quantity)==7){
            count++;
           }
    }
    fclose(fp);
    return count;
}

void viewProductsAdmin()
{
    Product p[100];
    int n = loadProducts(p, 100);

    if(n==0){
        printf("\nNo products available!\n");
        return;
    }

    printf("\t===== ALL PRODUCTS =====\n");
    printf("ID\tName\t\tPrice\tQuantity\tUnit\tCategory\n");

    for(int i=0;i<n;i++){
        printf("%d\t%s\t%.2f\t%.2f\t\t%s\t%s\n", p[i].productID, p[i].name,
                p[i].price, p[i].quantity,p[i].unit, p[i].category);
    }
}

void viewTransactions()
{
    FILE *fp = fopen("orders.txt", "r");
    if(fp==NULL){
        printf("Error opening Transactions file.\n");
        return;
    }

    char line[512];
    int found = 0;
    Order o;


    printf("\t===== All Transactions =====\n");
    printf("%-8s  %-10s  %-10s  %-12s  %-15s  %-8s %-10s %-12s\n",
           "OrderID", "ProductID", "FarmerID", "ConsumerID",
           "Product", "Qty", "Total", "Status");
    printf("------------------------------------------------------------------------\n");

    while(fgets(line, sizeof(line), fp)) {

        if(sscanf(line, "%d|%d|%d|%d|%30[^|]|%f|%f|%14[^|]",&o.orderID, &o.productID, &o.farmerID,
                        &o.consumerID, o.name, &o.quantity, &o.totalPrice, o.status) == 8) {
             found = 1;
             printf("%-8d %-10d  %-10d  %-12d  %15s %-8.2f  %-10.2f  %-12s\n",
                        o.orderID, o.productID, o.farmerID, o.consumerID,
                        o.name, o.quantity, o.totalPrice, o.status);

    printf("----------------------------------------------------------------------\n");
        }
    }

    if(!found){
        printf("\nNo transactions found.\n");
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

    printf("\t==== FAILED ADMIN LOGIN ATTEMPTS ====\n");

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
    FILE *fp=fopen("orders.txt", "r");
    if(fp==NULL){
        printf("No file found!\n");
        return;
    }

    char line[512];
    Order o;
    float totalRevenue = 0.0;
    int found = 0;

    while(fgets(line, sizeof(line),fp)){
        if(sscanf(line,"%d|%d|%d|%d|%30[^|]|%f|%f|%14[^|]",
        &o.orderID,&o.productID,&o.farmerID, &o.consumerID, o.name, &o.quantity,&o.totalPrice,o.status)==8){
        totalRevenue+= o.totalPrice;
        found = 1;
        }
    }

    fclose(fp);

    printf("\n========= Total Platform Revenue =========\n");

    if(!found) printf("No transactions found.\n");
    else printf("Total Revenue: %.2f Tk\n",totalRevenue);
}

void recordSale(int productID, float quantity)
{
    FILE *fp = fopen("sales.dat","ab");
    if(fp==NULL){
        printf("Error opening sales file!\n");
        return;
    }

    Sale s;
    s.productID = productID;
    s.quantitySold = quantity;

    fwrite(&s, sizeof(Sale), 1, fp);
    fclose(fp);
}

float getTotalSold(int productID)
{
    FILE *fp = fopen("sales.dat","rb");
    if(fp==NULL){
        printf("File not found!\n");
        return 0;
    }

    Sale s;
    float total =0;

    while(fread(&s, sizeof(Sale),1,fp)){
        if(s.productID==productID){
            total+=s.quantitySold;
        }
    }

    fclose(fp);
    return total;
}

void topSellingProduct()
{
    Product p[100];
    int n = loadProducts(p, 100);

    if(n==0){
        printf("\nNo products available!\n");
        return;
    }

    int maxIndex = -1;
    float maxSold = 0;

    for(int i=0; i<n; i++){
        float sold = getTotalSold(p[i].productID);
        if(sold>maxSold){
            maxSold = sold;
            maxIndex = i;
        }
    }

    if(maxIndex== -1){
        printf("\nNo sales recorded yet!\n");
        return;
    }

     printf("\nTop-Selling Product:\n");
     printf("Product ID   : %d\n",p[maxIndex].productID);
     printf("Name         : %s\n",p[maxIndex].name);
     printf("Category     : %s\n",p[maxIndex].category);
     printf("Sold Quantity: %.2f %s\n",maxSold,p[maxIndex].unit);
}

void topPerformingFarmer()
{
    FILE *fp = fopen("orders.txt", "r");
    if (fp==NULL){
        printf("Error opening transactions file.\n");
        return;
    }

    int farmerIDs[100];
    float farmerRevenue[100];
    int farmerCount=0;

    char line[512];
    Order o;
    int found;

    while (fgets(line, sizeof(line),fp)){
        if (sscanf(line,"%d|%d|%d|%d|%30[^|]|%f|%f|%14[^|]",
            &o.orderID,&o.productID,&o.farmerID, &o.consumerID, o.name, &o.quantity,&o.totalPrice,o.status)==8){
            found = 0;

            for(int i=0; i<farmerCount;i++){
                if(farmerIDs[i]==o.farmerID){
                    farmerRevenue[i]+=o.totalPrice;
                    found=1;
                    break;
                }
            }

            if(!found){
                farmerIDs[farmerCount]=o.farmerID;
                farmerRevenue[farmerCount]=o.totalPrice;
                farmerCount++;
            }
        }
    }
    fclose(fp);

    if(farmerCount==0){
        printf("\nNo transactions found.\n");
        return;
    }

    int topIndex =0;
    for(int i=1; i<farmerCount;i++){
        if(farmerRevenue[i]>farmerRevenue[topIndex]){
            topIndex=i;
        }
    }
    printf("\t======== TOP PERFORMING FARMER ========\n");
    printf("Farmer ID     :%d\n", farmerIDs[topIndex]);
    printf("Total Revenue :%.2f\n", farmerRevenue[topIndex]);
}

void systemStats()
{
    Product p[100];
    int n = loadProducts(p, 100);

    if(n==0){
        printf("\nNo products available!\n");
        return;
    }

    FILE *fp=fopen("farmers.dat", "rb");
    if(fp==NULL){
        printf("Error opening farmer file.\n");
        return;
    }

    FILE *ff=fopen("consumers.dat", "rb");
    if(fp==NULL){
        printf("Error opening consumer file.\n");
        return;
    }

    User u;
    int totalfarmers=0, totalconsumers=0;

    while(fread(&u, sizeof(User), 1, fp)){
        if(u.type==1) totalfarmers++;
    }
    fclose(fp);

    while(fread(&u, sizeof(User), 1, ff)){
        if(u.type==2) totalconsumers++;
    }
    fclose(ff);


    FILE *fs = fopen("sales.dat","rb");
    if(fs==NULL){
        printf("File not found!\n");
        return;
    }
    float totalSold=0;

    Sale s;

    if(fs != NULL) {
        while(fread(&s, sizeof(Sale), 1, fs)){
            totalSold +=s.quantitySold;
        }
        fclose(fs);
    }

    int maxIndex = -1;
    float maxSold = 0;

    for(int i=0; i<n; i++){
        float sold = getTotalSold(p[i].productID);
        if(sold>maxSold){
            maxSold = sold;
            maxIndex = i;
        }
    }

    printf("\t===== SYSTEM STATISTICS =====\n");
    printf("Total Products      : %d\n", n);
    printf("Total Farmers       : %d\n", totalfarmers);
    printf("Total Consumers     : %d\n", totalconsumers);
    printf("Total Quantity Sold : %.2f units\n", totalSold);

    if(maxIndex != -1){
        printf("\nTop-Selling Product:\n");
        printf("Product ID   : %d\n",p[maxIndex].productID);
        printf("Name         : %s\n",p[maxIndex].name);
        printf("Category     : %s\n",p[maxIndex].category);
        printf("Sold Quantity: %.2f %s\n",maxSold,p[maxIndex].unit);
    }
    else printf("\nNo sales recorded yet.\n");
}

void farmerMenu()
{
    int choice;

     while(1){
        printf("\n");
        printf("\t====== WELCOME FARMERS! ======\n");
        printf("What would you like to do?\n");
        printf("1. Sign up\n");
        printf("2. Login\n");
        printf("3. Back\n");
        printf("======================================\n");
        printf("Enter choice: ");
        scanf("%d",&choice);


    switch(choice){
        case 1:farmerRegister();
            break;
        case 2: farmerLogin();
            break;
        case 3:
             return;
        default: printf("\nInvalid choice! Try again.\n");
            break;
    }
  }
}

void farmerRegister()
{
    FILE *fp=fopen("farmers.dat", "ab+");
    if (fp==NULL){
        printf("Error opening farmer file\n");
        return;
    }

    User u,temp;
    char phone[20];

    printf("\t===== FARMER REGISTRATION =====\n");

    printf("Enter your phone number: ");
    scanf("%s", phone);

    rewind(fp);
    while(fread(&temp,sizeof(User),1,fp)){
        if (strcmp(temp.phonenum, phone)==0 && temp.type==1){
            printf("Farmer with this phone number already exists!\n");
            fclose(fp);
            return;
        }
    }

    strcpy(u.phonenum, phone);

    printf("Enter Your Full Name: ");
    getchar();
    fgets(u.username,sizeof(u.username),stdin);

    u.username[strcspn(u.username,"\n")]='\0';

    printf("Enter Password: ");
    scanf("%s",u.password);

    u.type=1;

    u.id=10001;

    rewind(fp);
    while(fread(&temp, sizeof(User), 1, fp)){
        if(temp.id>=u.id) u.id=temp.id+1;
    }

    fwrite(&u, sizeof(User), 1, fp);

    printf("\nRegistration Successful! Your Farmer ID is: %d\n", u.id);

    fclose(fp);
}

int farmerLogin()
{
    FILE *fp=fopen("farmers.dat", "rb");
    if (fp==NULL){
        printf("Error opening User File\n");
        return -1;
    }
    char number[20],password[20];
    User u;

    printf("\t===== FARMER LOGIN =====\n");

    printf("Enter Phonenumber: ");
    scanf("%s",number);

    printf("Enter Password: ");
    scanf("%s", password);

    while(fread(&u, sizeof(User), 1, fp)){
        if(u.type==1 && strcmp(u.phonenum, number)==0 && strcmp(u.password,password)==0){
            printf("\nLogin Successful! Welcome %s (ID: %d)\n", u.username, u.id);
            farmerDashboard(u.id);
            fclose(fp);
            return u.id;
        }
    }
    printf("\nInvalid Phone Number or Password.\n");
    fclose(fp);
    return -1;

}

void clearInputBuffer(void)
 {
     int c;
     while((c=getchar()) != '\n' && c != EOF);

 }

 void removeNewLine(char *str)
 {
     int len=strlen(str);

     if(str[len - 1] == '\n'){
        str[len - 1] = '\0';
     }
 }

 int getNewProductID(void)
 {
     FILE *fp = fopen(PRODUCT_FILE, "r");
     if(fp == NULL) return 1;

     int maxID = 0;
     char line[200];

     while(fgets(line, sizeof(line), fp)){
         int id;
         if(sscanf(line, "%d|", &id) == 1){
            if(id > maxID) maxID = id;
           }
      }
     fclose(fp);
     return maxID + 1;
 }


 void farmerDashboard(int farmerID)
 {
     int choice;

     do{
        printf("\t===== FARMER DASHBOARD (Farmer ID: %d) =====\n", farmerID);
        printf("1. Add Product\n");
        printf("2. View My Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. View Orders\n");
        printf("6. Approve Order\n");
        printf("7. Mark Order Delivered\n");
        printf("8. View Notifications\n");
        printf("0. Log Out\n");

        printf("Enter your choice: ");

        if(scanf("%d",&choice) != 1) {
            printf("Invalid input. Try again.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch(choice){
            case 1:
                addProduct(farmerID);
                break;

            case 2:
                viewMyProducts(farmerID);
                break;

            case 3:
                updateProduct(farmerID);
                break;

            case 4:
                deleteProduct(farmerID);
                break;

            case 5:
                viewOrders(farmerID);
                break;

            case 6:
                approveOrder(farmerID);
                break;

            case 7:
                markOrderDelivered(farmerID);
                break;


            case 8:
                viewNotifications(farmerID);
                break;

            case 0:
                printf("Logging Out...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    while(choice != 0);

 }

 void addProduct(int farmerID)
 {
     Product p;

     printf("\t===== ADD NEW PRODUCT =====\n");

     p.productID = getNewProductID();
     p.farmerID = farmerID;


     printf("Enter Product Name (no commas): ");
     if(!fgets(p.name, sizeof(p.name), stdin)){
        printf("Input error.\n");
        return;
     }
     removeNewLine(p.name);
     if(strlen(p.name) == 0 || strchr(p.name, ',') != NULL) {
        printf("Invalid product name (empty or contains comma).\n");
        return;
     }


     printf("Select Category:\n");
     for(int i = 0; i < CATEGORY_COUNT; i++) {
        printf("%d. %s\n", i+1, CATEGORIES[i]);
     }
     printf("Enter choice (1-%d): ", CATEGORY_COUNT);

     int ch;
     if(scanf("%d", &ch) != 1) {
        clearInputBuffer();
        printf("Invalid input.\n");
        return;
     }
     clearInputBuffer();

     if(ch < 1 || ch > CATEGORY_COUNT){
        printf("Invalid option.\n");
        return;
     }
     strncpy(p.category, CATEGORIES[ch-1], sizeof(p.category)-1);
     p.category[sizeof(p.category)-1] = '\0';



     printf("Select Unit:\n");
     for(int i = 0; i < UNIT_COUNT; i++) {
        printf("%d. %s\n", i+1, UNITS[i]);
     }
     printf("Enter choice (1-%d): ", UNIT_COUNT);

     int chUnit;
     if(scanf("%d", &chUnit) != 1) {
        clearInputBuffer();
        printf("Invalid input.\n");
        return;
     }
     clearInputBuffer();

     if(chUnit < 1 || chUnit > UNIT_COUNT){
        printf("Invalid option.\n");
        return;
     }
     strncpy(p.unit, UNITS[chUnit-1], sizeof(p.unit)-1);
     p.unit[sizeof(p.unit)-1] = '\0';


     printf("Enter Price (per unit): ");
     if(scanf("%f", &p.price) != 1) {
        clearInputBuffer();
        printf("Invalid price.\n");
        return;
     }
     clearInputBuffer();

     printf("Enter Quantity in %s (float): ", p.unit);
     if(scanf("%f", &p.quantity) != 1) {
        clearInputBuffer();
        printf("Invalid quantity.\n");
        return;
     }
     clearInputBuffer();



     FILE *fp = fopen(PRODUCT_FILE, "a");
     if(fp == NULL){
        printf("Error opening products file!\n");
        return;
     }

     fprintf(fp, "%d|%d|%s|%s|%s|%0.2f|%0.2f\n",
             p.productID, p.farmerID,
             p.name, p.category,
             p.unit, p.price, p.quantity);

     fclose(fp);

     printf("\nProduct Added Successfully!\n");
     printf("\nID: %d\nName: %s\nCategory: %s\nPrice: %0.2f per %s\nQuantity: %0.2f %s\n",
               p.productID, p.name, p.category, p.price, p.unit, p.quantity, p.unit);

 }

 void viewMyProducts(int farmerID)
 {
     FILE *fp = fopen(PRODUCT_FILE, "r");
     if(fp == NULL){
        printf("No products found (products file missing).\n");
        return;
     }

     char line[512];
     int found=0;

     printf("\t===== MY PRODUCTS =====\n");
     printf("%-6s  %-30s  %-15s  %-8s  %-8s  %-8s\n", "ID", "Name", "Category", "Price", "Qty", "Unit");

     printf("-----------------------------------------------------------------------------------\n");

     while(fgets(line, sizeof(line), fp)){
            Product p;
        if(sscanf(line, "%d|%d|%99[^|]|%39[^|]|%9[^|]|%f|%f\n",
                  &p.productID, &p.farmerID, p.name, p.category,
                   p.unit, &p.price, &p.quantity) == 7) {

            if(p.farmerID == farmerID){
                found = 1;
                printf("%-6d  %-30s  %-15s  %-8.2f  %-8.2f  %-8s\n",
                        p.productID, p.name, p.category, p.price, p.quantity, p.unit);
            }
        }
     }
     if(!found){
        printf("\nYou have no listed products.\n");
     }

     fclose(fp);

 }

 void updateProduct(int farmerID)
 {
     int targetID, found = 0, choice;
     Product p;

     printf("\t===== UPDATE PRODUCT =====\n");
     printf("Enter Product ID to update: ");

     if (scanf("%d", &targetID) != 1) {
         clearInputBuffer();
         printf("Invalid Product ID.\n");
         return;
     }
     clearInputBuffer();

     FILE *fp = fopen(PRODUCT_FILE, "r");
     FILE *temp = fopen("temp_products.txt", "w");

     if (fp == NULL || temp == NULL) {
         printf("File error.\n");
         if (fp) fclose(fp);
         if (temp) fclose(temp);
         return;
     }

     while (fscanf(fp, "%d|%d|%99[^|]|%39[^|]|%9[^|]|%f|%f\n",
                       &p.productID, &p.farmerID, p.name,
                       p.category, p.unit, &p.price,
                       &p.quantity) == 7) {

        if (p.productID == targetID && p.farmerID == farmerID) {
            found = 1;

            printf("\nCurrent Details:\n");
            printf("Name     : %s\n", p.name);
            printf("Category : %s\n", p.category);
            printf("Price    : %.2f\n", p.price);
            printf("Quantity : %.2f\n", p.quantity);
            printf("Unit     : %s\n", p.unit);


            printf("\nWhat do you want to update?\n");
            printf("1. Price\n");
            printf("2. Quantity\n");
            printf("3. Both\n");
            printf("Enter choice: ");

            if (scanf("%d", &choice) != 1) {
                clearInputBuffer();
                printf("Invalid choice.\n");
                fclose(fp);
                fclose(temp);
                remove("temp_products.txt");
                return;
            }
            clearInputBuffer();

            if (choice == 1 || choice == 3) {
                printf("Enter New Price: ");
                if (scanf("%f", &p.price) != 1) {
                    clearInputBuffer();
                    printf("Invalid price.\n");
                    fclose(fp);
                    fclose(temp);
                    remove("temp_products.txt");
                    return;
                }
                clearInputBuffer();
            }

            if (choice == 2 || choice == 3) {
                printf("Enter New Quantity in %s(float): ", p.unit);
                if (scanf("%f", &p.quantity) != 1) {
                    clearInputBuffer();
                    printf("Invalid quantity.\n");
                    fclose(fp);
                    fclose(temp);
                    remove("temp_products.txt");
                    return;
                }
                clearInputBuffer();
            }

            printf("\nID: %d\nName: %s\nCategory: %s\nPrice: %0.2f per %s\nQuantity: %0.2f %s\n",
               p.productID, p.name, p.category, p.price, p.unit, p.quantity, p.unit);
        }



        fprintf(temp,
                "%d|%d|%s|%s|%s|%.2f|%.2f\n",
                p.productID,
                p.farmerID,
                p.name,
                p.category,
                p.unit,
                p.price,
                p.quantity);
     }

     fclose(fp);
     fclose(temp);

     remove(PRODUCT_FILE);
     rename("temp_products.txt", PRODUCT_FILE);

     if (found) {
         printf("\nProduct updated successfully!\n");

     }
     else
         printf("\nProduct not found or not yours.\n");

 }

 void deleteProduct(int farmerID)
 {
     int id;

     printf("\t===== DELETE PRODUCT =====\n");
     printf("\nEnter Product ID to Delete: ");
     if(scanf("%d", &id) != 1) {
          clearInputBuffer();
          printf("Invalid ID.\n");
          return;
     }
     clearInputBuffer();

     FILE *fp = fopen(PRODUCT_FILE, "r");
     FILE *temp = fopen("temp_products.tmp", "w");

     if(fp == NULL || temp == NULL){
        printf("Error opening file!\n");
        return;
     }

     char line[512];
     int found = 0;
     while(fgets(line, sizeof(line), fp)) {
            Product p;
        if(sscanf(line, "%d|%d|%99[^|]|%39[^|]|%9[^|]|%f|%f\n",
                        &p.productID, &p.farmerID,
                        p.name, p.category, p.unit,
                        &p.price, &p.quantity) == 7) {

          if(p.productID == id && p.farmerID == farmerID){
              found = 1;
              printf("\nID: %d\nName: %s\nCategory: %s\nPrice: %0.2f per %s\nQuantity: %0.2f %s\n",
                      p.productID, p.name, p.category, p.price, p.unit, p.quantity, p.unit);
          }
          else{
            fprintf(temp, "%d|%d|%s|%s|%s|%0.2f|%0.2f\n",
                          p.productID, p.farmerID,
                          p.name, p.category, p.unit,
                          p.price, p.quantity);
          }
       }
    }

     fclose(fp);
     fclose(temp);

     remove(PRODUCT_FILE);
     rename("temp_products.tmp", PRODUCT_FILE);

     if(found){
        printf("\nProduct deleted successfully!\n");
     }
     else{
        printf("\nProduct not found or not yours.\n");
     }

 }

 void addNotification(int farmerID, int productID, const char *name, const char *msg)
 {
     FILE *fp = fopen(NOTIFY_FILE, "a");
     if(fp == NULL) return;

     fprintf(fp, "%d|%d|%s|%s\n", farmerID, productID, name, msg);
     fclose(fp);

 }

 void notifyOutOfStock(int farmerID, const char *name)
 {

     addNotification(farmerID, 0, name, "Product is OUT OF STOCK");

 }

 void viewNotifications(int farmerID)
 {
     FILE *fp = fopen(NOTIFY_FILE, "r");

     if(fp == NULL) {
        printf("No notifications yet.\n");
        return;
     }
     char line[512];
     int found = 0;
     printf("\t===== NOTIFICATIONS =====\n");

     while(fgets(line, sizeof(line), fp)) {
        Notification n;
        if(sscanf(line, "%d|%d|%99[^|]|%199[^\n]",
                        &n.farmerID, &n.productID, n.name, n.msg) == 4) {
                if(n.farmerID == farmerID) {
                    found = 1;
                    printf("\n[ALERT] %s: %s\n", n.name, n.msg);
                }
          }
     }
     if(!found) {
        printf("No notifications for you.\n");
     }
     fclose(fp);

 }

 int updateProductQuantity(int productID, float orderedQty)
 {
     FILE *in = fopen(PRODUCT_FILE, "r");
     FILE *out = fopen("temp.txt", "w");

     if (!in || !out) {
            printf("File error.\n");
            if(in) fclose(in);
            if(out) fclose(out);
            return 0;
     }

     Product p;
     int updated = 0;


     while (fscanf(in, "%d|%d|%99[^|]|%39[^|]|%9[^|]|%f|%f\n",
           &p.productID, &p.farmerID, p.name,
           p.category, p.unit, &p.price, &p.quantity) == 7) {

        if (p.productID == productID) {
            p.quantity -= orderedQty;
            if (p.quantity <= 0) {
                p.quantity = 0;
                notifyOutOfStock(p.farmerID, p.name);
            }
            updated = 1;
        }

        fprintf(out, "%d|%d|%s|%s|%s|%.2f|%.2f\n",
                p.productID, p.farmerID, p.name,
                p.category, p.unit, p.price, p.quantity);
    }
     fclose(in);
    fclose(out);

    remove(PRODUCT_FILE);
    rename("temp.txt", PRODUCT_FILE);

    return updated;

 }

 void viewOrders(int farmerID)
 {
    FILE *fp = fopen(ORDER_FILE, "r");

    if(fp == NULL){
        printf("\nNo orders found yet.\n");
        return;
    }
    char line[512];
    int found = 0;

    printf("\t===== ORDERS FOR YOUR PRODUCTS =====\n");
    printf("%-10s  %-12s  %-12s  %-30s  %-8s  %-10s  %-12s\n",
           "OrderID", "ProductID", "ConsumerID", "Name", "Qty", "Total", "Status");
    printf("------------------------------------------------------------------------\n");

    while(fgets(line, sizeof(line), fp)) {
            Order o;
        if(sscanf(line, "%d|%d|%d|%d|%99[^|]|%f|%f|%14[^|]\n",
                        &o.orderID, &o.productID, &o.farmerID,
                        &o.consumerID, o.name, &o.quantity,
                        &o.totalPrice, o.status) == 8) {

          if(o.farmerID == farmerID) {
             found = 1;
             printf("%-10d  %-12d  %-12d  %-30s  %-8.2f  %-10.2f  %-12s\n",
                        o.orderID, o.productID, o.consumerID, o.name,
                        o.quantity, o.totalPrice, o.status);

    printf("----------------------------------------------------------------------\n");
          }
       }
    }
    if(!found){
        printf("\nNo orders placed for your products yet.\n");
    }
    fclose(fp);

 }

 void approveOrder(int farmerID)
 {
     FILE *fp = fopen(ORDER_FILE, "r");
     FILE *temp = fopen("temp.txt", "w");
     if (!fp || !temp) {
         printf("File error.\n");
         return;
     }

     int id, found = 0;

     printf("\t===== APPROVE ORDER =====\n");
     printf("Enter Order ID to approve: ");

     if (scanf("%d", &id) != 1) {
         clearInputBuffer();
         printf("Invalid Order ID.\n");
         return;
     }
     clearInputBuffer();

     Order o;
     while (fscanf(fp, "%d|%d|%d|%d|%99[^|]|%f|%f|%14[^\n]\n",
                      &o.orderID, &o.productID, &o.farmerID,
                      &o.consumerID, o.name, &o.quantity, &o.totalPrice, o.status) == 8) {

          if (o.orderID == id && o.farmerID == farmerID &&
              strcmp(o.status, "Pending") == 0) {

                found = 1;
                strcpy(o.status, "Approved");

                printf("\nOrder Approved Successfully!\n");
                printf("----------------------------\n");
                printf("Order ID    : %d\n", o.orderID);
                printf("Product ID  : %d\n", o.productID);
                printf("Name        : %s\n", o.name);
                printf("Quantity    : %.2f\n", o.quantity);
                printf("Total Price : %.2f\n", o.totalPrice);
                printf("Status      : %s\n", o.status);

                recordSale(o.productID, o.quantity);
                updateProductQuantity(o.productID, o.quantity);
          }

          fprintf(temp, "%d|%d|%d|%d|%s|%.2f|%.2f|%s\n",
                        o.orderID, o.productID, o.farmerID,
                        o.consumerID, o.name, o.quantity, o.totalPrice, o.status);
     }

     fclose(fp);
     fclose(temp);
     remove(ORDER_FILE);
     rename("temp.txt", ORDER_FILE);

     if (!found)
        printf("\nOrder not found, not yours, or already approved.\n");

 }

 void markOrderDelivered(int farmerID)
 {
     FILE *fp = fopen(ORDER_FILE, "r");
     FILE *temp = fopen("temp.txt", "w");
     if (!fp || !temp) {
         printf("File error.\n");
         return;
     }

     int id, found = 0;

     printf("\t===== MARK ORDER AS DELIVERED =====\n");
     printf("Enter Order ID to mark delivered: ");
     if (scanf("%d", &id) != 1) {
         clearInputBuffer();
         printf("Invalid Order ID.\n");
         return;
     }
     clearInputBuffer();

     Order o;
     while (fscanf(fp, "%d|%d|%d|%d|%99[^|]|%f|%f|%14[^\n]\n",
                       &o.orderID, &o.productID, &o.farmerID,
                       &o.consumerID, o.name, &o.quantity, &o.totalPrice, o.status) == 8) {

         if (o.orderID == id && o.farmerID == farmerID &&
             strcmp(o.status, "Approved") == 0) {

                found = 1;
                strcpy(o.status, "Delivered");

                printf("\nOrder Marked as Delivered!\n");
                printf("----------------------------\n");
                printf("Order ID    : %d\n", o.orderID);
                printf("Product ID  : %d\n", o.productID);
                printf("Name        : %s\n", o.name);
                printf("Quantity    : %.2f\n", o.quantity);
                printf("Total Price : %.2f\n", o.totalPrice);
                printf("Status      : %s\n", o.status);
         }

         fprintf(temp, "%d|%d|%d|%d|%s|%.2f|%.2f|%s\n",
                        o.orderID, o.productID, o.farmerID,
                        o.consumerID, o.name, o.quantity, o.totalPrice, o.status);
     }

     fclose(fp);
     fclose(temp);
     remove(ORDER_FILE);
     rename("temp.txt", ORDER_FILE);

     if (!found)
        printf("\nOrder not found, not yours, or not approved yet.\n");

 }

 void consumerMenu()
{
     printf("\n                              WELCOME TO YOUR GO-TO DESTINATION FOR FRESH GROCERIES!!!");
     printf("\n                              ________________________________________________________");

     int choice;

     while(1){
        printf("\n");
        printf("\t====== WELCOME! ======\n");
        printf("What would you like to do?\n");
        printf("1. Sign up\n");
        printf("2. Login\n");
        printf("3. Back\n");
        printf("======================================\n");
        printf("Enter choice: ");
        scanf("%d",&choice);


        switch(choice){
            case 1: signup();
                break;
            case 2: consumerLogin();
                break;
            case 3:
                return;
            default: printf("\nInvalid choice! Try again.\n");
                break;
        }
    }
}

void signup(){

    FILE *fp=fopen("consumers.dat","ab+");

    if(fp==NULL){
        printf("Error opening file.\n");
        return;
    }

    User c,temp;
    char phone[12];

    printf("\t===== SIGN UP TO EMBARK ON THE JOURNEY! =====\n");
    printf("Enter Your Phone Number: ");
    scanf("%11s",&phone);

    rewind(fp);

    while(fread(&temp,sizeof(User),1,fp)){
        if(strcmp(temp.phonenum,phone)==0 && temp.type==2){
            printf("Account with this phone number already exists!\n");
            fclose(fp);
            return;
        }
    }

    strcpy(c.phonenum,phone);

    printf("Enter Full Name: ");
    getchar();
    fgets(c.username,sizeof(c.username),stdin);
    c.username[strcspn(c.username,"\n")]='\0';

    printf("Enter Password: ");
    scanf("%29s",c.password);

    c.type=2;
    c.id=20001;

    rewind(fp);
    while(fread(&temp,sizeof(User),1,fp)){
        if(temp.id>=c.id)
            c.id=temp.id+1;
    }


    fwrite(&c,sizeof(User),1,fp);
    fclose(fp);

    printf("\nAccount Created Successfully! Your Customer ID is: %d\n",c.id);

}

int consumerLogin(){

    FILE *fp=fopen("consumers.dat","rb");
    if(fp==NULL){
        printf("\nOops! File Not Found!\n");
        return -1;
    }

    User c;
    char n[30],p[30];

    printf("\t===== LOGIN =====\n");
    printf("Phone Number: ");
    scanf("%29s",n);
    printf("Password: ");
    scanf("%29s",p);


    while(fread(&c,sizeof(User),1,fp)){
        if(c.type==2 && strcmp(c.phonenum,n)==0 && strcmp(c.password,p)==0){
            fclose(fp);
            printf("\nLogin Successful!\nWelcome %s (ID: %d)\n",c.username,c.id);
            consumerDashboard(c.id);
            return c.id;
        }
    }

    printf("\nInvalid Phone Number or Password!\n");
    fclose(fp);
    return -1;
}

int getOrderID()
{
   FILE *fp=fopen("orders.txt","r");
   if(!fp)
      return 1001;

   int lastID=1000;
   char line[200];

   while(fgets(line, sizeof(line), fp)){
         int id;
         if(sscanf(line, "%d|", &id) == 1){
            if(id > lastID) lastID = id;
         }
    }
   fclose(fp);
   return lastID+1;
}

void consumerDashboard(int consumerID)
{
     Product item[MAX_PRODUCTS];
     int n;

     n=loadProducts(item, 300);

     int choice;
        do{
        printf("\t====== DASHBOARD ======\n");
        printf("\n1.View All Products\n");
        printf("2.View by Categories\n");
        printf("3.Search Products\n");
        printf("4.Add To Cart\n");
        printf("5.Place Order\n");
        printf("6.Order History\n");
        printf("7.Feedback\n");
        printf("8.Log Out\n");
        printf("ENTER YOUR CHOICE: ");
        if(scanf("%d",&choice)!=1){
            while(getchar()!='\n');
            printf("Invalid Input. Choose Again: \n");
            continue;
        }


        switch(choice){
         case 1:
             viewProducts(item,n);
             break;
         case 2:
             viewByCategory(item,n);
             break;
         case 3:
             searchProduct(item,n);
             break;
         case 4:
             addToCart(item,n);
             break;
         case 5:
             placeOrder(consumerID,item,n);
             break;
         case 6:
             orderHistory(consumerID);
             break;
         case 7:
             feedback(consumerID);
             break;
         case 8:
             printf("Thank You For Visiting!!");
             return;
         default:
             printf("Invalid Choice!\n\n");
             break;
        }

    }while(choice != 8);

}

void viewProducts(Product item[], int n)
{
    printf("\nALL PRODUCTS:\n");
    for(int i=0;i<n;i++){
            printf("\n%d.%s \n(Category:%s)\n->BDT %.2f\nStock:%.2f %s\n",
                   item[i].productID, item[i].name, item[i].category, item[i].price, item[i].quantity, item[i].unit);
    }
}

void viewByCategory(Product item[], int n)
{
       char cate[40];

       printf("Select Category:\n");
       for(int i = 0; i < CATEGORY_COUNT; i++) {
           printf("%d. %s\n", i+1, CATEGORIES[i]);
       }
       printf("Enter choice (1-%d): ", CATEGORY_COUNT);

       int ch;
       if(scanf("%d", &ch) != 1) {
          clearInputBuffer();
          printf("Invalid input.\n");
          return;
       }

       strcpy(cate, CATEGORIES[ch-1]);
       cate[sizeof(cate)-1] = '\0';

       printf("%s: \n", cate);

       int found=0;
       for(int i=0;i<n;i++){
         if(strcmp(item[i].category,cate)==0){
            printf("\n%d. %s->BDT %.2f\nStock: %.2f %s\n",item[i].productID, item[i].name, item[i].price, item[i].quantity, item[i].unit);
            found=1;
         }
       }

       if(found==0){
        printf("Oops! No Products Found In This Category.\n");
       }

}


void searchProduct(Product item[],int n){
    char srch[50];
    char temp[50];
    printf("Search The Product Name: ");
    getchar();
    fgets(srch, sizeof(srch),stdin);

    srch[strcspn(srch,"\n")]='\0';

    strlwr(srch);

    int found=0;
    printf("\nSearch Results: \n");
    printf("ID\tName\t\tPrice\tQty\tUnit\tCategory\n");

    for(int i=0;i<n;i++){
            strcpy(temp,item[i].name);
            strlwr(temp);

        if(strstr(temp,srch) != NULL){
            printf("%d.\t%s\t%.2f\t%.2f\t%s\t%s\n", item[i].productID, item[i].name, item[i].price, item[i].quantity, item[i].unit, item[i].category);
            found=1;
        }
    }


    if(found==0){
        printf("\nSorry, No Products Matched!\n");
    }
}

void addToCart(Product item[],int n){

    int id;
    float qty;

    printf("Enter Product ID: ");
    if(scanf("%d", &id)!=1){
       while(getchar()!='\n');
       printf("\nInvalid Input.\n");
       return;
    }
    while(getchar()!='\n');

    int index=-1;
    for(int i=0;i<n;i++){
        if(id == item[i].productID){
            index = i;
            break;
        }
    }

    if(index==-1){
        printf("Oops! Product Not Found!\n");
        return;
    }

    printf("Enter Quantity in %s(float): ", item[index].unit);
    if(scanf("%f",&qty)!=1){
     while(getchar()!='\n');
     printf("\nInvalid Input.\n");
     return;
    }

    while(getchar()!='\n');
    if(qty<=0){
     printf("Quantity must be positive.\n");
     return;
    }

    if(qty>item[index].quantity){
     printf("Oh, No~ Not Enough Stock!\n");
     return;
    }

    if(cartCount<=MAX_CART){
        cart[cartCount].productID=item[index].productID;
        cart[cartCount].farmerID=item[index].farmerID;
        strcpy(cart[cartCount].product,item[index].name);
        cart[cartCount].price=item[index].price;
        cart[cartCount].quantity=qty;
        cartCount++;

        printf("\n%s Added To Your Cart!\n",item[index].name);
    }
    else printf("Cart is full!\n");
}

int placeOrder(int consumerID,Product item[],int n)
{
    if(cartCount==0){
        printf("Cart is empty. Add To Your Cart First!\n");
        return 0;
    }

    FILE *fp=fopen("orders.txt","a");
    if(fp==NULL){
        printf("Error Opening File!\n");
        return 0;
    }

    for(int i=0;i<cartCount;i++){
        Order o;
        o.orderID=getOrderID();
        o.consumerID=consumerID;
        o.productID=cart[i].productID;
        o.farmerID=cart[i].farmerID;
        strcpy(o.name, cart[i].product);
        o.quantity=cart[i].quantity;
        o.totalPrice=cart[i].price*o.quantity;

        fprintf(fp,"%d|%d|%d|%d|%s|%.2f|%.2f|Pending\n", o.orderID, o.productID, o.farmerID, o.consumerID, o.name, o.quantity, o.totalPrice);

        printf("\nOrder Placed: %s\nQuantity: %0.2f\nTotal: %.2f\nID: %d\n", o.name, o.quantity, o.totalPrice, o.orderID);
    }

    cartCount=0;
    fclose(fp);
    return 1;
}

void orderHistory(int consumerID){
     FILE *fp=fopen("orders.txt","r");
     if(fp==NULL){
        printf("No Transactions Found.\n");
        return;
     }

     char line[512];
     int found=0;

     printf("\t===== YOUR ORDER HISTORY =====\n");
     printf("%-10s  %-12s  %-30s  %-8s  %-10s  %-12s\n",
           "OrderID", "ProductID", "Name", "Qty", "Total", "Status");
     printf("--------------------------------------------------------------------------------------\n");
      while(fgets(line, sizeof(line), fp)) {
            Order o;
         if(sscanf(line, "%d|%d|%d|%d|%99[^|]|%f|%f|%14[^|]\n",
                        &o.orderID, &o.productID, &o.farmerID,
                        &o.consumerID, o.name, &o.quantity,
                        &o.totalPrice, o.status) == 8) {
           if(consumerID==o.consumerID){
              found=1;
              printf("%-10d  %-12d  %-30s  %-8.2f  %-10.2f  %-12s\n",
                        o.orderID, o.productID, o.name,
                        o.quantity, o.totalPrice, o.status);

           printf("--------------------------------------------------------------------------------------\n");
           }
        }
     }

     if(found==0){
        printf("\nOh, No~ No Transactions Yet!\n");
     }
    fclose(fp);
}


void feedback(int consumerID){
    char cmnt[200];
    printf("Write Your Feedback: ");
    getchar();
    fgets(cmnt,sizeof(cmnt),stdin);

    FILE *fp = fopen("feedback.txt","a");

    if(!fp){
        printf("Error!\n");
        return;
    }
    else
    fprintf(fp,"%d: %s", consumerID, cmnt);
    fclose(fp);

    printf("\nThank You For Your Feedback!\n");
}


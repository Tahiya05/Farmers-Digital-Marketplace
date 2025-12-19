 #include<stdio.h>
 #include<string.h>
 #include<stdlib.h>
 #include "farmer.h"



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
        printf("\n===== FARMER DASHBOARD (Farmer ID: %d) =====\n", farmerID);
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

     printf("\n===== ADD NEW PRODUCT =====\n");

     p.productID = getNewProductID();
     strcpy(p.farmerID,farmerID);


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
     printf("ID: %d\nName: %s\nCategory: %s\nPrice: %0.2f per %s\nQuantity: %0.2f %s\n",
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

     printf("\n===== MY PRODUCTS =====\n");
     printf("%-6s  %-30s  %-15s  %-8s  %-8s  %-8s\n", "ID", "Name", "Category", "Price", "Qty", "Unit");

     printf("--------------------------------------------------------------------\n");

     while(fgets(line, sizeof(line), fp)){
            Product p;
        if(sscanf(line, "%d|%d|%99[^|]|%39[^|]|%9[^|]|%f|%f\n",
                  &p.productID, &p.farmerID, p.name, p.category,
                   p.unit, &p.price, &p.quantity) == 7) {

            if(p.farmerID == farmerID){
                found = 1;
                printf("%-6d  %-30s  %-15s  %-8.2f  %-6.2f  %-8s\n",
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
     int targetID, found = 0;
     Product p;

     printf("\n===== UPDATE PRODUCT =====\n");
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

            printf("\nEnter New Price: ");
            if (scanf("%f", &p.price) != 1) {
                clearInputBuffer();
                printf("Invalid price.\n");
                fclose(fp);
                fclose(temp);
                remove("temp_products.txt");
                return;
            }

            printf("Enter New Quantity: ");
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

     if (found)
         printf("\nProduct updated successfully!\n");
     else
         printf("\nProduct not found or not yours.\n");

 }

 void deleteProduct(int farmerID)
 {
     int id;

     printf("\n===== DELETE PRODUCT =====\n");
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
        if(sscanf(line, "%d|%d|%99[^|]|%39[^|]|%9[^|]|%f|%d|%d\n",
                        &p.productID, &p.farmerID
                        p.name, p.category, p.unit,
                        &p.price, &p.quantity) == 7) {

          if(p.productID == id && p.farmerID == farmerID){
              found = 1;
          }
          else{
            fprintf(temp, "%d|%d|%s|%s|%s|%0.2f|%0.2f\n",
                          p.productID, p.farmerID
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
     printf("\n===== NOTIFICATIONS =====\n");

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
            if (fp) fclose(fp);
            if (temp) fclose(temp);
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

    printf("\n===== ORDERS FOR YOUR PRODUCTS =====\n");
    printf("%-10s  %-12s  %-12s  %-8s  %-10s  %-12s\n",
           "OrderID", "ProductID", "ConsumerID", "Qty", "Total", "Status");
    printf("------------------------------------------------------------------------------------\n");

    while(fgets(line, sizeof(line), fp)) {
            Order o;
        if(sscanf(line, "%d|%d|%d|%d|%f|%f|%14[^|]\n",
                        &o.orderID, &o.productID, &o.farmerID,
                        &o.consumerID, &o.quantity,
                        &o.totalPrice, o.status) == 7) {

          if(o.farmerID == farmerID) {
             found = 1;
             printf("%-10d  %-12d  %-12d  %-8.2f  %-10.2f  %-12s\n",
                        o.orderID, o.productID, o.consumerID,
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

 int approveOrder(int farmerID)
 {
     FILE *fp = fopen(ORDER_FILE, "r");
     FILE *temp = fopen("temp.txt", "w");

     int id;
     printf("Enter Order ID to approve: ");
     scanf("%d", &id);
     clearInputBuffer();

     Order o;
     while (fscanf(fp, "%d|%d|%d|%d|%f|%f|%14[^\n]\n",
                      &o.orderID, &o.productID, &o.farmerID,
                      &o.consumerID, &o.quantity, &o.totalPrice, o.status) == 7) {

          if (o.orderID == id && o.farmerID == farmerID &&
              strcmp(o.status, "Pending") == 0) {

                strcpy(o.status, "Approved");
                updateProductQuantity(o.productID, o.quantity);
          }

          fprintf(temp, "%d|%d|%d|%d|%.2f|%.2f|%s\n",
                        o.orderID, o.productID, o.farmerID,
                        o.consumerID, o.quantity, o.totalPrice, o.status);
     }

     fclose(fp);
     fclose(temp);
     remove(ORDER_FILE);
     rename("temp.txt", ORDER_FILE);

 }

 void markOrderDelivered(int farmerID)
 {
     FILE *fp = fopen(ORDER_FILE, "r");
     FILE *temp = fopen("temp.txt", "w");

     int id;
     printf("Enter Order ID to mark delivered: ");
     scanf("%d", &id);
     clearInputBuffer();

     Order o;
     while (fscanf(fp, "%d|%d|%d|%d|%f|%f|%14[^\n]\n",
                       &o.orderID, &o.productID, &o.farmerID,
                       &o.consumerID, &o.quantity, &o.totalPrice, o.status) == 7) {

         if (o.orderID == id && o.farmerID == farmerID &&
             strcmp(o.status, "Approved") == 0) {

                strcpy(o.status, "Delivered");
         }

         fprintf(temp, "%d|%d|%d|%d|%.2f|%.2f|%s\n",
                        o.orderID, o.productID, o.farmerID,
                        o.consumerID, o.quantity, o.totalPrice, o.status);
     }

     fclose(fp);
     fclose(temp);
     remove(ORDER_FILE);
     rename("temp.txt", ORDER_FILE);

 }

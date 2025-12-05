 #include<stdio.h>
 #include<string.h>
 #include<stdlib.h>
 #include "farmer.h"



 void clearInputBuffer(void)
 {
     int c;
     while((c=getchar()) != '\n' && c != EOF) {}

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

     int lastID = 0;
     char line[200];

     while(fgets(line, sizeof(line), fp)){
         int id;
         if(sscanf(line, "%d|", &id) == 1){
            if(id > lastID) lastID = id;
           }
      }
     fclose(fp);
     return lastID + 1;
 }


 void farmerDashboard(int farmerID)
 {
     int choice;

     do{
        printf("\n===== FARMER DASHBOARD (Farmer ID: %d) =====\n", farmerID);
        printf("1. Add Product\n");
        printf("2. View My Products\n");
        printf("3. Update My Product\n");
        printf("4. Delete My Product\n");
        printf("5. View Orders\n");
        printf("6. View Notifications\n");
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
     if(!fgets(p.productName, sizeof(p.productName), stdin)){
        printf("Input error.\n");
        return;
     }
     removeNewLine(p.name);
     if(strlen(p.productName) == 0 || strchr(p.productName, ',') != NULL) {
        printf("Invalid product name (empty or contains comma).\n");
        return;
     }


   printf("Select Category:\n");
     for(int i = 0; i < CATEGORY_COUNT; ++i) {
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

     if(ch < 1 || ch > CATEGORY_COUNT) ch = CATEGORY_COUNT;
     strncpy(p.category, CATEGORIES[ch-1], sizeof(p.category)-1);
     p.category[sizeof(p.category)-1] = '\0';


   printf("Enter Price (per unit): ");
     if(scanf("%f", &p.price) != 1) {
        clearInputBuffer();
        printf("Invalid price.\n");
        return;
     }
     clearInputBuffer();

   printf("Enter Quantity (integer): ");
     if(scanf("%d", &p.quantity) != 1) {
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

     fprintf(fp, "%d|%s|%s|%0.2f|%d|%d\n",
             p.productID,
             p.productName,
             p.category,
             p.price,
             p.quantity;
             p.farmerID);

     fclose(fp);

     printf("\nProduct Added Successfully!\n");
     printf("ID: %d\nName: %s\nPrice: %0.2f\nQuantity: %d\n",
               p.productID, p.productName, p.price, p.quantity);

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
     printf("%-6s  %-30s  %-15s  %-8s  %-6s\n", "ID", "Name", "Category", "Price", "Qty");

     printf("--------------------------------------------------------------------\n");

     while(fgets(line, sizeof(line), fp)){
            Product p;
            if(sscanf(line, "%d|%99[^|]|%39[^|]|%f|%d|%d",
                      &p.productID, &p.productName, &p.category, &p.price, &p.quantity, &p.farmerID) == 6) {
                          if(p.farmerID == farmerID){
                            found = 1;
                            printf("%-6d  %-30s  %-15s  %-8.2f  %-6d\n",
                                   p.productID, p.productName, p.category, p.price, p.quantity);
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
     int targetId;
     printf("Enter Product ID to update: ");
     if(scanf("%d", &targetId) != 1) {
        clearInputBuffer();
        printf("Invalid ID.\n");
        return;
     }

     clearInputBuffer();

     FILE *fp = fopen(PRODUCT_FILE,"r");
     if(fp == NULL) {
       printf("No products file.\n");
       return;
     }

     Product *arr = NULL;
     size_t count = 0, cap = 0;
     char line[512];

     while(fgets(line, sizeof(line), fp)){
        Product p;
        if(sscanf(line, "%d|%99[^|]|%39[^|]|%f|%d|%d",
                  &p.productID, p.productName, p.category,
                  &p.price, &p.quantity, &p.farmerID) == 6) {

                    if(count >= cap) {
                        cap = cap == 0 ? 64 : cap * 2;
                        arr = realloc(arr, cap * sizeof(Product));

                        if(!arr) {
                            fclose(fp);
                            printf("Memory error.\n");
                            return;
                        }
                   }
                    arr[count++] = p;
            }
     }
     fclose(fp);

     int found = 0;

     for(size_t i = 0; i < count; ++i){
        if(arr[i].productID == targetId
             &&
           arr[i].farmerID == farmerID) {
               found = 1;
               printf("\n===== Current Product Details =====\n");
               printf("Name : %s\n", arr[i].productName);
               printf("Category : %s\n", arr[i].category);
               printf("Price : %0.2f\n", arr[i].price);
               printf("Quantity : %d\n", arr[i].quantity);


               printf("\nEnter New Name (no commas): ");

               if(!fgets(arr[i].productName, sizeof(arr[i].productName), stdin)) {}
               removeNewLine(arr[i].productName);
               if(strlen(arr[i].productName) == 0 || strchr(arr[i].productName, ',') != NULL) {
                    printf("Invalid name. Aborting update.\n");
                    free(arr);
                    return;
               }


               printf("Select New Category: ");

               for (int c = 0; c < CATEGORY_COUNT; ++c) {
                    printf("%d. %s\n", c+1, CATEGORIES[c]);
               }
               printf("Enter choice (1-%d): ", CATEGORY_COUNT);

               int ch;
               if(scanf("%d", &ch) != 1) {
                  clearInputBuffer();
                  printf("Invalid input.\n");
                  free(arr);
                  return;
               }
               clearInputBuffer();

               if(ch < 1 || ch > CATEGORY_COUNT) ch = CATEGORY_COUNT;
               strncpy(arr[i].category, CATEGORIES[ch-1], sizeof(arr[i].category)-1);
               arr[i].category[sizeof(arr[i].category)-1] = '\0';


               printf("Enter New Price: ");

               if(scanf("%f", &arr[i].price) != 1) {
                    clearInputBuffer();
                    printf("Invalid.\n");
                    free(arr);
                    return;
               }
               clearInputBuffer();


               printf("Enter New Quantity: ");

               if(scanf("%d\n", &arr[i].quantity) != 1) {
                    clearInputBuffer();
                    printf("Invalid.\n");
                    free(arr);
                    return;
               }
               clearInputBuffer();

               break;
           }
     }

     if(!found){
        printf("Product not found OR not yours.\n");
        free(arr);
        return;
     }

     FILE *out = fopen(PRODUCT_FILE, "w");
     if(out == NULL){
        printf("Write Error.\n");
        free(arr);
        return;
     }

     for(size_t i = 0; i < count; ++i){
        fprintf(out, "%d|%s|%s|%0.2f|%d|%d\n",
                arr[i].productID, arr[i].productName, arr[i].category,
                arr[i].price, arr[i].quantity, arr[i].farmerID);
     }

     fclose(out);
     free(arr);

     printf("\nProduct updated successfully!\n");

 }

 void deleteProduct(int farmerID)
 {
     int id;
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
        if(sscanf(line, "%d|%99[^|]|%39[^|]|%f|%d|%d\n",
                  &p.productID,
                  p.productName,
                  p.category,
                  &p.price,
                  &p.quantity,
                  &p.farmerID) == 6) {

          if(p.productID == id && p.farmerID == farmerID){
             found = 1;
          }
          else{
            fprintf(temp, "%d|%s|%s|0.2%f|%d|%d\n",
                    p.productID,
                    p.productName,
                    p.category,
                    p.price,
                    p.quantity,
                    p.farmerID);
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

 void addNotification(int farmerID, int productID, const char *productName, const char *msg)
 {
     FILE *fp = fopen(NOTIFY_FILE, "a");
     if(fp == NULL) return;

     fprintf(fp, "%d|%d|%s|%s\n", farmerID, productID, productName, msg);
     fclose(fp);

 }

 void notifyOutOfStock(int farmerID, const char *productName)
 {
     char msg[200];
     snprintf(msg, sizeof(msg), "Product '%s' is OUT OF STOCK.", productName);

     printf("\n[ALERT] %s\n", msg);
     addNotification(farmerID, 0, productName, msg);

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
        int fid, pid;
        char pname[100], msg[200];

        if(sscanf(line, "%d|%d|%99[^|]|%199[^\n]",
                        &fid, &pid, pname, msg) >= 3) {
                if(fid == farmerID) {
                    found = 1;
                    printf("- %s\n", msg);
                }
          }
     }
     if(!found) {
        printf("No notifications for you.\n");
     }
     fclose(fp);

 }

 int updateProductQuantity(int productID, int orderedQty)
 {
     FILE *fp = fopen(PRODUCT_FILE, "r");
     if(fp == NULL) return 0;

     Product *arr = NULL;
     size_t count = 0, cap = 0;
     char line[512];

     while(fgets(line, sizeof(line), fp)) {
        Product p;
        if(sscanf(line, "%d|%99[^|]|%39[^|]|%f|%d|%d",
                        &p.productID, p.productName, p.category,
                        &p.price, &p.quantity, &p.farmerID) == 6) {
                if(count >= cap) {
                    cap = cap == 0 ? 64 : cap * 2;
                    arr = realloc(arr, cap * sizeof(Product));
                    if(!arr) {
                        fclose(fp);
                        return 0;
                    }
                }
                arr[count++] = p;
          }
     }
     fclose(fp);

     int found = 0;
     for(size_t i = 0; i < count; ++i) {
        if(arr[i].productID == productID) {
            found = 1;
            arr[i].quantity -= orderedQty;
          if(arr[i].quantity <= 0) {
                arr[i].quantity = 0;
                notifyOutOfStock(arr[i].farmerID, arr[i].productName);
           }
          break;
        }
     }
     if(!found) {
        free(arr);
        return 0;
     }

     FILE *out = fopen(PRODUCT_FILE, "w");
     if(!out) {
        free(arr);
        return 0;
     }
     for(size_t i = 0; i < count; ++i) {
        fprintf(out, "%d|%s|%s|%0.2f|%d|%d\n",
                     arr[i].productID, arr[i].productName, arr[i].category,
                     arr[i].price, arr[i].quantity, arr[i].farmerID);
     }
     fclose(out);
     free(arr);
     return 1;

 }

 void viewOrders(int farmerID)
 {
    FILE *fp = fopen("orders.txt", "r");

    if(fp == NULL){
        printf("\nNo orders found yet.\n");
        return;
    }
    char line[512];
    int found = 0;

    printf("\n===== ORDERS FOR YOUR PRODUCTS =====\n");
    printf("%-6s  %-12s  %-6s  %-30s  %-6s\n",
           "OID", "Consumer", "PID", "Product Name", "Qty");
    printf("------------------------------------------------------------------------------------\n");

    while(fgets(line, sizeof(line), fp)) {
            Order o;
        if(sscanf(line, "%d|%19[^|]|%d|%d|%99[^|]|%f|%d\n",
                        &o.orderID,
                        o.consumerPhone,
                        &o.farmerID,
                        &o.productID,
                        o.productName,
                        &o.price,
                        &o.quantity) == 7) {

          if(o.farmerID == farmerID) {
             found = 1;
             printf("\nOrder ID    : %d\n", o.orderID);
             printf("Product ID    : %d\n", o.productID);
             printf("Product Name  : %s\n", o.productName);
             printf("Quantity      : %d\n", o.quantity);
             printf("Consumer Phone: %s\n", o.consumerPhone);

    printf("------------------------------------------\n");
          }
       }
    }
    if(!found){
        printf("\nNo orders placed for your products yet.\n");
    }
    fclose(fp);

 }

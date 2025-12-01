 #include<stdio.h>
 #include<string.h>
 #include<stdlib.h>
 #include "farmer.h"



void clearInputBuffer()
{
     int c;
     while((c=getchar()) != '\n' && c != EOF) {}

}

void farmerDashboard(char farmerPhone[])
{
     int choice;

     do{
        printf("\n--- Farmer Dashboard ---\n");
        printf("1. Add Product\n");
        printf("2. View My Products\n");
        printf("3. Update My Product\n");
        printf("4. Delete My Product\n");
        printf("5. View Orders\n");
        printf("0. Log Out\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        clearInputBuffer();

        switch(choice){
            case 1:
                addProduct(farmerPhone);
                break;

            case 2:
                viewMyProducts(farmerPhone);
                break;

            case 3:
                updateProduct(farmerPhone);
                break;

            case 4:
                deleteProduct(farmerPhone);
                break;

            case 5:
                viewOrders(farmerPhone);
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

 void removeNewLine(char *str)
 {
     int len=strlen(str);

     if(str[len - 1] == '\n'){
        str[len - 1] = '\0';
     }
 }

 int getNewProductID()
 {
     FILE *fp = fopen(PRODUCT_FILE, "r");
     if(fp == NULL) return 1;

     int lastID = 0;
     char line[200];

     while(fgets(line, sizeof(line), fp)){
         int id;
         sscanf(line, "%d|", &id);
         if(id > lastID) lastID = id;
     }
     fclose(fp);
     return lastID + 1;
 }

 void addProduct(char farmerPhone[])
 {
     struct Product p;
     char buffer[200];

     printf("\n--- Add New Product ---\n");

     p.id = getNewProductID();
     strcpy(p.farmerPhone,farmerPhone);

     printf("Enter Product Name: ");
     fgets(p.name, sizeof(p.name), stdin);
     removeNewLine(p.name);

     printf("Enter Price: ");
     fgets(buffer, sizeof(buffer), stdin);
     sscanf(buffer, "%f", &p.price);

     printf("Enter Quantity: ");
     fgets(buffer, sizeof(buffer), stdin);
     sscanf(buffer, "%d", &p.quantity);

     FILE *fp = fopen(PRODUCT_FILE, "a");
     if(fp == NULL){
        printf("Error opening products file!\n");
        return;
     }

     fprintf(fp, "%d|%s|%s|%0.2f|%d\n",
             p.id,
             p.farmerPhone,
             p.name,
             p.price,
             p.quantity);

     fclose(fp);

     printf("\nProduct Added Successfully!\n");
     printf("ID: %d\nName: %s\nPrice: %0.2f\nQuantity: %d\n",
               p.id, p.name, p.price, p.quantity);

 }

 void viewMyProducts(char farmerPhone[])
 {
     FILE *fp = fopen("products.txt", "r");
     if(fp == NULL){
        printf("\n[Error] Could not open products.txt\n");
        return;
     }

     Product p;
     int found=0;

     printf("\n--- My Products ---\n");
     while(1){
        if(fgets(p.farmerPhone, sizeof(p.farmerPhone), fp) == NULL) break;

        p.farmerPhone[strcspn(p.farmerPhone, "\n")] = '\0';

        if(fgets(p.name, sizeof(p.name), fp) == NULL) break;

        p.name[strcspn(p.name, "\n")] = '\0';

        if(fscanf(fp, "%f\n", &p.price) != 1) break;

        if(fscanf(fp, "%d\n", &p.quantity) ) break;

        fgetc(fp);

        if(strcmp(p.farmerPhone, farmerPhone) == 0){
            printf("\nProduct Name : %s", p.name);
            printf("\nPrice : %0.2f", p.price);
            printf("\nQuantity : %d\n", p.quantity);

        printf("-----------------------------------\n");

            found = 1;
        }
     }

     if(!found){
        printf("\nNo products found.\n");
     }

     fclose(fp);

 }

 void updateProduct(char farmerPhone[])
 {
     FILE *fp = fopen(PRODUCT_FILE,"rb");
     if(fp == NULL) {
       printf("No product file found.\n");
       return;
     }

     Product products[100];
     int count = 0;

     while(fread(&products[count], sizeof(Product), 1, fp) == 1){
        count++;
     }
     fclose(fp);

     if(count == 0){
        printf("No products available.\n");
        return;
     }

     int targetId;
     printf("Enter Product ID to update: ");
     scanf("%d", &targetId);

     int found = 0;

     for(int i = 0; i < count; i++){
        if(products[i].productId == targetId
           &&
           strcmp(products[i].farmerPhone, farmerPhone) == 0){
               found = 1;
               printf("\n--- Current Product Details ---\n");
               printf("Name : %s\n", products[i].name);
               printf("Price : %0.2f\n", products[i].price);
               printf("Quantity : %d\n", products[i].quantity);

               printf("\nEnter New Name: ");
               scanf(" %[^\n]", &products[i].name);

               printf("Enter New Price: ");
               scanf("%f", &products[i].price);

               printf("Enter New Quantity: ");
               scanf("%d\n", &products[i].quantity);

               break;
           }
     }

     if(!found){
        printf("Product not found OR does not belong to you.\n");
        return;
     }

     fp = fopen(PRODUCTS_FILE, "wb");

     if(fp == NULL){
        printf("Error opening file.\n");
        return;
     }

     for(int i = 0; i < count; i++){
        fwrite(&products[i],  sizeof(Product), 1, fp);
     }

     fclose(fp);

     printf("\nProduct updated successfully!\n");

 }

 void deleteProduct(char farmerPhone[])
 {
     FILE *fp, *temp;
     Product p;
     int id, found = 0;

     printf("\nEnter Product ID to Delete: ");
     scanf("%d", &id);

     fp = fopen(PRODUCT_FILE, "r");
     temp = fopen("data/temp.txt", "w");

     if(fp == NULL || temp == NULL){
        printf("Error opening file!\n");
        return;
     }

     while(fscanf(fp, "%d|%[^|]|%f|%d|%[^|]\n",
                  &p.id,
                  p.name,
                  &p.price,
                  &p.quantity,
                  p.farmerPhone) == 5)
     {
         if(p.id == id && strcmp(p.farmerPhone, farmerPhone) == 0){
            found = 1;
         }
         else{
            fprintf(temp, "%d|%s|%f|%d|%s\n",
                    p.id,
                    p.name,
                    p.price,
                    p.quantity,
                    p.farmerPhone);
         }
     }

     fclose(fp);
     fclose(temp);

     remove(PRODUCT_FILE);
     rename("data/temp.txt", PRODUCT_FILE);

     if(found){
        printf("\nProduct deleted successfully!\n");
     }
     else{
        printf("\nProduct not found or doesn't belong to you.\n");
     }

}

void viewOrders()
{
    FILE *fp;
    Order o;
    int found = 0;

    fp = fopen("orders.txt", "r");

    if(fp == NULL){
        printf("\nNo orders found yet.\n");
        return;
    }

    printf("\n--- My Orders ---\n");

    while(fscanf(fp, "%d|%d|%[^|]|%d|%[^|]|%[^|]\n",
                 &o.orderID,
                 &o.productID,
                 o.productName,
                 &o.quantity,
                 o.consumerPhone,
                 o.farmerPhone) == 6)
    {
        if(strcmp(o.farmerPhone, farmerPhone) == 0){
            found = 1;
            printf("\nOrder ID    : %d\n",o.orderID);
            printf("Product ID    : %d\n",o.productID);
            printf("Product Name  : %s\n",o.productName);
            printf("Quantity      : %d\n",o.quantity);
            printf("Consumer Phone: %s\n",o.consumerPhone);

    printf("------------------------------------------\n");
        }
    }

    fclose(fp);

    if(!found){
        printf("\nNo orders placed for your products yet.\n");
    }
}

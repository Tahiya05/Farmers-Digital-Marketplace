 #include<stdio.h>
 #include<string.h>
 #include<stdlib.h>
 #include "farmer.h"
 #include "product.h"
 #include "utils.h"

 #define PRODUCT_FILE "products.txt"

 struct Product{
   int id;
   char farmerPhone[20];
   char productName[50];
   float price;
   int quantity;
 };

void clearInputBuffer()
{ int c;
  while((c=getchar()) != '\n' && c != EOF);
}

void farmerDashboard(char farmerPhone[])
{ int choice;
  while(1){
        printf("\n--- Farmer Dashboard ---\n");
        printf("1. Add Product\n");
        printf("2. View My Products\n");
        printf("3. Update My Product\n");
        printf("4. Delete My Product\n");
        printf("5. View Orders\n");
        printf("0. Log Out\n");
        printf("Enter choice: ");

        if(scanf("%d",&choice) != 1){
            printf("Invalid Input. Try again.\n");
            clearInputBuffer();
            continue;
        }

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
                printf("Invalid choice. Try again.\n");

        }
    }
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
   FILE *fp = fopen(PRODUCT_FILE,"r");
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



 }


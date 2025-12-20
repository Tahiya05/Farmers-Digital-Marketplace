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
     int productID;
     int farmerID;
     char name[100];
     char category[40];
     char unit [10];
     float price;
     float quantity;
}Product;

typedef struct{
    char product[100];
    float quantity;
    float price;
}CartItem;

typedef struct {
    int orderID;
    int productID;
    int farmerID;
    int consumerID;
    char name[100];
    float quantity;
    float totalPrice;
    char status[15];
} Order;

CartItem cart[MAX_CART];
int cartCount=0;

void consumerMenu();
void signup();
int consumerLogin();
int getOrderID();
void consumerDashboard(int consumerID);
void viewProducts(Product item[],int n);
void viewByCategory(Product item[],int n);
void searchProduct(Product item[],int n);
void addToCart(Product item[],int n);
int placeOrder(int consumerID,Product item[],int n);
void orderHistory(int consumerID);
void feedback(int consumerID);



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
        if(strcmp(temp.phonenum,phone)==0 && temp.type==1){
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
        if(c.type==1 && strcmp(c.phonenum,n)==0 && strcmp(c.password,p)==0){
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
   FILE *fp=fopen("order.txt","r");
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
            printf("\n%d.%s \n(Category:%s)\n->BDT %.2f\nStock:%d %s\n",
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
       p.category[sizeof(p.category)-1] = '\0';

       printf("%s: \n", cate);

       int found=0;
       for(int i=0;i<n;i++){
         if(strcmp(item[i].category,cate)==0){
            printf("\n%d. %s->BDT %.2f\nStock: %d %s\n",item[i].productID, item[i].name, item[i].price, item[i].quantity, item[i].unit);
            found=1;
         }
       }

       if(found==0){
        printf("Oops! No Products Found In This Category.\n");
       }

}


void searchProduct(Product item[],int n){
    char srch[50];
    char tmp[50];
    printf("Search The Product Name: ");
    scanf("%49s",srch);

    strlwr(srch);

    int found=0;
    printf("\nSearch Results: \n");
    printf("ID\tName\tPrice\tQuantity\tUnit\tCategory\n");

    for(int i=0;i<n;i++){
            strcpy(tmp,item[i].name);
            strlwr(tmp);

        if(strstr(tmp,srch) != NULL){
            printf("%d.\t%s\t%.2f\t.2f\t%s\t%s\n", item[i].productID, item[i].name, item[i].price, item[i].quantity, item[i].unit, item[i].category);
            found=1;
        }
    }


    if(found==0){
        printf("\nSorry, No Products Matched!\n");
    }
}

void addToCart(Product item[],int n){

    int id, qty;

    printf("Enter Product ID: ");
    if(scanf("%d", &id)!=1){
       while(getchar()!='\n');
       printf("\nInvalid Input.\n");
       return;
   }



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

   if(qty<=0){
    printf("Quantity must be positive.\n");
    return;
   }

   if(qty>item[index].quantity){
    printf("Oh, No~ Not Enough Stock!\n");
    return;
   }

    strcpy(cart[cartCount].product,item[index].name);
    cart[cartCount].price=item[index].price;
    cart[cartCount].quantity=qty;
    cartCount++;

    printf("\n%s Added To Your Cart!\n",item[index].name);

}

int placeOrder(int consumerID,Product item[],int n)
{
    if(cartCount==0){
        printf("Cart is empty. Add To Your Cart First!\n");
        return 0;
    }

    FILE *fp=fopen("order.txt","a");
    if(fp==NULL){
        printf("Error Opening File!\n");
        return 0;
    }

    for(int i=0;i<cartCount;i++){
        Order o;
        o.orderID=getOrderID();

        o.productID=0;
        o.farmerID=0;

        o.consumerID=consumerID;
        strcpy(o.name, cart[i].product);
        o.quantity=cart[i].quantity;
        o.totalPrice=cart[i].price*o.quantity;

        fprintf(fp,"%d|%d|%d|%d|%s|%.2f|%.2f|Pending\n", o.orderID, o.productID, o.farmerID, o.consumerID, o.name, o.quantity, o.totalPrice);
        for(int j=0;j<n;j++){
            if(strcmp(item[j].name,o.name)==0){
                item[j]. quantity=item[j].quantity-t.quantity;
                break;
            }
        }

        printf("\nOrder Placed: %s\nQuantity: %0.2f\nTotal: %.2f\nID: %d\n", o.name, o.quantity, o.totalPrice, o.orderID);
    }

    fclose(fp);


    FILE *fp2=fopen("products.txt","w");
    if(fp2==NULL){
        printf("\nError Opening File.\n");
        cartCount=0;
        return 1;
    }

    for(int i=0;i<n;i++){
        fprintf(fp2,"%d %s %.2f %.2f %s\n",item[i].productID,item[i].name,item[i].price,item[i].quantity,item[i].category);
    }
        fclose(fp2);

        cartCount=0;
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

     printf("\n===== YOUR ORDER HISTORY =====\n");
     printf("%-10s  %-12s  %-30s  %-8s  %-10s  %-12s\n",
           "OrderID", "ProductID", "Name", "Qty", "Total", "Status");
     printf("------------------------------------------------------------------------------------\n");
      while(fgets(line, sizeof(line), fp)) {
            Order o;
         if(sscanf(line, "%d|%d|%d|%d|%99[^|]|%f|%f|%14[^|]\n",
                        &o.orderID, &o.productID, &o.farmerID,
                        &o.consumerID, o.name, &o.quantity,
                        &o.totalPrice, o.status) == 8) {
           if(customerID==o.consumerID){
              printf("\nID: %d\nItem: %s\nQuantity: %d\nTotal: %.2f\n",id,p,qty,total);
              found=1;
              printf("%-10d  %-12d  %-30s  %-8.2f  %-10.2f  %-12s\n",
                        o.orderID, o.productID, o.name,
                        o.quantity, o.totalPrice, o.status);

           printf("----------------------------------------------------------------------\n");
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


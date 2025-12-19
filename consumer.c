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
     int id;
     char name[100];
     float price;
     int quantity;
     char category[100];
}Product;

typedef struct{
    char product[50];
    int quantity;
    float price;
}CartItem;

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

void signup();
int login(char loggeduser[]);
int loadProd(Product item[]);
void viewProd(Product item[],int n);
void viewCtg(Product item[],int n);
void searchProd(Product item[],int n);
void addCart(Product item[],int n);
int transactionID();
int placeOrdr(char customer[],Product item[],int n);
void ordrHis(char customer[]);
void feedback(char customer[]);



int main(){

    Product item[MAX_PRODUCTS];
    int n;
    char customer[50];

     printf("\n                              WELCOME TO YOUR GO-TO DESTINATION FOR FRESH GROCERIES!!!");
     printf("\n                              ________________________________________________________");
     printf("\n\n>> CHOOSE WHAT TO DO:\n\n");
     int choice1;
     do{
        printf("\n>>MAIN MENU<<\n");
        printf("\n1.Sign Up\n2.Log In\n3.Exit\n\nEnter Your Choice: ");
        if(scanf("%d",&choice1)!=1){
            while(getchar()!='\n');
            printf("Invalid Input. Try again.\n");
            continue;
        }

        if(choice1==1){
            int sch;
            printf("\n>>SIGN UP: \n");
            printf("\n1. Create Account\n");
            printf("2.Back to Main Menu\n");
            printf("\nEnter Choice: \n");
            if(scanf("%d",&sch)!=1){
                while(getchar()!='\n');
                printf("Invalid Input!\n");
                continue;
            }

            if(sch==1){
                signup();
            }
            else if(sch==2){
                continue;
            }
            else{
                printf("Invalid Choice! Returning To Main Menu...\n");
                continue;
            }

      }
        else if(choice1==2){
                int lch;
            printf("\n>>LOGIN: \n");
            printf("\n1.Log in your account.\n");
            printf("2.Back to Main Menu\n");
            printf("\nEnter Choice: \n");
            if(scanf("%d",&lch)!=1){
                while(getchar()!='\n');
                printf("Invalid Input!\n");
                continue;
            }

            if(lch==1){
                if(login(customer)){
                n=loadProd(item);
                if(n==0){
                    printf("Oops! No Products Available.");
                    continue;
            }

        int choice2;
        do{
        printf("\n>>DASHBOARD<<\n");
        printf("\n1.View All Products\n");
        printf("2.View by Categories\n");
        printf("3.Search Products\n");
        printf("4.Add To Cart\n");
        printf("5.Place Order\n");
        printf("6.Order History\n");
        printf("7.Feedback\n");
        printf("8.Log Out\n");
        printf("ENTER YOUR CHOICE: ");
        if(scanf("%d",&choice2)!=1){
            while(getchar()!='\n');
            printf("Invalid Input. Choose Again: \n");
            continue;
        }


        switch(choice2){
         case 1:
            viewProd(item,n);
            break;
         case 2:
             printf("\nCHOOSE: \n");
            viewCtg(item,n);
            break;
         case 3:
             searchProd(item,n);
             break;
         case 4:
            addCart(item,n);
            break;
         case 5:
             placeOrdr(customer,item,n);
             break;
         case 6:
            ordrHis(customer);
            break;
         case 7:
             feedback(customer);
             break;
         case 8:
             printf("Thank You For Visiting!!");
             break;
         default:
            printf("Invalid Choice!\n\n");
            break;
     }

     }while(choice2!=8);
   }

    }

    else if(lch==2){
                continue;
            }
            else{
                printf("Invalid Choice! Returning To Main Menu...\n");
                continue;
            }
    }

    else if(choice1==3){
        printf("\nThank you for visiting!\n");
        break;
    }

    else{
        printf("Invalid Choice! Try Again.\n");
    }

}while(choice1!=3);

return 0;
}






void signup(){

    FILE *fp=fopen("users.dat","ab+");

    if(fp==NULL){
        printf("Error opening file.\n");
        return;
    }

    User c,temp;
    char phone[12];

    printf("\t>>>SIGN UP TO EMBARK ON THE JOURNEY!<<<\n");
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

    printf("\nUsername must have no space; eg: 'abcdefgh','abcd_efgh'\n");
    printf("Enter Full Name: ");
    getchar();
    fgets(c.username,sizeof(c.username),stdin);
    c.username[strcspn(c.username,"\n")]='\0';

    printf("Enter Password: ");
    scanf("%29s",c.password);

    c.type=1;
    c.id=10001;

    rewind(fp);
    while(fread(&temp,sizeof(User),1,fp)){
        if(temp.id>=c.id)
            c.id=temp.id+1;
    }


    fwrite(&c,sizeof(User),1,fp);
    fclose(fp);

    printf("\nAccount Created Successfully! Your Customer ID is: %d\n",c.id);

}

int login(char loggeduser[]){

    FILE *fp=fopen("users.dat","rb");
    if(fp==NULL){
        printf("\nOops! File Not Found!\n");
        return -1;
    }

    User c;
    char n[30],p[30];

    printf("\t>>LOGIN: \n");
    printf("Phone Number: ");
    scanf("%29s",n);
    printf("Password: ");
    scanf("%29s",p);


    while(fread(&c,sizeof(User),1,fp)){
        if(c.type==1 && strcmp(c.phonenum,n)==0 && strcmp(c.password,p)==0){
            strcpy(loggeduser,c.username);
            fclose(fp);
            printf("\nLogin Successful!\nWelcome %s (ID: %d)\n",c.username,c.id);
            return c.id;
        }
    }

    fclose(fp);

    printf("\nInvalid Phone Number or Password!\n");

    return -1;
}

int loadProd(Product item[]){
    FILE *fp=fopen("products.txt","r");
    if(fp==NULL){
        printf("Error. File Not Found.\n");
        return 0;
    }

    int count=0;
    while(count<MAX_PRODUCTS && fscanf(fp,"%d %99s %f %d %99s",&item[count].id,item[count].name,&item[count].price,&item[count].quantity,item[count].category)==5){
        count++;
    }
    fclose(fp);
    return count;
}


void viewProd(Product item[],int n){
    printf("\nALL PRODUCTS:\n");
    for(int i=0;i<n;i++){
            printf("\n%d.%s->BDT %.2f\nStock:%d\nCatagory:%s\n",
                   item[i].id,item[i].name,item[i].price,item[i].quantity,item[i].category);
    }
}

void viewCtg(Product item[],int n){
     char cat[30];
       printf("Choose Category: \n");
       printf("(Vegetable/Fruit/Grain/Dairy/Meat/Fish)\n");

       printf("Search: ");
       scanf("%99s",cat);
       printf("%s: \n",cat);

       int found=0;
       for(int i=0;i<n;i++){
        if(strcmp(item[i].category,cat)==0){
            printf("\n%d.%s->BDT %.2f\nStock: %d\n",item[i].id,item[i].name,item[i].price,item[i].quantity);
            found=1;
         }
       }

       if(found==0){
        printf("Oops! No Products Found In This Category.\n");
       }

}


void searchProd(Product item[],int n){
    char srch[50];
    char tmp[50];
    printf("Search The Product Name: ");
    scanf("%49s",srch);

    strlwr(srch);

    int found=0;
    printf("\nSearch Results: \n");
    printf("ID\tName\tPrice\tQuantity\tCategory\n");

    for(int i=0;i<n;i++){
            strcpy(tmp,item[i].name);
            strlwr(tmp);

        if(strstr(tmp,srch)!=NULL){
            printf("%d.\t%s\t%.2f\t%d\t%s\n",item[i].id,item[i].name,item[i].price,item[i].quantity,item[i].category);
            found=1;
        }
    }
    if(found==0){
        printf("\nSorry, No Products Matched!\n");
    }
}

void addCart(Product item[],int n){
    char name[50], tmp[50];
    int qty;

    printf("Enter Product Name: ");
    scanf("%49s",name);

    strlwr(name);
    int index=-1;
    for(int i=0;i<n;i++){
            strcpy(tmp,item[i].name);
            strlwr(tmp);

        if(strcmp(tmp,name)==0){
            index=i;
            break;
        }
    }

    if(index==-1){
        printf("Oops! Product Not Found!\n");
        return;
    }

    printf("Enter Quantity: ");
   if(scanf("%d",&qty)!=1){
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

int transactionID(){
   FILE *fp=fopen("transaction.txt","r");
   if(!fp)
    return 1001;

   int lastID=1000, id, qty;
   float price, total;
   char c[50], p[100];

   while(fscanf(fp,"%d %49s %99s %d %f %f",&id,c,p,&qty,&price,&total)!=6){
    lastID=id;
   }
   fclose(fp);
   return lastID+1;
}

int placeOrdr(char customer[],Product item[],int n)
{
    if(cartCount==0){
        printf("Cart is empty!\n");
        return 0;
    }

    FILE *fp=fopen("transaction.txt","a");
    if(fp==NULL){
        printf("Error Opening File!\n");
        return 0;
    }

    for(int i=0;i<cartCount;i++){
        Transaction t;
        t.ordrId=transactionID();

        t.productId=0;
        t.buyerId=0;

        strcpy(t.customer,customer);
        strcpy(t.product,cart[i].product);
        t.quantity=cart[i].quantity;
        t.price=cart[i].price;
        t.total=t.price*t.quantity;

        fprintf(fp,"%d %s %s %d %.2f %.2f\n",t.ordrId,t.customer,t.product,t.quantity,t.price,t.total);
        for(int j=0;j<n;j++){
            if(strcmp(item[j].name,t.product)==0){
                item[j].quantity=item[j].quantity-t.quantity;
                break;
            }
        }

        printf("\nOrder Placed: %s\nQuantity: %d\nTotal: %.2f\nID: %d\n",t.product,t.quantity,t.total,t.ordrId);
    }

    fclose(fp);


    FILE *fp2=fopen("products.txt","w");
    if(fp2==NULL){
        printf("\nError Opening File.\n");
        cartCount=0;
        return 1;
    }

    for(int i=0;i<n;i++){
        fprintf(fp2,"%d %s %.2f %d %s\n",item[i].id,item[i].name,item[i].price,item[i].quantity,item[i].category);
    }
        fclose(fp2);

        cartCount=0;
        return 1;
}

void ordrHis(char customer[]){
     FILE *fp=fopen("transaction.txt","r");
     if(fp==NULL){
        printf("No Transactions Found.\n");
        return;
     }

     int id,qty;
     float price,total;
     char c[50],p[100];
     int found=0;

     printf("\n>> YOUR ORDER HISTORY: \n");
     while(fscanf(fp,"%d %49s %99s %d %f %f",&id,c,p,&qty,&price,&total)==6){
        if(strcmp(c,customer)==0){
            printf("\nID: %d\nItem: %s\nQuantity: %d\nTotal: %.2f\n",id,p,qty,total);
            found=1;
        }
     }

     if(found==0){
        printf("\nOh, No~ No Transactions Yet!\n");
     }
    fclose(fp);
}


void feedback(char customer[]){
    char cmnt[200];
    printf("Write Your Feedback: ");
    getchar();
    fgets(cmnt,sizeof(cmnt),stdin);

    FILE *fp=fopen("feedback.txt","a");

    if(!fp){
        printf("Error!\n");
        return;
    }
    else
    fprintf(fp,"%s: %s",customer,cmnt);
    fclose(fp);

    printf("\nThank You For Your Feedback!\n");
}


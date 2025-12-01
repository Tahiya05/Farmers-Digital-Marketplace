#include<stdio.h>
#include<string.h>
#include<conio.h>

#include "admin.h"

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

int adminLogin()
{
    FILE *fp= fopen("users.dat", "rb");
    if(!fp){
        printf("File not found\n");
        return 0;
    }
    user u;
    char username[30],phonenumber[30],pass[20];

    printf("Enter Admin Username: ");
    scanf("%s",username);
    printf("Enter Password: ");
    scanf("%s",pass);

    while (fread(&u, sizeof(user), 1, fp)){
        if (u.type==0 && strcmp(u.username, username)==0 && strcmp(u.password, pass)==0){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    printf("\nInvalid username or password.\n");
    return 0;
}

void viewfarmers()
{
    FILE *fp=fopen("users.dat", "rb");
    if(fp==NULL){
        printf("Error opening User FIle\n");
        return;
    }
    user u;
    int found=0;

    printf("\t=====LIST OF FARMERS=====\n");

    while(fread(&u, sizeof(user), 1, fp)){
        if(u.type==1){
            found=1;
            printf("ID: %d\n", u.id);
            printf("Username: %d\n", u.username);
            printf("Phone Number: %d\n", u.phonenum);

            printf("\t-----------------------------------------\n");

        }
    }

    if(!found){
        printf("No farmers found.\n");
    }
    fclose(fp);
}

void viewconsumers()
{
    FILE *fp=fopen("users.dat", "rb");
    if(fp==NULL){
        printf("Error opening User FIle\n");
        return;
    }
    user u;
    int found=0;

    printf("\t=====LIST OF CONSUMERS=====\n");

    while(fread(&u, sizeof(user), 1, fp)){
        if(u.type==2){
            found=1;
            printf("ID: %d\n", u.id);
            printf("Username: %d\n", u.username);
            printf("Phone Number: %d\n", u.phonenum);

            printf("\t-----------------------------------------\n");

        }
    }

    if(!found){
        printf("No consumers found.\n");
    }
    fclose(fp);
}

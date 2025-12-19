#include<stdio.h>
#include<string.h>

#include "user.h"

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
    FILE *fp=fopen("users.dat", "ab+");
    if (fp==NULL){
        printf("Error opening Users_File\n");
        return;
    }

    user u,temp;
    char phone[20];

    printf("\t===== FARMER REGISTRATION =====\n");

    printf("Enter your phone number: ");
    scanf("%s", phone);

    rewind(fp);
    while(fread(&temp,sizeof(user),1,fp)){
        if (strcmp(temp.phonenum, phone)==0 && temp.type==1){
            printf("Farmer with this phone number already exists!\n");
            fclose(fp);
            return;
        }
    }

    strcpy(u.phonenum, phone);

    printf("Enter your full name: ");
    fgets(u.username,sizeof(u.username),stdin);

    u.username[strcspn(u.username,'\n')]='\0';

    printf("Enter Password: ");
    scanf("%s",u.password);

    u.type=1;

    u.id=10001;

    rewind(fp);
    while(fread(&temp, sizeof(user), 1, fp)){
        if(temp.id>=u.id) u.id=temp.id+1;
    }

    fwrite(&u, sizeof(user), 1, fp);

    printf("\nRegistration Successful! Your Farmer ID is: %d\n", u.id);

    fclose(fp);
}

int farmerLogin()
{
    FILE *fp=fopen("users.dat", "rb");
    if (fp==NULL){
        printf("Error opening User File\n");
        return -1;
    }
    char number[20],password[20];
    user u;

    printf("\t===== FARMER LOGIN =====\n");

    printf("Enter Phonenumber: ");
    scanf("%s",number);

    printf("Enter Password: ");
    scanf("%s", password);

    while(fread(&u, sizeof(user), 1, fp)){
        if(u.type==1 && strcmp(u.phonenum, number)==0 && strcmp(u.password,password)==0){
            printf("\nLogin Successful! Welcome %s (ID: %d)\n", u.username, u.id);
            fclose(fp);
            return u.id;
        }
    }
    printf("\nInvalid phonenumber or password.\n");
    fclose(fp);
    return -1;

}

void consumerMenu()
{
    int choice;

     while(1){
        printf("\n");
        printf("\t====== WELCOME CONSUMERS! ======\n");
        printf("What would you like to do?\n");
        printf("1. Sign up\n");
        printf("2. Login\n");
        printf("3. Back\n");
        printf("======================================\n");
        printf("Enter choice: ");
        scanf("%d",&choice);


    switch(choice){

        case 3:
             return;
        default: printf("\nInvalid choice! Try again.\n");
            break;
    }
  }
}


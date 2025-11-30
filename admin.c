#include<stdio.h>
#include<string.h>
#include<conio.h>

#include "admin.h"
#define USER_FILE "users.dat"

void adminExistence(){
    FILE *fp = fopen(USER_FILE,"rb");
    if (fp==NULL) {
        fp=fopen(USER_FILE, "wb");
        if (!fp){
            printf("Error!\n");
            return;
        }
        user admin={"Admin", "01711234567", "admin@123", 0, "active"};
        fwrite(&admin, sizeof(user), 1, fp);

        fclose(fp);

        printf("Default admin created!\n");
        return;
    }
    fclose(fp);
}

int adminLogin(){
    FILE *fp= fopen(USER_FILE, "rb");
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

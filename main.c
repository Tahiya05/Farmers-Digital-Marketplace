#include<stdio.h>

#include"admin.h"
#include"user.h"

int main()
{
    adminExistence();

    int choice;

    while(1){
        printf("\t====== FARMERS' DIGITAL MARKETPLACE ======\n");
        printf("\nWELCOME to the marketplace!\n");
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

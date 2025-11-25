#include<stdio.h>
#include<string.h>
#include<conio.h>
#include "admin.h"

void adminExistence(){
    FILE *fp = fopen("users.dat","rb");
    if (fp==NULL) {
        fp=fopen("users.dat", "wb");
        if (!fp){
            printf("Error!\n");
            return;
        }

    }
}

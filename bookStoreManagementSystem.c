#include<stdio.h>
#include<string.h>
#include<time.h>

#include "SearchBook.h"
#include "LoginSigup.h"
#include "progess line bar.h"
#include "addStock.h"
#include "updateBookInfo.h"
#include "buyOrderFunction.h"
#include "removeBook.h"
#include "restoreBook.h"
#include "RecordHistory.h"

//int showBuyBook();

main(){
    //welcomescreen
    int flag=1,option,loopStop=1;
    printf("\n");
    system("color F5");
    progressBar(15,45);
    printf(" Welcome to D1 BookStore Management System ");
    progressBar(15,45);

    while(loopStop==1){

        //LoginFirst
        if ( flag == 1 ){
            printf("\n\n\tLogin or Sign UP first!");
            LoginSignupFunction();
            flag++;
        }

        //login as staff;
        if (adminAccount==0){
            printf("\n\t1. Show all Book information");
            printf("\n\t2. Search Book by ID, Title...");
            printf("\n\t3. Buy or Order the books");
            printf("\n\t4. Log out");
            printf("\n\t5. Exit");

            printf("\nChoose the option above: ");scanf("%d",&option);
            switch(option){
                case 1:
                    readBookInfo();
                    break;
                case 2:
                    searchMainFunction();
                    break;

                case 3:
                    mainBuyOrder();
                    break;
                case 4:
                    printf("\n\n\tLoged out Successfully!");
                    flag=1;
                    system("cls");
                    break;
                case 5:
                    printf("\n\nExiting...\n");
                    loopStop=0;
                    break;

                default:
                    printf("\n\n===========Wrong input===========\n");
                }
        }
        //login as admin
        else if (adminAccount == 1){

            printf("\n\t1. Show all Book information");
            printf("\n\t2. Search Book by ID, Title...");
            printf("\n\t3. Buy or Order the books");
            printf("\n\t4. Add Book Information");
            printf("\n\t5. Update Book Information");
            printf("\n\t6. Show Revenue and History");
            printf("\n\t7. Remove all book information");
            printf("\n\t8. Restore deleted book");
            printf("\n\t9. Log out");
            printf("\n\t10. Exit");

            printf("\nChoose the option above: ");scanf("%d",&option);
            switch(option){
                case 1:
                    readBookInfo();
                    break;
                case 2:
                    searchMainFunction();
                    break;

                case 3:
                    mainBuyOrder();
                    break;
                case 4:
                    mainAddStock();
                    break;
                case 5:
                    mainUpdate();
                    break;
                case 6:
                    mainHistory();
                    break;
                case 7:
                   mainRemove();
                    break;
                case 8:
                    mainRestore();
                    break;
                case 9:
                    printf("\n\n\tLoged out Successfully!");
                    flag=1;
                    system("cls");
                    break;
                case 10:
                    printf("\n\nExiting...\n");
                    loopStop=0;
                    break;

                default:
                    printf("\n\n===========Wrong input===========\n");
                }
        }
    }
}


#include<stdio.h>
#include<string.h>

void  showRevenue();
void showOrderBook();
void showBuyBook();

int pubYear,amount,quatity, bookAmount,boughtAmount;


void showBuyBook(){
    FILE * readHistory;
    readHistory = fopen("receiptBuy.txt","r");
    float price,discount,grandTotal;
    char id[5],title[30],author[30],type[30],checkId[10],promoCode[20],name[40],tel[40];
    char day[20],mon[20],year[20],time[20];
    float buyRevenue;
    while(fscanf(readHistory,"%s\t%s\t%d\t%f\t%f\t%f\t%s %s %s %s",&id,&title,&bookAmount,&price,&discount,&grandTotal,&mon, &day,&year,&time)!=EOF){
        printf("\n\tReceipt record on %s %s,%s %s\n",mon,day,year,time);
        printf("\n\n\tID\tTitle\t\tQuantity\tTotal($)\tDiscount\tGrand Total($)");
        printf("\n\t___________________________________________________________________________________\n");
        printf("\n\t%s\t%s\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n\n",id,title,bookAmount,price,discount,grandTotal);
        buyRevenue = buyRevenue + grandTotal;
    }
}
void showOrderBook(){
    FILE * readHistory;
    readHistory = fopen("receiptOrder.txt","r");
    float price,discount,grandTotal, orderRevenue;
    char id[5],title[30],author[30],type[30],checkId[10],promoCode[20],name[40],tel[40];
    char day[20],mon[20],year[20],time[20];

    while(fscanf(readHistory,"%s\t%s\t%s\t%s\t%d\t%f\t%f\t%f\t%s %s %s %s",&id,&name,&tel,&title,&bookAmount,&price,&discount,&grandTotal,&mon,&day,&year,&time)!=EOF){
        printf("\n\tReceipt record on %s %s, %s %s\n",mon,day,year,time);
        printf("\n\n\tCustomer Order Name: %s, Tel: %s\n",name,tel);
        printf("\n\n\tID\tTitle\t\tQuantity\tTotal($)\tDiscount\tGrand Total($)");
        printf("\n\t___________________________________________________________________________________\n");
        printf("\n\t%s\t%s\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n\n",id,title,bookAmount,price,discount,grandTotal);
        orderRevenue = orderRevenue + grandTotal;
    }

}
void showRevenue(){
    FILE * bookInfo, *readBuy, * readOrder;

    bookInfo = fopen("bookinfo.txt","r");
    readBuy = fopen("receiptBuy.txt","r");
    readOrder = fopen("receiptOrder.txt","r");
    float price,discount,grandTotal,buyRevenue, orderRevenue;
    char id[5],title[30],author[30],type[30],checkId[10],promoCode[20],name[40],tel[40];
    char day[20],mon[20],year[20],time[20];
    float totalRevenue = 0, total = 0;
    int totalAmount= 0;

    while(fscanf(readBuy,"%s\t%s\t%d\t%f\t%f\t%f\t%s %s %s %s",&id,&title,&bookAmount,&price,&discount,&grandTotal,&mon, &day,&year,&time)!=EOF){
        buyRevenue = buyRevenue + grandTotal;
    }
    while(fscanf(readOrder,"%s\t%s\t%s\t%s\t%d\t%f\t%f\t%f\t%s %s %s %s",&id,&name,&tel,&title,&bookAmount,&price,&discount,&grandTotal,&mon,&day,&year,&time)!=EOF){
        orderRevenue = orderRevenue + grandTotal;

    }

    while(fscanf(bookInfo,"%s\t%s\t%s\t%d\t%f\t%s\t%d",&id,&title,&author,&pubYear,&price,&type,&amount)!=EOF){

        //printf("\nAmount: %d price: %.2f total %.2f",amount,price,total);
        total = total + (price * amount);
        totalAmount = totalAmount + amount;

    }
    totalRevenue = orderRevenue + buyRevenue ;

    printf("\n\tTotal Revenue : %.2f",totalRevenue);
    printf("\n\tTotal Expense : %.2f",total);
    printf("\n\tBook Amount   : %d",totalAmount);

    fclose(bookInfo);fclose(readBuy);fclose(readOrder);
}
void mainHistory(){
    int option;
    system("cls");
    while(1){
        printf("\n\t\t--------------------------------");
        printf("\n\t\t|=====Please choose option=====|");
        printf("\n\t\t--------------------------------");
        printf("\n\t\t1. BUYING History");
        printf("\n\t\t2. ORDER HISTORY");
        printf("\n\t\t3. SHOW REVENUE");
        printf("\n\t\t4. Back");

        printf("\n\n\t\tEnter the option(1 - 3): ");scanf("%d",&option);

        if (option==1){
            showBuyBook();
            continue;
        }
        if(option==2){
            showOrderBook();
            continue;
        }
        if (option == 3){
            showRevenue();
            continue;
        }
        if (option==4){
            system("cls");
            break;

        }
       else {
        printf("\n\t\tWrong input\n");

       }
    }

}

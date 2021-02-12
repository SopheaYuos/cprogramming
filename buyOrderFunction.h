#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>



void buyBook();
void orderBook();
void Date();

void Date() {

    //printf(" Date: %s Time : %s \n", __DATE__, __TIME__ );

    FILE     *fptr;
    char     *fmode, filename[255], strtime_sec[20], strtime_nsec[20];
    struct   tm* tm;
    struct   timespec ts;
    time_t   now;

    now = time(NULL);
    tm  = localtime(&now);

    clock_gettime(CLOCK_REALTIME, &ts);

    sprintf(filename, "record date and time.txt");
    fmode = "a";


    fptr = fopen(filename, fmode);
    if (fptr == NULL) {
        printf("Cannot open filename \n");
        exit(0);
    }

    fprintf(fptr, "%s %s \n", __DATE__, __TIME__ );


    fclose(fptr);
}
void buyBook()
{
        int pubYear,amount,quatity, bookAmount,boughtAmount;
    float price, total;
    char id[5],title[30],author[30],type[30],checkId[10],promoCode[20],checkPromo[20], proCode[20];
    int option=0,buy,order;

    FILE* buybook;
    FILE * promoCode1;
    FILE * date;
    FILE * receiptTemp;
    FILE * subtractTemp;
    FILE * recordBuy;
    char datetime[40];

    float grandTotal,disPercent,subTotal,discount;
    //read date
    promoCode1 = fopen("promoCode.txt","r");
    date = fopen("record date and time.txt","r");
    recordBuy = fopen("receiptBuy.txt","a");
    receiptTemp = fopen("receiptTemp.txt","w");
    //GET DATE
    Date();
    while(!feof(date)){
        fgets(datetime,40,date);
  //      printf("%s",datetime);
    }
    int limit;
    int loopStop = 1, flag = 0;
    printf("\n\tEnter Amount of Book Type: ");scanf("%d",&limit);
    if (limit == 0){
        printf("\n============Wrong input============");

    }else{
        for (int i=1; i<=limit; i++){
        printf("\n\t__________No:%d__________\n",i);
        printf("\n\tEnter Book ID: ");scanf("%s",&checkId);
        buybook=fopen("bookinfo.txt","r");
        subtractTemp = fopen("temp.txt","w");

        rewind(buybook);
        while(fscanf(buybook,"%s\t%s\t%s\t%d\t%f\t%s\t%d",&id,&title,&author,&pubYear,&price,&type,&amount)!=EOF) {
            int priceInt = price;
            int nopromocode=0,count =0;
            //printf("\n===%s ",id);
            if(strcmp(checkId,id)==0){

                flag = flag + 1;
                while(1){
                    printf("\n\tBook Quantity: ");scanf("%d",&bookAmount);
                    if (bookAmount > amount){
                        printf("\n\tWe just have %d in stock, RETRY!",amount);

                    }
                    else{

                        break;
                    }
                }
                if (flag == limit){
                char input[20];
                loopStop = 1;
                while(loopStop == 1){
                    printf("\n\tDo you have Promo Code(y/n): ");scanf("%s",&input);
                    if(stricmp(input,"y")==0) {

                        printf("\n\tPromo Code: "); scanf("%s",&checkPromo);


                        rewind(promoCode1);
                        while(fscanf(promoCode1,"%s %f",&proCode,&disPercent)!=EOF){
                            count++;
                            if(strcmp(checkPromo,proCode)== 0){
                                discount = disPercent;
                                printf("\n\tCongrats, you will get %.2f%% discount",disPercent);
                                nopromocode = 0;
                                loopStop = 0;
                            }
                            else{
                                nopromocode++;
                                loopStop = 0;
                            }
                        }

                        }
                        else if(stricmp(input,"n")==0){
                            discount = 0;
                            loopStop = 0;

                        }
                        else{
                            printf("\n============Wrong input============");
                        }
                    }
                    //message
                if (count == nopromocode){
                    disPercent = 0;
                    printf("\n\tNO PROMOCODE MATCHED!");
                    }
                }


            //receipt
            total = price * bookAmount;
            fprintf(receiptTemp,"%s\t%s\t%d\t%.2f\t%.2f\n",id,title,bookAmount,price,total);

            boughtAmount = amount - bookAmount; //subtract amount that already bought
            fprintf(subtractTemp,"%s\t%s\t%s\t%d\t%d\t%s\t%d\n",id,title,author,pubYear,priceInt,type,boughtAmount);
        }else{
            fprintf(subtractTemp,"%s\t%s\t%s\t%d\t%d\t%s\t%d\n",id,title,author,pubYear,priceInt,type,amount);
            }

        }fclose(buybook);fclose(subtractTemp);
        remove("bookinfo.txt");
        rename("temp.txt","bookinfo.txt");

    }
    }
        printf("\n\n\tReceipt Issues on %s",datetime);
        printf("\n\n\tID\tTitle\t\tQuantity\tPrice\t\tTotal($)");
        printf("\n\t_________________________________________________________________\n");

        fclose(receiptTemp);
        receiptTemp = fopen("receiptTemp.txt","r");

        float sum = 0, grandTotalRiel;
        while(fscanf(receiptTemp,"%s\t%s\t%d\t%f\t%f",&id,&title,&bookAmount,&price,&total)!= EOF) {
            sum = sum + total;
            printf("\n\t%s\t%s\t%d\t\t%.2f\t\t%.2f\n",id,title,bookAmount,price,total);
        }

        grandTotal = sum * (100- discount)/100;
        grandTotalRiel = grandTotal * 4100;
        printf("\n\tSubTotal     : %.2f",sum);
        printf("\n\tDiscount     : %.2f%% ",discount);
        printf("\n\tGrand Total  : %.2f(Dollars)",grandTotal);
        printf("\n\tGrand Total  : %.2f(Riels)",grandTotalRiel);
        printf("\n\tExchange Rate: 4100 Riels");
        printf("\n\t_______________________________\n");

        fclose(receiptTemp);
        receiptTemp = fopen("receiptTemp.txt","r");

        while(fscanf(receiptTemp,"%s\t%s\t%d\t%f\t%f",&id,&title,&bookAmount,&price,&total)!= EOF) {
            fprintf(recordBuy,"%s\t%s\t%d\t%.2f\t%.2f\t%.2f\t%s",id,title,bookAmount,price,discount,grandTotal,datetime);
        }
        fclose(receiptTemp);
        fclose(receiptTemp);
        fclose(date);
        fclose(promoCode1);fclose(recordBuy);


        //copy
}

void orderBook()
{

int pubYear,amount,quatity, bookAmount,boughtAmount;
float price, total;
char id[5],title[30],author[30],type[30],checkId[10],promoCode[20];
int option=0,buy,order;
    FILE * buybook, * promoCode1;
    FILE * date;
    FILE * receiptTemp;
    FILE * subtractTemp;
    FILE * recordBuy;
    char datetime[40];
    char proCode[20],checkPromo[20];
    float grandTotal,disPercent,subTotal,discount;
    //read date
    promoCode1 = fopen("promoCode.txt","r");
    date = fopen("record date and time.txt","r");
    recordBuy = fopen("receiptOrder.txt","a");
    receiptTemp = fopen("receiptOrderTemp.txt","w");
    //GET DATE
    Date();
    while(!feof(date)){
        fgets(datetime,40,date);
    }

    int limit;
    int loopStop = 1, flag = 0;
    char name[30], tel[20];

    printf("\n\tTo order, please input your Name and Phone number");
    printf("\n\tYour Name       : ");scanf("%s",&name);
    printf("\n\tPhone Number    : ");scanf("%s",&tel);

    printf("\n\tEnter Amount of Book Type: ");scanf("%d",&limit);

    if (limit <= 0){
        printf("\n============Wrong input============");

    }else{

        for (int i=1; i<=limit; i++){

        printf("\n\t__________No:%d__________\n",i);
        printf("\n\tEnter Book ID: ");scanf("%s",&checkId);
        buybook=fopen("bookinfo.txt","r");
        subtractTemp = fopen("tempOrder.txt","w");

        rewind(buybook);
        while(fscanf(buybook,"%s\t%s\t%s\t%d\t%f\t%s\t%d",&id,&title,&author,&pubYear,&price,&type,&amount)!=EOF) {
            int priceInt = price;
            int nopromocode=0,count =0;
            if(strcmp(checkId,id)==0){
                flag = flag + 1;
                while(1){
                    printf("\n\tBook Quantity: ");scanf("%d",&bookAmount);
                    if (bookAmount > amount){
                        printf("\n\tWe just have %d in stock, RETRY!",amount);

                    }
                    else{

                        break;
                    }
                }
                if (flag == limit){
                char input[20];
                loopStop = 1;
                while(loopStop == 1){
                    printf("\n\tDo you have Promo Code(y/n): ");scanf("%s",&input);
                    if(stricmp(input,"y")==0) {

                        printf("\n\tPromo Code: "); scanf("%s",&checkPromo);


                        rewind(promoCode1);
                        while(fscanf(promoCode1,"%s %f",&proCode,&disPercent)!=EOF){
                            count++;
                            if(strcmp(checkPromo,proCode)== 0){
                                discount = disPercent;
                                printf("\n\tCongrats, you will get %.2f%% discount",disPercent);
                                nopromocode = 0;
                                loopStop = 0;
                            }
                            else{
                                nopromocode++;
                                loopStop = 0;
                            }
                        }

                        }
                        else if(stricmp(input,"n")==0){
                            discount = 0;
                            loopStop = 0;

                        }
                        else{
                            printf("\n============Wrong input============");
                        }
                    }
                    //message
                if (count == nopromocode){
                    disPercent = 0;
                    printf("\n\tNO PROMOCODE MATCHED!");
                    }
                }


            //receipt
            total = price * bookAmount;
            fprintf(receiptTemp,"%s\t%s\t%d\t%.2f\t%.2f\n",id,title,bookAmount,price,total);

            boughtAmount = amount - bookAmount; //subtract amount that already bought
            fprintf(subtractTemp,"%s\t%s\t%s\t%d\t%d\t%s\t%d\n",id,title,author,pubYear,priceInt,type,boughtAmount);
        }else{
            fprintf(subtractTemp,"%s\t%s\t%s\t%d\t%d\t%s\t%d\n",id,title,author,pubYear,priceInt,type,amount);
            }

        }fclose(buybook);fclose(subtractTemp);
        remove("bookinfo.txt");
        rename("tempOrder.txt","bookinfo.txt");

    }
    }
        printf("\n\n\tReceipt Issues on %s",datetime);
        printf("\n\n\tCustomer Order Name: %s, Tel: %s",name,tel);
        printf("\n\n\tID\tTitle\t\tQuantity\tPrice\t\tTotal($)");
        printf("\n\t_________________________________________________________________\n");

        fclose(receiptTemp);
        receiptTemp = fopen("receiptOrderTemp.txt","r");

        float sum = 0, grandTotalRiel;

        while(fscanf(receiptTemp,"%s\t%s\t%d\t%f\t%f",&id,&title,&bookAmount,&price,&total)!= EOF) {

            sum = sum + total;
            printf("\n\t%s\t%s\t%d\t\t%.2f\t\t%.2f\n",id,title,bookAmount,price,total);
        }

        grandTotal = sum * (100- discount)/100;
        grandTotalRiel = grandTotal * 4100;
        printf("\n\tSubTotal     : %.2f",sum);
        printf("\n\tDiscount     : %.2f%% ",discount);
        printf("\n\tGrand Total  : %.2f(Dollars)",grandTotal);
        printf("\n\tGrand Total  : %.2f(Riels)",grandTotalRiel);
        printf("\n\tExchange Rate: 4100 Riels");
        printf("\n\t_______________________________\n");

        fclose(receiptTemp);
        receiptTemp = fopen("receiptOrderTemp.txt","r");

        while(fscanf(receiptTemp,"%s\t%s\t%d\t%f\t%f",&id,&title,&bookAmount,&price,&total)!= EOF) {
            fprintf(recordBuy,"%s\t%s\t%s\t%s\t%d\t%.2f\t%.2f\t%.2f\t%s",id,name,tel,title,bookAmount,price,discount,grandTotal,datetime);
        }
        fclose(receiptTemp);
        fclose(receiptTemp);
        fclose(date);
        fclose(promoCode1);fclose(recordBuy);


        //copy
}
void mainBuyOrder(){
//int main(){
    system("cls");
    while(1){
        printf("\n\t\t--------------------------------");
        printf("\n\t\t|=====Please choose option=====|");
        printf("\n\t\t--------------------------------");
        printf("\n\t\t1.BUY");
        printf("\n\t\t2.ORDER");
        printf("\n\t\t3.Back");

        printf("\n\n\t\tEnter the option(1 - 3): ");scanf("%d",&option);

        if (option==1){
            buyBook();
            continue;
        }
        if(option==2){
            orderBook();
            continue;
        }
        if (option==3){
            system("cls");
            break;

        }
       else {
        printf("\n\t\tWrong input\n");

       }
}
}

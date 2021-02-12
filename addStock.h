#include<stdio.h>
#include<string.h>

void storeInfoBook();
void addStock();


void bookinfo(){
    FILE * search;
    search = fopen("bookinfo.txt","r");
    int flag =1;
    system("cls");
    printf("\n___________________________________________________ All Book information _________________________________________________\n\n");

    while(fscanf(search,"%s\t%s\t%s\t%d\t%d\t%s\t%d\n",&id,&title,&author,&pubYear,&price,&type,&amount)!=EOF){

        //to set output print only one time
        if (flag==1){

            printf("\n\n\tID\t  Title\t\t  Type\t\tAuthor\t\tPublish Year\tPrice    AmountInStock");
            printf("\n\t_________________________________________________________________________________________________\n");
            flag= flag+1;
        }
        printf("\n\t%-7s %-15s %-15s %-18s %-14d $%-14d %-8d",id,title,type,author,pubYear,price,amount);

    }
    printf("\n");
    fclose(search);
}

void storeInfoBook(char filename[]){
char id[50],title[50],author[50],type[50],input[20];
int year,price,amount;
int n;
FILE*f1;
f1=fopen(filename, "a");
int loopStop =1;
 while(loopStop==1){

    printf("\n\tAmount of different book information (1,2,3,...): ");
    scanf("%d", &n);
    if(n==0){
        printf("\n\n\\t======Wrong input========");
        continue;
    }
    for(int m=1; m<=n; m++){
        printf("\n\t\t__________ %d __________\n",m);
        printf("\n\t\tEnter ID : ");
        scanf("%s", &id);

        printf("\n\t\tEnter Title : ");
        scanf("%s", &title);

        printf("\n\t\tEnter name of author: ");
        scanf("%s", &author);

        printf("\n\t\tEnter public Year: ");
        scanf("%d", &year);

        printf("\n\t\tEnter price($): ");
        scanf("%d", &price);

        printf("\n\t\tEnter Type of book: ");
        scanf("%s", &type);
        printf("\n\t\tEnter Amount of Books: ");
        scanf("%d",&amount);

        printf("\n");

        fprintf(f1,"\n%s\t%s\t%s\t%d\t%d\t%s\t%d",id,title,author,year,price,type,amount);
    }
        printf("\n__________________________________________ Book added Successfully __________________________________________\n");


            while(1){
            printf("\nDo you want to Add other new book infomation again(y/n): ");scanf("%s",&input);
            if(stricmp(input,"y")==0) {
                break;
            }
            else if(stricmp(input,"n")==0){
                loopStop = 0;
                break;
            }
            else{
                printf("\n============Wrong input============");

            }
        }
 }

    fclose(f1);

}
void addStock(){
    FILE * stock;
    FILE * newfile;

    char id[20], title[20],author[20],type[20],checkId[20],input[20];
    int year, price,amount,checkPrice,updateYear,pubYear, newStock;

    int total;

    int flag=1;
    while(flag==1){
        stock = fopen("bookinfo.txt","r");
        newfile = fopen("newfile.txt","w");
        printf("\n\n\tEnter the book ID: "); scanf("%s",&checkId);

        //rewind(update);//reset cursor to the first line
        while(fscanf(stock,"%s %s %s %d %d %s %d",&id,&title,&author,&pubYear,&price,&type,&amount)!=EOF){

                 if(strcmp(checkId,id)==0){
                 printf("\n\n\tEnter a new Amount of book (old book amount will be sum with new amount): ");scanf("%d",&newStock);
                total = newStock + amount;
                //update year will write to new file
                fprintf(newfile,"%s\t%s\t%s\t%d\t%d\t%s\t%d\n",id,title,author,pubYear,price,type,total);
            }
            else{
                //write old data to new file
                fprintf(newfile,"%s\t%s\t%s\t%d\t%d\t%s\t%d\n",id,title,author,pubYear,price,type,amount);
            }
        }

        //close file first before it was remove or renamed
        fclose(stock);
        fclose(newfile);
        //delete file
        remove("bookinfo.txt");
        //rename file
        rename("newfile.txt","bookinfo.txt");
        system("cls");
        bookinfo();
        while(1){
            printf("\n\tDo you want to add others again(y/n): ");scanf("%s",&input);
            if(stricmp(input,"y")==0) {
                break;

            }
            else if(stricmp(input,"n")==0){
                flag=0;
                system("cls");
                break;


            }
            else{
                printf("\n============Wrong input============");
            }


        }
  }

}

void mainAddStock(){
//int main(){
    char input[20];
    int option,loopStop=1;
    system("cls");
    bookinfo();
while(loopStop==1){
        printf("\n\n\t1. Add new Book information");
        printf("\n\n\t2. Add New Book Stock");
        printf("\n\n\t3. Back");
        printf("\n\n\tEnter the option (1-3): ");scanf("%d",&option);

        switch(option){
        case 1:
            storeInfoBook("bookinfo.txt");
            break;
        case 2:
            addStock();
            break;

        case 3:
            loopStop=0;
            system("cls");
            break;
        default:
            printf("\n\n===========Wrong input===========\n");
        }
    }


}








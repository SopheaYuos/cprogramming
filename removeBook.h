#include<stdio.h>
#include<string.h>

void removeBookInfo();
void showBookBeforeRemove();
int removeByIdCount = 0;
char id[20], title[20], author[20], type[20];
int pubYear, price, amount;
char checkId[20],check[20], checkTitle[20], checkAuthor[20],checkType[20];

void showBookBeforeRemove(){
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
void removeBookInfo(){
    FILE * update;
    FILE * newfile;
    char updateTitle[20];
    int flag=1;
    while(flag==1){

        printf("\n\n\tAre you sure to remove all book information?(y/n) : "); scanf("%s",&check);
        if(stricmp(check,"y") == 0){
            update = fopen("bookinfo.txt","r");
            newfile = fopen("restoreBookInfo.txt","w");
            while(fscanf(update,"%s\t%s\t%s\t%d\t%d\t%s\t%d",&id,&title,&author,&pubYear,&price,&type,&amount)!=EOF){

            fprintf(newfile,"%s\t%s\t%s\t%d\t%d\t%s\t%d\n",id,title,author,pubYear,price,type,amount);

            }
            fclose(update);
            fclose(newfile);
            //delete file
            remove("bookinfo.txt");
            printf("\n\t_____________________________________ Remove Successfully _____________________________________");
            flag = 0;
        }
        else if (stricmp(check,"n")== 0){
            break;
        }
        else{
            printf("\n\t===========Wrong input===========");
        }
    }
}
void removeById(){
    FILE * update;
    FILE * temp;
    FILE * removeById;
    char updateTitle[20];
    int flag=1;
    while(flag==1){

        printf("\n\n\tAre you sure to remove by ID?(y/n) : "); scanf("%s",&check);
        if(stricmp(check,"y") == 0){
            showBookBeforeRemove();
            printf("\n\tEnter Book ID: ");scanf("%s",checkId);
            update = fopen("bookinfo.txt","r");
            temp = fopen("temp.txt","w");
            removeById = fopen("removeByID.txt","a");
            int count, countPos =0;
            while(fscanf(update,"%s\t%s\t%s\t%d\t%d\t%s\t%d",&id,&title,&author,&pubYear,&price,&type,&amount)!=EOF){
                countPos++;
                if(strcmp(checkId,id)== 0){
                    count = countPos;
                    fprintf(removeById,"%d\t%s\t%s\t%s\t%d\t%d\t%s\t%d\n",count,id,title,author,pubYear,price,type,amount);
                    continue;
                }
                else{
                    fprintf(temp,"%s\t%s\t%s\t%d\t%d\t%s\t%d\n",id,title,author,pubYear,price,type,amount);
                }
            }
            fclose(temp);
            fclose(removeById);
            fclose(update);
            //delete file
            remove("bookinfo.txt");
            rename("temp.txt","bookinfo.txt");
            printf("\n\t_____________________________________ Remove Successfully _____________________________________");
            flag = 0;
        }
        else if (stricmp(check,"n")== 0){
            break;
        }
        else{
            printf("\n\t===========Wrong input===========");
        }
    }
}
void mainRemove(){
//int main(){
    char input[20];
    int option,loopStop=1;
    system("cls");
    while(loopStop==1){

        printf("\n\n\t1. Remove by ID");
        printf("\n\n\t2. Remove All Info");
        printf("\n\n\t3. Back");
        printf("\n\n\tEnter the option (1-3): ");scanf("%d",&option);

        switch(option){
        case 1:
            removeById();
            break;
        case 2:
            removeBookInfo();
            break;
        case 3:
            loopStop = 0;
            system("cls");
            break;
        default:
            printf("\n\n===========Wrong input===========\n");
        }
    }

}








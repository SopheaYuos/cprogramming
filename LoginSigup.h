#include<stdio.h>
#include<string.h>
#include<conio.h>
struct User{
    char name[30];
    char password[30];
};
int adminAccount = 1;
char verifyUsername[20];
char verifyPassword[20];

void signUpAccount();
void signInAccount();
void LoginSignupFunction();
void updateUsernamePass();
void hideEncriptPassword();


void LoginSignupFunction(){
//void main(){
    int userinput;
    int loopStop = 1;

    while(loopStop == 1){
        printf("\n\n____________________________Please sign in or sign up ____________________________");
        printf("\n\n1. Sigup\n2. Login");
        printf("\n\n\t======if you are Admin, just login======");
        printf("\n\nEnter the option(1-2): ");
        scanf("%d",&userinput);

        if(userinput==1){
            //signup
            signUpAccount();

        }
        else if(userinput==2){
            signInAccount();

        }
        else{
            printf("\n\tWrong input\n");
            continue;
        }
        while(1){
        char input[20];
            printf("\n\tDo you want to change USERNAME OR PASSWORD(y/n): ");scanf("%s",&input);
            if(stricmp(input,"y")==0) {
                updateUsernamePass();
                loopStop = 0;
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
        system("cls");
    }

}
void updateUsernamePass(){
    struct User account;
    FILE * StaffAccount;
    FILE * AdminAccount;
    FILE * oldFile;
    FILE * update;
    char newUserName[20],newPassword[20];
    char oldUserName[20], oldPassword[20];

    printf("\n\tTo verify it's you, please Sign in again");
    while(1){
        printf("\n\tEnter the Username: ");scanf("%s",&account.name);
        hideEncriptPassword(account.password);
        //Confirm account
        if( strcmp(account.name,verifyUsername)==0 && strcmp(account.password,verifyPassword) == 0 ){
            printf("\n\tYou account has been confirm successfully!");\
            break;
        }else{
            printf("\n\tUsername or password not matched, retry...");
        }
    }
    //choose option
    int option;
    while(1){
        printf("\n\tHere are some options: ");
        printf("\n\t\t1. Change Username only");
        printf("\n\t\t2. Change Password only");
        printf("\n\t\t3. Change both Username and Password");
        printf("\n\tEnter the option: ");scanf("%d",&option);
        if (option == 1){
            printf("\n\tNew Username: ");scanf("%s",&newUserName);
            break;
        }else if (option == 2 ){
            hideEncriptPassword(newPassword);
            break;
        }else if (option == 3){
            printf("\n\tNew Username: ");scanf("%s",&newUserName);
            hideEncriptPassword(newPassword);
            break;
        }else{
            printf("\n\tWrong Input");
        }

   }



   //admin or staff

    if (adminAccount == 1){
        oldFile = fopen("AdminAccount.txt","r");
        update = fopen("UpdateAdminInfo.txt","w");
        while(fscanf(oldFile,"%s %s",&oldUserName,&oldPassword)!=EOF){
            if (strcmp(oldUserName,account.name)== 0){
                    if (option == 1 ){
                        fprintf(update,"%s %s\n",newUserName,oldPassword);
                    }
                    else if (option == 2 ){
                        fprintf(update,"%s %s\n",oldUserName,newPassword);
                    }
                    else if (option == 3){
                        fprintf(update,"%s %s\n",newUserName,newPassword);
                    }
            }else{
                    fprintf(update,"%s %s\n",oldUserName,oldPassword);
                }
        }

    fclose(oldFile);fclose(update);
    remove("AdminAccount.txt");
    rename("UpdateAdminInfo.txt","AdminAccount.txt");
    }


    if (adminAccount==0){
        oldFile = fopen("StaffAccount.txt","r");
        update = fopen("UpdateStaffInfo.txt","w");
        while(fscanf(oldFile,"%s %s",&oldUserName,&oldPassword)!=EOF){
            if (strcmp(oldUserName,account.name)== 0){
                    if (option == 1 ){
                        fprintf(update,"%s %s\n",newUserName,oldPassword);
                    }
                    else if (option == 2 ){
                        fprintf(update,"%s %s\n",oldUserName,newPassword);
                    }
                    else if (option == 3){
                        fprintf(update,"%s %s\n",newUserName,newPassword);
                    }
            }else{
                    fprintf(update,"%s %s\n",oldUserName,oldPassword);
                }
        }
        fclose(oldFile);fclose(update);
        remove("StaffAccount.txt");
        rename("UpdateStaffInfo.txt","StaffAccount.txt");
    }


}

const char maxLength = 15;
void hideEncriptPassword(char password[maxLength+1]){

    char ch,charPos; //password[maxLength+1],charPos, username[maxLength+1];
    printf("\n==NOTE:Password cannot exceed 15 charater==");
    int loopStop = 1, flag =0;
    while(loopStop ==1){
    charPos = 0;
    printf("\n\tEnter the password: ");
        while(1){
           //password hidden
            password[charPos] = '\0';
            ch = getch();

            if (ch == 13){
                if(strlen(password)>0){
                    loopStop = 0;
                    break;
                }
                else{
                    break;
                    }

            }
            else if (ch==8){ //when hit backspace
                    if (charPos > 0){
                        charPos--;
                        password[charPos] = '\0';
                        printf("\b \b");
                    }
            }
            else{
                if (charPos < maxLength){
                    password[charPos] = ch + 2; //+2 TO ENCRIPTION
                    charPos++;
                    printf("*");
                }
                else{
                    printf("\n\tOver 15 characters");
                    break;
                }
            }
        }

            //password[charPos] = '\0';
        if (strlen(password)== 0){
            printf("NO PASSWORD ENTERED");
        }

    }

}
void signUpAccount(){
    struct User account;
    FILE * signup;
    char checkName[20],checkPass[20];
    signup = fopen("StaffAccount.txt","a+");

    while(1){
    int flag = 0;
    printf("\n\tEnter your name: ");scanf("%s",account.name);
//    printf("Enter your password: ");scanf("%s",account.password);
    hideEncriptPassword(account.password);

    strcpy(verifyUsername, account.name);
    strcpy(verifyPassword, account.password);


    rewind(signup);
    while(fscanf(signup,"%s %s",checkName,checkPass)!=EOF){
        if(strcmp(account.name,checkName)== 0){

            flag = 1;
        }
    }
    if(flag ==1 ){
        printf("\n\tUsername was already regigisteed, Please retry!");
    }
    else{
        adminAccount = 0;
        fprintf(signup,"%s %s\n",account.name,account.password);
        printf("\n\n____________________________Sign up as Staff Account Successfully ____________________________\n\n");
        break;
    }
}

    fclose(signup);
}
void signInAccount(){
    struct User account;
    //admin
    FILE *signIn;
    FILE * admin;
    int len;char encryptPass[30];
    char adminCheckName[30],adminCheckPassword[30];
    char newusername[30],newpassword[30],checkname[30],checkpassword[30];
    int option,loopStop =1;
    signIn = fopen("StaffAccount.txt","r");
    admin = fopen("AdminAccount.txt","r");

    while(loopStop == 1){
        printf("\nEnter your username: ");scanf("%s",&account.name);
        hideEncriptPassword(account.password);
        strcpy(verifyUsername, account.name); //copy  for account confirmation
        strcpy(verifyPassword, account.password);
        int flag = 0;
        //rewind position
        rewind(signIn), rewind(admin);
        while( fscanf(signIn,"%s %s", &checkname,&checkpassword)!=EOF || fscanf(admin,"%s %s",&adminCheckName,&adminCheckPassword)!=EOF) {
            //printf("%s %s\n",account.name,account.password);
            if (strcmp(account.name,checkname)== 0 && strcmp(account.password,checkpassword)==0) {
                adminAccount = 0; //staff
                flag = 1;
                }
            else if (strcmp(adminCheckName,account.name)== 0 && strcmp(adminCheckPassword,account.password)== 0){

                adminAccount = 1;
                flag = 1;
            }

        }
        if (flag == 1 ){
            printf("\n\n____________________________ Signed in successfully ____________________________\n\n");
            if(adminAccount==0){
                printf("\n\tYou're logined as a Staff");
            }else{
                printf("\n\tYou're logined as an Admin");
            }
            break;
        }
        else if (flag == 0 ){
        int stop = 1;
            printf("\n\n____________________________ Wrong username or password ____________________________");
            while(stop == 1){
                printf("\n\n1. Do you want to sign in again? ");
                printf("\n2. No account, please sign up a new one?");
                printf("\n\tInput(1 or 2): ");scanf("%d",&option);
                switch (option){
                case 1:
                    stop = 0;
                    break;
                case 2:
                    signUpAccount();
                    loopStop = 0;
                    break;
                default:
                    printf("\n\tWrong input");

                }
            }
        }
    }

    fclose(signIn);
    fclose(admin);
}

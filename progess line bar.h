

int speed;
int col;
void progressBar(speed,col){
    int num = 219;

    for(int i=1; i<=col; i++){

        Sleep(speed);
        printf("%c",num);

       }
}


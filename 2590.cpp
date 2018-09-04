#include <stdio.h>
int main(void){
    int paper[7];
    for(int i = 1; i <= 6; i++)
        scanf("%d", &paper[i]);
    int cnt = 0;
    cnt += paper[6]; // 6*6은 그냥 그 자체가 판 1개를 소모
    while(paper[5] > 0){ // 5*5를 판 1개에 부착하고 1*1을 최대한 많이 부착
        paper[5]--;
        paper[1] -= 11;
        if(paper[1] < 0) paper[1] = 0;
        cnt++;
    }
    while(paper[4] > 0){ // 4*4를 판 1개에 부착하고 2*2를 최대한 많이 부착
        paper[4]--;
        if(paper[2] >= 5) paper[2] -= 5;
        else{
            paper[1] -= (5-paper[2]) * 4;
            if(paper[1] < 0) paper[1] = 0;
            paper[2] = 0;
        }
        cnt++;
    }

    while(paper[3] > 0){
        if(paper[3] >= 4)  paper[3] -= 4;
        else if(paper[3] == 3){
            paper[3] = 0;
            if(paper[2] >= 1){
                paper[2]--;
                paper[1] -= 5;
            }
            else
                paper[1] -= 9;
            if(paper[1] < 0) paper[1] = 0;
        }
        else if(paper[3] == 2){
            paper[3] = 0;
            if(paper[2] >= 3){
                paper[2] -= 3;
                paper[1] -= 6;
            }
            else if(paper[2] == 2){
                paper[2] = 0;
                paper[1] -= 10;
            }
            else if(paper[2] == 1){
                paper[2] = 0;
                paper[1] -= 14;
            }
            else paper[1] -= 18;
            if(paper[1] < 0) paper[1] = 0;
        }
        else{ // paper[3] == 1;
            paper[3] = 0;
            if(paper[2] >= 5){
                paper[2] -= 5;
                paper[1] -= 7;
            }
            else{
                paper[1] -= 7 + (5-paper[2]) * 4;
                paper[2] = 0;
            }
            if(paper[1] < 0) paper[1] = 0;
        }
        cnt++;
    }
    int temp = paper[2] * 4 + paper[1];
    if(temp % 36 == 0)
        cnt += temp / 36;
    else
        cnt += temp / 36 + 1;
    printf("%d", cnt);
    return 0;
}

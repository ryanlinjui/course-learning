#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main()
{
    int64_t m=0,n=0;
    printf("$ ./hw0301\n");
    printf("Please enter the width : ");
    scanf("%lld",&m);
    printf("Please enter the height: ");
    scanf("%lld",&n);
    if(m<1||n<1){
        printf("ERROR\n");
    }
    int64_t mp=m,np=n;
    int64_t t[n][m];
    for(int i=0;i<n;i++){
        t[i][0] = i+1;
    }
    int64_t area = m*n;
    for(int i=n+1,d=0,x=n-1,y=0;i<=area;){
        if(d==0){
            for(int j=1;j<m;j++){
                y++;
                t[x][y] = i;
                i++;
            }
            d=1;
            m--;
        }
        else if(d==2){
            for(int j=1;j<m;j++){
                y--;
                t[x][y] = i;
                i++;
            }
            d=3;
            m--;
        }
        if(d==1){
            for(int j=1;j<n;j++){
                x--;
                t[x][y] = i;
                i++;
            }
            d=2;
            n--;
        }
        else if(d==3){
            for(int j=1;j<n;j++){
                x++;
                t[x][y] = i;
                i++;
            }
            d=0;
            n--;
        }
    
    }
    int64_t max_num=mp*np;

    for(int i=0;i<np;i++){
        
        for(int j=0;j<mp;j++){
            for(int n=0;n<(int)log10(max_num)-(int)log10(t[i][j]);n++){
                printf(" ");
            }
            printf("%lld ",t[i][j]);

        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
//1. m, n的範圍為32bit整數。
//2. invalid input在這題的定義是給定符合(1.)的m, n後，無法產生任何數字輸出的情況。
//小提示：所有符合(1.)、不違反(2.)的輸入，都必須完整且正確的輸出。

/*#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

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
    
    for(int i=1;i<=n;i++){
        printf("%ld",i);
        //for(int j=)
        printf("%ld\n",m+n+n-i-1);
    }
    return 0;
}
*/






#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main()
{
    int64_t m=0,n=0;
    printf("$ ./hw0301\n");
    printf("Please enter the width : ");
    scanf("%ld",&m);
    printf("Please enter the height: ");
    scanf("%ld",&n);
    if(m<1||n<1){
        printf("ERROR\n");
        return 0;
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
            printf("%ld ",t[i][j]);

        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

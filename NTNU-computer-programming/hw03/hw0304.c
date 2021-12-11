// 1. 這題不會故意去做不合法輸入，能輸進0~100不會出錯就行，其他像負數或數字過大什麼的，可擋可不擋。

//1. 如果有多個n同樣靠近2.7182818284590452354，請輸出最小的那個n。
//2. 找到的n請寫進hw0304.pdf，然後附上找到這個n的過程，即使是把所有結果印一次也行，拒絕只寫一行n=XXX。
//3. 這題需要有程式，沒有程式就算找到的n是對的一樣0分。
//小提示：希望你們知道之所以要給到小數後19位的涵義，如果不清楚的話可以去查一下浮點數精度，你會發現有某個浮點數型態很符合題目需求，沒有使用這個變數型態的最多算半對。

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

long double real_ans=0;

void authentication_max_n(){
    long double n=2,ans=0;
    while(1){
        ans=0;
        for(long double i = n;i>=2;i--){
            ans = 1/(1+1/(1+1/((2*i)+ans)));
        }
        ans = 2+1/(1+1/(2+ans));
        printf("n=%d,Answer: %.19Lf\n",(int)n,ans);
        if(ans==real_ans){
            printf("Close to n=%d\n",(int)n);
            exit(0);
        }
        n++;
    }
}


int main()
{
    long double n=0,ans=0;
    printf("$ ./hw0304\n");
    printf("Please enter n: ");
    scanf("%Lf",&n);
    if(n<2){
        printf("Invalid Input!!\n");
        exit(0);
    }
    for(;n>=2;n--){
       ans = 1/(1+1/(1+1/((2*n)+ans)));
    }
    ans = 2+1/(1+1/(2+ans));
    printf("Answer: %.19Lf\n",ans);
    real_ans = ans;
    //authentication_max_n();
    return 0;
}
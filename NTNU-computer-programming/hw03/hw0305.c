//1. 這題會用到高中數學統計相關知識，如果不記得的話可以去查一下"線性迴歸"、"least square"之類的東西。
//2. 年份的輸入是32bit整數，根據題意從20世紀開始視為合法年份(>=1900)，不考慮曆法影響，除了合法年份和終止點-1以外都是不合法輸入，需要提示。

// 1. 我會保證hw0305的計算過程中不會出現超過double範圍的數字。
// 2. 輸入的溫度低於絕對零度(這裡設為−273.15)視為非法輸入。
// 3. 輸入的參考資料筆數小於兩筆就輸入-1的話，請提示"The amount of data is not enough to predict."，並結束程式。
// 4. 輸入的溫度最多只會到小數後一位。
// 5. 輸入的溫度越來越低不是非法輸入，畢竟我們也不確定未來人類能不能讓地球降溫。

// 題目的意思是要你們根據給定的(年分/溫度)資料去生成一個Linear model，
// 然後透過代入年分進這個model去預測溫度，
// 所以這個預測年分沒有範圍限制，只有32bit整數限制，
// 可以小於enter year，甚至你輸入的預測年分和enter year重複也應該輸出對應的預測溫度，
// 預測歸預測、實際歸實際，
// 理論上Linear model是可以輸入到整個實數域的，
// 而我只要求你們作32bit整數的預測且保證計算過程不會讓double溢位。

//1. 年份重複、溫度不同算不合法輸入。
//2. 預測的溫度請四捨五入到小數後四位。

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    double year=0,sigma_x=0,sigma_y=0,sigma_xy=0,sigma_x2=0,temperature=0,a=0,b=0,n=0;
    printf("$ ./hw0305\n");
    while (1){
        printf("Please enter the year: ");
        scanf("%lf",&year);
        if(year==-1){
            if(n<=1){
                printf("The amount of data is not enough to predict.\n");
                exit(0);
            }
            break;
        }
        if(year<1900){
            printf("Invalid Input!!\n");
            exit(0);
        }
        printf("Temperature: ");
        scanf("%lf",&temperature);
        if(temperature==-1){
            if(n<=1){
                printf("The amount of data is not enough to predict.\n");
                exit(0);
            }
            break;
        }
        if(temperature<-273.15){
            printf("Invalid Input!!\n");
            exit(0);
        }
        n++;
        sigma_x += year;
        sigma_y += temperature;
        sigma_xy += year*temperature;
        sigma_x2 += year*year;
    }
    a=(n*sigma_xy-sigma_x*sigma_y)/(n*sigma_x2-sigma_x*sigma_x);
    b=(sigma_y-a*sigma_x)/n;
    printf("Please enter the prediction year: ");
    scanf("%lf",&year);
    temperature=a*year+b;
    printf("Temperature: %.4lf\n",(double)((int)((temperature* 10000) + 0.5) / 10000.0));
    return 0;
}

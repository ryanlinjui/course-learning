#include <stdio.h>
#include <math.h>

void hanoi_recursive(int n,int t1,int t2,int t3,int disk){
    if(n == 1) {
        printf("move disk %d to rod %d\n",disk,t2);
    }
    else {
        hanoi_recursive(n-1, t1, t3, t2,disk-1);
        hanoi_recursive(1, t1, t2, t3,disk);
        hanoi_recursive(n-1, t3, t2, t1,disk-1);
    }
}

void hanoi_iterative(int n,int t1,int t2,int t3){
    int disk_l[20]={0};
    int times = pow(2,n)-1;
    int disk_m=0,rod_d=0;
    for(int i=1;i<=times;i++){
        if(n%2==0){
            if(i%2==1){
                disk_m=1;
            }
            else{
                for(int j=i,i_count=0;;i_count++){
                    if(j%2==0){
                        j/=2;
                    }
                    else{
                        i_count++;
                        disk_m=i_count;
                        break;
                    }
                }
            }
            if(disk_m%2==0){
                disk_l[disk_m]=(disk_l[disk_m]+1)%3;
            }
            else{
                disk_l[disk_m]=(disk_l[disk_m]-1+3)%3;
            }
            rod_d=disk_l[disk_m]+1;
        }
        else{
            if(i%2==1){
                disk_m=1;
            }
            else{
                for(int j=i,i_count=0;;i_count++){
                    if(j%2==0){
                        j/=2;
                    }
                    else{
                        i_count++;
                        disk_m=i_count;
                        break;
                    }
                }
            }
            if(disk_m%2==0){
                disk_l[disk_m]=(disk_l[disk_m]-1+3)%3;
            }
            else{
                disk_l[disk_m]=(disk_l[disk_m]+1)%3;
            }
            rod_d=disk_l[disk_m]+1;
        }
        printf("move disk %d to rod %d\n",disk_m,rod_d);
    }
}
/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月07日 星期二 16时19分08秒
 ************************************************************************/
#include <stdio.h>
int add(int low,int high)
{
        int i,sum;
        for(i=low;i<=high;i++)
            sum = sum + i;
        return sum;

}
int main(int argc,char **argv)
{
        int result[100];
        result[0] = add(1,10);
        result[1] = add(1,100);
        printf("result[0] is %d\nresult[1] is %d \n",result[0],result[1]);  
        return 0;

}


#include <stdio.h>
struct answer Bursa(int *array, int size);

struct answer{
    int low;
    int high;
    int profit;
}ans;

int main()
{
    int array[] = {28,17,0,1,13,0};
    struct answer ans_main = Bursa(array,sizeof(array)/sizeof(int));
    printf("buy index: %d\nsell index: %d\nprofit: %d\n", ans_main.low, ans_main.high, ans_main.profit);
    return 0;
}

struct answer Bursa(int *array, int size)
{
    int i=0;
    int j=1;
    ans.low = i;
    ans.high = j;
    ans.profit = array[ans.high]-array[ans.low];
   
    while (j != size -1)
    {
        while(array[i+1]<array[i])
        {
            ++i;
            if ( i == size-1)
            {
                break;
            }
        }
        j=i;
        while (array[j+1]>=array[j] && j!=size-1)
        {
            ++j;
            if ( j == size-1)
            {
                break;
            }
        }
        
        if (array[j]-array[i]>ans.profit && ans.high>ans.low)
        {
            ans.high=j;
            ans.low = i;
            ans.profit = array[ans.high]-array[ans.low];
            
        }
        if (j == size-1)
        {
            break;
        }
        i=j;
    }
    return ans;
}

#include<cstdio>
#include<algorithm>
using namespace std;

int a[40005];
int d[40005];

// 求解最长升序子序列 (单调)
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    if (n==0)  //0个元素特判一下 
    {
        printf("0\n");
        return 0;
    }
    d[1]=a[1];  //初始化 
    int len=1;
    for (int i=2;i<=n;i++)
    {
        if (a[i]>=d[len]) d[++len]=a[i];  //如果可以接在len后面就接上，如果是最长上升子序列，这里变成> 
        else  //否则就找一个最该替换的替换掉 
        {
            int j=upper_bound(d+1,d+len+1,a[i])-d;  //找到第一个大于它的d的下标，如果是最长上升子序列，这里变成lower_bound 
            d[j]=a[i]; 
        }
    }
    printf("%d\n",len);    
    return 0;
}
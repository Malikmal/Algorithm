// ANSWERING EXAM ON HACKERRANK BY P. THIAR HASBIYA
//  https://www.hackerrank.com/contests/post-test/challenges/longest-common-subsequence-6/problem





#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a>b)?a:b;
}

int lcs(int n, int m, int arr1[], int arr2[])
{
    int L[n+1][m+1];
    int i, j;
    
    for(i=0; i<=n; i++)
    {
        for(j=0; j<=m; j++)
        {
            if(i == 0 || j == 0)
                L[i][j] = 0;
            else if(arr1[i-1] == arr2[j-1])   
            {
                L[i][j] = L[i-1][j-1] + 1;
            }
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }
    
    int index = L[n][m];
    int lcs[index+1];
    //lcs[index] = '';
    i=n, j=m;
    while(i>0 && j>0)
    {
        if(arr1[i-1] == arr2[j-1])
        {
            lcs[index-1] = arr1[i-1];
            i--; j--; index--;
        }
        else if (L[i-1][j] > L[i][j-1])
            i--;
        else
            j--;
    }
    for(i=0; i<L[n][m];i++)
    {
        printf("%d ", lcs[i]);
    }
    return L[n][m];
}

int main()
{
    int n, m, i;
    scanf("%d %d", &n, &m);
    int arr1[n], arr2[m];
    for(i=0;i<n; i++)
    {
        scanf("%d ",&arr1[i] );
    }
    for(i=0;i<m;i++)
    {
        scanf("%d", &arr2[i]);
    }
    int a = lcs(n, m, arr1, arr2);
    //printf("%d", a);
}

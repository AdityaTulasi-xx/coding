#include <stdio.h>

int main()
{
    int n;
    int k;

    scanf("%d %d", &n, &k);

    long long int inp;
    int count[k];

    for (int i = 0; i < k; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &inp);
        inp %= k;
        count[(int)inp]++;
    }

    // keep finding max of either of the sets
    // and adding them
    int ans = 0;

    // add only one of the numbers whose mod is 0 with k
    if (count[0] > 0)
    {
        ans = 1;
    }

    for (int i = 1; i < ((k + 1) / 2); i++)
    {
        if (count[i] > count[k - i])
        {
            ans += count[i];
        }
        else
        {
            ans += count[k - i];
        }
    }

    if ((k % 2) == 0)
    {
        if (count[k / 2] > 0)
        {
            ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}

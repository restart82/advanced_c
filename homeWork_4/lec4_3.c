#include <stdio.h>
#include <string.h>

#define SIZE 100
#define min(a, b)   (((a) < (b)) ? (a) : (b))

void zFunction2 (char *s, int z[])
{
    int n = strlen(s);
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r)
        {
            z[i] = min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            ++z[i];
        }
        
        if (i + z[i] - 1 > r)
        {
            l = i, r = i + z[i] - 1;
        }
    }
}

int main(int argc, char const *argv[])
{
    char    t[SIZE] = {0},
            p[SIZE] = {0};
    char    s[SIZE + SIZE] = {0};
    int     z[SIZE + SIZE] = {0};

    printf("Input text: ");
    scanf("%s",t);
    printf("Input word: ");
    scanf("%s",p);

    size_t tlen = strlen(t);
    size_t plen = strlen(p);
    sprintf(s, "%s#%s", p, t);
    zFunction2(s, z);
    for (size_t i = 0; i < tlen; i++)
    {
        if (z[i + plen] == plen)
        {
            printf("find word in position%zu\n", i);
        }
    }
    printf("\n");
    return 0;
}

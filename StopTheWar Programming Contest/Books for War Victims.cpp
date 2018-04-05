/*The answer is ceil(n/3)*/

#include <cstdio>

int main()
{
    int n;
    while(scanf("%d", &n) > 0)
    {
        int no_of_books = n/3 + (n%3 != 0);

        printf("%d\n", no_of_books);
    }

    return 0;
}

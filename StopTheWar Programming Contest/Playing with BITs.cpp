/*
 Maintain 60 segment trees. Each segment tree corresponds with one bit position.

T(n, b) Node n of segment tree corresponding to bit b holds the number of numbers in the range of n which have a bit set at position b.

I made a mistake that I had to write 1LL << p, not 1 << p, as that causes overflow.
*/

#include <cstdio>

#define LEFT(n) (2*n)
#define RIGHT(n) (2*n + 1)

const int MAX_BITS = 64, MAX_N = 1e5 + 5;
int no_of_set_bits[3*MAX_N][MAX_BITS];
long long A[MAX_N];

int bit_set(long long n, int position)
{
    return ( ( n & (1LL << position) ) != 0 );
}

void build(int n, int left, int right)
{
    if(left == right)
    {
        for(int bit = 0; bit < MAX_BITS; bit++)
        {
            no_of_set_bits[n][bit] = (bit_set(A[left], bit) ? 1 : 0);
        }

        return;
    }

    int mid = (left + right) >> 1;
    build(LEFT(n), left, mid);
    build(RIGHT(n), mid + 1, right);

    for(int bit = 0; bit < MAX_BITS; bit++)
        no_of_set_bits[n][bit] = no_of_set_bits[LEFT(n)][bit] + no_of_set_bits[RIGHT(n)][bit];
}

void set(int n, int left, int right, int index, int element)
{
    if(right < index || index < left)
        return;

    if(left == right)
    {
        A[index] = element;

        for(int bit = 0; bit < MAX_BITS; bit++)
        {
            no_of_set_bits[n][bit] = (bit_set(A[left], bit) ? 1 : 0);
        }
        return;
    }

    int mid = (left + right) >> 1;
    set(LEFT(n), left, mid, index, element);
    set(RIGHT(n), mid + 1, right, index, element);

    for(int bit = 0; bit < MAX_BITS; bit++)
        no_of_set_bits[n][bit] = no_of_set_bits[LEFT(n)][bit] + no_of_set_bits[RIGHT(n)][bit];
}

int get_bit_count(int n, int left, int right, int query_left, int query_right, int bit)
{
    if(query_right < left || right < query_left)
        return 0;

    if(query_left <= left && right <= query_right)
        return no_of_set_bits[n][bit];

    int mid = (left + right) >> 1;
    int left_answer = get_bit_count(LEFT(n), left, mid, query_left, query_right, bit);
    int right_answer = get_bit_count(RIGHT(n), mid + 1, right, query_left, query_right, bit);

    return (left_answer + right_answer);
}

int main()
{
    int no_of_elements;
    scanf("%d", &no_of_elements);

    for(int i = 1; i <= no_of_elements; i++) scanf("%lld", &A[i]);
    build(1, 1, no_of_elements);

    int no_of_queries;
    scanf("%d", &no_of_queries);

    while(no_of_queries--)
    {
        const int SET = 1, SUM = 2;
        int query_type;
        scanf("%d", &query_type);

        if(query_type == SET)
        {
            int index, element;
            scanf("%d %d", &index, &element);

            set(1, 1, no_of_elements, index, element);
        }
        else if(query_type == SUM)
        {
            int left, right, bit;
            scanf("%d %d %d", &left, &right, &bit);

            int answer = get_bit_count(1, 1, no_of_elements, left, right, bit);

            printf("%d\n", answer);
        }
    }

    return 0;
}

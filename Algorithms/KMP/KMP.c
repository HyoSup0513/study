#include <stdio.h>
#include <string.h>

#define STR_LEN 100

int *calculate_lps(char *_pattern_str)
{
    int pattern_length = strlen(_pattern_str);
    int *_lps = 0; // LPS Array
    int i, j;

    // LPS Array
    _lps = (int *)malloc(sizeof(int) * pattern_length);

    // Initialize LPS Array
    memset(_lps, 0, sizeof(int) * pattern_length);

    j = 0;
    for (i = 1; i < pattern_length; i++)
    {
        while (j > 0 && _pattern_str[i] != _pattern_str[j])
        {
            printf("%d\n", j);
            j = _lps[j - 1];
        }

        if (_pattern_str[i] == _pattern_str[j])
        {
            j++;
            _lps[i] = j;
        }
    }

    return _lps;
}

int main(void)
{
    // Target String
    char target_str[STR_LEN] = "ABABABABBABABABABC";

    // Pattern String
    char pattern_str[STR_LEN] = "ABABABABC";

    int target_len = strlen(target_str);
    int pattern_len = strlen(pattern_str);
    int *lps = 0;

    lps = calculate_lps(pattern_str);

    // Calculated LPS
    printf("i    value\n");
    for (int i = 0; i < pattern_len; i++)
    {
        printf("%d ---> %d\n", i, lps[i]);
    }

    // String matching
    printf("------ Start string matching of %s to %s\n", pattern_str, target_str);

    int j = 0;

    for (int i = 0; i < target_len; i++)
    {

        while (j > 0 && target_str[i] != pattern_str[j])
        {
            j = lps[j - 1];
        }

        if (target_str[i] == pattern_str[j])
        {
            if (j == (pattern_len - 1))
            {
                printf("Found matching at %d\n", (i - pattern_len + 1));
                j = lps[j];
            }
            else
            {
                j++;
            }
        }
    }

    return 0;
}
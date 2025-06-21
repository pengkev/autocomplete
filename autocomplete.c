#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"

int cmp_lex(const void *a, const void *b)
{
    const term *t1 = (const term *)a;
    const term *t2 = (const term *)b;
    return strcmp(t1->term, t2->term);
}

int cmp_weight(const void *a, const void *b)
{
    const term *t1 = (const term *)a;
    const term *t2 = (const term *)b;
    if (t1->weight > t2->weight)
        return -1;
    else if (t1->weight < t2->weight)
        return 1;
    else
        return 0;
}
void read_in_terms(term **terms, int *pnterms, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Cannot open file %s\n", filename);
        exit(1);
    }

    if (fscanf(fp, "%d\n", pnterms) != 1)
    {
        fprintf(stderr, "Error reading number of terms from %s\n", filename);
        fclose(fp);
        exit(1);
    }

    *terms = malloc((*pnterms) * sizeof(term));
    if (!*terms)
    {
        fprintf(stderr, "Memory allocation error\n");
        fclose(fp);
        exit(1);
    }

    char line[200];
    for (int i = 0; i < *pnterms; i++)
    {
        if (fgets(line, sizeof(line), fp))
        {
            char *tab = strchr(line, '\t');
            if (tab)
            {
                *tab = '\0';
                (*terms)[i].weight = atof(line);

                strcpy((*terms)[i].term, tab + 1);

                char *newline = strchr((*terms)[i].term, '\n');
                if (newline)
                    *newline = '\0';
            }
            else
            {
                fprintf(stderr, "Error parsing line %d: no tab found\n", i);
                fclose(fp);
                free(*terms);
                exit(1);
            }
        }
    }
    fclose(fp);

    qsort(*terms, *pnterms, sizeof(term), cmp_lex);
}

int lowest_match(term *terms, int nterms, char *substr)
{
    int left = 0, right = nterms - 1;
    int result = -1;
    int len = strlen(substr);

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = strncmp(terms[mid].term, substr, len);
        if (cmp == 0)
        {
            result = mid;
            right = mid - 1;
        }
        else if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return result;
}

int highest_match(term *terms, int nterms, char *substr)
{
    int left = 0, right = nterms - 1;
    int result = -1;
    int len = strlen(substr);

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = strncmp(terms[mid].term, substr, len);
        if (cmp == 0)
        {
            result = mid;
            left = mid + 1;
        }
        else if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return result;
}

void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr)
{
    int low = lowest_match(terms, nterms, substr);
    int high = highest_match(terms, nterms, substr);

    if (low == -1 || high == -1)
    {
        *answer = NULL;
        *n_answer = 0;
        return;
    }

    int count = high - low + 1;
    *n_answer = count;

    *answer = malloc(count * sizeof(term));
    if (!*answer)
    {
        fprintf(stderr, "Memory allocation error in autocomplete\n");
        exit(1);
    }

    for (int i = 0; i < count; i++)
    {
        (*answer)[i] = terms[low + i];
    }

    qsort(*answer, count, sizeof(term), cmp_weight);
}
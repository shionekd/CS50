#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool cycle_check(int can, int source);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            //printf("%i\n", ranks[rank]);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i <  candidate_count; i++)
    {
        for  (int j = 0; j <  candidate_count; j++)
        {
            if (strcmp(candidates[i], candidates[j])!= 0)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (strcmp(candidates[i], candidates[ranks[k]]) == 0)
                    {
                        preferences[i][j]++;
                        break;
                    }
                    else if (strcmp(candidates[j], candidates[ranks[k]]) == 0)
                    {
                        break;
                    }
                }
            }
        }
    }
    // for (int i = 0; i <  candidate_count; i++)
    // {
    //     for (int j = 0; j <  candidate_count; j++)
    //     {
    //         printf("%i", preferences[i][j]);
    //     }
    //     printf("\n");
    // }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    // printf("pair count: %i\n",  pair_count);
    // for(int i = 0; i < pair_count; i++)
    // {
    //     printf("winner: %i , Loser: %i\n", pairs[i].winner, pairs[i].loser);
    // }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for(int i = 0; i < pair_count; i++)
    {
        int big = 0;
        int bigIndex = 0;
        for (int j = i; j < pair_count; j++)
        {
            int w = pairs[j].winner;
            int l = pairs[j].loser;
            int diff = preferences[w][l] - preferences[l][w];
            if (big < diff)
            {
                big = diff;
                bigIndex = j;
            }
        }
        pair temp = pairs[i];
        pairs[i] = pairs[bigIndex];
        pairs[bigIndex] = temp;
    }
    printf("sorted pair count: %i\n",  pair_count);
    for(int i = 0; i < pair_count; i++)
    {
        printf("winner: %i , Loser: %i\n", pairs[i].winner, pairs[i].loser);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        locked[w][l] = true;
        if (cycle_check(l, l))
        {
            locked[w][l] = false;
        }
    }

    for (int i = 0; i <  candidate_count; i++)
    {
        for (int j = 0; j <  candidate_count; j++)
        {
            printf("%i", locked[i][j]);
        }
        printf("\n");
    }
    return;
}

bool cycle_check(int can, int source)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[can][i])
        {
            if (i == source)
            {
                return true;
            }
            else if(cycle_check(i, source))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    string winner = "";
    for (int i = 0; i <  candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(locked[j][i] == true)
            {
                break;
            }
            else if(j == candidate_count - 1)
            {
                winner = candidates[i];
            }
        }
    }
    printf("%s\n", winner);
    return;
}

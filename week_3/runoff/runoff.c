#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // candidates roop
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            // printf("%i", preferences[voter][rank]);
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // voter loop
    for (int i = 0; i < voter_count; i++)
    {
        // rank loop
        int rank = 0;
        do
        {
            if (candidates[preferences[i][rank]].eliminated == false)
            {
                candidates[preferences[i][rank]].votes++;
                // printf("votes: %i", candidates[preferences[i][rank]].votes);
                // printf(" name: %s", candidates[preferences[i][rank]].name);
                // printf("\n");
                break;
            }
            else
            {
                rank++;
            }
        }
        while (rank < 3);
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int min_votes = voter_count / 2 + 1;
    // printf("min_votes: %i", min_votes);
    // printf("\n");

    for (int i = 0; i < candidate_count; i++)
    {
        // printf("votes: %i", candidates[i].votes);
        if (candidates[i].votes >= min_votes)
        {
            printf("%s", candidates[i].name);
            printf("\n");
            return true;
        }
    }
    // printf("print_winner false\n");
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // printf("find_min check\n");
    int min_num = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            min_num = candidates[i].votes;
            continue;
        }
    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            if (candidates[j].votes < min_num)
            {
                min_num = candidates[j].votes;
            }
        }
    }
    // printf("min_num: %i", min_num);
    // printf("\n");
    return min_num;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // printf("is_tie check\n");
    // printf("\n");

    int tie_counts = 0;
    int tie_num = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min)
        {
            if (tie_num == candidates[i].votes)
            {
                tie_counts++;
            }
            else
            {
                tie_num = candidates[i].votes;
            }
        }

        if (candidates[i].votes == min)
        {
            tie_counts++;
            // printf("tie_counts %i", tie_counts);
            // printf("\n");
            // printf("candidates %i", candidates[i].votes);
            // printf("\n");
            // printf("candidates %s", candidates[i].name);
            // printf("\n");
        }
    }
    if (tie_counts == candidate_count)
    {
        // printf("tie check ok\n");
        return true;
    }
    else
    {
        // printf("tie check false\n");
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
                // printf("eliminated: %i", candidates[i].eliminated);
                // printf(" name: %s", candidates[i].name);
                // printf("\n");
            }
        }
    }
    return;
}

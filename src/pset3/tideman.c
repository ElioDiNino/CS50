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
}
pair;

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
void print_winner(void);
bool cycle(int start, int end);

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
    // Loop through all of the candidates and compare against the string input
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Add a vote to the voter's ranking
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Go through each rank and then add it to the preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    // Go through the entire preferences array with two loops
    for (int i = 0; i < candidate_count; i++)
    {
        for (int n = i + 1; n < candidate_count; n++)
        {
            // Update the pairs array if there is a difference in preference
            if (preferences[i][n] > preferences[n][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = n;
                pair_count += 1;
            }
            else if (preferences[i][n] < preferences[n][i])
            {
                pairs[pair_count].winner = n;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int max_diff = 0;
    int place = 0;

    // Loop through each pair
    for (int i = 0; i < pair_count + 1; i++)
    {
        // Loop through each pair to find the one with the largest vote difference
        for (int n = place; n < pair_count + 1; n++)
        {
            if (preferences[pairs[n].winner][pairs[n].loser] - preferences[pairs[n].loser][pairs[n].winner] > max_diff)
            {
                max_diff = preferences[pairs[n].winner][pairs[n].loser] - preferences[pairs[n].loser][pairs[n].winner];
            }
        }
        // Use the maximum difference found to move matching entries to the 1st position
        if (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner] == max_diff)
        {
            pairs[pair_count + 1] = pairs[place];
            pairs[place] = pairs[i];
            pairs[i] = pairs[pair_count + 1];
            place += 1;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Go through the ranked pairs and check against the cycle function
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool source;

    // Go through each entry and find which candidate has false for all values of argument 2
    for (int i = 0; i < pair_count + 1; i++)
    {
        source = true;
        for (int n = 0; n < pair_count + 1; n++)
        {
            if (locked[n][i])
            {
                source = false;
                break;
            }
        }
        if (source)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}

bool cycle(int start, int end)
{
    // Return true when the arguments are the same
    if (start == end)
    {
        return true;
    }

    // Cycle through the candidates and check recursively
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}
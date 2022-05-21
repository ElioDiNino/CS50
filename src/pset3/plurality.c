#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Loop through all of the candidates and compare against the string input
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Add a vote to the matching candidate
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Define highest votes and winner names array
    int highest = 0;
    int winners_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest)
        {
            highest = candidates[i].votes;
            winners_count = 1;
        }
        else if (candidates[i].votes == highest)
        {
            winners_count += 1;
        }
    }
    // Define the array to hold the winner names
    string names[winners_count];

    // Cycle through the candidates and save all of them that have the highest votes
    for (int n = 0; n < winners_count; n++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == highest)
            {
                names[n] = candidates[i].name;
                candidates[i].votes = 0;
                break;
            }
        }
    }

    // Cycle through the winner(s) and print them out
    for (int n = 0; n < winners_count; n++)
    {
        printf("Winner: %s\n", names[n]);
    }
    return;
}
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

// Main body
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
            bool vote; 
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
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++)
    {
        if (strcmp(name, candidates[candidateIndex].name) == 0)
        {
            preferences[voter][rank] = candidateIndex;
            printf("preferences[Voter%d][Rank%d]: %d\n", voter, rank, preferences[voter][rank]);
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int voterIndex = 0; voterIndex < voter_count; voterIndex++)
    {
        for (int rankIndex = 0; rankIndex < candidate_count; rankIndex++)
        {
            int candidateIndex = preferences[voterIndex][rankIndex];
            if (candidateIndex == -1)
            {
                continue;
            }
            if (candidates[candidateIndex].eliminated)
            {
                preferences[voterIndex][rankIndex] = -1;
            }
            else
            {
                candidates[candidateIndex].votes++;
                preferences[voterIndex][rankIndex] = -1;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++)
    {
        if(candidates[candidateIndex].votes > voter_count / 2)
        {
            printf("%s\n", candidates[candidateIndex].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = MAX_VOTERS;
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++)
    {
        if (candidates[candidateIndex].eliminated == false && candidates[candidateIndex].votes < min)
            min = candidates[candidateIndex].votes;
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++)
    {
        if (candidates[candidateIndex].eliminated == false && candidates[candidateIndex].votes != min)
            return false;
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++)
    {
        if (candidates[candidateIndex].votes == min)
        {
            candidates[candidateIndex].eliminated = true;
        }
    }
}
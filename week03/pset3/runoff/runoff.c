#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
}
candidate;

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


/*
AUXILIAR FUNCTIONS

*/

//print preference table
void print_preferences_table()
{
    for (int i = 0; i < voter_count; i++)
    {
        printf("Voter %i:", i);
        for (int j = 0; j < candidate_count; j++)
        {
            printf(" %i", preferences[i][j]);
        }
        printf("\n");
    }

    printf("Candidate 0: %s\n", candidates[0].name);
    printf("Candidate 1: %s\n", candidates[1].name);
}


// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Check if candidates name exist
    for (int i = 0; i < candidate_count; i++)
    {
        // Record on preferences when exist
        if (!strcmp(candidates[i].name, name))
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int candidate_voted;
    // Check the 1st-non-eliminated choice candidates of voters and add them
    for (int v = 0; v < voter_count; v++)
    {
        // Count only the highest non-eliminated rank
        for (int r = 0; r < candidate_count; r++)
        {
            candidate_voted = preferences[v][r];
            if (!candidates[candidate_voted].eliminated)
            {
                candidates[candidate_voted].votes += 1;
                break;
            }
        }

    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Compute the minimum number of votes required to win
    int min_required = voter_count / 2 + 1;
    //printf("min required: %i\n", min_required);
    // If a candidate fullfill the required minimum return true
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes >= min_required)
        {
            printf("%s\n", candidates[c].name);
            return true;
        }
    }
    // Otherwise return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_votes = voter_count;
    // Find the min number of votes for the non-eliminated candidates
    for (int c = 0; c < candidate_count; c++)
    {
        if ((candidates[c].eliminated == 0) && (candidates[c].votes < min_votes))
        {
            min_votes = candidates[c].votes;
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // How many candidates still active
    int candidates_active = 0;
    int candidates_lower_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            candidates_active += 1;
            if (candidates[i].votes == min)
            {
                candidates_lower_votes += 1;
            }
        }
    }

    // Check if active candidates equals candidates with min number of votes
    if (candidates_active == candidates_lower_votes)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // eliminate candidates with min number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}

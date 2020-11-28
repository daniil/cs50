#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j (adjacency matrix)
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
bool check_cycle(int winner, int loser);
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
            return true;
        }
    }
    // if no candidate found by that name, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // go through ranks - 1 candidates
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // and compare all the pairs for ranks
        for (int j = i + 1; j < candidate_count; j++)
        {
            // select candidate with higher and lower rank
            int higher_candidate = ranks[i];
            int lower_candidate = ranks[j];

            // update preferences
            preferences[higher_candidate][lower_candidate]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // go over each candidate pair
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if one candidate has more votes than another, record the pair, increment a pair counter
            if (preferences[i][j] > preferences[j][i])
            {
                pair curr_pair;

                curr_pair.winner = i;
                curr_pair.loser = j;

                pairs[pair_count] = curr_pair;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // mark first element as sorted
    for (int i = 1; i < pair_count; i++)
    {
        // get number of votes for pair and pair - 1
        int j = i - 1;
        int i_val = preferences[pairs[i].winner][pairs[i].loser];
        int j_val = preferences[pairs[j].winner][pairs[j].loser];
        pair key_pair = pairs[i];

        // if the current pair votes are larger than pair - 1, move it to the right
        while (i_val > j_val && j >= 0)
        {
            pairs[j + 1] = pairs[j];
            --j;
        }
        // insert key pair at the end of sorted items
        pairs[j + 1] = key_pair;
      }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

        // printf("%i : %i (%i) \n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    }
    return;
}

// Test if loser won over a person who beat the winner
bool check_cycle(int winner, int loser)
{
    // check if anyone beat the winner
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner] == true)
        {
            // check if the loser beat that candidate
            if (locked[loser][i] == true)
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
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        bool has_links = false;

        // find a candidate that has no links pointed at
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][winner])
            {
                has_links = true;
            }
        }

        if (!has_links)
        {
            printf("%s\n", candidates[winner]);
            return;
        }
    }
    return;
}


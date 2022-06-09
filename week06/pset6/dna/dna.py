"""
Usage:
$ python dna.py database.csv sequence.txt

Description:
This program identifies to whom a sequence of DNA belongs.
Receives as input a:
- database.csv wich contain the candidates to which belong the sequence.
- sequence.txt contains a long string with the whole sequence to pair with
If match found, print the name of the individual.
Else print "No match".

Examples:
$ python dna.py databases/small.csv sequences/4.txt
Alice

$ python dna.py databases/large.csv sequences/8.txt
Ginny

$ python dna.py databases/small.csv sequences/2.txt
No match
"""

import csv
import sys


def main():

    # command-line usage correctness
    if len(sys.argv) != 3:
        print("Usage: $ python dna.py data.csv sequence.txt")
        return 1

    # Read database file into a variable
    subjects = list()
    sequences_loaded = False
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            # Get the list of STR sequences to search
            if not sequences_loaded:
                subsequences = list(row.keys())
                sequences_loaded = True
            # Create a dictionary for every subject
            d = dict()
            for sequence in subsequences:
                d[sequence] = row[sequence]
            # Append every subject into a list
            subjects.append(d)

    # Read DNA sequence file into a variable
    sf = open(sys.argv[2], 'r')
    sequence = sf.readlines()[0].replace('\n', '')

    # Find longest match of each STR in DNA sequence
    subsequences = subsequences[1:]
    # store every longest match in matches
    matches = list()
    for subsequence in subsequences:
        matches.append(longest_match(sequence, subsequence))

    # Check database for matching profiles
    len_match = len(matches)
    subject_name = "No match"
    # Search for every subject dictionary
    for subject in subjects:
        i = 0
        # check every subsequence and compare it with longest matches
        for subsequence in subsequences:
            # if max matches equals the matches of the subject keep counting
            if (int(subject[subsequence]) == matches[i]):
                i += 1
            # otherwise stop an go to the next subject
            else:
                break
        # if matches found equals every subject match we gound the subject
        if len_match == i:
            subject_name = subject["name"]
            break

    # Print results
    print(subject_name)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()

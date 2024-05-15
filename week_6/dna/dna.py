import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command-line argument.")
        sys.exit(1)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        dna_sequence = file.read()
        # print("dna_sequence: ", dna_sequence)

    # Read database file into a variable
    people = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for dataB in reader:
            people.append(dataB)

    # print("people: ", people)

    # Check database for matching profiles
    key_list = list(people[0].keys())
    # print("key_list: ", key_list)

    longest_dict = {}
    for key in key_list[1:]:
        longest_dict[key] = 0

    for subsequence in key_list[1:len(key_list)]:
        longest_dict[subsequence] = longest_match(dna_sequence, subsequence)
    # print("longest_dict: ", longest_dict)

    for person in people:
        has_broke = False
        for key in longest_dict:
            # print("key:", key, " longest dict: ", longest_dict[key], "person: ", person[key])
            if int(person[key]) != longest_dict[key]:
                has_broke = True
                break
        if has_broke == False:
            print(person["name"])
            return

    print("No match")

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


main()

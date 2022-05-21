import csv
import sys


def main():
    # Check for correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE(.csv) SEQUENCE(.txt)")

    # Read the DNA samples into memory
    sequences = {}
    with open(sys.argv[1]) as peoplefile:
        people = csv.reader(peoplefile)
        for row in people:
            DNASequences = row
            DNASequences.pop(0)
            break
    for item in DNASequences:
        sequences[item] = 1

    # Read the database into memory
    dna = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            dna.append(row)

    # Read the test sequence into memory
    test = ""
    with open(sys.argv[2]) as file:
        test = file.read()

    # Run the DNA repeat test
    repeat(test, sequences)

    # Look for DNA matches
    read_dna(dna, sequences)


def repeat(test, sequences):
    # Go through each DNA sequence to count
    for key in sequences:
        highest = 0
        # Run through the test sequence and look for matches with the pattern variable
        for i in range(len(test) - len(key) + 1):
            count = 0
            # Once a match is found, count the consecutive repetitions
            if key == test[i:i + len(key)]:
                while key == test[i:i + len(key)]:
                    count += 1
                    i += len(key)
                # Check to see if there is a larger consecutive string elsewhere
                if highest == 0 or highest < count:
                    highest = count
        # Add the total to the results
        sequences[key] = highest

    return sequences


def read_dna(dna, results):
    # Go through everyone in the database
    for i in range(len(dna)):
        match = 0
        # Check the totals for each sequence found
        for key in results:
            # Add a match point if the values are the same
            if results[key] == int(dna[i][key]):
                match += 1
            # Exit if not
            else:
                break
        # If all of the values match, return their name
        if match == len(results):
            print(dna[i]['name'])
            return
    # Otherwise print this result
    print("No match")


if __name__ == "__main__":
    main()
def get_words_from_file(file_path):
    with open(file_path, 'r') as file:
        # Read lines, strip any extra whitespace and store them as a set for unique words
        words = set(line.strip() for line in file)
    return words

def print_unshared_words(file1, file2):
    words_file1 = get_words_from_file(file1)
    words_file2 = get_words_from_file(file2)
    
    # Find words that are in file1 but not in file2
    unique_to_file1 = words_file1 - words_file2
    # Find words that are in file2 but not in file1
    unique_to_file2 = words_file2 - words_file1
    
    # Print unshared words
    print("Words unique to", file1, ":")
    for word in unique_to_file1:
        print(word)
    
    print("\nWords unique to", file2, ":")
    for word in unique_to_file2:
        print(word)

# Example usage:
file1 = 'SimpleTree/LastOne.txt'
file2 = 'SimpleTree/newOneH.txt'
print_unshared_words(file1, file2)

# Hi there! these are the solutions to the questions seen in my
# Intro to Coding Interview Workshop. Please keep in mind that
# there might be many more solutions than the ones seen here, if
# you check the main method on this file, you will find some test
# cases with their expected outputs.

# Feel free to implement your own solutions and test them against
# the ones here. Good luck! -Juan.

class Solutions:
    # === Beginner 1: Is Unique ===
    def is_unique(string):
        if len(string) > 128:  # Considering ASCII set
            return False
        
        char_set = [False] * 128
        for char in string:
            val = ord(char)
            if char_set[val]:
                return False
            char_set[val] = True
        return True
        # Runtime Complexity: O(n), where n is the length of the string
        # Space Complexity: O(1), constant space usage

    # === Beginner 2: Check Permutation ===
    def check_permutation(str1, str2):
        if len(str1) != len(str2):
            return False
        
        letters = [0] * 128  # Assuming ASCII
        for char in str1:
            letters[ord(char)] += 1
        
        for char in str2:
            letters[ord(char)] -= 1
            if letters[ord(char)] < 0:
                return False
        
        return True
        # Runtime Complexity: O(n), where n is the length of the strings
        # Space Complexity: O(1), constant space usage

    # === Intermediate 1: Zero Matrix ===
    def zero_matrix(matrix):
        row = [False] * len(matrix)
        column = [False] * len(matrix[0])
        
        for i in range(len(matrix)):
            for j in range(len(matrix[0])):
                if matrix[i][j] == 0:
                    row[i] = True
                    column[j] = True
        
        for i in range(len(matrix)):
            for j in range(len(matrix[0])):
                if row[i] or column[j]:
                    matrix[i][j] = 0
        
        return matrix
        # Runtime Complexity: O(M * N), where M is the number of rows and N is the number of columns
        # Space Complexity: O(M + N), additional space for row and column arrays

    # === Intermediate 2: String Compression ===
    def compress_string(string):
        compressed = []
        count_consecutive = 0
        
        for i in range(len(string)):
            count_consecutive += 1
            if i + 1 >= len(string) or string[i] != string[i + 1]:
                compressed.append(string[i] + str(count_consecutive))
                count_consecutive = 0
        
        compressed_string = ''.join(compressed)
        return compressed_string if len(compressed_string) < len(string) else string
        # Runtime Complexity: O(n), where n is the length of the string
        # Space Complexity: O(n), space for the compressed string

# Test cases
if __name__ == "__main__":
    # Test cases for Beginner 1
    print("==== Beginner 1 Outputs ====")
    print(Solutions.is_unique("abcdef"))  # true
    print(Solutions.is_unique("aabcdef"))  # false

    # Test cases for Beginner 2
    print("==== Beginner 2 Outputs ====")
    print(Solutions.check_permutation("kniaghtro", "troknight"))  # true
    print(Solutions.check_permutation("abcd", "abcc"))  # false

    # Test cases for Intermediate 1
    print("==== Intermediate 1 Outputs ====")
    print("Original Matrix: ")
    matrix = [[1, 2, 3], [4, 0, 6], [7, 8, 9]]
    for row in matrix:
        print(row)
    print("Modified Matrix: ")
    zeroed_matrix = Solutions.zero_matrix(matrix)
    for row in zeroed_matrix:
        print(row)

    # Test cases for Intermediate 2
    print("==== Intermediate 2 Outputs ====")
    print(Solutions.compress_string("aabcccccaaa"))  # a2b1c5a3
    print(Solutions.compress_string("abc"))  # abc

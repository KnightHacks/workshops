// Hi there! these are the solutions to the questions seen in my
// Intro to Coding Interview Workshop. Please keep in mind that
// there might be many more solutions than the ones seen here, if
// you check the main method on this file, you will find some test
// cases with their expected outputs.

// Feel free to implement your own solutions and test them against
// the ones here. Good luck! -Juan.

class Solutions
{
    // === Beginner 1: Is Unique ===
    public static boolean isUnique(String str)
    {
        // Check if the string length exceeds the total number of unique ASCII characters
        if (str.length() > 128) return false; // Considering ASCII set
        
        // Create a boolean array to track occurrences of characters
        boolean[] char_set = new boolean[128];
        for (int i = 0; i < str.length(); i++)
        {
            int val = str.charAt(i);
            // If the character is already seen, return false
            if (char_set[val]) return false;
            char_set[val] = true;
        }
        
        // All characters are unique
        return true;
        // Runtime Complexity: O(n), where n is the length of the string
        // Space Complexity: O(1), constant space usage
    }

    // === Beginner 2: Check Permutation ===
    public static boolean checkPermutation(String str1, String str2)
    {
        // If lengths differ, they cannot be permutations
        if (str1.length() != str2.length()) return false;
        
        // Initialize an array to count character occurrences
        int[] letters = new int[128]; // Assuming ASCII
        for (char c : str1.toCharArray()) 
            letters[c]++;
        
        for (char c : str2.toCharArray())
        {
            letters[c]--;
            // If any count goes negative, str2 has extra characters not in str1
            if (letters[c] < 0) return false;
        }

        // Strings are permutations of each other
        return true;
        // Runtime Complexity: O(n), where n is the length of the strings
        // Space Complexity: O(1), constant space usage
    }

    // === Intermediate 1: Zero Matrix ===
    public static int[][] zeroMatrix(int[][] matrix)
    {
        // Create boolean arrays to track rows and columns to be zeroed
        boolean[] row = new boolean[matrix.length];
        boolean[] column = new boolean[matrix[0].length];
        
        // Identify the rows and columns that need to be zeroed
        for (int i = 0; i < matrix.length; i++)
        {
            for (int j = 0; j < matrix[0].length; j++)
            {
                if (matrix[i][j] == 0)
                {
                    row[i] = true;
                    column[j] = true;
                }
            }
        }
        
        // Zero out identified rows and columns
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                if (row[i] || column[j]) {
                    matrix[i][j] = 0;
                }
            }
        }
        return matrix;
        // Runtime Complexity: O(M * N), where M is the number of rows and N is the number of columns
        // Space Complexity: O(M + N), additional space for row and column arrays
    }

    // === Intermediate 2: String Compression ===
    public static String compressString(String str)
    {
        // Use StringBuilder for efficient string manipulation
        StringBuilder compressed = new StringBuilder();
        int countConsecutive = 0;
        
        // Iterate through the string to count consecutive characters
        for (int i = 0; i < str.length(); i++) {
            countConsecutive++;
            
            // If next character is different or end of string, append count
            if (i + 1 >= str.length() || str.charAt(i) != str.charAt(i + 1)) {
                compressed.append(str.charAt(i));
                compressed.append(countConsecutive);
                countConsecutive = 0;
            }
        }
        // Return the original string if compression doesn't reduce size
        return compressed.length() < str.length() ? compressed.toString() : str;
        // Runtime Complexity: O(n), where n is the length of the string
        // Space Complexity: O(n), space for the compressed string
    }

    public static void main (String[] args)
    {
        // Test cases for Beginner 1
        System.out.println("==== Beginner 1 Outputs ====");
        System.out.println(isUnique("abcdef")); // true
        System.out.println(isUnique("aabcdef")); // false

        // Test cases for Beginner 2
        System.out.println("==== Beginner 2 Outputs ====");
        System.out.println(checkPermutation("kniaghtro", "troknight")); // true
        System.out.println(checkPermutation("abcd", "abcc")); // false

        // Test cases for Intermediate 1
        System.out.println("==== Intermediate 1 Outputs ====");
        System.out.println("Original Matrix: ");
        int[][] matrix = {{1, 2, 3}, {4, 0, 6}, {7, 8, 9}};
        for (int i = 0; i < matrix.length; i++)
        {
            for (int j = 0; j < matrix[0].length; j++) 
            {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println("Modified Matrix: ");
        int[][] zeroedMatrix = zeroMatrix(matrix);
        for (int i = 0; i < zeroedMatrix.length; i++)
        {
            for (int j = 0; j < zeroedMatrix[0].length; j++)
            {
                System.out.print(zeroedMatrix[i][j] + " ");
            }
            System.out.println();
        }

        // Test cases for Intermediate 2
        System.out.println("==== Intermediate 2 Outputs ====");
        System.out.println(compressString("aabcccccaaa")); // a2b1c5a3
        System.out.println(compressString("abc")); // abc
    }
}

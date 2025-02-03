public class CodingPatterns
{
    // Welcome back to the coding section! here you will find
    // all the solutions to the problems seen in the workshop.
    // Make sure to visit the main function to test these or your
    // own solutions. Happy coding! :) - Juan.

    // ===== Two Pointers / Sliding Window =====
    
    // 19. Remove Nth Node from End of List (Two Pointers)
    public ListNode removeNthFromEnd(ListNode head, int n)
    {
        // Create a dummy node to handle edge cases (like removing the first node)
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode first = dummy;
        ListNode second = dummy;

        // Move first pointer n + 1 steps ahead
        for (int i = 0; i <= n; i++)
            first = first.next;
        

        // Move both first and second pointers, keeping the gap of n
        while (first != null)
        {
            first = first.next;
            second = second.next;
        }

        // Remove the nth node from the end
        second.next = second.next.next;

        return dummy.next; // Return the new head
    }

    // 5. Longest Palindromic Substring (Sliding Window)
    public String longestPalindrome(String s)
    {
        // If the string is empty or has only one character, it's a palindrome
        if (s == null || s.length() < 1) return "";

        String longest = "";
        
        for (int i = 0; i < s.length(); i++)
        {
            // Expand around center for odd-length palindromes
            String temp1 = expandAroundCenter(s, i, i);
            if (temp1.length() > longest.length())
                longest = temp1;
            

            // Expand around center for even-length palindromes
            String temp2 = expandAroundCenter(s, i, i + 1);
            if (temp2.length() > longest.length()) 
                longest = temp2;  
        }

        return longest;
    }

    private String expandAroundCenter(String s, int left, int right) {
        // Expand the window as long as it's a valid palindrome
        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }
        return s.substring(left + 1, right); // Return the found palindrome substring
    }

    // ===== BFS and DFS =====
    
    // 100. Same Tree (DFS)
    public boolean isSameTree(TreeNode p, TreeNode q)
    {
        // If both trees are empty, they are the same
        if (p == null && q == null) return true;

        // If one of them is null or values don't match, they are not the same
        if (p == null || q == null || p.val != q.val) return false;

        // Recursively check left and right subtrees
        return isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
    }

    // 101. Symmetrical Tree (DFS)
    public boolean isSymmetric(TreeNode root)
    {
        // If the tree is empty, it's symmetric
        if (root == null) return true;

        // Check if the tree is symmetric by comparing left and right subtrees
        return isMirror(root.left, root.right);
    }

    private boolean isMirror(TreeNode t1, TreeNode t2)
    {
        // If both nodes are null, they are mirrors
        if (t1 == null && t2 == null) return true;

        // If only one of them is null or values don't match, they are not mirrors
        if (t1 == null || t2 == null || t1.val != t2.val) return false;

        // Recursively check if the left of t1 is a mirror of the right of t2, and vice versa
        return isMirror(t1.left, t2.right) && isMirror(t1.right, t2.left);
    }

    // ===== Binary Search =====
    
    // 69. Sqrt(x) (Binary Search)
    public int mySqrt(int x)
    {
        // Edge case for x = 0 or 1
        if (x == 0 || x == 1) return x;

        // Binary search to find the integer part of the square root
        int left = 0, right = x;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long midSquare = (long) mid * mid;

            // If mid squared equals x, we found the square root
            if (midSquare == x) 
                return mid;
            
            // If mid squared is greater than x, adjust the search range
            else if (midSquare > x) 
                right = mid - 1;
            
            // If mid squared is less than x, move the search range up
            else
                left = mid + 1;
        }

        // If no exact match, return the integer part of the square root
        return right;
    }

    public static void main (String [] args)
    {
        // Feel free to test any methods here! You can also
        // add test cases from LeetCode or debugging statements
    }

    // ===== Helper Classes =====

    // ListNode class for Linked List problems
    public class ListNode
    {
        int val;
        ListNode next;
        ListNode(int x) { val = x; }
    }

    // TreeNode class for Tree problems
    public class TreeNode
    {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode(int x) { val = x; }
    }
}

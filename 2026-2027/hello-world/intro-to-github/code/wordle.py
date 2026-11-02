#!/usr/bin/env python3
"""A terminal recreation of Wordle.

The secret word is chosen from a separate file, words.txt
(one 5-letter word per line, in the same folder as this program)
Any five letters are accepted as a guess, whether or not they appear in that list.'
jhkjhk
"""



import os
import random
import sys
from collections import Counter

WORD_LENGTH = 5
MAX_GUESSES = 6
WORD_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "words.txt")

# ANSI colors: green = right spot, yellow = wrong spot, gray = not in word
GREEN = "\033[97;42m"
YELLOW = "\033[30;43m"
GRAY = "\033[97;100m"
RESET = "\033[0m"

CORRECT, PRESENT, ABSENT = "correct", "present", "absent"


def load_words(path=WORD_FILE):
    """Read the word list, keeping only valid 5-letter alphabetic words."""
    try:
        with open(path, encoding="utf-8") as f:
            words = {
                line.strip().lower()
                for line in f
                if len(line.strip()) == WORD_LENGTH and line.strip().isalpha()
            }
    except FileNotFoundError:
        sys.exit(f"Could not find the word list: {path}")
    if not words:
        sys.exit(f"No valid {WORD_LENGTH}-letter words found in {path}")
    return sorted(words)


def score_guess(guess, answer):
    """Return a list of CORRECT/PRESENT/ABSENT for each letter.

    Handles duplicate letters the way real Wordle does: greens are
    claimed first, then yellows are given only while unmatched copies
    of that letter remain in the answer.
    """
    result = [ABSENT] * WORD_LENGTH
    remaining = Counter()

    for i, (g, a) in enumerate(zip(guess, answer)):
        if g == a:
            result[i] = CORRECT
        else:
            remaining[a] += 1

    for i, g in enumerate(guess):
        if result[i] == ABSENT and remaining[g] > 0:
            result[i] = PRESENT
            remaining[g] -= 1

    return result


def color_tile(letter, status):
    color = {CORRECT: GREEN, PRESENT: YELLOW, ABSENT: GRAY}[status]
    return f"{color} {letter.upper()} {RESET}"


def render_row(guess, result):
    return "".join(color_tile(l, s) for l, s in zip(guess, result))


def render_keyboard(letter_status):
    rows = ["qwertyuiop", "asdfghjkl", "zxcvbnm"]
    lines = []
    for indent, row in enumerate(rows):
        tiles = []
        for ch in row:
            status = letter_status.get(ch)
            if status is None:
                tiles.append(f" {ch.upper()} ")
            else:
                tiles.append(color_tile(ch, status))
        lines.append(" " * (indent * 2) + "".join(tiles))
    return "\n".join(lines)


def update_keyboard(letter_status, guess, result):
    """Keep the best known status for each letter (correct > present > absent)."""
    rank = {ABSENT: 0, PRESENT: 1, CORRECT: 2}
    for letter, status in zip(guess, result):
        if letter not in letter_status or rank[status] > rank[letter_status[letter]]:
            letter_status[letter] = status


def play(words):
    answer = random.choice(words)
    history = []
    letter_status = {}

    print("\n=== WORDLE ===")
    print(f"Guess the {WORD_LENGTH}-letter word in {MAX_GUESSES} tries.")
    print("Green = right spot, Yellow = wrong spot, Gray = not in the word.\n")

    while len(history) < MAX_GUESSES:
        guess = input(f"Guess {len(history) + 1}/{MAX_GUESSES}: ").strip().lower()

        if len(guess) != WORD_LENGTH or not guess.isalpha():
            print(f"Please enter a {WORD_LENGTH}-letter word.")
            continue

        result = score_guess(guess, answer)
        history.append((guess, result))
        update_keyboard(letter_status, guess, result)

        print()
        for g, r in history:
            print("  " + render_row(g, r))
        print()
        print(render_keyboard(letter_status))
        print()

        if guess == answer:
            n = len(history)
            print(f"You got it in {n} {'guess' if n == 1 else 'guesses'}!")
            return

    print(f"Out of guesses. The word was {answer.upper()}.")


def main():
    words = load_words()
    while True:
        play(words)
        again = input("\nDo you want to play again? (y/n): ").strip().lower()
        if again not in ("y", "yes"):
            print("Thank you for playing!")
            break


if __name__ == "__main__":
    try:
        main()
    except (KeyboardInterrupt, EOFError):
        print("\nGoodbye!!!")

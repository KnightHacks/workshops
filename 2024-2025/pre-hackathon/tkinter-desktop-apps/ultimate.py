import tkinter as tk
from tkinter import ttk

# Initialize the board and game state
super_board = [["" for _ in range(3)] for _ in range(3)]
mini_boards = [[[["" for _ in range(3)] for _ in range(3)] for _ in range(3)] for _ in range(3)]
x_turn = True
next_board = None  # None means the player can choose any board
over = False


# Function to check for a winner in a single board
def check_winner(board):
    # Check rows, columns, and diagonals
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] != "":
            return board[i][0]
        if board[0][i] == board[1][i] == board[2][i] != "":
            return board[0][i]
    if board[0][0] == board[1][1] == board[2][2] != "":
        return board[0][0]
    if board[0][2] == board[1][1] == board[2][0] != "":
        return board[0][2]
    if all(board[i][j] != "" for i in range(3) for j in range(3)):
        return "Tie"
    return ""


# Function to check for the overall winner
def check_super_winner():
    winner = check_winner(super_board)
    return winner


# Function to handle a move
def make_move(bi, bj, i, j, buttons, turn_label):
    global x_turn, next_board, over

    # Reset the board if the game is over
    if over:
        # Reset the board values
        for bi in range(3):
            for bj in range(3):
                for i in range(3):
                    for j in range(3):
                        button = buttons[bi][bj][i][j]
                        button["state"] = "enabled"
                        button["style"] = "TButton"
                        button["text"] = ""
        x_turn = True
        over = False
        next_board = None
        update_turn_label(turn_label)

    # Check if the move is valid
    if next_board and (next_board != (bi, bj)):
        return

    # Extract the mini_board and check if valid
    mini_board = mini_boards[bi][bj]
    if mini_board[i][j] != "":
        return

    # Update the button and mini_board
    button = buttons[bi][bj][i][j]
    button["text"] = "X" if x_turn else "O"
    button["state"] = "disabled"
    mini_board[i][j] = "X" if x_turn else "O"

    # Handle a board winner
    winner = check_winner(mini_board)
    if winner:
        for row in buttons[bi][bj]:
            for b in row:
                b["state"] = "disabled"
        super_board[bi][bj] = winner
        if winner != "Tie":
            # Display the winner on the captured board and change the style to reflect
            for row in buttons[bi][bj]:
                for b in row:
                    b["text"] = winner
                    b["style"] = "Captured.TButton"

    # Handle the super winner
    super_winner = check_super_winner()
    if super_winner:
        # Reset and enable the board
        for bi in range(3):
            for bj in range(3):
                for i in range(3):
                    for j in range(3):
                        button = buttons[bi][bj][i][j]
                        button["state"] = "enabled"
                        button["style"] = "TButton"

        # Display the winner
        if super_winner != "Tie":
            turn_label["text"] = f"{super_winner} wins the game! Click any button to restart..."
            over = True
            return
        else:
            turn_label["text"] = "It's a tie! Click any button to restart..."
            over = True
            return

    # Update the turn
    next_board = (i, j) if super_board[i][j] == "" else None
    x_turn = not x_turn
    update_turn_label(turn_label)
    highlight_next_board(buttons)


# Function to reset the game
def reset_game(buttons, turn_label):
    global super_board, mini_boards, x_turn, next_board, over
    super_board = [["" for _ in range(3)] for _ in range(3)]
    mini_boards = [[[["" for _ in range(3)] for _ in range(3)] for _ in range(3)] for _ in range(3)]
    x_turn = True
    next_board = None
    over = False
    update_turn_label(turn_label)
    for bi in range(3):
        for bj in range(3):
            for i in range(3):
                for j in range(3):
                    button = buttons[bi][bj][i][j]
                    button["text"] = ""
                    button["state"] = "enabled"
                    button["style"] = "TButton"
    highlight_next_board(buttons)


# Function to update the turn label
def update_turn_label(turn_label):
    if next_board:
        turn_label["text"] = f"{'X' if x_turn else 'O'}'s Turn at {next_board}"
    else:
        turn_label["text"] = f"{'X' if x_turn else 'O'}'s Turn"


# Function to highlight the next board
def highlight_next_board(buttons):
    for bi in range(3):
        for bj in range(3):
            frame = buttons[bi][bj][0][0].master
            if next_board and next_board == (bi, bj):
                frame.configure(style="Active.TFrame")
            else:
                frame.configure(style="TFrame")


# Create the window
window = tk.Tk()
window.title("Knight Hacks Tkinter Workshop - Ultimate Tic Tac Toe")
window.geometry("1000x1000")
window.configure(bg="#f0f0f0")

# Create the title and description label
title_label = ttk.Label(window, text="Knight Hacks Tkinter Workshop - Ultimate Tic Tac Toe", font=("Calibri", 18, "bold"), background="#f0f0f0")
title_label.pack(pady=20, padx=20)
desc_label = ttk.Label(window, text="A 3x3 board of Tic Tac Toe games", font=("Calibri", 14), background="#f0f0f0")
desc_label.pack(pady=10, padx=20)

# Display whose turn it is
turn_label = ttk.Label(window, text="X's Turn", font=("Calibri", 18), background="#f0f0f0")
turn_label.pack(pady=10, padx=20)

# Create the board frame
board_frame = ttk.Frame(window, padding=20)
board_frame.pack(pady=20, padx=20)

# Creates the button style
button_style = ttk.Style()
button_style.configure("TButton", font=("Calibri Bold", 14), padding=5, width=4, height=2)
button_style.configure("Captured.TButton", font=("Calibri Bold", 14), padding=5, width=4, height=2, foreground="red")
button_style.map("TButton", foreground=[("disabled", "black")], background=[("!disabled", "#ccc")])

# Create styles for frames
button_style.configure("TFrame", background="#f0f0f0")
button_style.configure("Active.TFrame", background="#add8e6")

# Create the buttons for the board
buttons = [[[[] for _ in range(3)] for _ in range(3)] for _ in range(3)]
for bi in range(3):
    for bj in range(3):
        mini_frame = ttk.Frame(board_frame, style="TFrame")
        mini_frame.grid(row=bi, column=bj, padx=10, pady=10)
        for i in range(3):
            for j in range(3):
                button = ttk.Button(mini_frame, text="", command=lambda bi=bi, bj=bj, i=i, j=j: make_move(bi, bj, i, j, buttons, turn_label), style="TButton")
                button.grid(row=i, column=j, padx=2, pady=2, ipadx=10, ipady=10, sticky="nsew")
                buttons[bi][bj][i].append(button)

# Initial highlight
highlight_next_board(buttons)

# Run the event loop
window.mainloop()

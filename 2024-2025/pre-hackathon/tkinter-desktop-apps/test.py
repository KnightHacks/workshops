import tkinter as tk
from tkinter import ttk


# ULTIMATE TIC TAC TOE LOGIC
super_board = []
for _ in range(3):
    row = []
    for _ in range(3):
        row.append("")
    super_board.append(row)

mini_boards = []
for _ in range(3):
    board = []
    for _ in range(3):
        mini_board = []
        for _ in range(3):
            row = []
            for _ in range(3):
                row.append("")
            mini_board.append(row)
        board.append(mini_board)
    mini_boards.append(board)

# Variables
x_turn = True
next_board = None
over = False


# Function to check winner
def check_winner(board):
    # Check for each row, column
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] != "":
            return board[i][0]
        if board[0][i] == board[1][i] == board[2][i] != "":
            return board[0][i]

    # Check for diagonal
    if board[0][0] == board[1][1] == board[2][2] != "":
        return board[0][0]
    if board[0][2] == board[1][1] == board[2][0] != "":
        return board[0][2]

    # Ties (CHECKED EVERY TILE)
    if all(board[i][j] != "" for i in range(3) for j in range(3)):
        return "Tie"

    return ""


# Check super winner
def check_super_winner():
    winner = check_winner(super_board)
    return winner


# COMMAND FUNCTION
def make_move(bi, bj, i, j, buttons, turn_label):
    global x_turn, next_board, over
    print(bi, bj, i, j)

    # Check if they are in the right board
    if next_board and (next_board != (bi, bj)):
        return

    # Extract our mini board
    mini_board = mini_boards[bi][bj]
    if mini_board[i][j] != "":
        return

    # Grab the button we're looking at
    button = buttons[bi][bj][i][j]
    print(button)
    button["text"] = "X" if x_turn else "O"
    mini_board[i][j] = "X" if x_turn else "O"
    button["state"] = "disabled"
    next_board = (i, j) if super_board[i][j] == "" else None
    x_turn = not x_turn

    # Set Winner
    print(mini_board)
    winner = check_winner(mini_board)
    print("Winner", winner)
    if winner:
        for row in buttons[bi][bj]:
            for b in row:
                b["state"] = "disabled"
            super_board[bi][bj] = winner
            if winner != "Tie":
                for row in buttons[bi][bj]:
                    for b in row:
                        b["text"] = winner
                        b["style"] = "Captured.TButton"

    # Handle Super Winner
    super_winner = check_super_winner()
    if super_winner:
        for bi in range(3):
            for bj in range(3):
                for i in range(3):
                    for j in range(3):
                        button = buttons[bi][bj][i][j]
                        button["state"] = "enabled"
                        button["style"] = "TButton"
                        button["text"] = ""
                        x_turn = True
                        next_board = False

    highlight_next_board(buttons)
    update_turn_label(turn_label)


def update_turn_label(turn_label):
    if next_board:
        turn_label["text"] = f"{'X' if x_turn else 'O'}'s Turn at {next_board}"
    else:
        turn_label["text"] = f"{'X' if x_turn else 'O'}'s Turn"


def highlight_next_board(buttons):
    for bi in range(3):
        for bj in range(3):
            frame = buttons[bi][bj][0][0].master
            if next_board and next_board == (bi, bj):
                print("ACTIVE FRAME", bi, bj)
                frame.configure(style="Active.TFrame")
            else:
                frame.configure(style="TFrame")


# Create the main window
window = tk.Tk()
window.title("ULTIMATE TIC TAC TOE")
window.geometry("1000x1000")

# Create the title label
title_label = ttk.Label(window, text="Knight Hacks Tkinter Workshop", font=("Calibri", 18, "bold"))
title_label.pack(pady=20, padx=20)
desc_label = ttk.Label(window, text="A 3x3 game of Tic Tac Toe", font=("Calibri", 18))
desc_label.pack()
turn_label = ttk.Label(window, text="X's turn", font=("Calibri", 18))
turn_label.pack(padx=10, pady=10)

# Button Styles
button_style = ttk.Style()
button_style.configure("TButton", font=("Calibri", 14, "bold"))
button_style.configure("Captured.TButton", font=("Calibri", 14, "bold"), padding=5, width=4, height=2, foreground="red")
button_style.map("TButton", foreground=[("disabled", "black")], background=[("!disabled", "#ccc")])

# Create style for frames
frame_style = ttk.Style()
frame_style.configure("TFrame", background="#f0f0f0")
frame_style.configure("Active.TFrame", background="#000000")

# Create frame
board_frame = ttk.Frame(window, padding=20)
board_frame.pack()

# Initialize our buttons
buttons = [[[[] for _ in range(3)] for _ in range(3)] for _ in range(3)]
for bi in range(3):
    for bj in range(3):
        # In the sub board
        mini_frame = ttk.Frame(board_frame, style="TFrame", padding=5)
        mini_frame.grid(row=bi, column=bj, padx=10, pady=10)
        for i in range(3):
            for j in range(3):
                # Create the button
                button = ttk.Button(mini_frame, text="", command=lambda bi=bi, bj=bj, i=i, j=j: make_move(bi, bj, i, j, buttons, turn_label), padding=5)
                button.grid(row=i, column=j)
                buttons[bi][bj][i].append(button)

# Initial
highlight_next_board(buttons)

# Run the main loop
window.mainloop()

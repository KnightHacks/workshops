import tkinter as tk
from tkinter import ttk

# Initialize an empty board and start state
board = [["", "", ""], ["", "", ""], ["", "", ""]]
x_turn = True
over = False


# Function to check for a winner
def check_winner():
    # Check rows
    for row in board:
        if row[0] == row[1] == row[2] != "":
            return row[0]

    # Check columns
    for col in range(3):
        if board[0][col] == board[1][col] == board[2][col] != "":
            return board[0][col]

    # Check diagonals
    if board[0][0] == board[1][1] == board[2][2] != "":
        return board[0][0]
    if board[0][2] == board[1][1] == board[2][0] != "":
        return board[0][2]

    # Check for tie
    if all(board[i][j] != "" for i in range(3) for j in range(3)):
        return "Tie"

    # No winner yet
    return None


# Function to make a move
def make_move(i, j, buttons, turn_label):
    global x_turn
    global over

    # If the game is over, reset the board
    if over:
        for row in buttons:
            for b in row:
                b["text"] = ""
                b["state"] = "enabled"
        for i in range(3):
            for j in range(3):
                board[i][j] = ""
        x_turn = True
        over = False
        turn_label["text"] = "X's Turn"
        return

    # Update the button and board state
    button = buttons[i][j]
    button["text"] = "X" if x_turn else "O"
    button["state"] = "disabled"
    board[i][j] = "X" if x_turn else "O"

    # Handle winners and ties
    winner = check_winner()
    if winner:
        for row in buttons:
            for b in row:
                b["state"] = "enabled"

        if winner == "Tie":
            turn_label["text"] = "It's a tie! Click any button to restart..."
            over = True
            return
        else:
            turn_label["text"] = f"{winner} wins! Click any button to restart..."
            over = True
            return

    # Switch turns
    x_turn = not x_turn
    turn_label["text"] = "X's Turn" if x_turn else "O's Turn"


# Create the window
window = tk.Tk()
window.title("Knight Hacks Demo App - Tic Tac Toe")
window.geometry("800x800")
window.configure(bg="#f0f0f0")  # Set background color

# Create the title and description label
title_label = ttk.Label(window, text="Knight Hacks Demo App", font=("Calibri", 24, "bold"), background="#f0f0f0")
title_label.pack(pady=20, padx=20)
desc_label = ttk.Label(window, text="A sample Tkinter app that plays Tic Tac Toe", font=("Calibri", 14), background="#f0f0f0")
desc_label.pack(pady=10, padx=20)

# Display whose turn it is
turn_label = ttk.Label(window, text="X's Turn", font=("Calibri", 18), background="#f0f0f0")
turn_label.pack(pady=10, padx=20)

# Create the board frame
board_frame = ttk.Frame(window, padding=20)
board_frame.pack(pady=20, padx=20)

# Creates the button style
button_style = ttk.Style()
button_style.configure("TButton", font=("Calibri Bold", 20), padding=10, width=6, height=4)
button_style.map("TButton", foreground=[("disabled", "black")], background=[("!disabled", "#ccc")])

# Create the buttons for the board
buttons = []
for i in range(3):
    row = []
    for j in range(3):
        button = ttk.Button(board_frame, text="", command=lambda i=i, j=j, buttons=buttons: make_move(i, j, buttons, turn_label), style="TButton")
        button.grid(row=i, column=j, padx=5, pady=5)
        row.append(button)
    buttons.append(row)

# Run the event loop
window.mainloop()

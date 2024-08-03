import tkinter as tk
from tkinter import ttk
import time


# Decimal to binary conversion functionality
def convert():
    # Grab the binary number from the entry box
    try:
        binary_input = int(entry_val.get())
    except:
        output_label["text"] = "Invalid Binary Number..."
        output_label["foreground"] = "red"
        return

    # Validate that the input is a binary number
    for digit in str(binary_input):
        if digit not in ["0", "1"]:
            output_label["text"] = "Invalid Binary Number..."
            output_label["foreground"] = "red"
            return

    # Find the decimal value
    decimal_output = 0
    i = 0
    while binary_input != 0:
        remainder = binary_input % 10
        decimal_output += remainder * 2**i
        binary_input = binary_input // 10
        i += 1

    output_label["text"] = f"Output: {decimal_output}"
    output_label["foreground"] = "green"


# Create the main window
timeout = False
window = tk.Tk()
window.title("Knight Hacks Demo App - Binary Conversion")

# Create the title and description label
title_label = ttk.Label(window, text="Knight Hacks Demo App", font=("Calibri", 24))
title_label.pack(pady=20, padx=20)
desc_label = ttk.Label(window, text="A sample Tkinter app that converts a binary number to decimal")
desc_label.pack(padx=20)

# Create the input frame
input_frame = ttk.Frame(window)
entry_val = tk.StringVar()
entry = ttk.Entry(input_frame, textvariable=entry_val)
submit_button = ttk.Button(input_frame, text="Convert", command=convert)
entry.pack(side=tk.LEFT, padx=10)
submit_button.pack(side=tk.RIGHT)
input_frame.pack(pady=20)

# Output label
output_label = ttk.Label(window, text="Output: ", font=("Calibri", 24))
output_label.pack(pady=20)

# Run the main loop
window.mainloop()

import tkinter as tk

# Tkinter superset, where most widgets will come from
from tkinter import ttk

window = tk.Tk()
# Some Optional Values
window.title("Hello World!")
window.geometry("200x100")

# Hello Label
hello_label = ttk.Label(window, text="Hello World!")
hello_label.pack()

# Run the event loop
window.mainloop()

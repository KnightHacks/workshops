## Desktop Apps in Python w/ Tkinter
By the Knight Hacks Workshop Team :)

---

### Installation and Prerequisites
All you need for this workshop is Python 3.10 or newer :)

---

### What is Tkinter?
Tkinter is the standard for GUI (Graphical User Interface) apps in Python. While there are admittedly better solutions, Tkinter is extremely basic, simple, and included in all Python installations.

---
### TK or TTK?
Before getting started, we will be using **tk** and **ttk**. To clarify, **ttk** is a SUPER SET of **tk**, and offers access to modern features the first package lacked. Both are installed with Python

---

### Structure
Tkinter apps are composed of 3 simple categories, each working in unison.
- **WIDGETS:** components used in the app. Good examples are buttons, labels, text input fields, etc.
- **STYLES:** what gives the application life. Similar styling parameters to something like CSS.
- **LAYOUT:** where the widgets are actually placed on screen, using **pack**, **grid**, and **place**

---

### Event Driven Programming
Tkinter helps you create **event driven** software. Contrary to what is initially taught in programming courses, **event driven** courses do not execute from top to bottom as expected. Instead, these programs will run until stopped, and will list for input events every frame.


---

### Hello World (1/5)
To create a Tkinter app, create a python file with the following code. This will create the window and start the event loop.
```py
import tkinter as tk

window = tk.Tk()
# Some Optional Values
window.title("Hello World!")
window.geometry("400x400")

# Run the event loop
window.mainloop()
```

---

### Hello World (2/5)
The most simple widget is the **Label**, which lets us display text. Let's create a label that says "Hello World". We declare widgets before the event loop is called.

---

### Hello World (3/5)
When a widget is created, the first parameter is always the parent element. The parent element will tell the widget where it belongs on screen. In the case of our hello_label, it could be another label, a frame, but for simplicity lets assign it to the window.
```py
hello_label = ttk.Label(window, text="Hello World!")
```

---

### Hello World (4/5)
After creating a widget, we are going to need to pick a layout to use. The simplest is **pack**, which will vertically stack elements in the order they were packed.
```py
hello_label = ttk.Label(window, text="Hello World!")
hello_label.pack()
```
---

### Hello World (5/5)

```py
import tkinter as tk
# Tkinter superset, where most widgets will come from
from tkinter import ttk

window = tk.Tk()
# Some Optional Values
window.title("Hello World!")
window.geometry("400x400")

# Hello Label
hello_label = ttk.Label(window, text="Hello World!")
hello_label.pack()

# Run the event loop
window.mainloop()
```

---

### Hello World!
![[tkinter_hello_world.png]]

---

### Today's Project - TTK Tic Tac Toe
- Documentation: https://docs.python.org/3/library/tkinter.ttk.html
 
---

# But not just any Tic Tac Toe... 

---

# ULTIMATE TIC TAC TOE!!!
![[tkinter_ultimate_tic_tac_toe.png]]

---

# Feedback
![[tkinter feedback.png]]
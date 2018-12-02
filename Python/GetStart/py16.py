import tkinter as tk

window = tk.Tk()
window.title("Neverland_LY")
window.geometry('200x400')

var = tk.StringVar()
l = tk.Label(window, textvariable = var,
             bg = 'green', font = ('Arial',12),
             width = 15, height = 5)

l.pack()     #l.place()

on_hit = False

def hit_me():
    global on_hit
    if on_hit == False:
        var.set('you hit me')
        on_hit = True
    else:
        var.set('')
        on_hit = False

b = tk.Button(window, text = 'hit me', width = 15, height = 3,
              command = hit_me)

b.pack()


window.mainloop()

import customtkinter as ctk
from home_automation.gui import GUI

root = ctk.CTk()
app = GUI(root)
root.protocol("WM_DELETE_WINDOW", lambda: (app.stop_monitoring(), root.destroy()))  # Stop threads on close
root.mainloop()

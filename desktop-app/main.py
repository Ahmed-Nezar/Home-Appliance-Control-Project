
import serial
import serial.tools.list_ports

# Initialize CustomTkinter appearance
ctk.set_appearance_mode("Dark")  # Modes: "Dark", "Light"
ctk.set_default_color_theme("blue")  # Themes: "blue", "green", "dark-blue"

# Detect connected ports

port = "COM3"
ser = serial.Serial(port, 9600, timeout=1)
# Command functions
def turn_lamp_on():
    ser.write(b'o')  # Command for turning lamp on
    messagebox.showinfo("Info", "Lamp turned on")

def turn_lamp_off():
    ser.write(b'f')  # Command for turning lamp off
    messagebox.showinfo("Info", "Lamp turned off")

def get_temperature():
    ser.write(b't')  # Command for getting temperature
    temp = ser.readline().decode().strip()
    if temp:
        messagebox.showinfo("Temperature", f"Current Temperature: {temp}°C")
    else:
        messagebox.showerror("Error", "Failed to read temperature")

def get_door_status():
    ser.write(b'd')  # Command for getting door status
    status = ser.readline().decode().strip()
    if status:
        messagebox.showinfo("Door Status", f"Door is {status}")
    else:
        messagebox.showerror("Error", "Failed to read door status")

# Main GUI
root = ctk.CTk()
root.title("Home Automation")
root.geometry("400x300")

# Add buttons
ctk.CTkButton(root, text="Turn Lamp On", command=turn_lamp_on, width=200).pack(pady=10)
ctk.CTkButton(root, text="Turn Lamp Off", command=turn_lamp_off, width=200).pack(pady=10)
ctk.CTkButton(root, text="Get Temperature", command=get_temperature, width=200).pack(pady=10)
ctk.CTkButton(root, text="Get Door Status", command=get_door_status, width=200).pack(pady=10)

# Run the application
root.mainloop()

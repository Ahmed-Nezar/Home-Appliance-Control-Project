import customtkinter as ctk
import os
from PIL import Image
from tkinter import messagebox
import threading
from datetime import datetime
from home_automation.serial_connection import SerialConnection
from home_automation.utils import Utils
import pygame

class GUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Home Automation")
        self.root.geometry("1200x500")  
        ctk.set_appearance_mode("Dark")
        ctk.set_default_color_theme("blue")

        # Mock initial states
        self.lamp_status = "OFF"  # Lamp state: "ON" or "OFF"
        self.door_history_file = "door_history.txt"  # File to store door history
        self.door_history = self.load_door_history()  # Load door history from file
        self.door_status = "Closed"  # Door state: "Open" or "Closed"
        self.outlet_status = "Closed"  # Outlet state: "Open" or "Closed"
        self.temperature = "" # Initial Tempreature Value
        self.hot_temp = 30 # Hot Temperature Value
        self.serr = SerialConnection.init()

        base_dir = os.path.dirname(os.path.abspath(__file__))
        base_dir = base_dir.split("home-automation")[0]
        images_dir = os.path.join(base_dir, "images")
        self.reda_abd_3al = os.path.join(images_dir, "Alarm_For_Buzzer.mp3")

        self.images = {
            "door_open": ctk.CTkImage(Image.open(os.path.join(images_dir, "open_door.png")), size=(150, 150)),
            "door_closed": ctk.CTkImage(Image.open(os.path.join(images_dir, "closed_door.png")), size=(150, 150)),
            "bulb_on": ctk.CTkImage(Image.open(os.path.join(images_dir, "bulb_on.png")), size=(150, 150)),
            "bulb_off": ctk.CTkImage(Image.open(os.path.join(images_dir, "bulb_off.png")), size=(150, 150)),
            "temperature": ctk.CTkImage(Image.open(os.path.join(images_dir, "temperature.png")), size=(150, 150)),
            "outlet_open": ctk.CTkImage(Image.open(os.path.join(images_dir, "outlet_open.jpeg")), size=(150, 150)),
            "outlet_closed": ctk.CTkImage(Image.open(os.path.join(images_dir, "outlet_close.jpeg")), size=(150, 150)),
        }

        
        self.root.columnconfigure(0, weight=1)
        self.root.columnconfigure(1, weight=1)
        self.root.columnconfigure(2, weight=1)
        self.root.columnconfigure(3, weight=1)  
        self.root.rowconfigure(0, weight=1)  

        self.create_widgets()

        self.running = True
        self.start_monitoring()

    def create_widgets(self):
        # Door Status Section
        self.door_frame = self.create_column_frame("Door Status")
        self.door_frame.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")
        self.door_image_label = ctk.CTkLabel(self.door_frame, image=self.images["door_closed"], text="")
        self.door_image_label.pack(pady=30)
        self.door_label = ctk.CTkLabel(self.door_frame, text="Door Status: Closed", font=("Arial", 14))
        self.door_label.pack(pady=10)
        self.door_history_button = ctk.CTkButton(self.door_frame, text="View Door History", command=self.show_door_history)
        self.door_history_button.pack(pady=10)

        # Lamp Control Section
        self.lamp_frame = self.create_column_frame("Lamp Control")
        self.lamp_frame.grid(row=0, column=1, padx=10, pady=10, sticky="nsew")
        self.lamp_image_label = ctk.CTkLabel(self.lamp_frame, image=self.images["bulb_off"], text="")
        self.lamp_image_label.pack(pady=30)
        self.lamp_status_label = ctk.CTkLabel(self.lamp_frame, text="Lamp Status: OFF", font=("Arial", 14))
        self.lamp_status_label.pack(pady=10)

        self.lamp_on_button = ctk.CTkButton(self.lamp_frame, text="Turn Lamp On", command=self.turn_lamp_on)
        self.lamp_on_button.pack(pady=10)

        self.lamp_off_button = ctk.CTkButton(self.lamp_frame, text="Turn Lamp Off", command=self.turn_lamp_off)
        self.lamp_off_button.pack(pady=10)

        # Temperature Section
        self.temp_frame = self.create_column_frame("Temperature")
        self.temp_frame.grid(row=0, column=2, padx=10, pady=10, sticky="nsew")
        self.temp_image_label = ctk.CTkLabel(self.temp_frame, image=self.images["temperature"], text="")
        self.temp_image_label.pack(pady=30)
        self.temp_label = ctk.CTkLabel(self.temp_frame, text="Temperature: 25°C", font=("Arial", 14))
        self.temp_label.pack(pady=10)

        # Outlet Control Section
        self.outlet_frame = self.create_column_frame("Outlet Control")
        self.outlet_frame.grid(row=0, column=3, padx=10, pady=10, sticky="nsew")
        self.outlet_image_label = ctk.CTkLabel(self.outlet_frame, image=self.images["outlet_closed"], text="")
        self.outlet_image_label.pack(pady=30)
        self.outlet_status_label = ctk.CTkLabel(self.outlet_frame, text="Outlet Status: Closed", font=("Arial", 14))
        self.outlet_status_label.pack(pady=10)

        self.outlet_open_button = ctk.CTkButton(self.outlet_frame, text="Open Outlet", command=self.open_outlet)
        self.outlet_open_button.pack(pady=10)

        self.outlet_close_button = ctk.CTkButton(self.outlet_frame, text="Close Outlet", command=self.close_outlet)
        self.outlet_close_button.pack(pady=10)

    def create_column_frame(self, title):
        """Create a column frame with a shadow and a title."""
        frame = ctk.CTkFrame(self.root, corner_radius=15, fg_color="#2b2b2b")  # Shadow effect
        ctk.CTkLabel(frame, text=title, font=("Arial", 16, "bold")).pack(pady=20)
        return frame

    def load_door_history(self):
        """Load door history from the file."""
        if os.path.exists(self.door_history_file):
            with open(self.door_history_file, "r") as file:
                return file.readlines()
        return []

    def save_door_history_to_file(self):
        """Save door history to the file."""
        with open(self.door_history_file, "w") as file:
            file.writelines(self.door_history)

    def start_monitoring(self):
        threading.Thread(target=self.monitor_door_temperature, daemon=True).start()

    def monitor_door_temperature(self):
        while self.running:

            previous_door_status = self.door_status
            message = SerialConnection.get_message(self.serr)
            message = message.split("#")
            temperature_messages = []                
            door_messages = []
            
            if len(message) == 0:
                continue

            if Utils.check_is_door(message[0]):
                door_messages.append(message[0])
            elif Utils.check_is_temperature(message[0]):
                temperature_messages.append(message[0])
            
            door_message = door_messages[-1]
            if door_message == 'D':
                self.door_status = "Open"
            if door_message == 'C':
                self.door_status = "Closed"
            if self.door_status != previous_door_status:
                self.save_door_history(self.door_status)
    
            self.update_door_status_label()

            temperature_value = temperature_messages[-1].split("_")[1]
            temperature_value = ord(temperature_value) - ord('0')
            self.temperature = temperature_value
            self.update_temperature_label()
            


    def update_temperature_label(self):
        if self.temperature > self.hot_temp:
            self.temp_label.configure(text=f"Temperature: {self.temperature}°C\nWarning: High Temperature Detected\nTake Care Very Hot")
            pygame.mixer.init()
            pygame.mixer.music.load(self.reda_abd_3al)
            pygame.mixer.music.play()

        else:
            self.temp_label.configure(text=f"Temperature: {self.temperature}°C")

    def update_door_status_label(self):
        self.door_label.configure(text=f"Door Status: {self.door_status}")
        if self.door_status == "Open":
            self.door_image_label.configure(image=self.images["door_open"])
        else:
            self.door_image_label.configure(image=self.images["door_closed"])
    def update_outlet_status_label(self):   
        self.outlet_status_label.configure(text=f"Outlet Status: {self.outlet_status}")
        if self.outlet_status == "Open":
            self.outlet_image_label.configure(image=self.images["outlet_open"])
        else:
            self.outlet_image_label.configure(image=self.images["outlet_closed"])

    def save_door_history(self, status):
        """Save the door status change to history."""
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        entry = f"{status} at {timestamp}\n"
        self.door_history.insert(0, entry)  # Most recent at the top
        self.save_door_history_to_file()

    def show_door_history(self):
        """Show the door history in a new window."""
        history_window = ctk.CTkToplevel(self.root)
        history_window.title("Door History")
        history_window.geometry("400x300")

        # Create a scrollable frame
        scrollable_frame = ctk.CTkFrame(history_window)
        scrollable_frame.pack(fill="both", expand=True)

        canvas = ctk.CTkCanvas(scrollable_frame, bg="#2b2b2b", highlightthickness=0)
        canvas.pack(side="left", fill="both", expand=True)

        scrollbar = ctk.CTkScrollbar(scrollable_frame, command=canvas.yview)
        scrollbar.pack(side="right", fill="y")

        canvas.configure(yscrollcommand=scrollbar.set)

        inner_frame = ctk.CTkFrame(canvas)
        canvas.create_window((0, 0), window=inner_frame, anchor="nw")

        for record in self.door_history:
            record_label = ctk.CTkLabel(inner_frame, text=record.strip(), font=("Arial", 12), anchor="w")
            record_label.pack(fill="x", padx=10, pady=2)

        inner_frame.update_idletasks()
        canvas.config(scrollregion=canvas.bbox("all"))

    def turn_lamp_on(self):
        if self.lamp_status == "ON":
            messagebox.showwarning("Warning", "The lamp is already ON.")
        elif self.lamp_status == "OFF":
            self.lamp_status = "ON"
            self.update_lamp_status_label()
            SerialConnection.turn_lamp_on(self.serr)
        else:
            print(self.lamp_status)

    def turn_lamp_off(self):
        if self.lamp_status == "OFF":
            messagebox.showwarning("Warning", "The lamp is already OFF.")
        elif self.lamp_status == "ON":
            self.lamp_status = "OFF"
            self.update_lamp_status_label()
            SerialConnection.turn_lamp_off(self.serr)
        else:
            print(self.lamp_status)

    def update_lamp_status_label(self):
        self.lamp_status_label.configure(text=f"Lamp Status: {self.lamp_status}")
        if self.lamp_status == "ON":
            self.lamp_image_label.configure(image=self.images["bulb_on"])
        else:
            self.lamp_image_label.configure(image=self.images["bulb_off"])

    def open_outlet(self):
        if self.outlet_status == "Open":
            messagebox.showwarning("Warning", "The outlet is already OPEN.")
        elif self.outlet_status == "Closed":
            self.outlet_status = "Open"
            self.outlet_status_label.configure(text=f"Outlet Status: {self.outlet_status}")
            self.outlet_image_label.configure(image=self.images["outlet_open"])
            self.update_outlet_status_label()
            SerialConnection.open_outlet(self.serr)
        else:
            print(self.outlet_status)

    def close_outlet(self):
        if self.outlet_status == "Closed":
            messagebox.showwarning("Warning", "The outlet is already CLOSED.")
        elif self.outlet_status == "Open":
            self.outlet_status = "Closed"
            self.outlet_status_label.configure(text=f"Outlet Status: {self.outlet_status}")
            self.outlet_image_label.configure(image=self.images["outlet_closed"])
            self.update_outlet_status_label()
            SerialConnection.close_outlet(self.serr)
        else:
            print(self.outlet_status)

    def stop_monitoring(self):
        self.running = False
        self.save_door_history_to_file()


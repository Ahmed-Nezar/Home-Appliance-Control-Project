import serial
import serial.tools.list_ports

class SerialConnection:
    
    @staticmethod
    def find_tiva_port():
        ports = serial.tools.list_ports.comports()
        return ports[0].device    

    @staticmethod
    def init():
        port = SerialConnection.find_tiva_port()
        if port:
            ser = serial.Serial(port, 9600, timeout=1)
        else:
            raise Exception("Tiva board not found")
        return ser
    
    @staticmethod
    def turn_lamp_on(ser):
        ser.write(b'o')
    
    @staticmethod
    def turn_lamp_off(ser):
        ser.write(b'f')
    
    @staticmethod
    def get_temperature(ser):
        ser.write(b't')
        return ser.readline().decode().strip()
    
    @staticmethod
    def get_door_status(ser):
        ser.write(b'd')
        return ser.readline().decode().strip()
    
    @staticmethod
    def get_lamp_status(ser):
        ser.write(b's')  # 's' is a command to get the lamp's status
        status = ser.readline().decode().strip()
        return "ON" if status == "1" else "OFF"
    
    @staticmethod
    def close_outlet(ser):
        ser.write(b'c')

    @staticmethod
    def open_outlet(ser):
        ser.write(b'a')
    
    
        
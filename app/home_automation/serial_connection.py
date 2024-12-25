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
            ser = serial.Serial(
                port, 
                9600, 
                timeout=1,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                bytesize=serial.EIGHTBITS
            )
        else:
            raise Exception("Tiva board not found")
        return ser
    
    @staticmethod
    def turn_lamp_on(ser):
        ser.write(b'O')
    
    @staticmethod
    def turn_lamp_off(ser):
        ser.write(b'F')
    
    @staticmethod 
    def get_message(ser):
        message = ser.readline().decode().strip() # T -> Temperature, O -> Lamp On, F -> Lamp Off, D -> Door Open, C -> Door Close
        return message
    
    @staticmethod
    def close_outlet(ser):
        ser.write(b'c')

    @staticmethod
    def open_outlet(ser):
        ser.write(b'a')
    
    
        
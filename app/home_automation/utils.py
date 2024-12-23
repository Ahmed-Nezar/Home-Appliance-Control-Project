class Utils:
    
    @staticmethod
    def check_is_door(message):
        is_door = True if message == 'D' or message == 'C' else False
        return is_door
    
    @staticmethod
    def check_is_temperature(message):
        is_temperature = True if len(message) > 1 else False
        return is_temperature
    
    
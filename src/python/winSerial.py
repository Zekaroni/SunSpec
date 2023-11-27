import serial

def monitor_serial(port, baud_rate):
    ser = serial.Serial(port, baud_rate)
    while True:
        line = ser.readline().decode('utf-8').strip()
        print(line)

if __name__ == "__main__":
    serial_port = 'COM14'
    baud_rate = 9600
    monitor_serial(serial_port, baud_rate)
s
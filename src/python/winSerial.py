import serial

def monitor_serial(port, baud_rate):
    ser = serial.Serial(port, baud_rate)
    try:
        while True:
            line = ser.readline().decode('utf-8').strip()
            print(f'Received: {line}')
    except KeyboardInterrupt:
        print("Monitoring stopped by the user.")
    finally:
        ser.close()

if __name__ == "__main__":
    serial_port = 'COM14'
    baud_rate = 9600
    monitor_serial(serial_port, baud_rate)

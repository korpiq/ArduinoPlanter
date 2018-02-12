import serial

# ser = serial.Serial('/dev/tty.usbmodem621', 9600)
baud = 115200
open_ports = {}

def open_serial(port_name):
    try:
        return serial.Serial(port_name, baud, timeout=1)
    except serial.SerialException:
        print ('Port not available: ' + port_name)

def read_from_serial(port_name):
    if port_name not in open_ports or not open_ports[port_name]:
        open_ports[port_name] = open_serial(port_name)
    port = open_ports[port_name]
    try:
        port.write(b's\r\n');
        return port.readline()
    except serial.SerialException:
        print ('Port not responding: ' + port_name)
        port.close()
        open_ports.pop(port_name)

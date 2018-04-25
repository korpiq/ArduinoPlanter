import serial

open_ports = {}

def open_serial(settings):
    port_name = settings['port']
    port_speed = settings['speed']

    try:
        return serial.Serial(port_name, port_speed, timeout=1)
    except serial.SerialException:
        print ('Port not available: ' + port_name)

def read_from_serial(settings):
    port_name = settings['port']

    if port_name not in open_ports or not open_ports[port_name]:
        open_ports[port_name] = open_serial(settings)
    port = open_ports[port_name]

    try:
        port.write(b's\r\n');
        return port.readline()
    except serial.SerialException:
        print ('Port not responding: ' + port_name)
        port.close()
        open_ports.pop(port_name)

import serial
import sys


open_ports = {}


def open_serial(settings):
    port_name = settings['port']
    port_speed = settings['speed']

    try:
        return serial.Serial(port_name, port_speed, timeout=1)
    except serial.SerialException:
        print ('Port not available: ' + port_name)


def get_open_port(settings):
    port_name = settings['port']

    if port_name not in open_ports or not open_ports[port_name]:
        open_ports[port_name] = open_serial(settings)

    return open_ports[port_name]


def do_with_port(description, settings, handler):
    port = get_open_port(settings)

    try:
        return handler(port)
    except serial.SerialException as se:
        print('Failed to %s port "%s": %s' % (description, port_name, str(se)))
        port.close()
        open_ports.pop(port_name)


def write_to_serial(settings, message):
    return do_with_port('write to', settings, lambda port: port.write(b'%s\r\n' % message))


def read_lines_from_serial(settings):
    return do_with_port('read from', settings, lambda port: port.readlines())

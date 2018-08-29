import os
import sys
import time
import json
import glob
import atexit
import threading
from IothubClient import IothubClient
from SerialCommunicator import read_lines_from_serial, write_to_serial


configuration = {
    'plantation_id': 'PLANTATION_ID_NOT_SET',
    'planters': {},  # 'name': { 'port': 'eg. COM3 or /dev/tty.usbmodem621', 'speed': 9600 }
    'delay': 10,
    'iothub_connection_string': 'IOTHUB_CONNECTION_STRING_NOT_SET'
}


console_input = None


def create_log_exit():
    filename = __file__
    def log_exit():
        sys.stderr.write(filename + " exit.\n")

    return log_exit


atexit.register(create_log_exit())


def flatten(collection, prefix='', separator='_'):
    result = {}
    keys = isinstance(collection, dict) and collection.keys() or range(0, len(collection))

    for key in keys:
        value = collection[key]
        if isinstance(value, dict) or isinstance(value, list):
            result.update(flatten(value, prefix + str(key) + separator, separator))
        else:
            result[prefix + str(key)] = value

    return result


def handle_planter_message(name, planter_message):
    planter_data = json.loads(planter_message.decode('utf8'))
    flat_data = flatten(planter_data)

    result = {
        'plantation_id': configuration['plantation_id'],
        'planter_id': name,
        'data': flat_data
    }

    return json.dumps(result)


def handle_planter(iothub_client, name, settings):
    planter_messages = read_lines_from_serial(settings)

    for planter_message in planter_messages:
        iothub_client.send(handle_planter_message(name, planter_message))

console_reader_thread = None
def start_console_reader():
    """
    Starts reading input lines one by one from console into global console_input without blocking.
    Set console_input to None after use to read more.
    Set console_input to False to finish reading.
    """

    def console_reader():
        global console_input
        console_input = None

        while console_input is not False:
            sys.stderr.write("reading\n")
            if console_input is None:
                console_input = sys.stdin.readline()
            else:
                time.sleep(1)

    console_reader_thread = threading.Thread(target=console_reader)


def iothub_client_telemetry_run():
    iothub_client = IothubClient(configuration['iothub_connection_string'])
    iothub_client.send(json.dumps({
        'plantation_id': configuration['plantation_id'],
        'plantation':'started'
    }))

    try:
        global console_input
        console_input = None
        start_console_reader()
        while True:
            if console_input is not None:
                print("Console input: " + console_input)
                console_input = None

            try:
                for name, settings in configuration['planters'].items():
                    handle_planter(iothub_client, name, settings)
            except Exception as e:
                sys.stderr.write('\n')

            sys.stderr.flush()
            sys.stdout.flush()

            time.sleep(configuration['delay'])

    except KeyboardInterrupt:
        sys.stderr.write(__file__ + " stopped by user.\n")
    except Exception as e:
        sys.stderr.write('%s failed: %s\n' % (__file__, str(e)))


def configure(filenames):
    try:
        for filename in filenames:
            sys.stdout.write("Reading configuration file '%s': " % filename)

            with open(filename, 'r', encoding='utf8') as file_handle:
                settings = json.load(file_handle)

                if 'planter' in filename:
                    name = os.path.splitext(os.path.basename(filename))[0]
                    configuration['planters'][name] = settings
                    print("Planter '%s'" % name)
                else:
                    configuration.update(settings)
                    print("Configuration.")
            sys.stdout.flush()

    except Exception as e:
        sys.stderr.write('Failed to read configuration file "%s" %s: "%s"\n' % (filename, e.__class__.__name__, str(e)))

        # dump configuration read so far to help debug
        json.dump(configuration, sys.stdout)
        print('\n')

        raise

if __name__ == '__main__':
    configuration_filenames = ['plant*.conf']
    if len(sys.argv) > 1:
        configuration_filenames = sys.argv[1:]

    expanded_conf_filenames = []
    for globname in configuration_filenames:
        expanded_conf_filenames = expanded_conf_filenames + glob.glob(globname)

    configure(expanded_conf_filenames)

    print ( "RpiPlantation %s collecting and sending data from planters to IOT hub" % configuration['plantation_id'] )

    iothub_client_telemetry_run()

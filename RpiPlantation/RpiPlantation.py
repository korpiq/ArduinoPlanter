import os
import sys
import time
import json
import glob
import atexit
from IothubClient import IothubClient
from SerialCommunicator import read_from_serial


configuration = {
    'plantation_id': 'PLANTATION_ID_NOT_SET',
    'planters': {},  # 'name': { 'port': 'eg. COM3 or /dev/tty.usbmodem621', 'speed': 9600 }
    'delay': 10,
    'iothub_connection_string': 'IOTHUB_CONNECTION_STRING_NOT_SET'
}


MSG_TXT = '{ "plantation_id": "%s", "planter_id": "%s", "data": %s }'


def log_exit():
    sys.stderr.write(__file__ +  " exit.\n")


atexit.register(log_exit)


def handle_planter(iothub_client, name, settings):
    planter_message = read_from_serial(settings)

    if planter_message:
        iothub_client.send(MSG_TXT % (configuration['plantation_id'], name, planter_message.decode('utf8')))


def iothub_client_telemetry_run():
    iothub_client = IothubClient(configuration['iothub_connection_string'])

    try:
        while True:
            try:
                for name, settings in configuration['planters'].items():
                    handle_planter(iothub_client, name, settings)
            except Exception as e:
                sys.stderr.write('\n')

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

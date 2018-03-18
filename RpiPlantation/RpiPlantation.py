import time
from IothubClient import IothubClient
from SerialCommunicator import read_from_serial

MSG_TXT = "{\"plantation_id\": \"pythontestdevice\",\"planter_id\":\"%s\",\"data\": %s}"
PORT_NAME='COM15'
DELAY = 10

def iothub_client_telemetry_run():
    iothub_client = IothubClient()

    try:
        while True:
            planter_message = read_from_serial(PORT_NAME)

            if planter_message:
                iothub_client.send(MSG_TXT % (PORT_NAME, planter_message.decode('utf8')))

            time.sleep(DELAY)

    except KeyboardInterrupt:
        print ( "RpiPlantation stopped" )

if __name__ == '__main__':
    print ( "RpiPlantation collecting and sending data from planters to IOT hub" )

    iothub_client_telemetry_run()

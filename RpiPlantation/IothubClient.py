import sys
import iothub_client
from iothub_client import IoTHubClient, IoTHubClientError, IoTHubTransportProvider, IoTHubClientResult
from iothub_client import IoTHubMessage, IoTHubMessageDispositionResult, IoTHubError, DeviceMethodReturnValue
from local_config import CONNECTION_STRING


class IothubClient(object):
    """maintains connection for communication with Azure IotHub"""

    # connection will be initialized when None and reset to None on errors.
    client = None
    messages_sent = 0
    messages_confirmed = 0

    protocol = IoTHubTransportProvider.MQTT
    message_timeout = 10000

    def __init__(self, iothub_connection_string):
        self.iothub_connection_string = iothub_connection_string

    def iothub_client_init(self):
        # prepare iothub client
        client = IoTHubClient(self.iothub_connection_string, protocol)
        # set the time until a message times out
        client.set_option("messageTimeout", message_timeout)
        client.set_option("logtrace", 0)
        client.set_option("product_info", "rpi-plantation")
        messages_sent = 0
        messages_confirmed = 0
        return client

    def get_client(self):
        if client is None:
            client = self.iothub_client_init()
        return client

    def send_confirmation_callback(self, message, result, user_context):
        if result == IoTHubClientResult.OK:
            messages_confirmed += 1
        else:
             sys.stderr.writeln( "IoTHub send \"%s\" failed: \"%s\"" % (message.message_id, result) )
             client = None

    def send(self, message):
        try:
            iothub_message = IoTHubMessage(message)
            messages_sent += 1
            iothub_message.message_id = "message_%d" % messages_sent
            self.get_client().send_event_async(iothub_message, send_confirmation_callback, messages_sent)
        except IoTHubError as iothub_error:
             sys.stderr.writeln( "IoTHub error: \"%s\"" % iothub_error )
             client = None

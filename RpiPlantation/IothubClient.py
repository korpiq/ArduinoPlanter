import sys
import iothub_client
from iothub_client import IoTHubClient, IoTHubClientError, IoTHubTransportProvider, IoTHubClientResult
from iothub_client import IoTHubMessage, IoTHubMessageDispositionResult, IoTHubError, DeviceMethodReturnValue


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
        client = IoTHubClient(self.iothub_connection_string, self.protocol)
        # set the time until a message times out
        client.set_option("messageTimeout", self.message_timeout)
        client.set_option("logtrace", 0)
        client.set_option("product_info", "rpi-plantation")
        return client

    def get_client(self):
        if self.client is None:
            self.client = self.iothub_client_init()
            self.messages_sent = 0
            self.messages_confirmed = 0
        return self.client

    def send_confirmation_callback(self, message, result, user_context):
        if result == IoTHubClientResult.OK:
            self.messages_confirmed += 1
        else:
             sys.stderr.write( "IoTHub send \"%s\" failed: \"%s\"\n" % (message.message_id, result) )
             self.client = None

    def send(self, message):
        try:
            iothub_message = IoTHubMessage(message)
            self.messages_sent += 1
            iothub_message.message_id = "message_%d" % self.messages_sent
            self.get_client().send_event_async(iothub_message, self.send_confirmation_callback, self.messages_sent)
        except IoTHubError as iothub_error:
             sys.stderr.write( "IoTHub error: \"%s\"\n" % iothub_error )
             self.client = None

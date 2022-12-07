# Import the necessary modules
import network
import usocket as socket
import utime
import bh1750
import ml8511

# Set the credentials for connecting to ThingSpeak
# Replace with your own channel ID, API key, and WiFi credentials
channel_id = 0000000
api_key = "YOUR_API_KEY"
wifi_ssid = "YOUR_WIFI_SSID"
wifi_password = "YOUR_WIFI_PASSWORD"

# Create instances of the sensors
light_sensor = bh1750.BH1750()
uv_sensor = ml8511.ML8511()

# Function to connect to WiFi
def connect_wifi():
    # Create a new WiFi interface
    wifi = network.WLAN(network.STA_IF)
    # Connect to WiFi
    wifi.active(True)
    wifi.connect(wifi_ssid, wifi_password)
    # Wait until connection is established
    while not wifi.isconnected():
        utime.sleep(1)

# Function to send data to ThingSpeak
def send_data(data):
    # Set the URL for sending data to ThingSpeak
    url = "http://api.thingspeak.com/update?api_key={}&field1={}&field2={}".format(api_key, data[0], data[1])
    # Connect to ThingSpeak
    _, _, host, path = url.split("/", 3)
    addr = socket.getaddrinfo(host, 80)[0][-1]
    s = socket.socket()
    s.connect(addr)
    # Send the data
    s.send(bytes("GET /{} HTTP/1.0\r\nHost: {}\r\n\r\n".format(path, host), "utf8"))
    # Close the connection
    s.close()

# Connect to WiFi
connect_wifi()

# Continuously read and send data from the sensors
while True:
    # Read data from the sensors
    light_level = light_sensor.read()
    uv_intensity = uv_sensor.read()
    # Send the data to ThingSpeak
    send_data((light_level, uv_intensity))
    # Wait 1 minute before sending the next data
    utime.sleep(60)

# Import the necessary libraries
import machine
import time
import micropython
import network
import esp32

# Connect to WiFi network
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect("my_wifi_network", "my_wifi_password")

# Import ThingSpeak library
import thingspeak

# Set ThingSpeak channel credentials
channel_id = 123456
write_key = "ABCDEFGHIJKLMNOP"

# Set sensor pin
sensor_pin = machine.Pin(32, machine.Pin.IN, machine.Pin.PULL_UP)

# Create a function to read the UV index from the sensor
def read_uv_index():
    # Code to read UV index from ML8511 sensor goes here
    return uv_index

# Create a function to write the UV index to ThingSpeak
def write_to_thingspeak(uv_index):
    # Write the UV index to ThingSpeak
    thingspeak.write([uv_index], channel_id=channel_id, write_key=write_key)

# Create an infinite loop to read and write UV index to ThingSpeak every minute
while True:
    # Read the UV index from the sensor
    uv_index = read_uv_index()

    # Write the UV index to ThingSpeak
    write_to_thingspeak(uv_index)

    # Sleep for one minute
    time.sleep(60)

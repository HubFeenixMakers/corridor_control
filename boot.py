from time import sleep
import machine
import network
import usocket as socket

import esp
esp.osdebug(True)

global server_socket

wlan_ap = network.WLAN(network.AP_IF)
wlan_ap.config(dhcp_hostname="esp_root") # open
wlan_ap.active(True)
wlan_ap.config(essid="ESP32" , password="password" ) # open


station = network.WLAN(network.STA_IF)
station.active(True)
print(station.scan())
station.config(dhcp_hostname='esp_root')
station.connect('TP-Link_Extender', '') 
name = station.config('dhcp_hostname')
print("DNS " + name)

addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('', 80))
server_socket.listen(5)


print(wlan_ap.ifconfig())
print('Listening on:', addr)


while True:

  try:
    conn, addr = server_socket.accept()
    conn.settimeout(3.0)
    print('Got a connection from %s' % str(addr))
    request = conn.recv(1024)
    conn.settimeout(None)
    request = str(request)
    print('Content = %s' % request)
    response = "Ho"
    conn.send('HTTP/1.1 200 OK\n')
    conn.send('Content-Type: text/html\n')
    conn.send('Connection: close\n\n')
    conn.sendall(response)
    conn.close()
  except OSError as e:
    conn.close()
    print('Connection closed')

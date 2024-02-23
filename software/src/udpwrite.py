import socket
import time


UDP_IP = "Vintage-LED-Clock"
UDP_PORT = 2233

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP

iBrHHigh = 100
iBrHLow = 100
iBrMHigh = 100
iBrMLow = 100

iHHigh = 1
iHLow = 2
iMHigh = 3
iMLow = 4

for iVal in range(0,9999):
    iHHigh = int(iVal / 1000) % 10
    iHLow = int(iVal / 100) % 10
    iMHigh = int(iVal / 10) % 10
    iMLow = int(iVal % 10)

    # iBrHHigh = int(iVal % 10) * 10
    # iBrHLow = int(iVal % 10) * 10
    # iBrMHigh = int(iVal % 10) * 10
    # iBrMLow = int(iVal % 10) * 10

    sock.sendto(bytes([iBrHHigh,iBrHLow,iBrMHigh,iBrMLow,iHHigh,iHLow,iMHigh,iMLow]), (UDP_IP, UDP_PORT))
    #print("Update")
    time.sleep(0.1)
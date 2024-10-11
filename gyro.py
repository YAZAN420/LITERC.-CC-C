from cvzone.SerialModule import SerialObject
import requests
import json
from time import sleep
esp8266_ip = "http://192.168.139.181"  
url = f"{esp8266_ip}/array" 
urlMode = f"{esp8266_ip}/mode" 
mode=1
aurdino = SerialObject("COM23")
data = [0,0]
toMakeGyroZeroInfo = [0,0]

def gyro_zero():
    global toMakeGyroZeroInfo
    toMakeGyroZeroInfo = aurdino.getData()
def getXY():
    if(len(data) < 2 ): return [0,0]
    elif (data[0] == '' or data[1]==''): return [0,0]
    return [(int(data[0])-int(toMakeGyroZeroInfo[0]))//10,(int(data[1])-int(toMakeGyroZeroInfo[1]))//10]

sleep(2)
json_mode = json.dumps([mode])
response = requests.post(urlMode, json_mode , headers={"Content-Type": "application/json"})
gyro_zero()
while True:
    data = aurdino.getData()
    gyroData = getXY()
    if len(gyroData)==2:
        print(gyroData[0],gyroData[1])
    json_data = json.dumps(gyroData)
    try:
        response = requests.post(url, data=json_data, headers={"Content-Type": "application/json"})
    except Exception as e:
        print(f"Error: {e}")
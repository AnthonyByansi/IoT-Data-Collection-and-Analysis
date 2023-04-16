# IoT Data Collection and Analysis

This project is an Internet of Things (IoT) application that connects devices and sensors to the internet, collects data, and performs actions based on the data. The application uses MQTT as the communication protocol, Mosquitto as the message broker, and Node-RED as the dashboard. It also utilizes AWS IoT for cloud-based management of devices and data analysis.

## Getting Started
To get started with this project, you will need the following:

* A Raspberry Pi or any other computer that is always connected to the internet
* A temperature sensor (e.g. DS18B20) and a smart light bulb
* NodeMCU ESP8266 microcontroller
* AWS account
* MQTT broker (e.g. Mosquitto)

## Prerequisites
Before running the application, you will need to install the following software:

* Node-RED
* MQTT client (e.g. MQTT.fx)

## Installing
1. Clone the repository to your Raspberry Pi or computer: 
```bash
git clone https://github.com/AnthonyByansi/IoT-Data-Collection-and-Analysis.git

```
2. Install the required Node-RED packages:
```bash
cd IoT-Data-Collection-and-Analysis
npm install

```

3. Start Node-RED:
```bash 
node-red
```
4. Open a web browser and go to `http://localhost:1880` to access the Node-RED dashboard.

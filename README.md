# beebit-mqttc-sdk
The **Beebit** project provides a set of modules for developers who attempt to secure data communication.

Message Queue Telemetry Transport (MQTT) is a light-weight data exchange protocol [1]. The publisher/subscriber (Pub/Sub) pattern of MQTT is suitable for most Internet of Thing (IoT) applications. Currently, MQTT is widely accepted by many IoT platform provider, such as Google IoT Core, Microsoft IoT Hub, Amazon IoT, etc. MQTT provides Transport Layer Security (TLS). However, end-to-end security is demanded to exchange privacy data in security-sensitive IoT applications. Unfortunately, it can be a obstacle to directly add end-to-end security in application layer for IoT application developers.

The **beebit-mqttc-sdk** module implements an extensible and transparent end-to-end security to MQTT according to our work - **MQTT Thing-to-Thing (MQTT-TTS)**[2]. There are three features of MQTT-TTS

1. Provide end-to-end security
2. Ease to extend security mechanisms
3. Transparent to application developers  

The implementation is based on open source project - [Eclipse Paho](https://www.eclipse.org/paho/)[3]. Paho is the most popular projecr which provides MQTT and MQTT-SN client and supports a variety of langiages. The **beebit-mqttc-sdk** is based on C language.

## Install
~~~bash
cd paho.mqtt.c
make clean
make uninstall
make install
~~~

## Evaluation
Run subscriber on one terminal 
~~~bash
./build/output/samples/paho_cs_sub au/csie --host iot.eclipse.org
~~~

Run publisher on the other terminal
~~~bash
./build/output/samples/paho_cs_pub au/csie --host iot.eclipse.org
hello world
~~~

## Reference
1. http://mqtt.org/
2. MQTT-TTS (paper submitted)
3. https://www.eclipse.org/paho/

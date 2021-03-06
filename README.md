# beebit-mqttc-sdk
The **Beebit** project provides a set of modules for developers who attempt to secure data communication in Internet of Thing (IoT) environment.

Message Queue Telemetry Transport (MQTT) is a light-weight data exchange protocol [1]. The publisher/subscriber (Pub/Sub) pattern of MQTT is suitable for most IoT applications. Currently, MQTT is widely accepted by many IoT platform providers, such as Google IoT Core, Microsoft IoT Hub, Amazon IoT, etc. MQTT has built-in Transport Layer Security (TLS) which provides end-to-broker encryption. However, end-to-end security is demanded to exchange privacy data for security-sensitive IoT applications. Unfortunately, it can be a obstacle to directly add end-to-end security in application layer for IoT application developers.

The **beebit-mqttc-sdk** module implements an extensible and transparent end-to-end security to MQTT according to our research work - **MQTT Thing-to-Thing Security (MQTT-TTS)**[2]. There are three features of MQTT-TTS

1. Provide end-to-end security
2. Ease to extend security mechanisms
3. Transparent to application developers

The implementation is based on open source project - [Eclipse Paho](https://www.eclipse.org/paho/)[3]. Paho is the most popular project which provides MQTT and MQTT-SN client and supports a variety of languages. The **beebit-mqttc-sdk** is based on C language.

## Installation
In order to applying Ciphertext-Policy Attribute-Based Encryption (CP-ABE) in MQTT-TTS, you **MUST** install the [**beebit-cpabe-sdk**](https://github.com/beebit-sec/beebit-cpabe-sdk) module (native C). 

~~~bash
cd paho.mqtt.c
make clean
make uninstall
make
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

## How to add a new security mechanism in MQTT-TTS
Assume we want to add a dummy security mechanism, called RV_LOWER, in which encoder does nothing and decoder juse lower case of data.
### Step 1. Revise beebit_extend.h
1. Redefine constant NOM
2. Include your header file (eg. `#include "beebit_lower.h"`)

### Step 2. Revise beebit_extend.c
Add one entry in function pointer array, `baseinit_sec_map[]`. (eg. `init_lower`)

### Step 3. Prepare your source and header files
1. `beebit_lower.h`
2. `beebit_lower.c`

### Step 4. Add beebit options in applications
1. `paho_cs_pub.c`
2. `paho_cs_sub.c`

### Step 5. Rebuild project
~~~base
make clean
make uninstall
make
make install
~~~

## Reference
1. http://mqtt.org/
2. Wei-Tsung Su, Wei-Cheng Chen, and Chao-Chun Chen, "An Extensible and Transparent Thing-to-Thing Security Enhancement for MQTT Protocol in IoT Environment,", Global IoT Summit 2019, Jun. 17-21, 2019, Aarhus, Denmark.
3. https://www.eclipse.org/paho/

### Smarthome ![actions](https://github.com/lafin/smarthome/workflows/actions/badge.svg)
___

### Nodered
![](assets/flow.png)

### Settings nodered's flow
[here](example/flow1.json)

### Sketch (temperature+humidity+relay)
[here](example/example1.ino)

### Result
<img src="assets/screen.png" height="400">

### x86_64 (armhf, arm64)
```bash
$ mkdir -p homebridge nodered && \
  curl -O https://raw.githubusercontent.com/lafin/smarthome/master/docker-compose.yml && \
  curl -o homebridge/config.json https://raw.githubusercontent.com/lafin/smarthome/master/homebridge/config/config.json
$ docker-compose pull
$ docker-compose up -d
```

### Zigbee
https://www.zigbee2mqtt.io/getting_started/what_do_i_need.html
```bash
$ cat zigbee/configuration.yaml
homeassistant: false
permit_join: true
mqtt:
  base_topic: zigbee2mqtt
  server: 'mqtt://localhost'
serial:
  port: /dev/ttyUSB0
advanced:
  log_level: debug
devices:
  '0x842e14fffe68246d':
    friendly_name: socket1
  '0x00158d0004a0165d':
    friendly_name: 'sensor1'
  '0x00158d00048533d7':
    friendly_name: 'sensor2'
  '0x00158d000632be03':
    friendly_name: 'sensor3'
```

### Existed issues
- doesn't work on a Docker for MacOS [#issues/68](https://github.com/docker/for-mac/issues/68)
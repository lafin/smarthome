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
$ docker run -it -d -v $(pwd)/zigbee:/app/data --device=/dev/ttyUSB0 -e TZ=Europe/Tallinn --privileged=true --restart=always --network host koenkk/zigbee2mqtt
```

### Existed issues
- doesn't work on a Docker for MacOS [#issues/68](https://github.com/docker/for-mac/issues/68)
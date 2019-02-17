### Smarthome [![Build Status](https://travis-ci.org/lafin/smarthome.svg?branch=master)](https://travis-ci.org/lafin/smarthome)
___

### Nodered
![](assets/flow.png)

### Settings nodered's flow
[here](example/flow1.json)

### Sketch (temperature+humidity+relay)
[here](example/example1.ino)

### Result
<img src="assets/screen.png" height="400">

### x86_64
```bash
$ mkdir -p homebridge nodered && \
  curl -O https://raw.githubusercontent.com/lafin/smarthome/master/docker-compose.yml && \
  curl -O https://raw.githubusercontent.com/lafin/smarthome/master/docker-compose.x86_64.yml && \
  curl -O https://raw.githubusercontent.com/lafin/smarthome/master/docker-compose.deploy.yml && \
  curl -o homebridge/config.json https://raw.githubusercontent.com/lafin/smarthome/master/homebridge/config/config.json
$ docker-compose -f docker-compose.x86_64.yml pull
$ docker-compose -f docker-compose.yml -f docker-compose.x86_64.yml -f docker-compose.deploy.yml up -d
```

### armhf
```bash
$ mkdir -p homebridge nodered && \
  curl -O https://raw.githubusercontent.com/lafin/smarthome/master/docker-compose.yml && \
  curl -O https://raw.githubusercontent.com/lafin/smarthome/master/docker-compose.armhf.yml && \
  curl -O https://raw.githubusercontent.com/lafin/smarthome/master/docker-compose.deploy.yml && \
  curl -o homebridge/config.json https://raw.githubusercontent.com/lafin/smarthome/master/homebridge/config/config.json
$ docker-compose -f docker-compose.armhf.yml pull
$ docker-compose -f docker-compose.yml -f docker-compose.armhf.yml -f docker-compose.deploy.yml up -d
```

### How to add grafana and influxdb? [look here](https://github.com/lafin/grafana-influxdb)
<img src="assets/grafana.png" height="300">

### Existed issues
- doesn't work on a Docker for MacOS [#issues/68](https://github.com/docker/for-mac/issues/68)
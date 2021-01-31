FROM alpine

RUN apk add --no-cache --virtual .build-deps make gcc g++ python3 \
    && apk add --no-cache nodejs npm openssl avahi-compat-libdns_sd avahi-dev dbus
RUN npm i -g --unsafe-perm homebridge homebridge-mqtt \
    && apk del .build-deps
RUN apk add --no-cache dumb-init

ENV NODE_ENV production
USER root
WORKDIR /root
RUN mkdir -p ./.homebridge/config
COPY ./config/config.json ./.homebridge/
COPY entrypoint.sh .

VOLUME ./.homebridge

EXPOSE 5353 51826
ENTRYPOINT ["/root/entrypoint.sh"]
CMD ["dumb-init", "homebridge", "-U", "/root/.homebridge"]

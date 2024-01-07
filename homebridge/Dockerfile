FROM alpine:3.18

RUN apk add --no-cache --virtual .build-deps make gcc g++ python3 \
    && apk add --no-cache nodejs npm openssl avahi-compat-libdns_sd avahi-dev dbus
RUN npm i -g homebridge homebridge-mqtt homebridge-config-ui-x \
    && apk del .build-deps
RUN apk add --no-cache dumb-init tzdata

ENV NODE_ENV production
USER root
WORKDIR /root
RUN mkdir -p ./.homebridge/config
COPY ./config/config.json ./.homebridge/
COPY entrypoint.sh .

VOLUME ./.homebridge

EXPOSE 5353 8581 51826
ENTRYPOINT ["/root/entrypoint.sh"]
CMD ["dumb-init", "hb-service", "run", "--allow-root", "-U", "/root/.homebridge"]

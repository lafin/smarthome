FROM alpine:3.7

ENV NPM_CONFIG_LOGLEVEL info
RUN apk add --no-cache --virtual .build-deps make gcc g++ python \
    && apk add --no-cache nodejs openssl avahi-compat-libdns_sd avahi-dev dbus \
    && mkdir -p ~/.homebridge/config
RUN npm i --unsafe-perm -g homebridge homebridge-mqtt \
    && apk del .build-deps

COPY config ~/.homebridge/config
VOLUME ~/.homebridge

EXPOSE 5353 51826
COPY entrypoint.sh .
ENTRYPOINT ["entrypoint.sh"]
CMD homebridge

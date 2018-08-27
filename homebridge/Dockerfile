FROM alpine:3.8

ENV NPM_CONFIG_LOGLEVEL info
RUN apk add --no-cache --virtual .build-deps make gcc g++ python \
    && apk add --no-cache nodejs npm openssl avahi-compat-libdns_sd avahi-dev dbus \
    && mkdir -p /root/.homebridge/config
RUN npm i --unsafe-perm -g homebridge homebridge-mqtt \
    && apk del .build-deps

COPY config/config.json /root/.homebridge/
VOLUME /root/.homebridge

EXPOSE 5353 51826
COPY entrypoint.sh .
ENTRYPOINT ["./entrypoint.sh"]
CMD ["homebridge"]

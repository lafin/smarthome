FROM alpine:3.4

ENV NPM_CONFIG_LOGLEVEL info
RUN addgroup -g 1000 node \
    && adduser -u 1000 -G node -s /bin/sh -D node

RUN apk add --no-cache --virtual .build-deps make gcc g++ python \
    && apk add --no-cache nodejs openssl avahi-compat-libdns_sd avahi-dev dbus \
    && mkdir -p /root/.homebridge/config

RUN npm i --unsafe-perm -g homebridge homebridge-mqtt \
    && apk del .build-deps

USER root
COPY config/config.json /root/.homebridge/config
VOLUME /root/.homebridge

EXPOSE 5353 51826
ADD entrypoint.sh /root/
ENTRYPOINT ["/root/entrypoint.sh"]
CMD /usr/bin/homebridge

FROM alpine:3.13

RUN apk add --no-cache --virtual .build-deps make gcc g++ python3 \
    && apk add --no-cache nodejs npm openssl avahi-compat-libdns_sd avahi-dev dbus
RUN npm i -g --unsafe-perm homebridge homebridge-mqtt \
    && apk del .build-deps
RUN apk add --no-cache dumb-init

RUN addgroup -g 1000 node \
    && adduser -u 1000 -G node -s /bin/sh -D node

ENV NODE_ENV production
USER node
WORKDIR /home/node
RUN mkdir -p ./.homebridge/config
COPY --chown=node:node ./config/config.json ./.homebridge/
VOLUME ./.homebridge

EXPOSE 5353 51826
COPY --chown=node:node entrypoint.sh .
ENTRYPOINT ["/home/node/entrypoint.sh"]
CMD ["dumb-init", "homebridge", "-U", "/home/node/.homebridge"]

FROM alpine:3.13

RUN apk add --no-cache --virtual .build-deps make gcc g++ python2 \
    && apk add --no-cache nodejs npm openssl
RUN npm i -g --unsafe-perm node-red node-red-contrib-mqtt-broker \
    && apk del .build-deps
RUN apk add --no-cache dumb-init

RUN addgroup -g 1000 node \
    && adduser -u 1000 -G node -s /bin/sh -D node

ENV NODE_ENV production
USER node
WORKDIR /home/node
VOLUME ./.node-red
COPY --chown=node:node entrypoint.sh .

EXPOSE 1880
ENTRYPOINT ["/home/node/entrypoint.sh"]
CMD ["dumb-init", "node-red", "-v", "/home/node/.node-red/flows.json"]

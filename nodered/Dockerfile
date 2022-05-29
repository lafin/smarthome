FROM alpine

RUN apk add --no-cache --virtual .build-deps make gcc g++ python3 krb5-dev zeromq-dev \
    && apk add --no-cache nodejs npm openssl
RUN npm i -g node-red node-red-contrib-mqtt-broker \
    && apk del .build-deps
RUN apk add --no-cache dumb-init tzdata

RUN addgroup -g 1000 node \
    && adduser -u 1000 -G node -s /bin/sh -D node

ENV NODE_ENV production
USER node
WORKDIR /home/node
COPY --chown=node:node entrypoint.sh .

VOLUME ./.node-red

EXPOSE 1880
ENTRYPOINT ["/home/node/entrypoint.sh"]
CMD ["dumb-init", "node-red", "-v", "/home/node/.node-red/flows.json"]

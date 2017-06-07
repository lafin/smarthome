FROM alpine:3.4

ENV NPM_CONFIG_LOGLEVEL info
RUN addgroup -g 1000 node \
    && adduser -u 1000 -G node -s /bin/sh -D node

RUN apk add --no-cache --virtual .build-deps make gcc g++ python \
    && apk add --no-cache nodejs openssl

RUN npm i --unsafe-perm -g node-red node-red-contrib-mqtt-broker \
    && apk del .build-deps

USER root
VOLUME /root/.node-red

EXPOSE 1880
ADD entrypoint.sh /root/
ENTRYPOINT ["/root/entrypoint.sh"]
CMD /usr/bin/node-red -v /root/.node-red/flows.json

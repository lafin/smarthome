FROM alpine:3.12

ENV NPM_CONFIG_LOGLEVEL info
RUN apk add --no-cache --virtual .build-deps make gcc g++ python3 \
    && apk add --no-cache nodejs npm openssl

RUN npm i --unsafe-perm -g node-red node-red-contrib-mqtt-broker \
    && apk del .build-deps

VOLUME /root/.node-red

EXPOSE 1880
COPY entrypoint.sh .
ENTRYPOINT ["./entrypoint.sh"]
CMD ["/usr/bin/node-red", "-v", "/root/.node-red/flows.json"]

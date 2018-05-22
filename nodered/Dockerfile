FROM alpine:3.7

ENV NPM_CONFIG_LOGLEVEL info
RUN apk add --no-cache --virtual .build-deps make gcc g++ python \
    && apk add --no-cache nodejs openssl

RUN npm i --unsafe-perm -g node-red node-red-contrib-mqtt-broker \
    && apk del .build-deps

VOLUME ~/.node-red

EXPOSE 1880
ADD entrypoint.sh .
ENTRYPOINT ["entrypoint.sh"]
CMD /usr/bin/node-red -v ~/.node-red/flows.json

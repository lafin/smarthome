FROM alpine:3.7

RUN apk add --no-cache mosquitto mosquitto-clients \
    && mkdir -p /mqtt/config /mqtt/data /mqtt/log

COPY config /mqtt/config
VOLUME ["/mqtt/config", "/mqtt/data", "/mqtt/log"]

EXPOSE 1883 9001
COPY entrypoint.sh .
ENTRYPOINT ["entrypoint.sh"]
CMD /usr/sbin/mosquitto -c /mqtt/config/mosquitto.conf

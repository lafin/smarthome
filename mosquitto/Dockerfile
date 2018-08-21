FROM alpine:3.8

RUN apk add --no-cache mosquitto mosquitto-clients \
    && mkdir -p /mqtt/config /mqtt/data /mqtt/log

COPY config /mqtt/config

EXPOSE 1883 9001
COPY entrypoint.sh .
ENTRYPOINT ["./entrypoint.sh"]
CMD ["/usr/sbin/mosquitto", "-c", "/mqtt/config/mosquitto.conf"]

FROM alpine:3.4

RUN adduser -D mosquitto
RUN apk add --no-cache mosquitto mosquitto-clients \
    && mkdir -p /mqtt/config /mqtt/data /mqtt/log

COPY config /mqtt/config
RUN chown -R mosquitto:mosquitto /mqtt
VOLUME ["/mqtt/config", "/mqtt/data", "/mqtt/log"]

EXPOSE 1883 9001
ADD entrypoint.sh /usr/bin/
ENTRYPOINT ["entrypoint.sh"]
CMD /usr/sbin/mosquitto -c /mqtt/config/mosquitto.conf

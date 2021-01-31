FROM --platform=$BUILDPLATFORM alpine

RUN apk add --no-cache mosquitto mosquitto-clients

RUN addgroup -g 1000 mqtt \
    && adduser -u 1000 -G mqtt -s /bin/sh -D mqtt

USER mqtt
WORKDIR /home/mqtt
RUN mkdir -p ./.mosquitto/config ./.mosquitto/data ./.mosquitto/log
COPY --chown=mqtt:mqtt config ./.mosquitto/config
COPY --chown=mqtt:mqtt entrypoint.sh .

EXPOSE 1883 9001
ENTRYPOINT ["/home/mqtt/entrypoint.sh"]
CMD ["mosquitto", "-c", "/home/mqtt/.mosquitto/config/mosquitto.conf"]

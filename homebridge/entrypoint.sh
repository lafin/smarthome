#!/bin/sh

rm -rf /var/run/dbus.pid
rm -rf /var/run/avahi-daemon//pid

sed -i "s/rlimit-nproc=3/#rlimit-nproc=3/" /etc/avahi/avahi-daemon.conf

dbus-daemon --system
avahi-daemon -D

sleep 5

exec "$@"

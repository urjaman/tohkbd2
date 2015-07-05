#!/bin/bash
systemctl stop harbour-tohkbd2.service
systemctl disable harbour-tohkbd2.service
udevadm control --reload
DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/100000/dbus/user_bus_socket" dbus-send --type=method_call --dest=org.freedesktop.DBus / org.freedesktop.DBus.ReloadConfig
systemctl start harbour-tohkbd2.service

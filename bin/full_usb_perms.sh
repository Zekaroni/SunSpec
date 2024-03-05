#!/bin/bash

RULE_CONTENT='SUBSYSTEM=="usb", MODE="0666"'
echo "$RULE_CONTENT" | sudo tee /etc/udev/rules.d/99-usb-permissions.rules >/dev/null
sudo udevadm control --reload-rules
sudo udevadm trigger
echo "USB device permissions set to 0666 for all devices."

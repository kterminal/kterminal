#!/bin/bash

./build.sh
sudo cp build/kterminal /usr/bin
sudo desktop-file-install kterminal.desktop
sudo update-desktop-database

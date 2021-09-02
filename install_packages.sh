#!/bin/sh

sudo apt-get update -y
sudo apt-get upgrade -y

sudo apt-get install -y qt5-default
sudo apt-get install -y build-essential
sudo apt-get install -y messa-common-dev
sudo apt-get install -y libglu1-mesa-dev
sudo apt-get install -y qml-module-qtquick-controls
sudo apt-get install -y qml-module-qt-quick-dialogs
sudo apt-get install -y qtdeclarative5-dev

sudo apt-get update -y
sudo apt-get upgrade -y

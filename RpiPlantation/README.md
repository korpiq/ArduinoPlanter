RpiPlantation
=============

RpiPlantation passes messages from ArduinoPlanters to IotHub.
Details of connections are given in configuration files.

## Setup

Install python3 and required libraries:

    brew install python3
    pip3 -r requirements.txt

IotHub client library is only available on Windows and Linux.

Copy and fill in appropriate configuration files from associated templates.

## Run

    python3 RpiPlantatation.py [configuration-filenames]

If no configuration files are specified, files matching `plant*.conf` in current directory will be used.


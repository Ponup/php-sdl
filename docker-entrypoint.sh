#!/usr/bin/env bash

Xvfb :99 -screen 0 800x600x24 -ac &

chmod +x ./run-tests.php

export DISPLAY=:99
./run-tests.php -q --show-diff

killall -9 Xvfb

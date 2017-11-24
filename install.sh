#!/bin/bash
apt-get install default-libmysqlclient-dev
apt-get install libldns-dev
g++ core.cpp core.h dns.cpp dns.h global.h main.cpp mysql_controller.cpp mysql_controller.h some_error.h -O3 -lmysqlclient -lldns -o scanDnsToDB

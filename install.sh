#!/bin/bash
apt-get install default-libmysqlclient-dev -y
apt-get install libldns-dev -y
g++ HeaderFile/controller_class.h HeaderFile/dns_class.h HeaderFile/global.h HeaderFile/mysql_class.h SourceFile/controller_class.cpp SourceFile/dns_class.cpp SourceFile/mysql_class.cpp main.cpp -O3 -lldns -lmysqlclient -o scanDnsToDB

#include <iostream>
#include "HeaderFile/global.h"
#include "HeaderFile/controller_class.h"
#include "HeaderFile/mysql_class.h"
#include "HeaderFile/dns_class.h"
int main(int argc,char * argv[]) {
//    controller * Controller = new controller;
//    Controller->debug = true;
//    Controller->start(argc,argv);
//    Controller->loadConfig();
//    Controller->readDict();
//    Controller->ConnectMysql();
    dns_class dns;
    dns.debug = false;
    dns.start(argc,argv);
    dns.loadConfig();
    dns.readDict();
    dns.ConnectMysql();
    dns.Enum();
    //delete Controller;std::cout << "Hello, World!" << std::endl;
    return 0;
}
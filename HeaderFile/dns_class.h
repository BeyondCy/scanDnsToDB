//
// Created by payloads on 11/27/17.
//

#ifndef NEWSCANDNSTODB_DNS_CLASS_H
#define NEWSCANDNSTODB_DNS_CLASS_H

#include <ldns/ldns.h>
#include <iostream>
#include <vector>
#include "controller_class.h"
#include "mysql_class.h"
#include <arpa/inet.h>
#include "mysql_class.h"
class dns_class: public controller{
public:
    bool Enum();
    dns_class();
private:
    ldns_resolver   *res;
    ldns_rdf        *name;
    ldns_rdf        *nameserver;
    ldns_rdf        *rr_rdf;
    ldns_pkt        *p;
    ldns_rr_list    *info;
    ldns_rr         *rr;
    ldns_status     s;
};
#endif //NEWSCANDNSTODB_DNS_CLASS_H

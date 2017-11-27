#include "global.h"
#include "core.h"
#include "mysql_controller.h"
#include "dns.h"
#include <getopt.h>
#include <sstream>
#include <sys/time.h>
#define VERSION 0.11
#define CREATE_TIME 20171123
void help(char * argv[]){
    std::cout << "例子：" << argv[0] << " -dpayloads.online -t5 -rsubnames.txt" << std::endl;
    std::cout << "-d[你要枚举的域名]" << std::endl;
    std::cout << "-s[制定DNS服务器地址](默认是202.101.172.35)" << std::endl;
    std::cout << "-c[配置文件路径](默认是当前目录中的my.ini)" << std::endl;
    std::cout << "-r[字典路径](默认在my.ini中)" << std::endl;
    std::cout << "-u 开启调试模式(无需参数)" << std::endl;
    std::cout << "-t[线程数]" << std::endl;
    std::cout << "-v 输出版本信息" << std::endl;
    std::cout << "-h 输出帮助信息" << std::endl;
    std::cout << "创建日期:\t" << CREATE_TIME << std::endl;
}
int main(int argc,char * argv[]) {
    // v version
    // d domain
    // t thread numbers
    // o output
    // r dic dir
    // SomeError ERROR;
    struct Options Opt;
    struct globalSet GLOBAL;
    struct timeval times;
    std::stringstream timeStr;
    timeStr << times.tv_sec;
    gettimeofday(&times,NULL);
    std::string opt("v::d:t::o::r:h::s:u::"); int option;
    GLOBAL.debug=false;
    Opt.config_file = "./my.ini";
    Opt.DnsServer = "202.101.172.35";
    Opt.threadNum = 5;
    Opt.output = "./"+timeStr.str();
    Opt.start = times.tv_sec;
    Core CoreEngine(&Opt,&GLOBAL);
    while((option=getopt(argc,argv,opt.c_str())) != -1){
        switch (option){
            case 'v':
                std::cout << argv[0] << "  [Version " << VERSION  << "] by payloads "<< std::endl;
                std::cout <<"Email  : " << "\tpayloads@aliyun.com "<< std::endl;
                std::cout <<"Author : " << "\t倾旋 "<< std::endl;
                exit(0);
            case 'd':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
                Opt.domain = optarg;
                break;
            case 'u':
                GLOBAL.debug = true;
                break;
            case 't':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
            //std::cout << optarg << " | "<< Opt.threadNum << std::endl;
                Opt.threadNum = atoi(optarg);
                break;
            case 'o':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
                Opt.output = optarg;
                break;
            case 's':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
                Opt.DnsServer = optarg;
                break;
            case 'r':
                if(optarg==NULL){
                    CoreEngine.Error=NOT_GIVE_DOMAIN_DICT;
                    std::cout << CoreEngine.error_handle() << std::endl;
                    exit(EXIT_FAILURE);
                }
                Opt.dict_path = optarg;
                break;
            case 'h':
                help(argv);
                exit(EXIT_SUCCESS);
            case 'c':
                if(optarg==NULL){
                    help(argv);
                    exit(EXIT_FAILURE);
                }
                Opt.config_file = optarg;
                break;
            default:
                help(argv);
                exit(EXIT_SUCCESS);
        }
    }
    if(optind < 3){
        help(argv);
        exit(EXIT_FAILURE);
    }
    MySQL_Controller  controller;
    controller.debug = GLOBAL.debug;
    CoreEngine.loadMysqlConfig();
    if(!controller.connect(GLOBAL.mysql_host,GLOBAL.mysql_user,GLOBAL.mysql_pass,GLOBAL.mysql_database,atoi(GLOBAL.mysql_port.c_str()))){
        CoreEngine.Error=MYSQL_CANT_CONNECT;
        CoreEngine.error_handle();
    }
    CoreEngine.readDict();
    DNS run(&controller);
    run.Enum(&Opt,&GLOBAL,CoreEngine.dicLists);
    return 0;
}

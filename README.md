# scanDnsToDB

## 简介

该工具用于通过字典枚举DNS，它是基于C/C++语言开发的，我们可以灵活的指定DNS服务器，效率非常高效！尽情享受

## 安装在KaliLinux上

将`install.sh` 以root权限执行即可安装满足此工具需要的扩展库

注意事项：你的Kali Linux必须确保已经更新了源，并且开启了MySQL服务(已经自带了)，以及安装了gcc/g++

启动MySQL:`service mysql start`

## 参数介绍
```
例子：./scanDnsToDB -dpayloads.online -t5 -rsubnames.txt
-d[你要枚举的域名]
-s[制定DNS服务器地址](默认是202.101.172.35)
-c[配置文件路径](默认是当前目录中的my.ini)
-r[字典路径](默认在my.ini中)
-u 开启调试模式(无需参数)
-t[线程数]
-v 输出版本信息
-h 输出帮助信息
创建日期:	20171123
```
以上帮助都可以通过`-h`参数获得到

## 关于配置文件

首先要创建一个(MySQL)数据库以及数据表：

```
DROP TABLE IF EXISTS `domain`;
CREATE TABLE `domain` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `md51` char(32) NOT NULL,
  `domain` varchar(255) NOT NULL,
  `ip` varchar(255) NOT NULL,
  `md52` char(32) NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE KEY `md51` (`md51`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8;
```

`my.ini`是配置文件

```
mysql_host=127.0.0.1 #这是数据库的地址，如果是本地，建议写 localhost
mysql_user=root      #数据库用户名
mysql_pass=root      #数据库密码
mysql_database=test  #数据库名称
mysql_table=domain   #数据库表名称
mysql_port=3306      #数据库端口，Linux下可以填写为 0
dict=dict            #字典路径 例如： /root/dict/sub.txt
```

## 关于此项目

该项目暂未支持多线程，版本是0.1


在运行时，它将首先解析你的参数，然后加载配置文件，去连接数据库

数据库中的 `md51` 是 域名+ip 的MD5值，不允许重复，为了防止多次写入相同的数据，所以增加了唯一键。

`md52`是用于存储域名的MD5值，保证你的唯一性

## 它的优势

你可以在Linux下自定义计划任务，对一个域名进行周期性的爆破，然后比较它们的变动，有了hash，将意味着有更多的数据库处理可能。

## 感谢

谢谢我的那些朋友，在梦想的道路上携手并进，预计在下一个版本会加上多线程的技术，另外，它目前只是枚举了A记录，未来还会加上更多的DNS解析类型。


如果你有任何问题，可以联系我的微信：Guest_Killer_0nlis 邮箱：payloads@aliyun.com

预计后面会开发一个前渗透测试框架，加油。 :)



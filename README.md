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

## 关于它的优势

你可以在Linux下自定义计划任务，对一个域名进行周期性的爆破，然后比较它们的变动，有了hash，将意味着有更多的数据库处理可能。

## 演示一次使用

```bash
payloads@koone:~/CLionProjects/scanDnsToDB$ sudo ./install.sh
[sudo] payloads 的密码：
正在读取软件包列表... 完成
正在分析软件包的依赖关系树
正在读取状态信息... 完成
default-libmysqlclient-dev 已经是最新版 (1.0.2ubuntu1)。
default-libmysqlclient-dev 已设置为手动安装。
升级了 0 个软件包，新安装了 0 个软件包，要卸载 0 个软件包，有 0 个软件包未被升级。
正在读取软件包列表... 完成
正在分析软件包的依赖关系树
正在读取状态信息... 完成
libldns-dev 已经是最新版 (1.7.0-1ubuntu1.17.10.1)。
升级了 0 个软件包，新安装了 0 个软件包，要卸载 0 个软件包，有 0 个软件包未被升级。
payloads@koone:~/CLionProjects/scanDnsToDB$ ./scanDnsToDB -h
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
payloads@koone:~/CLionProjects/scanDnsToDB$ ./scanDnsToDB -dbaidu.com -rdict.txt
[*]115.239.211.112	www.baidu.com
[*]115.239.210.27	www.baidu.com
[*]10.99.145.36	pop.baidu.com
[*]115.239.217.68	m.baidu.com
[*]115.239.217.67	m.baidu.com
[*]111.202.115.84	autodiscover.baidu.com
[*]10.26.109.19	admin.baidu.com
[*]180.97.104.167	bbs.baidu.com
[*]180.76.134.214	test.baidu.com
[*]61.135.163.61	mx.baidu.com
[*]111.202.115.84	email.baidu.com
[*]220.181.7.233	wap.baidu.com
[*]220.181.7.234	wap.baidu.com
[*]172.17.124.253	oa.baidu.com
[*]202.108.22.220	ns1.baidu.com
[*]220.181.50.247	vpn.baidu.com
[*]61.135.165.235	ns2.baidu.com
[*]115.239.210.43	www2.baidu.com
[*]10.105.97.153	mysql.baidu.com
[*]180.97.36.41	dev.baidu.com
[*]115.239.210.174	news.baidu.com
[*]180.97.33.136	news.baidu.com
[*]115.239.211.51	calendar.baidu.com
[*]180.149.131.88	shop.baidu.com
[*]220.181.163.54	shop.baidu.com
[*]115.239.217.112	mobile.baidu.com
[*]10.48.30.87	web.baidu.com
[*]220.181.50.172	sip.baidu.com
[*]115.239.211.112	www1.baidu.com
[*]115.239.210.27	www1.baidu.com
[*]115.239.211.92	img.baidu.com
[*]180.149.131.33	search.baidu.com
[*]180.97.104.203	support.baidu.com
[*]220.181.163.54	media.baidu.com
[*]180.149.131.88	media.baidu.com
[*]10.65.43.129	files.baidu.com
[*]180.76.138.9	e.baidu.com
[*]115.239.210.38	video.baidu.com
[*]115.239.217.112	app.baidu.com
[*]180.149.144.203	my.baidu.com
[*]10.65.3.178	crm.baidu.com
[*]172.22.1.82	portal.baidu.com
[*]10.73.191.38	demo.baidu.com
[*]115.239.210.90	api.baidu.com
[*]220.181.50.175	lyncdiscover.baidu.com
[*]202.108.22.220	dns.baidu.com
[*]180.97.33.134	images.baidu.com
[*]115.239.210.36	images.baidu.com
[*]10.26.109.19	db.baidu.com
[*]115.239.210.223	info.baidu.com
[*]10.99.57.42	docs.baidu.com
[*]115.239.211.92	static.baidu.com
[*]220.181.37.10	ns3.baidu.com
[*]180.97.34.209	download.baidu.com
[*]10.26.109.19	forum.baidu.com
[*]10.26.7.93	cms.baidu.com
******************************
[MySQL]
mysql> select * from domain order by id desc limit 10;
+------+----------------------------------+-------------------+-----------------+----------------------------------+
| id   | md51                             | domain            | ip              | md52                             |
+------+----------------------------------+-------------------+-----------------+----------------------------------+
| 1448 | f4476ced55f839327d716377e824a143 | intern.baidu.com  | 10.48.40.64     | ad0d04181509c3c874399bd6ab472c40 |
| 1447 | 41ea1a8358389a21d0c63a3966e01c38 | ews.baidu.com     | 111.202.115.84  | dbe42c97ea3876299eafbb3c03a2903f |
| 1446 | fc7dfa43964b7cd67cf7f8e69b0fe3d5 | mai.baidu.com     | 220.181.57.55   | 00d950a57718568c42d4a2072d9a51b0 |
| 1445 | 3386cef86b6f634819885ec2810f3983 | wedding.baidu.com | 180.149.131.12  | 0d90c47facbcafa7e842609e0219f1e5 |
| 1444 | 22f5497dc16327ecb176f236e1a44dc8 | t2.baidu.com      | 60.190.116.48   | 0f8a3631a421ece3df8f07714aed6384 |
| 1443 | 05a9f6cc1198657d1493bf34ea5130c2 | do.baidu.com      | 182.61.58.78    | 552c20646e30ec020c8767b21295a199 |
| 1442 | 7cc91a3391bca905cee29a9cfcafb7cc | cosmos.baidu.com  | 10.23.250.252   | 9f366a44924fd751b443cedaeb022ec8 |
| 1441 | 97a49e03b8fa6645e2cbf0bc34fc376d | bao.baidu.com     | 220.181.112.105 | 61287fd62ecc828b0cf6a014bdb67a1c |
| 1440 | b9bd99c5ed058e99271b4ee001e18a6d | bao.baidu.com     | 123.125.142.73  | 61287fd62ecc828b0cf6a014bdb67a1c |
| 1439 | f2986185813e763be41b262ac8d90358 | bao.baidu.com     | 123.125.112.68  | 61287fd62ecc828b0cf6a014bdb67a1c |
+------+----------------------------------+-------------------+-----------------+----------------------------------+
10 rows in set (0.00 sec)
mysql> select count(*) from domain where domain like '%baidu.com%';
+----------+
| count(*) |
+----------+
|     1260 |
+----------+
1 row in set (0.00 sec)

可以看到有1260条关于baidu的DNS A记录……  如果加上其他类型，我们还能获取更多的信息。
```

## 感谢

谢谢我的那些朋友，在梦想的道路上携手并进，预计在下一个版本会加上多线程的技术，另外，它目前只是枚举了A记录，未来还会加上更多的DNS解析类型。


如果你有任何问题，可以联系我的微信：Guest_Killer_0nlis 邮箱：payloads@aliyun.com

预计后面会开发一个前渗透测试框架，加油。 :)




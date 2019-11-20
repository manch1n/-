# 简单加密算法

### 简要：  

实现了Ceasar，PlayFair，Hill，Des经典算法，并从26个字母的范围扩展到一个字节。  
用benchmark测试一万到一千万字节在本机下的加密解密速率。

### 编译要求：  

windows：visual studio 2019 中用c++17选项     直接生成即可  
linux  ：需要支持c++17的g++（4.8.5或更高版本） 直接 make 即可   

### 说明：  

1）完全使用C++STL，没有任何系统依赖函数。   
2）Windows下的QT界面暂时没写出。   
3）Ceasar类默认使用3个字节的偏移，如需要改变则在构造函数的参数中输入。   
4）PlayFair为了支持字节加密，扩展为16阶加密矩阵，并用map存储索引，发现性能与Ceasar相近。   
5）Hill类为了支持字节加密，发现书上的矩阵并不满足要求。为了简便，不随机求取加密矩阵，参考《1》的4阶矩阵为加密矩阵。     
6）Des默认密钥为（0x0808），子密钥一次性在构造函数中求出，可以看到加密解密1000w字节使用一个线程需要14s。  
7）测试命令：*make && ./benchmark && make clean*   
8）本机运行截图：cpu：i57300HQ 4核4线程   
encrypt          10000 bytes:               4us   decrypt         10000 bytes:             12us    test success!  
encrypt    	100000 bytes:             40us   decrypt       100000 bytes:           107us    test success!  
encrypt      1000000 bytes:          423us   decrypt     1000000 bytes:         1092us    test success!  
encrypt    10000000 bytes:        3974us   decrypt   10000000 bytes:       10434us   test success!  

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

PlayFair  
encrypt        10000 bytes:            367us   decrypt         10000 bytes:            101us   test success!  
encrypt      100000 bytes:            897us   decrypt       100000 bytes:            842us   test success!  
encrypt    1 000000 bytes:         8608us   decrypt      000000 bytes:           9190us   test success!  
encrypt   10000000 bytes:       96296us   decrypt   10000000 bytes:       94665us   test success!  

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Hill  
encrypt         10000 bytes:             957us   decrypt         10000 bytes:             796us   test success!  
encrypt       100000 bytes:           8698us   decrypt      100000 bytes:            8706us   test success!  
encrypt     1000000 bytes:         87425us   decrypt    1000000 bytes:         88739us   test success!  
encrypt   10000000 bytes:      853005us   decrypt   10000000 bytes:      876754us   test success!   

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Des   
encrypt          10000 bytes:          14349us   decrypt         10000 bytes:           14207us   test success!   
encrypt        100000 bytes:        146959us   decrypt       100000 bytes:        149171us   test success!   
encrypt     1000000 bytes:       1492957us   decrypt    1000000 bytes:      1441464us   test success!   
encrypt   10000000 bytes:    14360740us   decrypt   10000000 bytes:    14718177us   test success!   

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



参考：    
《1》http://kns.cnki.net/KCMS/detail/detail.aspx?dbcode=CJFD&dbname=CJFDLAST2016&filename=JZGC201626113&uid=WEEvREcwSlJHSldRa1FhdkJkVG5heGJMd2lJaUcwUEF3Wi9GM2RycWp3dz0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4IQMovwHtwkF4VYPoHbKxJw!!&v=MzEyOTExVDNxVHJXTTFGckNVUkxPZVorZHBGeXpsV3IvT0x6Zk1iYkc0SDlmT3FZNUVaNFI4ZVgxTHV4WVM3RGg=
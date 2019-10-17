# xinxianquan

###简要：  
实现了Ceasar，PlayFair，Hill经典算法，并从26个字母的范围扩展到一个字节。  
用benchmark测试一万到一千万字节在本机下的加密解密速率。
  
###编译要求：  
windows：visual studio 2019 中用c++17选项     直接生成即可  
linux  ：需要支持c++17的g++（4.8.5或更高版本） 直接 make 即可  
   
###说明：  
1）完全使用C++STL，没有任何系统依赖函数。   
2）Windows下的QT界面暂时没写出。   
3）Ceasar类默认使用3个字节的偏移，如需要改变则在构造函数的参数中输入。   
4）PlayFair为了支持字节加密，扩展为16阶加密矩阵，并用map存储索引，发现性能与Ceasar相近。   
5）Hill类为了支持字节加密，发现书上的矩阵并不满足要求。为了简便，不随机求取加密矩阵， 
    参考《1》的4阶矩阵为加密矩阵。     
6）测试命令：*make && ./benchmark && make clean*   
7）本机运行截图：cpu：i57300HQ 4核4线程   
Ceaser   
encrypt      10000 bytes:           6us   decrypt      10000 bytes:          12us   test success!  
encrypt     100000 bytes:          46us   decrypt     100000 bytes:         103us   test success!  
encrypt    1000000 bytes:         440us   decrypt    1000000 bytes:        1039us   test success!   
encrypt   10000000 bytes:        5599us   decrypt   10000000 bytes:       11441us   test success!   
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
PlayFair    
encrypt      10000 bytes:         141us   decrypt      10000 bytes:         113us   test success!    
encrypt     100000 bytes:        1027us   decrypt     100000 bytes:        1112us   test success!    
encrypt    1000000 bytes:       10626us   decrypt    1000000 bytes:       10199us   test success!     
encrypt   10000000 bytes:      111107us   decrypt   10000000 bytes:      105783us   test success!    
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    
Hill    
encrypt      10000 bytes:         896us   decrypt      10000 bytes:         970us   test success!   
encrypt     100000 bytes:        8973us   decrypt     100000 bytes:        9325us   test success!   
encrypt    1000000 bytes:       89448us   decrypt    1000000 bytes:       93488us   test success!   
encrypt   10000000 bytes:      874612us   decrypt   10000000 bytes:      876191us   test success!   
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
   
参考：   
《1》http://kns.cnki.net/KCMS/detail/detail.aspx?dbcode=CJFD&dbname=CJFDLAST2016&filename=JZGC201626113&uid=WEEvREcwSlJHSldRa1FhdkJkVG5heGJMd2lJaUcwUEF3Wi9GM2RycWp3dz0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4IQMovwHtwkF4VYPoHbKxJw!!&v=MzEyOTExVDNxVHJXTTFGckNVUkxPZVorZHBGeXpsV3IvT0x6Zk1iYkc0SDlmT3FZNUVaNFI4ZVgxTHV4WVM3RGg=
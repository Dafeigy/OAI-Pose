## 2023/5/31

初步定下来，**一类信息放一个UDP的端口**，避免端口的占用与数据的分离问题。后端现在暂时用着Flask,后面应该可以有支持多线程的高效运行方法。目前想要的信息有`generated_SRS`的原始SRS数据，`received_SRS`的接受信号信息，同时应该可以顺带着把信号的功率、噪声功率给提出来。

需要注意一点的是，VSCode终端打印信息好像会有问题，当信息太多的时候程序会跟不上，这应该是硬件问题限制的，没办法；然后运行的时候最好是直接本地运行而不是远程VSCode运行，笔记本用无线网络连接的时候特比特别的卡，导致效果很差。

相关的代码在`openair1/PHY/NR_ESTIMATION/nr_ul_channel_estimation.c`里面，定位关键词是`SRS_DEBUG`。要用Protobuf进行数据的传输，以之前的代码为例子重新理顺一下吧：

```protobuf
syntax = "proto2";
package protocol;
message NR_SRS_IQ_EST {
  repeated CHANNLE_EST CHANNLE_EST_LIST = 4;
}

message CHANNLE_EST {
  required int32 image = 1;
  required int32 real  = 2;
}
```

在SRS信号传输的那部分，由于传输的数据是一个数组，数组里面的元素每一个都是由实部和虚部组成的。由于事先不知道数组的大小，所以用`repeated`的`CHANNLE_EST`来声明组成一个类似动态数组的结构`CHANNLE_EST_LIST`。注意这里的`CHANNLE_EST`也是一个自定义的`message`,但是里面的内容是确定的`required`。至于为什么CHANNLE_EST_LIST的标识符是4，其实这个没有特别说明，一个`message`里面出现的字段只要满足他们的标识符相互不同且不在某一个特定的范围`[19000－19999]`就行。

下面就可以设计一下我们需要传输的message了：暂时打算有几个内容需要打包传输：

![data-format.png](https://s2.loli.net/2023/05/31/RYMw96rBWjhLf8H.png)

对于上行信道估计的相关逻辑保存在`openair1/PHY/NR_ESTIMATION/nr_ul_channel_estimation.c`文件中，对应的函数是`int nr_srs_channel_estimation()`这个函数。该函数实现的功能有原始的SRS信号数据、接受的SRS信号数据、使用最小二乘的估计数据，接收的SRS信号的功率信息、噪声功率信息以及每个RB的噪声功率信息。定位关键词为`ifdef SRS_DEBUG`。

在这里有原始的SRS数据（`genRe`、`genIm`），接收的SRS数据（`rxRe`、`rxIm`）以及使用最小二乘估计的结果（`lsRe`、`lsIm`）。数据的存放使用的是数组，原始产生的数据用的是`srs_generated_signal`，接收的数据是`srs_received_signal`，最小二乘估计的结果是`ls_estimated`。

原始信号的数据打印和`openair1/SCHED_NR/phy_procedures_nr_gnb.c`中的数据打印方式类似，都是嵌套在多层循环里面，但是后者的打印逻辑是**每个负责SRS的UE端口中的每一个基站天线元的每一个接收符号**进行打印，一共是三层的嵌套。但是如果将SRS_DEBUG的宏定义取消掉即便在终端能打印出信息，但是可能存在一定的时延问题导致没法稳定的打印，但是进行运算是没问题的。


## 2023/6/1

完成了前端可视化部分的代码，代码逻辑应该没什么问题，需要考虑的就只有那个动态更新的功率。使用了一个双向队列`collections.deque`来限定长度，防止内存溢出；效果如图：

![SONY-demo](https://s2.loli.net/2023/06/02/kobU8NFBcuxJgOl.gif)

## 2023/6/2
讨论了一下应该是想用2T2R的配置。今天看看能不能把数据转发的工作完成，能完成就是胜利，然后下周再弄可视化和数据的处理。新提取到的数据长这样：
```log
[NR_PHY]   Calling nr_srs_channel_estimation function
[NR_PHY]   ====================== UE port 0 --> gNB Rx antenna 0 ======================
[NR_PHY]   ------------------------------------ 0 ------------------------------------
[NR_PHY]          __genRe________genIm__|____rxRe_________rxIm__|____lsRe________lsIm_
[NR_PHY]   (   0)    511             0  |    1489         1373  |     743          685
[NR_PHY]   (   2)   -315          -404  |     843        -1895  |     488          915
[NR_PHY]   (   4)    468          -207  |    2528         1489  |     854         1191
[NR_PHY]   (   6)    344          -379  |    1861         1011  |     250         1028
[NR_PHY]   (   8)   -483           170  |   -1049        -2449  |      88         1329
[NR_PHY]   (  10)   -250          -447  |    1813        -2280  |     552         1348
[NR_PHY]   ------------------------------------ 1 ------------------------------------
[NR_PHY]          __genRe________genIm__|____rxRe_________rxIm__|____lsRe________lsIm_
[NR_PHY]   (  12)   -499          -116  |    1188        -2212  |    -329         1212
[NR_PHY]   (  14)    488           153  |   -1559         1802  |    -474         1091
[NR_PHY]   (  16)    142           491  |   -3244          367  |    -274         1606
[NR_PHY]   (  18)    511            20  |    -278         2234  |     -96         1120
[NR_PHY]   (  20)   -490           151  |     687        -1526  |    -554          628
[NR_PHY]   (  22)   -494          -137  |    1669         -193  |    -780          316
[NR_PHY]   ------------------------------------ 2 ------------------------------------
[NR_PHY]          __genRe________genIm__|____rxRe_________rxIm__|____lsRe________lsIm_
[NR_PHY]   (  24)    -90           504  |    -977         -397  |    -110          515
[NR_PHY]   (  26)   -282          -428  |    1830          132  |    -560          728
[NR_PHY]   (  28)   -213          -466  |    2314         1627  |   -1222          714
[NR_PHY]   (  30)   -303           413  |    -422        -2340  |    -819          862
[NR_PHY]   (  32)   -264          -439  |    2314         1532  |   -1254          597
[NR_PHY]   (  34)   -369          -356  |    3139         2308  |   -1934          259
[NR_PHY]   ------------------------------------ 3 ------------------------------------
[NR_PHY]          __genRe________genIm__|____rxRe_________rxIm__|____lsRe________lsIm_
[NR_PHY]   (  36)     81           505  |     -41        -3475  |   -1717         -255
[NR_PHY]   (  38)   -504            90  |    2717         -565  |   -1387           39
[NR_PHY]   (  40)   -335           387  |    3230        -1045  |   -1452         -879
[NR_PHY]   (  42)    413          -302  |   -1921          770  |   -1002         -256
[NR_PHY]   (  44)    447           248  |   -1672        -1681  |   -1137         -329
[NR_PHY]   (  46)    425          -285  |   -1734          236  |    -786         -385

[NR_PHY]   ------------------------------------ 101 ------------------------------------
[NR_PHY]          __genRe________genIm__|____rxRe_________rxIm__|____lsRe________lsIm_
[NR_PHY]   (1212)    -90           504  |    -841         2894  |    1498          159
[NR_PHY]   (1214)   -494          -137  |   -1587         -953  |     893          247
[NR_PHY]   (1216)   -490           151  |   -2040          167  |    1000          220
[NR_PHY]   (1218)    511            20  |    2292          653  |    1156          281
[NR_PHY]   (1220)    142           491  |    -846         1034  |     378          549
[NR_PHY]   (1222)    488           153  |    1596         2602  |    1149         1001
[NR_PHY]   ------------------------------------ 102 ------------------------------------
[NR_PHY]          __genRe________genIm__|____rxRe_________rxIm__|____lsRe________lsIm_
[NR_PHY]   (1224)   -499          -116  |    -938        -1673  |     646          709
[NR_PHY]   (1226)   -250          -447  |     553        -2373  |     900          820
[NR_PHY]   (1228)   -483           170  |   -2181         -986  |     865          827
[NR_PHY]   (1230)    344          -379  |    2194          853  |     421         1098
[NR_PHY]   (1232)    468          -207  |    1208         3464  |    -149         1827
[NR_PHY]   (1234)   -315          -404  |    1565        -2412  |     470         1359
[NR_PHY]   ------------------------------------ 103 ------------------------------------
[NR_PHY]          __genRe________genIm__|____rxRe_________rxIm__|____lsRe________lsIm_
[NR_PHY]   (1236)    511             0  |    -476         3670  |    -238         1831
[NR_PHY]   (1238)    511             0  |    -700         4141  |    -350         2066
[NR_PHY]   (1240)   -315          -404  |    2685        -1770  |    -128         1603
[NR_PHY]   (1242)    468          -207  |     577         2813  |    -305         1402
[NR_PHY]   (1244)    344          -379  |    1472         3282  |    -721         1647
[NR_PHY]   (1246)   -483           170  |     489        -2240  |    -603          975
[NR_PHY]   signal_power = 2845797
[NR_PHY]   noise_power = 19480, SNR = 21 dB
```
相关的配置信息：
```log
[NR_PHY]   ====================== UE port 0 --> gNB Rx antenna 0 ======================
[NR_PHY]   =============== OFDM Symbol Size: 1536 --> srs_pdu->num_symbols: 0 ==============
[NR_PHY]   signal_power = 1432
[NR_PHY]   noise_power = 32, SNR = 16 dB
[NR_PHY]   Calling nr_srs_channel_estimation function
[NR_PHY]   subcarrier_offset: 900 | N_ap: 1 | K_TC: 2 | m_SRS_b: 104 | M_sc_b_SRS 624| fd_cdm : 1 | mem_offset: 0
```
| OFDM Symbol Size | subcarrier_offset | N_ap | K_TC | m_SRS_b | M_sc_b_SRS | fd_cdm | mem_offset |
| ---------------- | ----------------- | ---- | ---- | ------- | ---------- | ------ | ---------- |
| 1536             | 900               | 1    | 2    | 104     | 624        | 1      | 0          |

## 2023/6/5
~~困得想死，买了瓶陈醋可乐居然要7.9￥！我好崩溃...~~今天要做的是将json数据解析分解然后传到Flask端，Flask端中的js代码来解析传入的数据。另外还需要考虑一个问题：信道估计那104个值，如果使用反三角函数来计算他的相位那么运行时间还是比较大的，要不考虑简单点的数据处理？比如说区间划分啥的可以降低计算复杂度。直接再Echarts官网可视化了一下数据：

<img src="https://s2.loli.net/2023/06/05/HuN5ZCQdl4paX3x.png" style="zoom:50%;" />

没有原始码本信息的时候有：

<img src="https://s2.loli.net/2023/06/05/iXocrb4pUJLhZ8a.png" alt="without_origin_data" style="zoom:50%;" />

当数据格式采用genSRS+recSRS+lsSRS+signalPower+noisePower时，UDP的开销非常大延迟大概有0.24s。解决方法是传到多个socket里面。对104个SRS估计的结果，传输的信道矩阵延迟约为0.08s，能满足10fps的要求。

## 2023/6/6
以为是UDP的接收端的问题，结果发现好像是C端的传输能力问题。数据的处理几乎不耗费时间，唯一的问题在于UDP发射速率。我在想是否和线程阻塞有关，反正至少现在UDP没有丢包。接下来先摸几天，然后看下那个104以及一些参数的设定。以及`CMakelist`的修改暂时搁置，每次用protobuf的时候还是CD到那个地方然后再引入吧，现在效果如图：

![82d2ea1c8337752927c133ffce050e4](https://s2.loli.net/2023/06/06/ZgQuFVxsvTyEl4M.png)

还有一个值得关注的点就是UDP发送的阻塞。多线程去做？回去看一下他们代码怎么写的。

## 2023/6/7

~~打算使用pthread去建立socket，进而使用UDP进行传输。~~

~~start_server启动线程，用的是OAI里面的线程管理。~~

发送端性能拉满了，问题在接收端。UDP的时延再优化也只能做到0.08s。只能保障接收，不能保证渲染。前端如果要实时查看的话，应该帧率在10帧左右。备选方案是采用时间同步+相机数据的同步采集。Ubuntu下可参考[performance - Receive an high rate of UDP packets with python - Stack Overflow](https://stackoverflow.com/questions/51448972/receive-an-high-rate-of-udp-packets-with-python)实现离线的交互。



gnb中的数据，来源于`fill_srs_channel_matrix()`函数中的一个参数channel_matrix，他作为一个返回的值，被`srs_estimated_channel16`或`srs_estimated_channel8`的值所赋予，，而他的依赖又是`srs_estimated_channel_freq`，也是一个参数返回值，在实际使用的时候对应的是`srs_estimated_channel_freq`，实际上在`nr_srs_channel_estimation()`中被使用，依赖是`srs_est`。返回的应该是频率的估计，还没整理完；补充一些额外的配置参数，在`openair1/PHY/NR_UE_TRANSPORT/srs_modulation_nr.c`中找到`SRS_DEBUG`又一大长串：

| B_SRS | C_SRS | b_hop | K_TC | n_SRS_cs | n_shift | l0   | n_SRS_cs_max |
| ----- | ----- | ----- | ---- | -------- | ------- | ---- | ------------ |
| 0     | 25    | 0     | 2    | 0        | 0       | 12   | 8            |

所以分配到的PRB通过查表可以看出来是104个。

## 2023/6/8

信道栅格的计算。当知道绝对信道频点编号$N_{REF}$后通过查表计算升级频率值：
$$
F_{REF}=F_{REF-Offs}+\Delta F_{Global}(N_{REF}-N_{REF-Offs})
$$

| 频率范围/**MHz** | **$\Delta F_{Global}/MHz$** | **$F_{REF-offs}/MHz$** | **$N_{REF-Offs}$** | **$N_{REF}$取值范围** |
| :--------------: | :-------------------------: | :--------------------: | :----------------: | :-------------------: |
|     0~3,000      |              5              |           0            |         0          |       0~599,999       |
|   3,000~24,250   |             15              |         3,000          |      600,000       |   600,000~2,016,666   |
|  24,250~100,000  |             60              |       24,250.08        |     2,016,667      |  2,016,667~3,279,165  |

以OAI的配置文件为例，`absoluteFrequencySSB=641280`，即为SSB绝对频点$N_{REF}$，计算$(641280-600000)*15KHz+3000MHz=3.6192MHz$。



## 2023/6/9

弄懂配置了：

![image-20230609130403803](https://s2.loli.net/2023/06/09/xjYlATzv645HIKM.png)

得到的估计是624/slot，

## 2023/6/12

用docker部署一个Gitlab方便开发。

```bash
docker pull gitlab/gitlab-ce:latest
```

随后启动：

```bash
# 启动容器
docker run \
 -itd  \
 -p 9980:80 \
 -p 9922:22 \
 -v /home/gitlab/etc:/etc/gitlab  \
 -v /home/gitlab/log:/var/log/gitlab \
 -v /home/gitlab/opt:/var/opt/gitlab \
 --restart always \
 --privileged=true \
 --name gitlab \
 gitlab/gitlab-ce
```

进入容器内部修改：

```bash
#进容器内部
docker exec -it gitlab /bin/bash
 
#修改gitlab.rb
vi /etc/gitlab/gitlab.rb
 
#加入如下
#gitlab访问地址，可以写域名。如果端口不写的话默认为80端口
external_url 'http://192.168.0.140'
#ssh主机ip
gitlab_rails['gitlab_ssh_host'] = '192.168.0.140'
#ssh连接端口
gitlab_rails['gitlab_shell_ssh_port'] = 9922
 
# 让配置生效
gitlab-ctl reconfigure
```

## 2023/6/13

摸了一天

## 2023/6/14

研究了一下射频卡，发现free5gc核心网识别不了amf的TAI信息

同时Gitlab崩了，核心网主机不够位置，换了个地方。顺便把上面的补齐：

```bash
# 修改http和ssh配置
vi /opt/gitlab/embedded/service/gitlab-rails/config/gitlab.yml
 
  gitlab:
    host: 192.168.124.194
    port: 9980 # 原本是这里改为9980
    https: false
```

修改root用户密码：

```bash
# 进入容器内部
docker exec -it gitlab /bin/bash
 
# 进入控制台
gitlab-rails console -e production
 
# 查询id为1的用户，id为1的用户是超级管理员
user = User.where(id:1).first
# 修改密码为rdc-china
user.password='rdc-china'
# 保存
user.save!
# 退出
exit
 
```

## 2023/6/15
N310拿了出来，但是安装起来比较麻烦。修改了智邮的gNB参数，现在可以COTSUE连接智邮的gNB+Free5GC的核心网，但是使用OAI的UE连接gNB偶尔会溢出，暂时没有解决方案。

## 2023/6/16
网络崩了，然后准备画图

## 2023/6/19
图画好了巨好看：


今天配一下N310：
![N310](https://kb.ettus.com/images/0/0c/n310_kit.png)

配置N310时要用网线一端直接接RJ45口，另一端接路由器，然后通过`uhd_find_devices`指令可以找到连接的N310的IP地址。注意不能通过SFP口再使用ssh连接，RJ45的网线口是可以远程连接的，用户名为root，默认没有密码。

连接上后需要更新驱动和镜像，这些按照[官网教程](https://kb.ettus.com/USRP_N300/N310/N320/N321_Getting_Started_Guide#Connecting_to_the_ARM_via_SSH)或[博客](https://blog.csdn.net/gibbs_/article/details/122043328)可查到。
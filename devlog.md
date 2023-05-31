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


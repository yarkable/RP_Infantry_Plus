


# 深圳大学步兵视觉开源方案 RP_Infantry_Plus

---
首先在开头感谢 DJI 夏令营开源代码以及大连交通大学 RM2018 开源代码对本套代码的完成提供的巨大帮助，希望这套代码也能够帮助其他队伍在 RM 这个舞台上得到更大的提升。

如有相关疑问，可以咨询相关人员，欢迎大家一起讨论交流，微信联系方式如下：

* 陈晓嘉(大小符) chanxj_ 
* 叶凯(自瞄) sk8_brings_much

## Table Of Contents

* [深圳大学步兵视觉开源方案 RP_Infantry_Plus](#深圳大学步兵视觉开源方案-RP_Infantry_Plus)

* [Table Of Contents](#Table-Of-Contents)

* [1.功能介绍](#1功能介绍)

* [2.效果展示](#2效果展示)

* [3.依赖环境](#3依赖环境)

* [4.整体框架](#4整体框架)

* [5.实现方案](#5实现方案)

* [6.通讯协议](#6通讯协议)

* [7.配置与调试](#7配置与调试)

* [8.总结展望](#8总结展望)


## 1.功能介绍

本套代码完成了对 RoboMaster2019 赛场上大小符以及机器人装甲板的识别，通过自定的通讯协议将视觉处理后的信息发送给下位机，由嵌入式单片机处理视觉信息并控制云台的运动。

我们选用的是 Dahua A5131CU210 工业相机，与下位机通讯选用 TTL-USB 串口模块，mini PC 选用的是 Intel NUC8i5BEH 。若想运行代码，只需给 PC 插上一个 TTL-USB 串口模块和一个 USB cam ， 再稍微改动一下代码就可。

## 2.效果展示

### 装甲板检测

在参考了众多的优秀开源代码后，我们也构思出了一套稳定的识别装甲板的方案。在 6m 内的识别准确率几乎 100% ，加上 ROI 操作和多线程，处理一张图片的时间在 1ms 以内，整个程序跑下来也只需要 4-6ms ，时延非常低，方便更好地做移动预测。并且预处理对不同曝光也很适应，适用曝光范围在 3000-6000（各工业相机参数不同，这里仅针对 Dahua 此型号相机）。

![此为效果图](https://github.com/yarkable/RP_Infantry_Plus/blob/master/assets/autoaim.gif)

### 大小符识别

大小符采用的是深度学习和传统方法结合的方法。可以做到实时预测旋转之后的位置，加上roi和多线程操作之后，处理一张图片的时间在2ms之内，加上读图也只需要4-6ms。大小符所使用的摄像头跟自瞄相同。

附上效果图：

![此为效果图](https://github.com/yarkable/RP_Infantry_Plus/blob/master/assets/rune_desc.jpg)

## 3.依赖环境

运行环境： 
* ubuntu 16.04.3
* OpenCV 3.4.4
* Qt Creator 5.10.1
* CMake 3.5.1
* GCC 5.4.0

## 4.整体框架

### 文件树

```
RP_Infantry_Plus/
├── depends（系统动态链接库）
├── extraFile
│   ├── AimXMl
│   │   ├── calib_no_4_1280.yml
│   │   └── param_config.yml
│   ├── caffemodel
│   │   ├── armornet_iter_200000.caffemodel
│   │   ├── deploy.prototxt
│   │   ├── lenet_iter_200000.caffemodel
│   │   └── lenet_train_test_deploy.prototxt
│   └── Rune
│       ├── lenet
│       │   ├── deploy.prototxt
│       │   ├── lenet_iter_80000.caffemodel
│       │   ├── lenet_iter_80000加了负样本.caffemodel
│       │   └── lenet_iter_80000_旋转后.caffemodel
│       ├── xml
│       │   └── Mono_out.xml
│       └── yolo
│           ├── tiny-yolov2-trial3-noBatch_235000.weights
│           ├── tiny-yolov2-trial3-noBatch_80000.weights
│           ├── tiny-yolov2-trial3-noBatch.cfg
│           └── 单通道
│               ├── tiny-yolov2-trial3-noBatch_80000.weights
│               └── tiny-yolov2-trial3-noBatch.cfg
├── include
│   ├── Aim
│   │   ├── AngleSolver.hpp
│   │   ├── ArmorDetector.hpp
│   │   ├── separate.h
│   │   └── Settings.hpp
│   ├── Camera
│   │   └── video.h
│   ├── header.h
│   ├── ImageConsProd.hpp
│   ├── Rune
│   │   ├── Detect.h
│   └── SerialPort
│       ├── CRC_Check.h
│       └── serialport.h
├── includes （相机 SDK 包含头文件）
├── main.cpp
├── RP_Infantry_Plus.pro
├── RP_Infantry_Plus.pro.user
└── src
    ├── Aim
    │   ├── AngleSolver.cpp
    │   └── ArmorDetector.cpp
    ├── Camera
    │   └── video.cpp
    ├── ImageConsProd.cpp
    ├── Rune
    │   ├── Detect.cpp
    └── SerialPort
        ├── CRC_Check.cpp
        └── serialport.cpp
```

### 文件描述

|文件名|包含类|用途|
|:-- |:-- |:-- |
|AngleSolver.cpp |RectPnPSolver / AngleSolver /AngleSolverFactory|对目标进行角度解算（DJI开源）|
|ArmorDetector.cpp|ArmorDetector|进行装甲板检测|
|video.cpp|Video|将工业相机 SDK 封装成类|
|ImageConsProd.cpp|ImageConsProd|处理多线程以及数据传输|
|Detect.cpp|Detect|进行大小符装甲检测|
|serialport.cpp|SerialPort|自定义与下位机通讯的通讯协议|



## 5.实现方案

### 装甲板识别

自瞄系统的逻辑流程很简单，通过面向对象思想将整一套流程实现，配合多线程使用，整体通俗易懂，以下是自瞄流程图：

![流程图](https://github.com/yarkable/RP_Infantry_Plus/blob/master/assets/peocess.png)


#### 基本原理

1. 如果 `last_result` 为 `true`，则检测区域在上一帧的附近，也就是用到了 ROI 方法，如果超过一定帧数未检测到目标，则逐渐扩大搜索范围，直到 33 帧仍然未检测到目标则全图搜索，此时将与 ROI 有关的变量全部清零。

2. 对检测区域内的图进行二值化，也就是预处理，思路就是先将图片用灰度阈值进行二值化，这样子可以将图片中发光的物体给提取出来（装甲板灯条以及日光灯等等），然后再用某种方法将图片中红色或蓝色的区域提取出来，之后再膨胀一下，跟灰度二值化图片逻辑与，最后得到的就是一张只有红/蓝灯条的二值图，在这上面进行接下去的操作。
	* 一种方法是用 RGB 的红蓝通道相减，根据设定的阈值得到一张二值图，这种方法虽好，但是在识别蓝色的时候，有时候无法排除掉日光灯干扰，除此之外，操作简洁，耗时低，国赛我们选用的就是这种方法。
	* 另一种是先将图片转化成 HSV 颜色空间再用通道范围将红色/蓝色提取出来（网上可找到对应的表），这种方法可以排除掉很多干扰，但是近距离的时候装甲板灯条发白，如果膨胀不到位的话会出现灯条断裂的情况，膨胀的卷积核过大又会造成预处理耗时过久，因此要权衡一下。

3. 在当前二值图内找到所有的轮廓点，用最小旋转矩形将他们包围，此时得到一个个单独的旋转矩形，根据装甲板灯条的几何特征首先筛除掉一些旋转矩形
	```cpp
            bool if1 = (fabs(rrect.angle) < 45.0 && rrect.size.height > rrect.size.width); // 往左
            bool if2 = (fabs(rrect.angle) > 60.0 && rrect.size.width > rrect.size.height); // 往右
            bool if3 = max_rrect_len > _para.min_light_height; // 灯条的最小长度+
            bool if4 = (max_rrect_len / min_rrect_len >= 1.1) && (max_rrect_len / min_rrect_len < 15); // 灯条的长宽比
    ```
    
4. 将这些灯条两两再次组成一个大的旋转矩形（也就是候选装甲板），根据一些限制条件筛除掉不符合条件的装甲板，将剩下的待选装甲板放入一个向量中。（其中利用灯条的角度差信息 angleabs 为大连交通大学开源）
	```cpp
            bool condition1 = delta_h > _para.min_light_delta_h && delta_h < _para.max_light_delta_h;
            bool condition2 = MAX(leni, lenj) >= 113 ? abs(yi - yj) < 166\
                                            && abs(yi - yj) < 1.66 * MAX(leni, lenj) :
                                            abs(yi - yj) < _para.max_light_delta_v\
                                            && abs(yi - yj) < 1.2 * MAX(leni, lenj); 
            bool condition3 = lr_rate < _para.max_lr_rate;
            bool condition4 = sentry_mode ? angleabs < 25 : angleabs < 15 - 5; // 给大点防止运动时掉帧
    ```
    
5. 如果向量中没有元素，则说明没有找到目标，只有一个的话则这就是最终选择的装甲板，有两个以上元素的话就得进行接下去的比较，最容易误识别的地方为装甲板灯条和它两边的两根灯条，经过分析，我们发现这种情况下如果用到了 ROI 操作，包围真正装甲板的那个旋转矩形的角度是最小的，我们可以根据这个特征进行筛选，具体思路请看代码。

6. 找到装甲板之后对其进行 pnp 解算，得到云台转至其中间所需要的 pitch 和 yaw 值，角度解算请参考 DJI 开源的算法，距离信息我们实际测量得到了灯条的长度和实际距离的函数关系，直接代入即可求得距离，误差在 20cm 之内。

7. 哨兵比较特殊，我们对其进行了特殊处理，如果接收到电控传来哨兵模式，我们会对其装甲板匹配条件进行宽松处理，并且对其用上多分类识别装甲板贴纸上的 ID ，在10帧之内如果未找到目标依旧给电控发送找到目标的标志位，直到超过上述帧数才发送未识别到目标，这样子防止了灯条被打灭就失去目标导致云台突然停一下的问题，打灭了之后云台依旧会向前运动，可以快速推掉哨兵。

![判别思路](https://ae01.alicdn.com/kf/H13ce20c8449e4464b3cfb63e71d4d4e1F.png)

### 大小符击打

![流程图](https://ae01.alicdn.com/kf/Hfec6496fe62c4334a737048fa5700ad0a.jpg)

#### 基本原理
1. 在 `include/Detect.h` 中的 `sParam.use_yolo` 变为 1，则使用 yolo 来检测没有打过的扇叶，若为 0 则根据 `lastData` 是否有效来进行 ROI 区域的检测。
2. 对 ROI 区域或者整图进行二值化，在 `src/Detect.h` 可以选择二值化的方法
``` cpp
        enum binaryMode{
			BGR = 1,
			HSV = 2,
			BGR_useG = 3,
			OTSU = 4,
			GRAY = 5,
			YCrCb = 6,
			LUV = 7,
    };
```

3.  检测所有轮廓，统计所有轮廓的子轮廓的个数，排除子轮廓数目大于 1 的轮廓，以及通过面积和长宽比进行排除，得到候选的扇叶。
``` cpp
        bool condition1 =  whrio < param.flabellum_whrio_max && whrio > param.flabellum_whrio_min;// 长宽比
        bool condition2 = area > param.flabellum_area_min;// 最小面积
```

4. 如果得到的扇叶个数大于 1，可以使用 lenet 或者选择面积最小的得到最终的未打过的扇叶。
   在 `inlcude/Detect.h` 里面的 `sParam.use_lenet` 可以控制是否使用 `lenet` 进行分类。
   
5. 在得到的最终的扇叶中，再次寻找所有轮廓，寻找装甲板的中心。其中的条件为长宽比，矩匹配，面积筛选。
``` cpp
        bool condition1 = whrio < param.armor_whrio_max && whrio > param.armor_whrio_min;// 长宽比
        bool condition2 = rev < param.armor_rev_thres;// 矩匹配阈值
        bool condition3 = area > param.armor_area_min;// 最小面积
```

6. 如果为小符，那么就可以不用进行预测，直接将数据发送给下位机，但如果是大符的话，就需要进行圆周预测。预测采用的方法为先预测到切线然后进行修正。根据旋转矩形的角度先预测到切线的位置，然后再绕着装甲点旋转一定角度，近似到圆周上,由于预测角度小，所以预测点和真实打击点基本吻合。

7. 对得到的装甲板的数据进行保存和发送。其中装甲板的象限数据是通过箭头坐标以及旋转矩形的角度进行确定。圆心是通过象限以及给定的半径进行确定。

![大符预测](https://ae01.alicdn.com/kf/Ha4fd6dba0079447c8c6c7d0ddb121249Y.png)

## 6.通讯协议

我们自定的通讯协议一共有 30 个字节，除去校验和预留的数据位，还有 12 个字节的 float 型数据 和 6 个字节的标志位可供使用，能够完成大部分数据的传输。

|Byte0|Byte1|Byte2|Byte3|Byte4|Byte5|Byte6|Byte7|Byte8|Byte9|
|:--|:--|:--|:--|:--|:--|:--|:--|:--|:--|
|0xA5|cmdID|CRC8_Check|pitch_data|pitch_data|pitch_data|pitch_data|yaw_data|yaw_data|yaw_data|
|Byte10|Byte11|Byte12|Byte13|Byte14|Byte15|Byte16|Byte17|Byte18|Byte19|
|yaw_data|dist_data|dist_data|dist_data|dist_data|flag1|flag2|flag3|flag4|flag5|

> * 0xA5 -帧头 
> * cmdID : 8 bit int - 命令模式（0 不处理，1 为红色自瞄，2 为蓝色自瞄， 3 4 5 6 7 8 为大小符）
> * pitch_data : 32 bit float - 接收视觉解算出来的云台 pitch 值
> * yaw_data : 32 bit float - 接收视觉解算出来的云台 yaw 值
> * dist_data : 32 bit flaot - 接收视觉解算目标到相机的距离值
> * flag1 : 8 bit int - 是否瞄准到中心（大小符用） / 哨兵模式 （stm32 -> PC）
> * flag2 : 8 bit int - 是否找到目标（自瞄）/ 吊基地模式（stm32 -> PC）
> * flag3 : 8 bit int - 是否识别到大小符
> * flag4 : 8 bit int - 是否击打过大小符
> * flag5 : 8 bit int - 装甲板是否贴脸（已弃用）

## 7.配置与调试

### 配置

此份代码除了相机可能与其他学校不同，就只需要修改一下路径即可运行，涉及到的路径有以下：
* `main.cpp` 中的 `config_file_name`
* `src/Aim/ArmorDetector.hpp` 中的 `net`
* `include/header.h` 中的 `camera_yaml` `yolo_model_file` `yolo_txt_file` `lenet_model_file` `lenet_txt_file`
* `extraFile/AimXMl/param_config.yml` 中的 `intrinsic_file_720`

刚开始的配置参数是集合在一个 yaml 文件中，在实际调车过程中，发现还是直接修改程序中的代码来的更快捷方便一些，因此后续几乎没有用过 yaml 进行配置，当然，为了程序规范，建议还是用外部配置文件来更改参数，以下是我们之前用的 yaml 配置文件（已弃用），有需要可以在文件中添加配置或者删除配置。

```yaml
%YAML:1.0
---
# For Debug Image
show_image: 1
save_result: 0
# Parameter for Armor Detection System
min_light_height: 10
light_slope_offset: 30
max_light_delta_h: 720
min_light_delta_h: 20
max_light_delta_v: 100
max_light_delta_angle: 30
near_face_v: 100
max_lr_rate: 1.99
max_wh_ratio: 5.12
min_wh_ratio: 1.03
target_max_angle: 20
small_armor_wh_threshold: 3.33
binary_classfication_threshold: 166
# Parameter for Camera
intrinsic_file_720: "/home/nuc/kevin/RP_Infantry_Plus/extraFile/AimXMl/calib_no_4_1280.yml"
```

### 自启动

在赛场上，只有三分钟准备时间，因此我们需要让程序在 PC 开机之后自启动，这就需要写一个自启动脚本，并且，为了防止程序异常中断，我们还用了看门狗来保护程序，原理就是不断检测程序是否在运行，若没有运行，则立刻运行，如果在运行，就隔一段时间再去检测。同样，只需要修改一下路径就可以运行。（我们发现如果在 PC 意外断电的时候，会有几率将二进制文件给损坏，导致程序无法运行，因此为了保险起见，在开机时重新 make 一下程序），为了防止极端情况，在程序意外中断 10 次之后我们直接重启 PC （一般不会遇到这种情况）。

```shell
#!/bin/bash

sec=1
cnt=0
name=RP_Infantry_Plus
Thread=`ps -ef | grep $name | grep -v "grep"`
cd /home/s305-nuc5/kevin/build-$name-Desktop-Debug/
make clean && make -j
while [ 1 ]
do
count=`ps -ef | grep $name | grep -v "grep" | wc -l`
echo "Thread count: $count"
echo "Expection count: $cnt"
if [ $count -gt 1 ]; then
	echo "The $name is still alive!"
	sleep $sec
else 
	echo "Starting $name..."
	cd ~ && ./ttyUSB.sh
    cd /home/s305-nuc5/kevin/build-$name-Desktop-Debug/
    gnome-terminal -x bash -c "./$name;exec bash;"
    echo "$name has started!"		
	sleep $sec
	((cnt=cnt+1))
	if [ $cnt -gt 9 ]; then
		reboot
	fi
fi
done
```

其中的 `ttyUSB.sh` 是对 TTL-USB 串口赋权限用的，内容如下，默认串口为名为 `/dev/ttyUSB0`，因为串口松动可能会变成 `/dev/ttyUSB1`，因此我们对两个串口都赋予权限（有一个串口会不存在，不过不妨碍程序运行）

```shell
#!/bin/bash
echo ubuntu|sudo -S sudo chmod +777 /dev/ttyUSB0
echo ubuntu|sudo -S sudo chmod +777 /dev/ttyUSB1
```
只需将 `watchDog.sh` 添加到 ubuntu 系统的 `StartUp Applications` 中就可以实现开机自启动程序。

### 调试

#### 装甲板识别

由于调试时需要知道所处环境对曝光的适应程度，并且要输出一些信息来帮助我们判断是否有误识别，因此在 `src/Aim/ArmorDetector.cpp` 和 `src/ImageConsProd.cpp` 中定义了多个宏定义开关方便调试，在正式比赛时要将这些开关关闭，否则会影响算法的实时性。

* 开启 `src/Aim/ArmorDetector.cpp` 中的 `SHOW_DEBUG_IMG` 宏定义，展示代码每一步的图片处理细节
* 开启 `src/Aim/ArmorDetector.cpp` 中的 `COUT_LOG` 宏定义，输出匹配灯条的信息
* 开启 `src/Aim/ArmorDetector.cpp` 中的 `CLASSIFICATION` 宏定义，使用多分类识别装甲板（已弃用）
* 开启 `src/ImageConsProd.cpp` 中的 `SHOW_IMAGE` 宏定义，展示程序最终选择的目标装甲板图
* 开启 `src/ImageConsProd.cpp` 中的 `COUT` 宏定义，输出读一张图以及处理一张图所耗费的时间
* 开启 `src/ImageConsProd.cpp` 中的 `SERIAL_DEBUG` 宏定义，强制选择自瞄或大小符模式，正式比赛务必关闭这个开关
* 开启 `src/ImageConsProd.cpp` 中的 `CAP_VIDEO` 宏定义，在程序运行的同时将采取到的图片帧保存为视频存入本地


#### 大小符识别

由于在赛场的时候，灯光等场地因素对我们的图像处理有影响，因此我们也需要通过一些信息来判断程序是否成功识别成功，因此在 `include/Detect.h` 里面有个调试的开关。同时，在开启这个开关之后，对算法的实时性也有影响。

* 把 `include/Detect.h` 中的 `sParam.debug` 变成1，将会输出二值化后的图，以及程序处理过程中的细节以及得到的结果。
* 开启 `src/ImageConsprod.cpp` 中的 `RUNE_CAP_VIDEO`宏定义，在程序运行的同时将采取到的图片帧保存为视频存入本地。

## 8.总结展望

### 总结 

本套代码实现了装甲板识别和大小符的识别这两个功能，自瞄视觉处理后直接将云台到目标的转角输出给下位机，大小符发送目标在相机中的像素值坐标，甚至不用标定相机，一次标定，一劳永逸，只需要修改角度偏移即可，无需过多调试，有较强的可移植性和鲁棒性。

* 装甲板识别
	* 算法简单，配合高帧率相机，可在 6ms 内处理完 1280 * 720 整张图，利用 ROI 在找到目标时更可是在 1ms 内处理结束，整体算法耗时非常低。
	* 采用权重思想对最终选择出来的若干待选择对象进行判定，有效的避免了对假装甲的误识别，使每一次击打都正中装甲板。
	* 在 ROI 的基础上，如果在当前 ROI 视野中未发现目标，则根据相机帧率在一段时间还未发现目标后逐渐扩大 ROI 区域，而不是立刻扩大 ROI ，这个方法有效的避免了装甲板被打灭后 ROI 区域内没有目标的情况。

* 大小符
	* 采用深度学习yolo检测和传统方法相结合，并准备了多种二值化的方法，对场地灯光有比较强的适应性。
	* 圆周运动的预测采用了切线然后修正补偿的方法，无需进行拟合圆心以及识别中间的R。
	* 对区分打过的扇叶以及未打过的扇叶采用了子轮廓个数和lenet分类来区别，不单单只采用面积，有较强的鲁棒性。

### 展望

虽然本套代码将该实现的功能都实现了，但是还是有做的不足的地方。

希望未来可以做到自适应性曝光，这样就不用在适应性训练中修改曝光值调整参数了，并且解 pnp 得到的距离也不准，应该是算法上有些问题，希望下一年可以解决这个问题，直接用 pnp 算法求得敌方装甲板到自己的距离。

并且之后可以尝试视觉直接用二阶卡尔曼滤波器做移动预测，目前是电控在做移动预测，但是偶尔会出现一些问题，如果是视觉在做预测的话可以更加方便的发现问题所在，不用双方都进行 debug 。

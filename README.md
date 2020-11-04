openqtCamera
利用QMultimedia的技术实现的一个简单的摄像头程序
2020/10/21第一次更新

#### （Contact author）
send emails liuminghang0821@gmail.com或者liuminghang0821@qq.com（china））
#### Linux build-dep（linux安装所需）
sudo apt-get install libqt5multimedia5 libqt5multimediawidgets5
#### Linux build（linux编译和安装）
mkdir build
cd build
qmake ..
make 
make install

#### Linux
* 报 va 相关错误  
参考：https://bugreports.qt.io/browse/QTBUG-23761  
解决：sudo apt-get remove gstreamer1.0-vaapi  
感谢：liujianfeng@deepin.org
* 不报错  
    sudo apt-get install gst123  
    下列【新】软件包将被安装：  
    gst123 gstreamer1.0-pulseaudio gstreamer1.0-x  

#### Windows
* 安装 LAV Filters 解码解决。


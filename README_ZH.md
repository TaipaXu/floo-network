# 飞路网

这是一个桌面端文件分享应用，允许用户通过创建或加入房间来实时共享和下载文件。简单操作，即刻连接，安全高效地交换文件。

[English](./README.md) | 中文

![](./app.png)


## 编译

编译[Floo Network Web](https://github.com/TaipaXu/floo_network_web.git)项目后将编译后的web目录复制至本项目根目录。

```sh
$ git clone https://github.com/TaipaXu/floo-network.git
$ cd floo-network
$ ./web.sh #运行web.sh脚本
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make -j$(nproc)
```

## 协议

[GPL-3.0](LICENSE)

[toc]

# 1.简介

协议通过规定比特流中不同位置比特的含义，利用比特流进行信息的交互与传输。

# 2.客户端与服务器

## 2.1.协议头

通用的登录协议头如下：

| 变量           | 位置下标           | 含义                   |
| ---------------- | ------------------- | -------------------------- |
| op             | [0,0]             | 表示期望的操作          |
| ～             | [1+n*20,(n+1)*20] | 变长字段                |

上表中n根据op而定

每一个用户的用户名和密码长度都不能大于20，对于不足的地方用0x00在后补齐

登录成功后，服务器返回一个随机的20位码，作为以后的操作密钥(key)

通用的文件操作协议头如下：

|变量|位置下标|含义|
|-------------------------|---------------------|-----------------------------|
| op | [0,0] | 表示期望的操作 |
| key | [1,20] | 登录成功后服务器返回的操作密钥 |
| 后续操作 | [21,~] | 变长字段 |

不同的操作拥有不一样的信息传输方式，参考2.2节。

## 2.2.注意事项

1:字节流中的各属性的长度信息的数据类型为byte，字符串信息用string转化为字节流。

2:错误码返回的是字符串，需要将字节流转化为string

## 2.3 op变量

- 1:新建用户
- 2:删除用户
- 3.修改用户密码
- 4.登录
- 5:上传文件
- 6:下载文件
- 7:删除文件
- 8:创建路径
- 9:删除路径
- 127.服务器扩展
- 255:请求该目录下文件

### 2.3.1.新建用户

新建用户时，用户需要提供长度不超过20的字符串作为用户名和密码。

| 变量         | 位置下标   | 含义   |
| ------------ | ------------ | ---------- |
| username | [1,20] | 用户名字符串 |
| passwd       | [21,40]| 密码字符串  |

### 2.3.2.删除用户

注销只能在登录后才能注销

注销时，用户需要再次输入密码进行身份确认。

| 变量         | 位置下标         | 含义       |
| ------------ | ------------------ | ----------------- |
| key | [1,20] | 操作密钥 |
| passwd | [21，40] | 密码字符串  |

### 2.3.3.修改用户密码

修改密码时，用户需要提供原来的密码和新的密码

| 变量            | 位置下标            | 含义         |
| --------------- | ------------------ | ------------ |
| key          | [1,20] |  操作密钥     |
| newpasswd    | [21,40] | 新密码字符串          |

### 2.3.4.登陆

登陆时，用户需要输入密码进行身份确认。

| 变量         | 位置下标       | 含义      |
| ------------ | --------------- | --- |
| username | [1,20] | 用户名字符串 |
| passwd       | [21,40] | 密码字符串        |

### 2.3.5/6/7上传文件,下载文件，删除文件

对于文件传输操作，首先应当新建立一个新的socket连接，只用于单个的下载、上传操作

统一的文件操作头如下:

| 变量    | 位置下标    | 含义  |
| ---------- | -------- | --------- |
| key            | [1,20] | 操作密钥 |
| pathLength     | [21,22] | 路径长度，不超过short |
| path           | [22+1,22+pathLength] | 路径。|
| filenameLength | [22+pathLength+1,22+pathLength+1]   | 文件名长度，不超过char  |
| filename       | [22+pathLengh+2,22+pathLength+2+filenameLength] | 文件名 |

#### 上传

先发送文件头，收到服务器返回255后，再向socket中写入全部文件流

文件流写完后立刻结束socket连接

除第一个包和最后一个包外，中间数据包默认每一个单独的包位4KB(与操作系统一致)

#### 下载

先有上述文件头请求，master服务器返回包含一个文件啥信息和服务器ip信息的包，结构如下:

| 变量 | 位置下标    | 含义  |
| ---- | -------- | ------- |
|op    | [0,0]    | 服务器返回码             |
|sha   | [1,32]   | 文件对应sha              |
|ip(1) | [32,36]  | 文件第1部分所在服务器ip  |
|ip(2) | [36,40]  | 文件第2部分所在服务器ip  |
|ip(n) | [32+(n-1)*4+1,32+n*4] | 文件第n部分所在服务器ip |

随后客户端使用上述sha和ip依次请求n个数据服务器，将所有请求返回值拼接即构成完整文件

请求格式如下:

| 变量 | 位置下标    | 含义  |
| ---- | -------- | ------- |
| op  | [0,0]   | 操作码             |
| sha(string)   | [1,64]   | 文件对应sha的字符串格式   |
| '-' | [65,65] | 固定字符'-' |
| num | [66,69] | 包数量，int范围 |

ip数量位int类型，若每个ip存储4KB，最大单文件大小为16T

#### 删除文件

直接删除


注意:

对于path

pdfs的文件存储在pdfs项目下的namespace文件夹，namespace文件夹下的各个文件夹是每个用户的个人存储空间。

如一个用户的用户名为user，其存储了一个文件file在其个人存储空间的根目录中，则有路径../pdfs-handler/namespace/user/file

**注意，如上所示的例子，若用户想要存储$file到其存储空间的根目录下，则应该提供的是相对用户空间的路径（不包括文件名）。即"/"** 

### 2.3.7/8.创建文件夹,删除文件夹

| 变量          | 位置下标     | 含义       |
| ------------- | --------- | ------------- |
| key           | [1,20] | 操作密钥 |
| pathLength    | [21,22]     | 路径长度，不超过short   |
| path          | [22+1,22+pathLength]               | 路径    |
| dirnameLength | [22+pathLength+1,22+pathLength+1]    | 文件夹名称长度，不超过char     |
| dirname       | [22+pathLengh+2,22+pathLength+2+filenameLength] | 文件夹名称|

注意:

对于path

pdfs的文件存储在pdfs项目下的namespace文件夹，namespace文件夹下的各个文件夹是每个用户的个人存储空间

如一个用户的用户名为user，其存储了一个文件夹dir在其个人存储空间的根目录中，则有路径../pdfs-handler/namespace/user/dir

**注意，如上所示的例子，若用户想要存储$file到其存储空间的根目录下，则应该提供的是相对用户空间的路径（不包括文件夹名）。即"/"** 

### 2.3.127.服务器扩展

保留但未定义

### 2.3.255.请求该目录下文件

| 变量       | 位置下标                                   | 含义           |
| ---------- | ------------------------------------------ | -------------- |
| key | [1,20] | 操作密钥 |
| pathLength | [21,22]      | 路径长度，不超过short |
| path       | [22+1,22+pathLength] | 路径   |

服务器返回

## 2.4.错误码

错误码仅在与master节点通信时有效，其仅表示逻辑错误，不表示数据错误

在与数据服务器通信时，由于TCP/IP的特性，认为没有错误产生

| 返回值 | (请求码)含义                  |
| ------ | --------------------- |
|0 |(?)未定义操作|
|1 |(1)新建用户成功|
|2 |(1)用户名被注册|
|3 |(2)删除用户成功|
|4 |(2)删除用户密码核对失败|
|5 |(3)修改密码成功|
|6 |(3)修改密码失败|
|7 |(4)登录成功|
|8 |(4)无用户|
|9 |(4)密码错误|
|10|(5)上传文件成功|
|11|(6)下载文件返回|
|12|(6)未找到文件|
|13|(7)删除文件成功|
|14|(7)未找到文件|
|15|(8)路径创建成功|
|16|(8)路径已存在|
|17|(9)路径删除成功|
|18|(9)路径不存在|
|19|(5,6,7,8,9)权限不足|
|20|登录密钥过期|
|127|(127)服务器扩展成功|
|254|(255)文件请求成功|
|255|OK|

# 3.服务器和后端

## 3.1.请求协议

| 变量     | 位置下标 | 含义                                                         |
| -------- | -------- | ------------------------------------------------------------ |
| op       | [0,0]    | 操作类型<br />1代表写操作<br />2代表读操作<br />3代表删除操作 |
| fileName | [1,EOF]  | 文件名                                                       |

## 3.2.返回值

| 返回值 | 含义                 |
| ------ | -------------------- |
| 0      | 表示成功             |
| 1      | 操作失败，未知错误   |
| 2      | 操作失败，文件不存在 |
| 3      | 操作失败，操作不存在 |

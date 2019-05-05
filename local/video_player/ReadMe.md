## Video player using usart

这个是[video_player_usart](https://github.com/zeyugao/atmega8a/tree/master/video_player_usart)的配套PC程序

运行程序需要安装有Python用于剪视频转化为字符以及将字符进行简单的处理，在Python 3.7.2下测试通过

首先需要运行```v2char.py /path/to/your/video -e```将视频转化为字符，再运行```char2data.py```将字符进行处理

最后使用```program.exe **port**```，这里的```**port**```需要替换为usart的USB口的端口号
import sys
from PyQt5.QtCore import QDateTime, QTimer
from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import QApplication, QLabel, QWidget

class TimeDisplayWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('实时显示系统时间')
        self.setGeometry(300, 300, 1000, 1000)
        self.label = QLabel(self)
        self.label.setGeometry(20, 20, 800, 800)
        
        # 设置字体大小为20
        font = QFont()
        font.setPointSize(40)
        self.label.setFont(font)
        
        # 创建一个定时器，每10毫秒触发一次更新时间的函数
        self.timer = QTimer()
        self.timer.timeout.connect(self.updateTime)
        self.timer.start(1)

    def updateTime(self):
        # 获取当前系统时间
        currentDateTime = QDateTime.currentDateTime()
        # 格式化时间为字符串，包含毫秒
        currentTime = currentDateTime.toString('yyyy-MM-dd hh:mm:ss.zzz')
        # 更新显示的时间
        self.label.setText(currentTime)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    widget = TimeDisplayWidget()
    widget.show()
    sys.exit(app.exec_())
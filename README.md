# QtMCS
本次作业实现了随机化芯片设计方法中芯片的手动设计与芯片流速与浓度的关联计算与图形化显示，基于 Qt 设计了一个 Microfluidic Chip Simulation 用户界面系统。

## 具体功能

- 用户可以通过工具栏上的 `Create` 新建所需芯片，可自定义的参数包括：芯片大小、输入输出管道的位置
- 用户可以在芯片界面单击芯片内某根管道，切换管道的开闭，进行直观的修改
- 用户可以通过工具栏上的 `Random` 随机生成芯片
- 用户可以通过工具栏上的 `Config` 自定义输入管道的流速、浓度，和随机生成芯片时每条管道被生成的概率
- 用户可以通过工具栏上的 `Switch` 切换流速模式和浓度模式

## 交互界面及逻辑

本程序有着十分良好的交互界面及逻辑。

 - `Create` 和 `Config` 在打开的时候所显示的为当前参数值，方便用户修改单个数据，而不是全部参数重新输入
 - 当用户修改了某项参数，主界面芯片自动实时计算修改后的芯片的流速和浓度，并显示三个输出口的流速和浓度
 - 当光标停留在某条管道上时，状态栏自动现实此管道的流速和浓度
 - 芯片的图形化界面中，管道的颜色会随着流速或浓度的大小变化，直观地展现芯片内各个管道的流速和浓度
 - 窗口标题会显示当前是流速模式还是浓度模式

## 代码设计

程序源文件组成如下：

![](pic\1.png)

- main.cpp	主程序
	 mainwindow.cpp/h	主窗口
	 graphitem.cpp/h	2D 绘图元件
	 createconfig.cpp/h	`Create` 对话框
	 config.cpp/h	`Config` 对话框
	 calculate.cpp/h	有关流速和浓度的计算算法

### mainwindows.cpp/h

继承 `QMainWindow` 定义了 `MainWindow` 类，实现主窗口。

#### members:
```C++
Ui::MainWindow *ui; // 主窗口界面
QGraphicsScene *scene; // 2D 图形界面
GraphItem *pipeRow[7][8], *pipeCol[8][7], *cross[8][8], *pipeIn[8], *pipeOut[8]; // 管道和管道交界处的小方格的图形元件
QGraphicsTextItem *textitem[3]; // 输出口下方的文字显示图形元件
// 以及有关芯片的各种信息
```

#### public:
```C++
void sceneNew(); // 新建 QGraphicsScene 界面
void sceneDraw(); // 在 QGraphicsScene 界面上进行绘图
void updateCross(); // 更新芯片图内交点小正方形的显示状态和颜色
void updateText(); // 更新芯片图下方显示输出口信息的文字
void Simulation(); // 以当前芯片模拟液体流入
```

#### slots:
```C++
void on_actionCreate_triggered(); // 工具栏 Create 被触发
void on_actionRandom_triggered(); // 工具栏 Random 被触发
void on_actionConfig_triggered(); // 工具栏 Config 被触发
void on_actionSwitch_triggered(); // 工具栏 Switch 被触发
void create(int, bool*, bool*); // 接受从 Create 对话框返回的参数信息并新建芯片 
void updateConfig(int, int, int, int, int); // 接受从 Config 对话框返回的参数信息并更新芯片信息
void chipChanged(); // 芯片被修改后重新计算新的流速和浓度信息
```

### graphitem.cpp/h

自定义 `QGraphicsItem` 类为 `GraphItem`，实现 2D 图形界面的绘图元件，为矩形元素（例如芯片图上的管道和管道交界处的方格）

#### members:
```C++
int x, y, width, height; // 矩形左上角坐标和矩形的长宽
bool Enable, NotChange; // 是否
double v = 0, c = 50;
```

#### signals:
```C++
void pipeChanged(); // 管道开闭状态改变，调用 MainWindow::chipChange
void hoverEnter(QString); // 光标进入矩形显示范围，调用 statusBar::showMessage(QString) 修改状态栏信息
void hoverLeave(); // 光标离开矩形显示范围，调用 statusBar::clearMessage() 清空状态栏
```

#### protected:
```C++
void mousePressEvent(QGraphicsSceneMouseEvent *event);
void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
```

### createconfig.cpp/h

定义 `CreateConfig` 类，继承 `QDialog` 类。

重载构造函数，要求构造时传入当前芯片的大小和输入输出口位置，并将对话框各项复选框切换成当前芯片的参数大小，方便用户修改单一的参数。

#### signals:
```C++
void finished(int,bool*,bool*); // 将新的参数传输给 MainWindow::create() 新建芯片
```

#### slots:
```C++
void on_sizeBox_currentIndexChanged(int index); // 当芯片大小修改时，将不在芯片大小范围内的输入输出口复选框的 enable 设为 false
void on_buttonBox_accepted(); // 当触发时，检查所选择的输入输出口数量是否符合限制，若不符合则弹出错误窗口，若符合则发送 finished 信号
```

### config.cpp/h

定义 `Config` 类，继承 `QDialog` 类。

重载构造函数，要求构造时传入当前芯片参数，并将对话框各项复选框切换成当前芯片参数，方便用户修改单一的参数。

使用 `QIntValidator` 对 `QLineEdit` 控件进行整数范围的输入限制。

#### signals:
```C++
void finished(int, int, int, int, int); // 将新的参数传输给 MainWindow::updateConfig() 更新芯片
```

### calculate.cpp

自行编写的流速和浓度的模拟算法。

流速模拟算法：将流速看做电流，每个交点的电势和输出口外的电势设为未知数，共 $n^2+2$ 个；每个管道交叉处都满足入流总和等于出流总和，再加上输入流的大小限制，可得到 $n^2+2$ 条方程，接着进行复杂度为 $O(n^3)$ 的高斯消元求解，最后再根据每个点的电势求地每条边的电流，也就是流速。

浓度模拟算法：先进行流速模拟，得到每条边的流向，接着针对管道交叉处的出入不同情况分类讨论，进行拓扑排序，即可得到每条管道的浓度。

```C++
vector<double> caluconspeed(...); // 模拟液体流动得到所有管道的流速
vector<double> calconcen(...); // 模拟液体流动得到所有管道的浓度
```

## 编写环境

IDE：Qt 5.0, SublimeText

System：Windows 10

## Github

Github 上提供 releases 版本。

https://github.com/Konano/QtMCS

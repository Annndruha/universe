## ��������� OpenCV ����� Visual Studio ��� C++
#### � �������:
**���������/�������/�������������������/���������������/�������������������/����/��������**
��������: `"C:\opencv\build\x64\vc14\bin"`

#### � Visual Studio:
�������� ����� ����������� �� �64
������������ �������� �����

**�������� VC++/�������� ���������**

`C:\opencv\build\x64\vc14\lib;$(LibraryPath)`

**�++/�����/��� �������� ���������� ������**

`C:\opencv\build\include\opencv;C:\opencv\build\include\opencv2;C:\opencv\build\include;$(IncludePath);%(AdditionalIncludeDirectories)`

**�����������/�����/��� �������� ���������**
`C:\opencv\build\x64\vc14\lib;%(AdditionalLibraryDirectories)`

**�����������/����/��� �����������--��������� ������ � �����(d)**
`opencv_world400d.lib;%(AdditionalDependencies)`


```c++
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
```

#### ������ ������� ��� ������� ��������� ������ � ����������� �����������
**�����������/�������/����������**
������� **Windows (/SUBSYSTEM:WINDOWS).**

**�����������/�������������/����� �����**
������� **mainCRTStartup**
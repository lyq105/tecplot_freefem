# 说明
这是一个在windows将freefem++中的数据保存为tecplot acsii 和 二进制格式的c++扩展。

# 编译安装流程  
1. mingw，codeblock中自带的编译器。
2. 将FreeFem++安装文件夹中的example++-load中的include文件夹拷贝到当前文件夹中并重命名为ff_include，并将libff.dll和FreeFem-api.dll拷贝到当前文件夹。
2. 将tecplot安装文件夹中的example++-load中的include文件夹拷贝到当前文件夹中并重命名为tec_include，并将tecio.lib和tecio.dll拷贝到当前文件夹。
3. 运行build.bat
4. 将生成的tecplot.dll和tecio.dll拷贝到FreeFem++.exe所在的文件夹。双击teciotest.edp运行一下查看结果。

从简单的测试freefem++文件可以知道，采用二进制输出需要的时间是ascii模式输出的1/10.


# SiemensSpaceUbuntu
VirtualBox+Ubuntu下SIR的数据集Siemens和space的操作步骤。
1，create-ver-dir.c 可放置于文件夹source下，运行时，读入参数vers，在traces下生成如下vers个文件夹：v1,v2,...v(vers).
    接着，可手工添加文件夹vok，用于存储object的正确版本生成的数据。
2，assembcov.c 可放置于文件夹source下，运行时，运行时，读入参数objectName（对象名），将SIR提供的scripts/runall.sh转换成我自己的getcovs.sh.
   getcovs.sh依次运行object的所有故障版本，并记录它们的程序在测试所有测试用例的输出结果（存储于outputs/v(?)/t(?)）;以及各测试用例的覆盖情况（存储于traces/v(?)/t(?).gcov）。
3，runallversh.c 自动化执行object的所有故障版本,每个故障版本都要求测试所有测试用例。该程序要求读入参数vers（故障版本数目）。runallversh.exe拷贝buildexe.origin.sh为buildexe.sh，并修改     其中的版本号，将故障版本程序编译为.exe文件。runallversh.exe拷贝getcovs.origin.sh为getcovs.sh，并修改其中的版本号，记录所有测试用例的结果。
两个bash的shell程序：
I，buildexe.origin.sh和buildexe.sh 将object各版本程序编译为.exe文件
II,getcovs.origin.sh和getcovs.sh   在object各版本.exe上执行所有测试用例，并记录程序输出结果和代码覆盖情况。

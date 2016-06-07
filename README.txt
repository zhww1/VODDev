1：
	在VS2013下这个第三方类扩展库（thirdpart）里面的4个文件 需要稍加修改才能运行。否则在VS2013提示错误。
2：
	1、皮肤的dll文件放到当前工程否则运行debug提示错误。
	2、编译提示链接错误，解决方法是把uncode 改成未设置。
	注意问题：有时候调试运行提示中断，有可能是以下原因
				1、不能同时打开2个工作工程时候调试另一个工程。运行提示中断。
 				2、换个皮肤 你没有清理再重新运行 
				3、或者把皮肤库文件都从skin文件夹下复制出来拷贝到当前目录，
		   		   然后包含和加载皮肤库的位置修改成当前目录如下代码
				//#include "./skin/SkinMagicLib.h"
				//#pragma comment(lib, "./skin/SkinMagicTrial.lib")
				#include "SkinMagicLib.h"
				#pragma comment(lib, "SkinMagicTrial.lib")	
				//2 加载皮肤文件
				//VERIFY(1 == LoadSkinFile(_T("./skin/xpsteel.smf")));
				/*VERIFY(1 == LoadSkinFile(_T("./skin/corona.smf")));*/
				VERIFY(1 == LoadSkinFile(_T("corona.smf")));
				4、把皮肤库文件复制出来放到bin下的server下。一般只需要dll和smf文件。因为加载的时候需要这些文件就可以直接在bin下运行了 。这也是开发完成后部署需要注意的问题。


3、对数据库操作需要修改：
//#import "C:\Program Files\Common Files\System\ADO\msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")

#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")
因为是64位系统 带86
编译有个4996错误增加宏_CRT_SECURE_NO_WARNINGS

4、修正了类从原来的VC6.0上添加AXTIVE控件生成的6个文件3个头文件和3个源文件使用这3个类否则第2天的下午在选择datagrid行时下面的控件文本哪里实现不了
   原因是因为返回LPDISPATCH而不是类对象



	

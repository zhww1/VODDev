1��
	��VS2013���������������չ�⣨thirdpart�������4���ļ� ��Ҫ�Լ��޸Ĳ������С�������VS2013��ʾ����
2��
	1��Ƥ����dll�ļ��ŵ���ǰ���̷�������debug��ʾ����
	2��������ʾ���Ӵ��󣬽�������ǰ�uncode �ĳ�δ���á�
	ע�����⣺��ʱ�����������ʾ�жϣ��п���������ԭ��
				1������ͬʱ��2����������ʱ�������һ�����̡�������ʾ�жϡ�
 				2������Ƥ�� ��û���������������� 
				3�����߰�Ƥ�����ļ�����skin�ļ����¸��Ƴ�����������ǰĿ¼��
		   		   Ȼ������ͼ���Ƥ�����λ���޸ĳɵ�ǰĿ¼���´���
				//#include "./skin/SkinMagicLib.h"
				//#pragma comment(lib, "./skin/SkinMagicTrial.lib")
				#include "SkinMagicLib.h"
				#pragma comment(lib, "SkinMagicTrial.lib")	
				//2 ����Ƥ���ļ�
				//VERIFY(1 == LoadSkinFile(_T("./skin/xpsteel.smf")));
				/*VERIFY(1 == LoadSkinFile(_T("./skin/corona.smf")));*/
				VERIFY(1 == LoadSkinFile(_T("corona.smf")));
				4����Ƥ�����ļ����Ƴ����ŵ�bin�µ�server�¡�һ��ֻ��Ҫdll��smf�ļ�����Ϊ���ص�ʱ����Ҫ��Щ�ļ��Ϳ���ֱ����bin�������� ����Ҳ�ǿ�����ɺ�����Ҫע������⡣


3�������ݿ������Ҫ�޸ģ�
//#import "C:\Program Files\Common Files\System\ADO\msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")

#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")
��Ϊ��64λϵͳ ��86
�����и�4996�������Ӻ�_CRT_SECURE_NO_WARNINGS

4�����������ԭ����VC6.0�����AXTIVE�ؼ����ɵ�6���ļ�3��ͷ�ļ���3��Դ�ļ�ʹ����3��������2���������ѡ��datagrid��ʱ����Ŀؼ��ı�����ʵ�ֲ���
   ԭ������Ϊ����LPDISPATCH�����������



	

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ASIONET_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ASIONET_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ASIONET_EXPORTS
#define ASIONET_API __declspec(dllexport)
#else
#define ASIONET_API __declspec(dllimport)
#endif

#define BOOST_ALL_DYN_LINK 
#define BOOST_LIB_DIAGNOSTIC
#define BOOST_AUTO_LINK_TAGGED
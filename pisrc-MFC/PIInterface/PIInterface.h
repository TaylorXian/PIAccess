// #include <wtypes.h>
// #include <atlconv.h>
// #include <tchar.h>
//#pragma once
//#include <jni.h>
// #ifndef _PI_INTERFACE_MAO
// #define _PI_INTERFACE_MAO

#include "piapix.h"
#include "piaccess_PiDb.h"
//#include "jni_md.h"
#define TAG_LEN 80

typedef struct _TAG
{
	char tagname[TAG_LEN+1];
	int32 pointnum;
	char descriptor[27];   
	char engunit[32];
	char instrumenttag[33];
	//	char pt_type;
	PIvaluetype pt_typex;
	float64 rval;//, arcrval;
	int32  ival;//, arcival;
	void  *bval;//, *arcbval;
	uint32 bsize;//, arcbsize;
	int32  istat;//, arcistat;
	int16  flags;//, arcflags;
	PITIMESTAMP ts;//, arcts;
} TAG;
//InitTAGFromjTag˵����
//����java�е�Tag����jobjTag��ʼ��C�е�TAG�ṹ��tag����jobjTag����tagname����pointnum
//���ȡPI�иõ����������λ���������͵���Ϣ������ֵ��tag����jobject�е�
//tagname����pointnumΪ�գ���0������tag�ṹ��ĸ����ֶξ�ΪĬ��ֵ��
//����ֵ��Ϣ��0��ϵͳ����-1����ǩ��û���ҵ�����δ���ӵ���������1����ȡ�ɹ�
//            2��jobjTag��tagname����pointnum��Ϊ�գ�0����tag���ֶ�ΪĬ��ֵ
int InitTAGFromjTag(JNIEnv *env,jobject jobjTag, TAG tag);
//SetjTagFromTAG˵����
//��InitTAGFromjTag�෴����TAG�ṹ��tag�ĸ�������ֵ��ֵ��jobjTag�����ֶ�
int SetjTagFromTAG(JNIEnv *env,TAG tag,jobject jobjTag);
//
//void PIValueTypeToChar(PIvaluetype PtType,char* cType);
//��Calendarת����PITIMESTAMP���ͣ�����objCal����ΪCalendar��Ķ���
PITIMESTAMP CalendarToPITIMESTAMP(JNIEnv *env,jobject objCal);
//��PITIMESTAMP����ת����Calendar����
jobject PITIMESTAMPToCalendar(JNIEnv *env, PITIMESTAMP tmStamp);
//��java��Tag��Ķ���jobjTag�е�ts�ֶ�����ΪjobjCal��jobjCal����ΪCalendar��Ķ���
void SetTagCalendar(JNIEnv *env,jobject jobjTag, jobject jobjCal);
//����java�е�Tag��Ķ���objTag�ĸ����ֶε�ֵ
void SetObject(JNIEnv *env,jobject objTag,double rval, int ival, int istat, short iflag,PITIMESTAMP tmStp);
//��jobjTag��pt_typex�ֶ�����ΪvalType
void SetTagPIvaluetype(JNIEnv *env, jobject jobjTag, PIvaluetype valType);
//��ö������pttype��ֵת�����ַ�������
const char *GetTypeStr ( PIvaluetype pttype)

//#endif
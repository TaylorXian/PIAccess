
#pragma once

#include "piapix.h"
#include "piaccess_PiDb.h"
#define TAG_LEN 80

typedef struct _TAG
{
	char tagname[TAG_LEN+1];
	int32 pointnum;
	char descriptor[27];   
	char engunit[32];
	char instrumenttag[33];
	PIvaluetype pt_typex;
	float64 rval;
	int32  ival;
	void  *bval;
	uint32 bsize;
	int32  istat;
	int16  flags;
	PITIMESTAMP ts;
} TAG;
//InitTAGFromjTag˵����
//����java�е�Tag����jobjTag��ʼ��C�е�TAG�ṹ��tag����jobjTag����tagname����pointnum
//��ֵ��tag����Ӧ�ֶ�
int GetTAGFromjTag(JNIEnv *env,jobject jobjTag, TAG &tag);
//SetjTagFromTAG˵����
//��InitTAGFromjTag�෴����TAG�ṹ��tag�ĸ�������ֵ��ֵ��jobjTag�����ֶ�
int SetjTagFromTAG(JNIEnv *env,TAG &tag,jobject jobjTag);
//����PI��ֵ��ʼ��һ��TAG���͵Ķ���,tag����ʱ��Ҫָ��tagname����pointnum��
//����һ���Ѿ���ʼ����TAG������TAG�ĵ�λ��������������͵���Ϣ���Ѿ�����
//����ֵ��Ϣ��0��ϵͳ����-1����ǩ��û���ҵ�����δ���ӵ���������1����ȡ�ɹ�
//            -2��jobjTag��tagname����pointnum��Ϊ�գ�0����tag���ֶ�ΪĬ��ֵ
int InitTAGFromPI(TAG &tag);
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
const char *GetTypeStr ( PIvaluetype pttype);

//#include "piapix.h"
//#include <jni.h>
//#include "piaccess_PiDb.h"
#include "PIInterface.h"
//#include <jni.h>

int GetTAGFromjTag(JNIEnv *env,jobject jobjTag, TAG &tag)
{
	//��ȡ��
	jclass jclsTag = env->GetObjectClass(jobjTag);
	if(!jclsTag)
	{
		printf("Error in GetSnapShot GetObjectClass(Tag)\n");
		return 0;
	}
	//��ȡ����ǩ��
	jfieldID idName = env->GetFieldID(jclsTag,"tagname","Ljava/lang/String;");
	jstring jstrName = (jstring)env->GetObjectField(jobjTag,idName);
	if(jstrName)
	{
		const char* strConName = env->GetStringUTFChars(jstrName,NULL);
		strcpy(tag.tagname,strConName);
		env->ReleaseStringUTFChars(jstrName,strConName);
		return 1;
	}
	jfieldID  idPtNum =env->GetFieldID(jclsTag,"pointnum","I");
	tag.pointnum = env->GetIntField(jobjTag,idPtNum);
	
	return 1;
	
}
int SetjTagFromTAG(JNIEnv *env,TAG &tag,jobject jobjTag)
{
	//��ȡ��
	jclass clsTag = env->GetObjectClass(jobjTag);
	if(!clsTag)
	{
		printf("Error in GetSnapShot GetObjectClass(Tag)");
		return 0;
	}
	jfieldID jfID = env->GetFieldID(clsTag,"rval","D");
	env->SetDoubleField(jobjTag,jfID,tag.rval);
	jfID = env->GetFieldID(clsTag,"ival","I");
	env->SetIntField(jobjTag,jfID,tag.ival);
	jfID = env->GetFieldID(clsTag,"istat","I");
	env->SetIntField(jobjTag,jfID,tag.istat);
	jfID = env->GetFieldID(clsTag,"flags","S");
	env->SetShortField(jobjTag,jfID,tag.flags);
	jfID = env->GetFieldID(clsTag,"pointnum","I");
	env->SetIntField(jobjTag,jfID,tag.pointnum);
	jobject jobjCal = PITIMESTAMPToCalendar(env,tag.ts);
	SetTagCalendar(env,jobjTag,jobjCal);
	SetTagPIvaluetype(env,jobjTag,tag.pt_typex);
	//����String���͵��ֶ�
	jfID = env->GetFieldID(clsTag,"tagname","Ljava/lang/String;");
	jstring jstr = env->NewStringUTF(tag.tagname);
	env->SetObjectField(jobjTag,jfID,jstr);

	jfID = env->GetFieldID(clsTag,"descriptor","Ljava/lang/String;");
	jstr = env->NewStringUTF(tag.descriptor);
	env->SetObjectField(jobjTag,jfID,jstr);

	jfID = env->GetFieldID(clsTag,"engunit","Ljava/lang/String;");
	jstr = env->NewStringUTF(tag.engunit);
	env->SetObjectField(jobjTag,jfID,jstr);
	
	env->DeleteLocalRef(jstr);
	return 1;
}
int InitTAGFromPI(TAG &tag)
{
	int result;
	if('\0'!=tag.tagname[0])
	{
		//printf("name:%s",tag.tagname);
		result = pipt_findpoint(tag.tagname,&tag.pointnum);
		if(result)
		{
			if(result>0)
			{
				printf("System Error!");
				return 0;
			}
			if(-2==result)
			{
				printf("Passed tag is all spaces");
				return 0;
			}
			if(-5==result)
			{
				printf("Tag not found, or not yet connected to a server");
				return -1;
			}
		}
	}
	else//��û�б�ǩ������ֱ�Ӹ��ݱ�ǩ���
	{
		if(!tag.pointnum)
		{
			//�򵥳�ʼ����tag�����ֶξ�ΪĬ��ֵ
			printf("δָ����ǩ�����߱�ǩ���");
			return -2;
		}
		result = pipt_ptexist(tag.pointnum);
		if(!result)
		{
			printf("Point do not exist");
			return -1;
		}	
		pipt_tag(tag.pointnum,tag.tagname,81);
	}

	//��ȡ��λ��Ϣ�����浽tag��
	result = pipt_engunitstring ( tag.pointnum, tag.engunit, 32 );
	if ( result )
	{
		printf ( "\npipt_engunitstring %ld", result );
		tag.engunit[0] = '\0';
	}

	//��ȡ������Ϣ�����浽tag��
	result = pipt_descriptor ( tag.pointnum, tag.descriptor, 27 );
	if ( result )
	{
		printf ( "\npipt_descriptor %ld", result );
		tag.descriptor[0] = '\0';
	}
	//��ȡ��ǩ���������Ϣ�����浽tag��
	result = pipt_pointtypex ( tag.pointnum, &tag.pt_typex );
	if ( result )
	{
		printf ( "\npipt_pointtypex %ld", result );
		tag.pt_typex = PI_Type_bad;
	}
	//��ȡ��ǩ����豸��ǩ��Ϣ�����浽tag��
	result = pipt_instrumenttag ( tag.pointnum, tag.instrumenttag,33);
	if(result)
	{
		printf("\npipt_instrumenttag %ld",result);
		tag.instrumenttag[0] = '\0';
	}
	//���ݱ�ǩ������ͣ��Խ�����ֵ�ļ����������и�ֵ
	switch (tag.pt_typex ) {
			case PI_Type_PIstring:
			case PI_Type_blob:
			case PI_Type_PItimestamp:
				//��������������ʱ������
				break;
			case PI_Type_int16:
			case PI_Type_int32:
				tag.rval = NULL;
				tag.bval = NULL;
				tag.bsize = 0;
				break;
			case PI_Type_digital:
				tag.rval = NULL;
				tag.bval = NULL;
				tag.ival = NULL;
				tag.bsize = 0;
				break;
			default:/* floats, PI2 */
				tag.ival = NULL;
				tag.bval = NULL;
				tag.bsize = 0;
				break;
	}
	return 1;
}
void PIValueTypeToChar(PIvaluetype PtType,char* cType)
{
	char *PIValueTab[] ={
		"PI_Type_null", //= 0,
		"PI_Type_bool",
		"PI_Type_uint8",
		"PI_Type_int8",
		"PI_Type_char",
		"PI_Type_uint16",
		"PI_Type_int16",
		"PI_Type_uint32",
		"PI_Type_int32",
		"PI_Type_uint64",
		"PI_Type_int64",
		"PI_Type_float16",
		"PI_Type_float32",
		"PI_Type_float64",
		"PI_Type_PI2",
		"PI_Type_digital", //= 101,
		"PI_Type_blob",
		"PI_Type_PItimestamp", //= 104,
		"PI_Type_PIstring",
		"PI_Type_bad" //= 255
	};
	if(PtType<15)
	{
		cType = PIValueTab[PtType];
		return;
	}
	switch(PtType)
	{
	case 101:
		cType ="PI_Type_digital";
		break;
	case 102:
		cType ="PI_Type_blob";
		break;
	case 104:
		cType ="PI_Type_PItimestamp";
		break;
	case 105:
		cType ="PI_Type_PIstring";
		break;
	case 255:
		cType ="PI_Type_bad";
		break;
	default:
		break;
	}


}
//��Calendarת����PITIMESTAMP
PITIMESTAMP CalendarToPITIMESTAMP(JNIEnv *env,jobject objCal)
{
	PITIMESTAMP tmStamp;
	//�����ж�objCal��������Calendar���ͣ��򲻽���ת��
// 	jclass jclsCal = env->FindClass("java/util/Calendar");
// 	if(!jclsCal)
// 	{
// 		printf("Error in CalToPITIMESTAMP FindClass!");
// 		return tmStamp;
// 	}
// 	jobject jobjCal = env->AllocObject(jclsCal);
// 
// 	if(!jobjCal)
// 	{
// 		printf("Error in CalToPITIMESTAMP AllocObject!");
// 		return tmStamp;
// 	}
// 	if (!(env->IsSameObject(jobjCal,objCal)))
// 	{
// 		printf("Not a Calendar Object!");
// 		return tmStamp;
// 	}
// 	env->DeleteLocalRef(jobjCal);
	//��ȡCalendar������
	jclass jclsCal = env->GetObjectClass(objCal);
	jmethodID jmGetID = env->GetMethodID(jclsCal,"get","(I)I");
	
	//��
	jfieldID jfID = env->GetStaticFieldID(jclsCal,"YEAR","I");
	jint jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.year = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);
	
	jfID = env->GetStaticFieldID(jclsCal,"MONTH","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.month = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);

	jfID = env->GetStaticFieldID(jclsCal,"DAY_OF_MONTH","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.day = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);

	jfID = env->GetStaticFieldID(jclsCal,"HOUR_OF_DAY","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.hour = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);

	jfID = env->GetStaticFieldID(jclsCal,"MINUTE","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.minute= (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);

	jfID = env->GetStaticFieldID(jclsCal,"SECOND","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.second = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);

//	printf("Year Code is %d,Year is %d",jCode,jYear);

	env->DeleteLocalRef(jclsCal);
	return tmStamp;
}
//����jobject������
void SetObject(JNIEnv *env,jobject objTag,double rval, int ival, 
			   int istat, short iflag,PITIMESTAMP tmStp)
{
	//��ȡ��
	jclass clsTag = env->GetObjectClass(objTag);
	if(!clsTag)
	{
		printf("Error in GetSnapShot GetObjectClass(Tag)");
		return ;
	}
//	printf("iNumber:%d,dValue:%f,iValue:%d",iNumber,pSnapDval,pSnapIval);
	jfieldID jRValID = env->GetFieldID(clsTag,"rval","D");
	env->SetDoubleField(objTag,jRValID,rval);
	jfieldID jIValID = env->GetFieldID(clsTag,"ival","I");
	env->SetIntField(objTag,jIValID,ival);
	jfieldID jIStatID = env->GetFieldID(clsTag,"istat","I");
	env->SetIntField(objTag,jIStatID,istat);
	jfieldID jFlagsID = env->GetFieldID(clsTag,"flags","S");
	env->SetShortField(objTag,jFlagsID,iflag);
	jobject jobjCal = PITIMESTAMPToCalendar(env,tmStp);
	SetTagCalendar(env,objTag,jobjCal);
}

jobject PITIMESTAMPToCalendar(JNIEnv *env, PITIMESTAMP tmStamp)
{
	jclass jclsCal = env->FindClass("java/util/Calendar");
	if(!jclsCal)
	{
		printf("Error in FindClass!");
		return NULL;
	}
	jmethodID jmGetInsID = env->GetStaticMethodID(jclsCal,"getInstance","()Ljava/util/Calendar;");
	if(!jmGetInsID)
	{
		printf("Error in GetStaticMethodID!");
		return NULL;
	}
	jobject jobjCal = env->CallStaticObjectMethod(jclsCal,jmGetInsID);
	if(!jobjCal)
	{
		printf("Error in CallStaticObjectMethod!");
		return NULL;
	}
	jmethodID jmSetID = env->GetMethodID(jclsCal,"set","(IIIIII)V");
	if(!jmSetID)
	{
		printf("Error in GetMethodID!");
		return NULL;
	}
	//printf("Month:%d\n",tmStamp.month);
	env->CallVoidMethod(jobjCal,jmSetID,tmStamp.year,tmStamp.month,
		tmStamp.day,tmStamp.hour,tmStamp.minute,tmStamp.second);
	printf("Second:%f",tmStamp.second);
	return jobjCal;
}
//���ñ�ǩ���Calendarֵ
void SetTagCalendar(JNIEnv *env,jobject jobjTag, jobject jobjCal)
{
	jclass jclsTag = env->GetObjectClass(jobjTag);
	jfieldID jfCalID = env->GetFieldID(jclsTag,"ts","Ljava/util/Calendar;");
	env->SetObjectField(jobjTag,jfCalID,jobjCal);
}
void SetTagPIvaluetype(JNIEnv *env, jobject jobjTag, PIvaluetype valType)
{
	const char* strValType = GetTypeStr(valType);
	//��ȡö�����͵�jobject����
	jclass jclsValType = env->FindClass("piaccess/PIvaluetype");
	if(!jclsValType)
	{
		printf("Error find PIValueType");
		return ;
	}
	jfieldID jidPtType = env->GetStaticFieldID(jclsValType,strValType,"Lpiaccess/PIvaluetype;");
	if(!jidPtType)
	{
		printf("Error in GetStaticFieldID");
		return ;
	}
	jobject jobjEnum = env->GetStaticObjectField(jclsValType,jidPtType);
	//��jobjTag��pt_typex������и�ֵ����
	jclass jclsTag = env->GetObjectClass(jobjTag);
	jfieldID jfValTypeID = env->GetFieldID(jclsTag,"pt_typex","Lpiaccess/PIvaluetype;");
	env->SetObjectField(jobjTag,jfValTypeID,jobjEnum);

}
const char *GetTypeStr ( PIvaluetype pttype)
{
	switch (pttype)
	{
	case PI_Type_null:
		return "PI_Type_null";
	case PI_Type_bool:
		return "PI_Type_bool";
	case PI_Type_char:
		return "PI_Type_char";
	case PI_Type_uint8:
		return "PI_Type_uint8";
	case PI_Type_int8:
		return "Integer-8";
	case PI_Type_uint16:
		return "PI_Type_uint16";
	case PI_Type_int16:
		return "PI_Type_int16";
	case PI_Type_uint32:
		return "PI_Type_uint32";
	case PI_Type_int32:
		return "PI_Type_int32";
	case PI_Type_uint64:
		return "PI_Type_uint64";
	case PI_Type_int64:
		return "PI_Type_int64";
	case PI_Type_digital:
		return "PI_Type_digital";
	case PI_Type_PIstring:
		return "PI_Type_PIstring";
	case PI_Type_PItimestamp:
		return "PI_Type_PItimestamp";
	case PI_Type_blob:
		return "PI_Type_blob";
	case PI_Type_float32:
		return "PI_Type_float32";
	case PI_Type_float16:
		return "PI_Type_float16";
	case PI_Type_float64:
		return "PI_Type_float64";
	case PI_Type_PI2:
		return "PI_Type_PI2";
	default:
		return "PI_Type_bad";
		break;
	}
}
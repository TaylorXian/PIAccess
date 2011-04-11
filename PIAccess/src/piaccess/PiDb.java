package piaccess;
import piaccess.Tag;
import java.util.Calendar;
//SN   SnapShot
//AR   Archive

//��������ǰע������ʾ����˼��
///*i*/�����������
///*o*/������������
///*i,o*/���ȴ���󴫳�

public class PiDb {
//	public Tag TagPoint;

//	public int iTest;
	
//	public native int Get();
//	public native int Set();
//	public native Tag GetSnapShot(int PointNumber);
	//ͨ����ǩ������ƻ�ñ�ǩ��ı��,����ֵΪ��ǩ���š���û���ҵ����򷵻�-1
	public native int FindPointNumber(/*i*/String TagName);
/*	//ͨ����ǩ��ı�Ż�ȡ��ǩ��ĵ����������ݣ�������λʵ�����ͣ�����ֵ1��ʾ�ɹ�
	public native int GetSNRealByNumber(iint PointNumber, oTag TagPoint);
	//ͨ����ǩ������ƻ�ȡ��ǩ��ĵ����������ݣ�������Ϊʵ�����ͣ�����ֵ1��ʾ�ɹ�
	public native int GetSNRealByName(iString TagName, oTag TagPoint);*/
	//��ȡ����TagPoint�����ݡ�����ʱ��Ҫ�ƶ�Tag���ƻ���Tag��š���ͬʱָ������Tag��������
	public native int GetSingleSNData(/*i,o*/Tag TagPoint);
	//��ȡ�����TagPtArray�����ݣ�����ʱ��Ҫ�ƶ�Tag���ƻ���Tag��š���ͬʱָ������Tag��������
	public native int GetArraySNData(/*i,o*/Tag[] TagPtArray);
	//���ڴ����봫������
	public native void DateTest(Calendar inCal, Calendar outCal);
	//����JNI����ö�����͵Ķ�ȡ
	public native PIvaluetype EnumTest();
	//���һ��ʱ�䷶Χ�ڼ�¼������,����ֵΪ��¼�ĸ���
	public native int GetARCount(/*i*/Calendar tmStart, /*i*/Calendar tmEnd, 
			/*i*/int PtNumber);
	//��ȡһ��ʱ�䷶Χ�ڵ�������ʷ��¼,ע��TagArray���洢����ΪPtNumber�ڲ�ͬʱ���ֵ
	//TagArray�Ĵ�С��Ҫ���û�ָ��,����ͨ��GetARCount��ȡ��
	public native int GetARData(/*i*/Calendar tmStart, /*i*/Calendar tmEnd,
			/*i*/int PtNumber, /*o*/Tag[] TagArray);
	//�������ṩ��ʱ�����У���ȡһ�ж�Ӧ��ֵ����ֵ��ͨ����ֵ�㷨�����
	public native int GetArrayARData(/*i*/Calendar[] arrayTime,/*i*/int PtNumber,
			/*o*/Tag[] TagArray);
	
	
	
	static {
		System.loadLibrary("PIInterface");
	}
/*	public static void main(String[] args)
	{
//		HelloWorld CCall = new HelloWorld();
		PiDb pb = new PiDb();
		Tag tg = pb.GetSnapShot();
		System.out.println(tg.getValue());
		
	}*/
}

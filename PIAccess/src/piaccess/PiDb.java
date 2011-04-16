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
	//ͨ����ǩ������ƻ�ñ�ǩ��ı��,����ֵΪ��ǩ���š���û���ҵ����򷵻�-1
	public native int FindPointNumber(/*i*/String TagName);
	//��ȡ����TagPoint�����ݡ�����ʱ��Ҫ�ƶ�Tag���ƻ���Tag��š���ͬʱָ������Tag��������
	public native int GetSingleSNData(/*i,o*/Tag TagPoint);
	//��ȡ�����TagPtArray�����ݣ�����ʱ��Ҫ�ƶ�Tag���ƻ���Tag��š���ͬʱָ������Tag��������
	public native int GetArraySNData(/*i,o*/Tag[] TagPtArray);
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
	//����iStateCode��ȡ״̬������PI�����������˼
	//public native int GetState(/*i*/int iStateCode, /*o*/String strState);
	
	//���ݷ������������ӷ�����,1��ʾ���ӳɹ���0��ʾ����ʧ�ܣ�����SvrNameһ��Ϊ��������IP��ַ,ProcNameΪ�Զ���ķ�����Process���ƣ�Ϊ�ĸ��ַ�����
	public native int ConnectServer(/*i*/String SvrName, /*i*/String ProcName/*�ĸ��ַ�����*/);
	//������ΪstrSvrName�ķ���������ΪĬ�Ϸ��������ɹ�����1�����򷵻�0��
	public native int SetDefaultServer(/*i*/String strSvrName);
	//��ȡĬ�ϵķ�������Ϣ��strSvrNameΪ���������ƣ�strAddrΪ��������ַ��bConnected��ʾ�Ƿ�������
	public native int GetDefaultServerInfo(/*o*/String strSvrName, /*o*/String strAddr, /*o*/Boolean iConnected);
	//��ȡָ��������ΪstrSvrName�ķ������ĵ�ַ������״̬���ɹ�����1�����򷵻�0
	public native int GetServerInfo(/*i*/String strSvrName, /*o*/String strAddr, /*o*/Boolean iConnected);
	
	static {
		System.loadLibrary("PIInterface");
	}

}

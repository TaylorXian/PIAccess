package piaccess;

import java.util.Calendar;
public class Tag {
	   public String tagname = null;// = new char[81];//PI��char����
	   public int pointnum = 0;//PI��int32����               
	   public String descriptor = null;// = new char[27];
	   public String engunit = null;// = new char[32];
//	   String itag;// = new char[33];
//	   char pt_type;
	   public PIvaluetype pt_typex = null;
	   public double rval = 0.0/*, arcrval*/;//PI��float32����
	   public int  ival = 0/*, arcival*/;
	   public String bval = null/*, arcbval*/;
//	   public int bsize, arcbsize;//PI��uint32����
	   public int  istat = 0/*, arcistat*/;
	   public short  flags = 0/*, arcflags*/;//PI��int16����
	   public int timedate = 0;
	   public Calendar ts = Calendar.getInstance();
//	   public Calendar arcts = Calendar.getInstance();
/*	 public double getValue()
	   {
		   return rval;
	   }
	 public int getStat()
	   {
		   return istat;
	   }*/
}

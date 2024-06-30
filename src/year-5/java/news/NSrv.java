import java.io.*;
import java.net.*;
import java.lang.*;

class NSrv
{
  public static void main(String args[])
    {
      System.out.println("News server on-line.");
      JNewsSrv nServer = new JNewsSrv(8888);
      nServer.GoGoGo();
    }
}

//
//  PROVIDER
//
class SNewsProvider extends Thread
{
  DataOutputStream os = null; 
  BufferedReader is = null;   
  String data;

  void ready(BufferedReader x)    
    {
      try
	{
	  while (!x.ready());
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
     }

  public SNewsProvider(Socket s)
    {
      try
	{
          is   = new BufferedReader( 
                 new InputStreamReader(s.getInputStream())); 
          os   = new DataOutputStream(s.getOutputStream());     
	  data = new String("");
	}
      catch(IOException e)
	{
	  System.out.println(e);
	} 	
    }

  public void run()
    {
      System.out.println("News provider connected to port");
      
      try
	{
	  ready(is);
	  data = is.readLine();
	  // verifica domeniul
	  if ((data.compareTo("politica") != 0) &&
	      (data.compareTo("sport") != 0) &&
	      (data.compareTo("economie") != 0) &&
	      (data.compareTo("cultura") != 0))
	    {
	      System.out.println("Error : invalid domain");
	      os.writeBytes("invalid domain\n");
	      return;
	    }

	  // so we have a valid domain - open a file; first send the ack
	  os.writeBytes("ready to receive\n");

	  RandomAccessFile newsfile;
	  newsfile = new RandomAccessFile(data, "rw");
	  newsfile.seek(newsfile.length());

	  // read in the news & write to file
	  while(data.compareTo("End of news") != 0)
	    {
	      ready(is);
	      data = is.readLine();
	      newsfile.writeBytes(data);
	      newsfile.writeBytes(new String("\n"));
	    }
	  // close file
	  newsfile.close();
	  os.writeBytes(new String("received ok\n"));	
	  //sock.close();
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
    }
}

//
//  CONSUMER
//
class SNewsConsumer extends Thread
{
  DataOutputStream os = null; 
  BufferedReader is = null;
  String data; 

  void ready(BufferedReader x)    
    {
      try
	{
	  while (!x.ready());
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
     }

  public SNewsConsumer(Socket s)
    {
      try
	{
          is   = new BufferedReader( 
                 new InputStreamReader(s.getInputStream())); 
          os   = new DataOutputStream(s.getOutputStream());     
	  data = new String("");
	}
      catch(IOException e)
	{
	  System.out.println(e);
	} 	
    }

  int count(RandomAccessFile where) throws IOException
    {
      int records = -1;
      int i;
      String aLine = new String("");

      where.seek(0);
      for(; aLine != null;)
	{
	  while(true)
	    {
	      aLine = where.readLine();
	      if (aLine == null) break;
	      if (aLine.compareTo("End of news") == 0) break;
	    }
	  records++;
	}
      return records;
    }

  void seek(RandomAccessFile where, long records) throws IOException
    {
      int i;
      String aLine = new String("");

      try
	{
	  where.seek(0);
	  for(i = 1; (i <= records) && (aLine != null); i++)
	    {
	      while(true)
		{
		  aLine = where.readLine();
		  if (aLine == null) break;
		  if (aLine.compareTo("End of news") == 0) break;
		}
	    }
	}
      catch(IOException e)
	{
	  System.out.println(e);
	  throw e;
	}
    }

  public void run()
    {
      System.out.println("News consumer connected to port.");
      try
	{
	ready(is);
	data = is.readLine();
	
	// send the confirmation
	os.writeBytes("user id ok\n");
	// we have the user name
	RandomAccessFile userfile;
	userfile = new RandomAccessFile("users"+File.separator+data, "rw");
	if (userfile.length() == 0)
	  {
	    userfile.writeLong(0);
	    userfile.writeLong(0);
	    userfile.writeLong(0);
	    userfile.writeLong(0);
	  }
	
	ready(is);
	data = is.readLine();
	// we have the domain 
	// verifica domeniul
	if ((data.compareTo("politica") != 0) &&
	    (data.compareTo("sport") != 0) &&
	    (data.compareTo("economie") != 0) &&
	    (data.compareTo("cultura") != 0))
	{
	  System.out.println("Error : invalid domain");
	  os.writeBytes("invalid domain\n");
	  return;
	}
	
	os.writeBytes("domain ok\n");

	int index = 0;
	if (data.compareTo("politica") == 0) index = 0;
	if (data.compareTo("sport") == 0) index = 1;
	if (data.compareTo("economie") == 0) index = 2;
	if (data.compareTo("cultura") == 0) index = 3;

	// open the newsfile
	RandomAccessFile newsfile = new RandomAccessFile(data, "rw"); 

	ready(is);
	data = is.readLine();
	// we have the news required by client
	int news;
	try
	  {
	    news = (new Integer(data)).intValue();
	  }
	catch(NumberFormatException n)
	  {
	    System.out.println(n);
	    os.writeBytes("not a number\n");
	    return;
	  }

	// confirm a valid number
	os.writeBytes("number ok\n");

	// read from file last news read by client
	long lastnews = 0;
	userfile.seek(index * 8);
	lastnews = userfile.readLong();
	
	seek(newsfile, lastnews);
	int i;
	String aLine = new String("");
	
	// send the news
	for(i = 0; (aLine != null) && ((news == -1) || ((i < news) && (news != -1))); i++)
	  {
	    while(true)
	      {
		aLine = newsfile.readLine();
		if (aLine == null)  break;
		if (aLine.compareTo("End of news") == 0) break;
		else
		  {
		    os.writeBytes(aLine+"\n");
		  }
	      }

	    if (aLine != null)
	      {
		os.writeBytes(String.valueOf(lastnews));
		os.writeBytes("\n");
		lastnews++;
	      }
	  }

	os.writeBytes("End of transmission\n");
	os.writeBytes(String.valueOf(count(newsfile)-lastnews));
	os.writeBytes("\n");
	System.out.println("near seek");
	
	userfile.seek(index * 8);
	System.out.println(lastnews);
	userfile.writeLong(lastnews);

	userfile.close();
	newsfile.close();
	//sock.close();
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
    }
}

class JNewsSrv
{
  ServerSocket server = null; 
  Socket sock = null; 
  DataOutputStream os = null; 
  BufferedReader is = null; 
  String data;
  boolean bye = false;

  public JNewsSrv(int port)
    {
      try
	{
	  server = new ServerSocket(port);  
	  data = new String("");
	}
      catch(IOException e)
	{
	  System.out.println(e);  
	}
    }

  String Din2InDoi(String what)
    {
      int i;
      String result = new String("");
      
      for(i = 0; i < what.length()/2; i++)
	{
	  result += what.charAt(2*i+1);
	}

      return result;
    }
   
   void Ready(BufferedReader x)
    {
      try
	{
	  while (!x.ready());
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
    }
   
   public void GoGoGo()
    {
      while(true)
	{
      try
	{
	  sock = server.accept(); 
          is   = new BufferedReader( 
                      new InputStreamReader(sock.getInputStream())); 
          os   = new DataOutputStream(sock.getOutputStream()); 
	  
	  Ready(is);
	  data = is.readLine();
	  if (data.compareTo("provider") == 0)
	    {
	      new SNewsProvider(sock).start();
	    }
	  if (data.compareTo("consumer") == 0)
	    {
	      new SNewsConsumer(sock).start();
	    }
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
	}
    }
}










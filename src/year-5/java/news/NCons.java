import java.io.*;
import java.net.*;
import java.lang.*;

class NCons
{
  public static void main(String args[])
    {
      System.out.println("News consumer.");
      CNewsConsumer nclient = new CNewsConsumer("localhost", 8888);
      nclient.Start();
    }
}

class CNewsConsumer
{
  Socket sock = null; 
  DataOutputStream os = null; 
  BufferedReader is = null;
  BufferedReader console = null; 
  String data;

  public CNewsConsumer(String host, int port)
    {
      try
	{
	  sock = new Socket(host, port);  
          is  = new BufferedReader( 
                new InputStreamReader(sock.getInputStream())); 
          os  = new DataOutputStream(sock.getOutputStream());
          console = new BufferedReader( 
                new InputStreamReader(System.in)); 
	  data = new String("");
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
    }

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
  
  public void Start()	
    {
      try
	{
	  // send type string
	  os.writeBytes("consumer\n");
	  
	System.out.println("Your id ?");
	data = console.readLine();
	os.writeBytes(data + "\n");
	ready(is);
	data = is.readLine();
	if (data.compareTo("user id ok") != 0) 
	  {
	    System.out.println("Error : " + data);
	    sock.close();
	    return;
	  }

	System.out.println("Domain ?");
	data = console.readLine();
	os.writeBytes(data + "\n");
	ready(is);
	data = is.readLine();
	if (data.compareTo("domain ok") != 0) 
	  {
	    System.out.println("Error : " + data);
	    sock.close();
	    return;
	  }

	System.out.println("Number of news to retrieve <-1 for all> ?");
	data = console.readLine();
	os.writeBytes(data + "\n");
	ready(is);
	data = is.readLine();
	if (data.compareTo("number ok") != 0) 
	  {
	    System.out.println("Error : " + data);
	    sock.close();
	    return;
	  }

	while (true)
	  {
	    ready(is);
	    data = is.readLine();
	    if (data.compareTo("End of transmission") == 0) break;
	    System.out.println(data);
	  }

	ready(is);
	data = is.readLine();
	System.out.println(data + " news unread.");
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
    }	
}



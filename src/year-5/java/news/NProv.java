import java.io.*;
import java.net.*;
import java.lang.*;

class NProv
{
  public static void main(String args[])
    {
      System.out.println("News provider.");
      JNewsProvider nprovider = new JNewsProvider("localhost", 8888);
      nprovider.Start();
    }
}

class JNewsProvider
{
  Socket sock = null; 
  DataOutputStream os = null; 
  BufferedReader is = null;
  BufferedReader console = null; 
  String data;
  boolean bye = false;
  String path;
  String server_response;

  public JNewsProvider(String host, int port)
    {
      try
	{
	  sock = new Socket(host, port);  
          is  = new BufferedReader( 
              new InputStreamReader(sock.getInputStream())); 
          os  = new DataOutputStream(sock.getOutputStream());
          console = new BufferedReader( 
              new InputStreamReader(System.in)); 
	  path = new String("/");
	  server_response = new String("");
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
	  // send id string
	  os.writeBytes("provider\n");
	  System.out.println("Domain ?");
	  data = console.readLine();	  
	  os.writeBytes(data);
	  os.writeBytes("\n");

	  // wait for ack
	  ready(is);
	  data = is.readLine();
	  if (data.compareTo("ready to receive") != 0)
	    {
	      System.out.println("Server error : " + data);
	      return;
	    }
	  // ok to send
	  System.out.println("Message ?");
	  while(data.compareTo("End of news") != 0)
	    {
		data = console.readLine();
		os.writeBytes(data);
		os.writeBytes(new String("\n"));
          }
	  // we've done it! - wait for ack
	  ready(is);
	  data = is.readLine();
	  if (data.compareTo("received ok") != 0)
	    {
	      System.out.println("Server error...news wasn't added");
		return;
	    }
	  System.out.println("Message succesfully sent."); 
      }
	catch(IOException e)
      {
	  System.out.println(e);
      }
    }	
}
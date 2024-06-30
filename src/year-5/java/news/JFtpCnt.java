import java.io.*;
import java.net.*;
import java.lang.*;

class JFtpCnt
{
  public static void main(String args[])
    {
      System.out.println("Client de FTP in Java");
      FtpClient ftpclient = new FtpClient("localhost", 8888);
      ftpclient.Start();
    }
}

class FtpClient
{
  Socket sock = null; 
  DataOutputStream os = null; 
  BufferedReader is = null;
  BufferedReader console = null; 
  String command;
  boolean bye = false;
  String path;
  String server_response;

  public FtpClient(String host, int port)
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
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
    }

  void llsCommand()
    {
      File this_path = new File(path);
      String[] contents = this_path.list();
      int i;
      
      if (!this_path.exists())
	{
	  System.out.println("Calea" + path + "nu exista");
	  return;
	}

      if (contents.length > 0)
      for(i = 1; i < contents.length; i++)
	{
	  System.out.println(contents[i]);
	}
      else System.out.println(path + " nu contine fisiere sau directoare");
    }

  void lsCommand()
    {
      os.writeChars(command + "\n");
      os.Flush();
      server_response = is.readLine();
      while(server_response.compareTo("vin directoare"))
	{
	  server_response = is.readLine();
	}
      
    }

  public void Start()
    {
      try
	{ 
	  System.out.println("Clientul de FTP a fost pornit.");

	  while(!bye)
	    {
              System.out.print("jftp>"); 
	      command = console.readLine();
	      //System.out.println("Comanda " + command);
	      command.toLowerCase();

	      if (command.compareTo("bye") == 0)
		{
		  bye = true;
		  os.writeChars(command + "\n");
		  os.flush();
		  continue;
		}
	      if (command.compareTo("lls") == 0)
		{
		  llsCommand();
		  continue;
		}
	      if (command.compareTo("ls") == 0)
		{
		  lsCommand();
		  continue;
		}
	    }
	}
      catch(IOException e)
	{
	  System.out.println(e);
	}
    }
}




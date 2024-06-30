import java.io.*;
import java.net.*;
import java.lang.*;

class JFtpSrv
{
  public static void main(String args[])
    {
      System.out.println("Tokmai atzi lansat serverul de ftp...");
      FtpServer ftpServer = new FtpServer(8888);
      ftpServer.Start();
    }
}

class FtpServer
{
  ServerSocket server = null; 
  Socket sock = null; 
  DataOutputStream os = null; 
  BufferedReader is = null; 
  String command;
  boolean bye = false;

  public FtpServer(int port)
    {
      try
	{
	  server = new ServerSocket(port);  
	  command = new String("");
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

  void lsCommand()
    {
      od.WriteChars("vin directoare");
    }

  public void Start()
    {
      try
	{
	  sock = server.accept(); 
          is   = new BufferedReader( 
                      new InputStreamReader(sock.getInputStream())); 
          os   = new DataOutputStream(sock.getOutputStream()); 
	  
	  System.out.println("S'a conectat un client.");

	  while(!bye)
	    {
              while(!is.ready());

	      command = is.readLine();

	      command = Din2InDoi(command);
	      System.out.println("Comanda " + command);
	      command.toLowerCase();

	      if (command.compareTo("bye") == 0)
		{
		   bye = true;
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

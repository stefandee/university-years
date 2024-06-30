import java.io.*;
import java.lang.*;

class XCopy
{
  public static void main(String args[])
    {
      if (args.length == 0)
	{
	  System.out.println("Folosire : XCopy [-a] destdir srcdir\n");
	  return;
	}
      if (((args[0].compareTo("-a") != 0) && (args.length != 2)) || 
          ((args[0].compareTo("-a") == 0) && (args.length != 3)))
	{
	  System.out.println("Folosire : XCopy [-a] destdir srcdir\n");
	  return;
	}
      if (args.length == 2) 
	{
	  System.out.println("Argumentele sint : " + args[0] + " si " + args[1]);
	  InternalCopy copy = new InternalCopy();
          copy.interactiveCopy(args[0], args[1], false);
	}
      else
        { 
	  System.out.println("Argumentele sint : " + args[1] + " si " + args[2]);
	  InternalCopy copy = new InternalCopy();
	  copy.interactiveCopy(args[1], args[2], true);
        }
   }
}

class InternalCopy
{
  public InternalCopy()
    {
    }

  void copyFile(String where, String from_where, String filename)
    {
      System.out.println("De copiat " + where + " din " + from_where + " fisierul " + filename); 
      File source = new File(from_where);
      File dest   = new File(where);

      dest.mkdirs();

      RandomAccessFile dest_stream;
      RandomAccessFile src_stream;	

      try
       	{
      	  dest_stream = new RandomAccessFile(where + filename, "rw");
      	  src_stream  = new RandomAccessFile(from_where, "r");
        }
      catch(IOException e)
	{
	  System.out.println("Eroare de copiere");
	  return;
	}

      byte[] buffer = new byte[32768];
      int bytes_read = 0;

      while(bytes_read != -1)
	{
	  try
          {
	    bytes_read = src_stream.read(buffer);
	  }
	  catch(IOException e)
	  {
	    System.out.println("Eroare de citire.");
	    break;
	  }

          try
	  {
	    if (bytes_read != -1) dest_stream.write(buffer, 0, bytes_read);
	  }
	  catch(IOException e)
	  {
	    System.out.println("Eroare de scriere");
	    break;
	  }
	}
      try
      {	
        dest_stream.close();
        src_stream.close();
      }
      catch(IOException e)
      {
	System.out.println("Nu pot inchide fisierele.");
      }
    }

  public void interactiveCopy(String destdir, String srcdir, boolean ask)
    {
      File file = new File(srcdir);
      String[] crt_dir_files = file.list();
      int i, key_pressed = 0;
      
      for(i = 0; i < crt_dir_files.length; i++)
	{
	  File crt_file = new File(srcdir + crt_dir_files[i]);
	  if (crt_file.isDirectory()) 
	    {
	      if (ask == true)
                {
	          System.out.println("Sa merg pe " + srcdir + crt_dir_files[i] + "/ ? [d/n]");

		  try
                  {
                    key_pressed = System.in.read();
		    while( (key_pressed != 'd') &&
                           (key_pressed != 'D') &&
	                   (key_pressed != 'n') &&
                           (key_pressed != 'N'))
                      {
	                System.out.println("DA sau NU ?");
	                key_pressed = System.in.read();
                      }
                   }
	           catch(IOException e)
	           {
	             System.out.println("Eroare de citire de la tastatura ? Beah...");
                   }  

	          if ((key_pressed == 'd') || (key_pressed == 'D')) 
                    interactiveCopy(destdir + crt_dir_files[i] + "/", srcdir + crt_dir_files[i] + "/", ask);
	        }
              else
                {
		  System.out.println("Merg pe " + srcdir + crt_dir_files[i] + "/");
	          interactiveCopy(destdir + crt_dir_files[i] + "/", srcdir + crt_dir_files[i] + "/", ask);
                }
	    }
          if (crt_file.isFile())
	    copyFile(destdir, srcdir + crt_dir_files[i], crt_dir_files[i]);
	}
    }

  public void silenceCopy(String destdir, String srcdir)
    {
    }
}

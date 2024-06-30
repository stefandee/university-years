import java.net.*; 
import java.io.*; 

public class JWget 
{ 
  public static void main(String[] args) throws Exception 
  { 
    URL base;
    
    if (args.length != 1) 
      {
	System.out.println("Folosire : JWget url");
	return;
      }
    
    if (!args[0].endsWith("\\")) args[0] = args[0] + "/";
    
    try
      { 
        base = new URL(args[0]); 
      }
    catch(MalformedURLException e)
      {
	System.out.println(e);
	return;
      }

    BufferedReader in = new BufferedReader( 
                            new InputStreamReader( 
                            base.openStream())); 

    String urlline; 

    while ((urlline = in.readLine()) != null)
      { 
	int index = 0;

        urlline = urlline.toLowerCase();
	//System.out.println(urlline);
	while (index != -1)
	  {
	    index = urlline.indexOf("<a href", index + 1);

	    if (index != -1)
	      {
		int index2 = urlline.indexOf("=", index+1);
		int index3 = urlline.indexOf(">", index+1);
		//System.out.println(index2 + " si " +  index3);
		String newurl = new String("");
		if ((index2 > 0) && (index3 >0)) 
		  {
		    newurl = urlline.substring(index2+1, index3-1);
		    if (newurl.startsWith("\"")) newurl = newurl.substring(1, newurl.length());

		    System.out.println("REFERINTA LA " + newurl);
	      
		    URL suburl;
		    
		    if (newurl.startsWith("http://"))
			{
			}
		    else
		      {
			if (newurl.endsWith(".html") || newurl.endsWith(".htm")) newurl = args[0] + newurl;
		      }
	       
		    try
		      {
			suburl = new URL(newurl); 
		      }
		    catch(MalformedURLException e)
		      {
			System.out.println(e);
			continue;
		      }

		    BufferedReader subin;
		    try
		      {
			subin = new BufferedReader( 
                                         new InputStreamReader( 
                                         suburl.openStream())); 
		      }
		    catch(IOException e)
		      {
			System.out.println(e);
			continue;
		      }

		    String subinputLine = new String(""); 

		    while ((subinputLine = subin.readLine()) != null) 
                        System.out.println(subinputLine); 

		    subin.close(); 
		  }
	      }
	  }
      }

    in.close(); 
   } 
}


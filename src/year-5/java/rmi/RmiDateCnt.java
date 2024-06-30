package examples.mydate;

import java.awt.*; 
import java.rmi.*; 

public class RmiDateCnt extends java.applet.Applet { 
  String message = ""; 
  public void init() 
  { 
    try 
    { 
      MyDate obj = (MyDate)Naming.lookup("//" + 
                   getCodeBase().getHost() + "/DateServer"); 
      message = obj.getDate(); 
    } 
    catch (Exception e) 
    { 
      System.out.println("RmiDateCnt exception: " + 
                          e.getMessage()); 
                          e.printStackTrace(); 
    } 
  } 
  public void paint(Graphics g) 
  { 
    Color rect_color = new Color(0, 0, 255);
    g.setColor(rect_color);
    FontMetrics fm = g.getFontMetrics();
    g.drawRect(10, 20 - fm.getHeight() - 2, 20 + fm.charsWidth(message.toCharArray(), 0, message.length()), 22);

    Color txt_color = new Color(255, 0, 0);
    g.setColor(txt_color);
    g.drawString(message, 20, 20); 
  } 
}





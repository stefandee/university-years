package examples.mydate;

import java.rmi.*; 
import java.rmi.server.UnicastRemoteObject; 
import java.util.*;

public class RmiDateSrv 
       extends UnicastRemoteObject 
       implements MyDate
{ 
  private String name; 

  public RmiDateSrv(String s) throws RemoteException 
  { 
    super(); 
    name = s; 
  } 

  public String getDate() throws RemoteException 
  { 
    Date today = new Date();
    return  today.toString(); 
  } 

  public static void main(String args[]) 
  { 
    // Create and install a security manager 
    System.setSecurityManager(new RMISecurityManager()); 

    try 
    { 
      RmiDateSrv obj = new RmiDateSrv("DateServer"); 
      Naming.rebind("//127.0.0.1/DateServer", obj); 
      System.out.println("DateServer bound in registry"); 
    } 
    catch (Exception e) 
    { 
      System.out.println("RmiDateSrv : " + e.getMessage()); 
      e.printStackTrace(); 
    } 
  } 
}

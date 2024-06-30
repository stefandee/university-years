package examples.mydate; 

public interface MyDate extends java.rmi.Remote 
{ 
  String getDate() throws java.rmi.RemoteException; 
}

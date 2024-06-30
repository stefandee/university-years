import java.lang.Thread;
class Filosofi
{
  public static void main(String args[]) 
  {
    Furculita Furc1 = new Furculita();
    Furculita Furc2 = new Furculita();
    Furculita Furc3 = new Furculita();
    Furculita Furc4 = new Furculita();
    Furculita Furc5 = new Furculita();

    new Filosof("SOCRATE", Furc1, Furc2).start(); 
    new Filosof("PITAGORA", Furc2, Furc3).start();
    new Filosof("ARISTOTEL", Furc3, Furc4).start();
    new Filosof("MARX", Furc4, Furc5).start();
    new Filosof("CIORAN", Furc5, Furc1).start();
   } 
} 
              
class Filosof extends Thread 
{ 
  int foamea;
  Furculita stinga;
  Furculita dreapta;

  public Filosof(String str, Furculita st, Furculita dr) 
  {
    super(str);
    foamea = 0;
    stinga = st;
    dreapta = dr;
  }

  public void run() 
  { 
    while(true)
    {
    System.out.println(getName() + " vrea acces la furculita");
    if (stinga.disponibila()) 
    {
      stinga.ia();
      if (dreapta.disponibila()) 
      {
        dreapta.ia();
        try
        {
          System.out.println(getName()+" maninca");
          sleep(1000);
	}
        catch(InterruptedException e)
	{
	}
        stinga.lasa();
        dreapta.lasa();
        try
        {
          System.out.println(getName()+" satul");
          sleep(1000);
	}
        catch(InterruptedException e)
        {
        }
      }
      else 
      {
        stinga.lasa();
        foamea++;
        if (foamea > 2) mort();
      } 
    }
    else
    {
      foamea++;
      if (foamea > 2) mort();
    }
    try
    {
      sleep(1000);
    }
    catch(InterruptedException e)
    {
    }
    } //while end
  } //end run 

  private void mort()
  {
    System.out.println(getName()+" a murit");
    stop();
  }
}// end class
 

class Furculita 
{ 
  private boolean available = true; 
                
  public synchronized void ia() 
  { 
    while (available == false) 
    { 
      try 
      { 
        wait();
      } 
      catch (InterruptedException e) 
      { 
      } 
    } 
    available = false; 
    notifyAll(); 
  } 

  public synchronized void lasa() 
  { 
    while (available == true)
    { 
      try 
      { 
        wait(); 
      } 
      catch (InterruptedException e) 
      { 
      } 
    } 
    available = true; 
  } 

  public boolean disponibila()
  {
    return available;
  }
}

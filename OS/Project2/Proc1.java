// Basil El-Hindi
// CS 4348.HON
// Project2
// Proc1.java

import java.net.*;
import java.io.*;
import java.util.*;
import java.util.concurrent.*;
import java.lang.*;

public class Proc1
{
	public static void main(String args[]) throws Exception
	{
		// Server Socket for Process 1 to host 2, 3, and 4 on port 5000
		ServerSocket ss = new ServerSocket(5000);
		System.out.println("Process 1 server is running...");
		// Stream objects to hold the endpoint of the connections
		// with each of the other processes
		DataInputStream dis2 = null;
		DataInputStream dis3 = null;
		DataInputStream dis4 = null;
		DataOutputStream dos2 = null;
		DataOutputStream dos3 = null;
		DataOutputStream dos4 = null;
		// Host each of the three other processes
		for(int i = 0; i < 3; i++)
		{
			Socket s = null;
			try
			{
				s = ss.accept();
				System.out.println("New client joined server 1: " + s);
				// Process 2 connection
				if(i == 0)
				{
					dis2 = new DataInputStream(s.getInputStream());
					dos2 = new DataOutputStream(s.getOutputStream());
				}
				// Process 3 connection
				if(i == 1)
				{
					dis3 = new DataInputStream(s.getInputStream());
					dos3 = new DataOutputStream(s.getOutputStream());
				}
				// Process 4 connection
				if(i == 2)
				{
					dis4 = new DataInputStream(s.getInputStream());
					dos4 = new DataOutputStream(s.getOutputStream());
				}
			}
			catch(Exception e)
			{
				s.close();
				e.printStackTrace();
			}
		}
		// Start 2 threads, one to send messages to other processes,
		// and one to receive incoming messages
		// The sender receives each of the output streams
		Thread sender = new Sender1(dos2, dos3, dos4);
		sender.start();

		// The receiver uses each of the input streams
		Thread receiver = new Receiver1(dis2, dis3, dis4);
		receiver.start();
		
		// Wait for all processes to be stopped
		sender.join();
		receiver.join();

		// Close every socket connection and safely exit
		try
		{
			ss.close();
			dis2.close();
			dis3.close();
			dis4.close();
			dos2.close();
			dos3.close();
			dos4.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}

class Sender1 extends Thread
{
	final DataOutputStream dos2;
	final DataOutputStream dos3;
	final DataOutputStream dos4;

	// Initialize output streams to each other processs
	public Sender1(DataOutputStream dos2, DataOutputStream dos3, DataOutputStream dos4)
	{
		this.dos2 = dos2;
		this.dos3 = dos3;
		this.dos4 = dos4;
	}

	// Overriding Thread class run method
	public void run()
	{
		// Read keyboard input until this process issues the stop command
		Scanner scanner = new Scanner(System.in);
		String line = scanner.nextLine();
		while(!line.equals("stop"))
		{
			// Parse the commands and determine where to send the messages
			String[] subs = line.split(" ");
			if(subs[0].equals("send"))
			{
				if(Integer.parseInt(subs[1]) == 0)
				{
					send(subs[2], dos2);
					send(subs[2], dos3);
					send(subs[2], dos4);
				}
				if(Integer.parseInt(subs[1]) == 2)
				{
					send(subs[2], dos2);	
				}
				if(Integer.parseInt(subs[1]) == 3)
				{
					send(subs[2], dos3);	
				}
				if(Integer.parseInt(subs[1]) == 4)
				{
					send(subs[2], dos4);		
				}
			}
			line = scanner.nextLine();
		}
		// Send the stop message to each other process
		send("stop", dos2);
		send("stop", dos3);
		send("stop", dos4);
	}

	// Method to send message to each other process as stream
	public void send(String message, DataOutputStream dos)
	{
		try
		{
			dos.writeUTF(message);
			dos.flush();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}

class Receiver1 extends Thread
{
	final DataInputStream dis2;
	final DataInputStream dis3;
	final DataInputStream dis4;

	// Initialize input streams from each other process 
	public Receiver1(DataInputStream dis2, DataInputStream dis3, DataInputStream dis4)
	{
		this.dis2 = dis2;
		this.dis3 = dis3;
		this.dis4 = dis4;
	}

	// Overwriting Thread class run method
	public void run()
	{
		boolean blocked = false;
		boolean block[] = new boolean[3];
		String line = "";
		// Wrap in try-catch to read properly
		try
		{
			// While all the processes aren't blocked
			while(!blocked)
			{
				// Only read from a process while it is not stopped
				if(!block[0])
				{
					// Check if there are bytes to read
					if(dis2.available() > 0)
					{
						// Output the lines to this process's terminal
						line = dis2.readUTF();
						System.out.println(line);
						// If the stop message is received, this process is blocked
						if(line.equals("stop"))
						{
							block[0] = true;
						}
					}
				}
				if(!block[1])
				{
					if(dis3.available() > 0) 
					{
						line = dis3.readUTF();
						System.out.println(line);
						if(line.equals("stop"))
						{
							block[1] = true;
						}
					}
				}
				if(!block[2])
				{
					if(dis4.available() > 0) 
					{
						line = dis4.readUTF();
						System.out.println(line);
						if(line.equals("stop"))
						{
							block[2] = true;
						}
					}
				}
				// Blocked is set to the AND of each process
				// Will be stopped when each process is stopped
				blocked = block[0] && block[1] && block[2];
			}
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}

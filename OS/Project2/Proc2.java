// Basil El-Hindi
// CS 4348.HON
// Project2
// Proc2.java

import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.lang.*;
import java.util.*;

public class Proc2
{
	public static void main(String args[]) throws Exception
	{
		// Stream objects to hold connections endpoints
		DataInputStream dis1 = null;
		DataInputStream dis3 = null;
		DataInputStream dis4 = null;
		DataOutputStream dos1 = null;
		DataOutputStream dos3 = null;
		DataOutputStream dos4 = null;
		// Process 1 connection on port 5000 with command line
		// argument of IP address of process 1's machine
		try
		{
			Socket socket1 = new Socket(args[0], 5000);
			dis1 = new DataInputStream(socket1.getInputStream());
			dos1 = new DataOutputStream(socket1.getOutputStream());
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		// Host server for processes 3 and 4 to connect on port 5001
		ServerSocket ss = new ServerSocket(5001);
		System.out.println("Process 2 server is running...");
		for(int i = 0; i < 2; i++)
		{
			Socket s = null;
			try
			{
				s = ss.accept();
				System.out.println("New client joined server 2: " + s);
				// Process 3 connection
				if(i == 0)
				{
					dis3 = new DataInputStream(s.getInputStream());
					dos3 = new DataOutputStream(s.getOutputStream());
				}
				// Process 4 connection
				if(i == 1)
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
		// The sender uses each of the output streams
		Thread sender = new Sender2(dos1, dos3, dos4);
		sender.start();

		// The receiver uses each of the input streams
		Thread receiver = new Receiver2(dis1, dis3, dis4);
		receiver.start();

		// Wait for all processes to be stoppped
		sender.join();
		receiver.join();

		// Close every socket connection and safely exit
		try
		{
			ss.close();
			dis1.close();
			dis3.close();
			dis4.close();
			dos1.close();
			dos3.close();
			dos4.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}

class Sender2 extends Thread
{
	final DataOutputStream dos1;
	final DataOutputStream dos3;
	final DataOutputStream dos4;

	// Initialize with the output streams to each other process
	public Sender2(DataOutputStream dos1, DataOutputStream dos3, DataOutputStream dos4)
	{
		this.dos1 = dos1;
		this.dos3 = dos3;
		this.dos4 = dos4;
	}
	
	// Overwriting Thread class run method
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
					send(subs[2], dos1);
					send(subs[2], dos3);
					send(subs[2], dos4);
				}
				if(Integer.parseInt(subs[1]) == 1)
				{
					send(subs[2], dos1);
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
		send("stop", dos1);
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

class Receiver2 extends Thread
{
	final DataInputStream dis1;
	final DataInputStream dis3;
	final DataInputStream dis4;

	// Initialize with input streams from each other process
	public Receiver2(DataInputStream dis1, DataInputStream dis3, DataInputStream dis4)
	{
		this.dis1 = dis1;
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
			// While all the processes aren't stopped
			while(!blocked)
			{
				// Only read from a process while it is not stopped
				if(!block[0])
				{
					// Check if there are bytes to read
					if(dis1.available() > 0)
					{
						// Read and output the lines to this process's terminal
						line = dis1.readUTF();
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
				// Blocked is set to the bitwise AND of each process
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

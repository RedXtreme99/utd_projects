// Basil El-Hindi
// CS 4348.HON
// Project2
// Proc3.java

import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.lang.*;
import java.util.*;

public class Proc3
{
	public static void main(String args[]) throws Exception
	{
		// Stream objects to hold connection endpoints
		DataInputStream dis1 = null;
		DataInputStream dis2 = null;
		DataInputStream dis4 = null;
		DataOutputStream dos1 = null;
		DataOutputStream dos2 = null;
		DataOutputStream dos4 = null;
		
		// Process 1 connection on port 5000 with command line IP address
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

		// Process 2 connection on port 5001 with command line IP address
		try
		{
			Socket socket2 = new Socket(args[1], 5001);
			dis2 = new DataInputStream(socket2.getInputStream());
			dos2 = new DataOutputStream(socket2.getOutputStream());
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		// Host server for process 4 to connect on port 5002
		ServerSocket ss = new ServerSocket(5002);
		System.out.println("Process 3 server is running...");
		// Process 4 connection
		Socket s = null;
		try
		{
			s = ss.accept();
			System.out.println("New client joined server 3: " + s);
			dis4 = new DataInputStream(s.getInputStream());
			dos4 = new DataOutputStream(s.getOutputStream());
		}
		catch(Exception e)
		{
			s.close();
			e.printStackTrace();
		}

		// Start 2 threads, one to send messages to other processes,
		// and one to receive incoming messages
		// The sender uses each of the output streams
		Thread sender = new Sender3(dos1, dos2, dos4);
		sender.start();

		// The receiver uses each of the input streams
		Thread receiver = new Receiver3(dis1, dis2, dis4);
		receiver.start();

		// Wait for all processes to be stopped
		sender.join();
		receiver.join();

		// Close every socket connection and safely exit
		try
		{
			ss.close();
			dis1.close();
			dis2.close();
			dis4.close();
			dos1.close();
			dos2.close();
			dos4.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}

class Sender3 extends Thread
{
	final DataOutputStream dos1;
	final DataOutputStream dos2;
	final DataOutputStream dos4;

	// Initialize with output stream of each other process
	public Sender3(DataOutputStream dos1, DataOutputStream dos2, DataOutputStream dos4)
	{
		this.dos1 = dos1;
		this.dos2 = dos2;
		this.dos4 = dos4;
	}

	// Overwriting default Thread class run method
	public void run()
	{
		// Read keyboard input until the stop command is issued
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
					send(subs[2], dos2);
					send(subs[2], dos4);
				}
				if(Integer.parseInt(subs[1]) == 1)
				{
					send(subs[2], dos1);
				}
				if(Integer.parseInt(subs[1]) == 2)
				{
					send(subs[2], dos2);
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
		send("stop", dos2);
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

class Receiver3 extends Thread
{
	final DataInputStream dis1;
	final DataInputStream dis2;
	final DataInputStream dis4;

	// Initialize with input stream from each other process
	public Receiver3(DataInputStream dis1, DataInputStream dis2, DataInputStream dis4)
	{
		this.dis1 = dis1;
		this.dis2 = dis2;
		this.dis4 = dis4;
	}

	// Overwriting the Thread class default run method
	public void run()
	{
		boolean blocked = false;
		boolean block[] = new boolean[3];
		String line = "";
		try
		{
			// While all the processes are not stopped
			while(!blocked)
			{
				// Only read from a process if it is not stopped
				if(!block[0])
				{
					// Check if there are any available bytes to read
					if(dis1.available() > 0)
					{
						// Read and output the lines to this process's terminal
						line = dis1.readUTF();
						System.out.println(line);
						// If the stop command is received mark this input as stopped
						if(line.equals("stop"))
						{
							block[0] = true;
						}
					}
				}
				if(!block[1])
				{
					if(dis2.available() > 0)
					{
						line = dis2.readUTF();
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
				// Will be stopped when all the processes are stopped
				blocked = block[0] && block[1] && block[2];
			}
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}

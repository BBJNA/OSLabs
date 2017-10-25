package haikuServer;

import java.net.*;
import java.util.*;
import java.io.*;

public class Server {
	private static ServerSocket sock;
	public static String Haiku() {
		String[] haiku = new String[3];
		haiku[0] = "The snow blankets all" + "\n" + "Transforming to still beauty" + "\n" + "Dazzling purity.";
		haiku[1] = "I see the busy streets" + "\n" + "Littered with scraps of human souls" + "\n" + "Floating idolent";
		haiku[2] = "A bird fly so high" + "\n" + "Singing a melodic song" + "\n" + "What a peaceful day";
		
		Random x = new Random();
		int i = x.nextInt(3);
		return haiku[i];
		
	}
	public static void main(String[] args) {
		try {
			sock = new ServerSocket(5575);
			
			//Listens for connections
			while(true) {
				Socket client = sock.accept();
				
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				
				//Write the haiku to the socket
				pout.println(Haiku());
				
				//Close the socket and resume listening for connections
				client.close();
				
			}
		}
		catch(IOException ioe) {
			System.err.println(ioe);
		}
	}
}

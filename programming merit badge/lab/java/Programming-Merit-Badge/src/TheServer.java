import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

/**
 * A TCP server that runs on port 8080.  When a client connects, it
 * sends the client the current date and time, then closes the
 * connection with that client.  Arguably just about the simplest
 * server you can write.
 */

public class TheServer {
	
	public static void main(String[] args) {
	
		try {
			ServerSocket listener = new ServerSocket(8080);
	        try {
	            while (true) {
	                Socket socket = listener.accept();
	                try {
	                    PrintWriter out =
	                        new PrintWriter(socket.getOutputStream(), true);
	                    
	                    out.println(new Date().toString());
	                } finally {
	                    socket.close();
	                }
	            }
	        }
	        finally {
	            listener.close();
	        }		
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
}

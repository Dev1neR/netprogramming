import java.io.*;
import java.net.*;
import java.util.*;
class SimpleThreadServer {
	public static void main(String[] args) {
		ServerSocket servSocket = null;
		PrintStream ps = null;
		int port = 8071;
		try {
			System.out.println("Initialize...");
			servSocket = new ServerSocket(port);
			System.out.println("Waiting incomming connections");
			while (true){
				Socket s = servSocket.accept();
				System.out.println("["+s.getInetAddress().getHostName()+
				"] connected");
				ServerThread srvThread = new ServerThread(s);
				srvThread.start();
			}
		} catch (Exception e) {
			System.err.println(e);
		}
		finally{
			try {
				servSocket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}

class ServerThread extends Thread {
	private PrintStream psr = null;
	private BufferedReader isr = null;
	private InetAddress inetAddr = null;
	public ServerThread(Socket s) throws IOException {
	psr = new PrintStream(s.getOutputStream());
	isr = new BufferedReader(
	new InputStreamReader(s.getInputStream()));
	inetAddr = s.getInetAddress();
	}
	public void disconnect() {
		try {
			System.out.println(inetAddr.getHostName()+
			" disconnected");
			psr.close();
			isr.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		finally{
			this.interrupt();
		}
	}
	public void run (){
		int i=0;
		String str=null;
		try {
			while ((isr.readLine())!=null){
			if ("PING".equalsIgnoreCase(str))
				psr.println("Server Date: " + (new Date()).toString() + "\n");
				System.out.println("PING-PONG"+i+
 " with"+inetAddr.getHostName());
			}
		} catch (IOException e) {
			System.out.println("Disconnect");
		}
		finally{
			disconnect();
		}
	}
}

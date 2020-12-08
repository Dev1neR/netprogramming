import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;

public class SimpleServer {
    public static void main(String[] args) {
        Socket s = null;
        ServerSocket servSocket = null;
        PrintStream ps = null;
        int port = 8030;
        try {
            servSocket = new ServerSocket(port);
            s = servSocket.accept();
            System.out.println("Підключився клієнт [" + s.getInetAddress() + "]");
            ps = new PrintStream(s.getOutputStream());
            ps.println("Привіт");
            ps.flush();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            ps.close();
            try {
                s.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
            try {
                servSocket.close();
            } catch (IOException e2) {
                e2.printStackTrace();
            }
        }
    }
}

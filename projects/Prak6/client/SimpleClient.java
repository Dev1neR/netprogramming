import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class SimpleClient {
    public static void main(String[] args) {
        Socket s = null;
        InputStreamReader isr = null;
        BufferedReader bufferedReader = null;
        String serverAddr = "localhost";
        int port = 8030;
        try {
            s = new Socket(serverAddr,port);
            isr = new InputStreamReader(s.getInputStream());
            bufferedReader = new BufferedReader(isr);
            String msg = bufferedReader.readLine();
            System.out.println("Повідомлення: " + msg);
        } catch (IOException e) {
            e.printStackTrace();
        } finally{
            try {
                bufferedReader.close();
                isr.close();
                s.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
    }
}

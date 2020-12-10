import java.io.PrintStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.*;

public class SimpleClient {
    public static void main(String[] args) {
        Socket s = null;
        InputStreamReader isr = null;
        BufferedReader bufferedReader = null;
		PrintStream ps = null;
        String serverAddr = "localhost";
        int port = 8030;
        try {
            s = new Socket(serverAddr,port);
            isr = new InputStreamReader(s.getInputStream());
			ps = new PrintStream(s.getOutputStream());
            bufferedReader = new BufferedReader(isr);
			Scanner sc= new Scanner(System.in);
			System.out.print("Enter a string: ");  
			String str= sc.nextLine();
			ps.println(str);
			ps.flush();
            String msg = bufferedReader.readLine();
            System.out.println(msg);
        } catch (IOException e) {
            e.printStackTrace();
        } finally{
			ps.close();
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

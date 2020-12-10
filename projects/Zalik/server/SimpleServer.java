import java.io.IOException;
import java.io.PrintStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;
import java.util.Comparator;

public class SimpleServer {
	public static int countWords(String s){

    int wordCount = 0;

    boolean word = false;
    int endOfLine = s.length() - 1;

    for (int i = 0; i < s.length(); i++) {
        if (Character.isLetter(s.charAt(i)) || Character.isDigit(s.charAt(i))  && i != endOfLine) {
            word = true;
        } else if (!Character.isLetter(s.charAt(i)) || !Character.isDigit(s.charAt(i)) && word) {
            wordCount++;
            word = false;
        } else if (Character.isLetter(s.charAt(i)) || Character.isDigit(s.charAt(i)) && i == endOfLine) {
            wordCount++;
        }
    }
    return wordCount;
}
	
    public static void main(String[] args) {
        Socket s = null;
        ServerSocket servSocket = null;
        PrintStream ps = null;
		BufferedReader bufferedReader = null;
		InputStreamReader isr = null;
        int port = 8030;
        try {
            servSocket = new ServerSocket(port);
            s = servSocket.accept();
			isr = new InputStreamReader(s.getInputStream());
            ps = new PrintStream(s.getOutputStream());
			bufferedReader = new BufferedReader(isr);
            System.out.println("Client connected [" + s.getInetAddress() + "]");
			String msg = bufferedReader.readLine();
			int wordsInString = countWords(msg);
			String longest = Arrays.stream(msg.split(" ")).max(Comparator.comparingInt(String::length)).orElse(null);
            ps.println("You entered: " + wordsInString + " words. Your longest word is: " + longest);
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

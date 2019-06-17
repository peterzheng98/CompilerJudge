package internet;

import utility.IPAddress;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class SocketClient {
    private Socket socket = null;
    private IPAddress ipAddress = null;
    private int ipPort = 0;

    public SocketClient(IPAddress ipAddress, int ipPort) {
        this.ipAddress = ipAddress;
        this.ipPort = ipPort;
    }

    public String sendAndReceive(String seqStr){
        assert ipAddress != null;
        try {
            socket = new Socket(ipAddress.toString(), ipPort);
            InputStream is = socket.getInputStream();
            OutputStream os = socket.getOutputStream();

            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(os));
            bw.write(seqStr);

            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            String ret = "";
            String res = "";
            while((ret = br.readLine()) != null)
                res = res + ret;
            return res;
        } catch (IOException e){
            e.printStackTrace();
        }
        return null;
    }
}

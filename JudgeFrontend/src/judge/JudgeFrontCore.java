package judge;


import internet.SocketClient;

import java.util.ArrayList;

public class JudgeFrontCore {
    private ArrayList<Process> processPool = new ArrayList<>();
    private static SocketClient socketClient = null;
    private ArrayList<String> logEntry = new ArrayList<>();
    private ArrayList<JudgeRecord> judgingQueue = new ArrayList<>();
    public JudgeFrontCore() {
        socketClient = new SocketClient(LoadConfig.getConfig_ipAddress(), LoadConfig.getConfig_port());
    }

    public void run() {
        assert socketClient != null;
        // Update Strategy of docker
        /*
        * Not sure how to describe this part
        * Maybe: check the SHA-1 of the local repo with remote repo,
        * If the SHA-1 hit, then push into judging queue
        *
        * */
    }
}

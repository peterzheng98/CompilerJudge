package judge;

public class JudgeRecord {
    public String repoSHA1 = "";
    public String repoURL = "";
    public String username = "";
    public int stage = 0;
    public int testcase = 0;

    public JudgeRecord(String repoSHA1, String repoURL, String username, int stage, int testcase) {
        this.repoSHA1 = repoSHA1;
        this.repoURL = repoURL;
        this.username = username;
        this.stage = stage;
        this.testcase = testcase;
    }
}

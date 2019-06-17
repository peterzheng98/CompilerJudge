package judge;

public class Main {

    public static void main(String[] args) {
	// write your code here
        LoadConfig loadConfig = new LoadConfig("/Users/peterzheng/Documents/Project/Compiler/CompilerJudge/JudgeFrontend/Sample/initSample.json");
        JudgeFrontCore judgeFrontCore = new JudgeFrontCore();
        judgeFrontCore.run();
    }
}

package judge;


import utility.IPAddress;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonObject;
import javax.json.JsonReader;
import javax.json.JsonValue;
import java.io.*;
import java.util.ArrayList;

public class LoadConfig {
    private String fileName = "";
    private static IPAddress config_ipAddress = null;
    private static int config_port = 0;


    private static int config_update_freq = 0;
    private static ArrayList<Short> config_update_time = new ArrayList<>();
    private static int config_thread_count = 0;
    private static String config_judge_name = "";

    private String jsonData = "";
    private File __fileStream = null;
    private FileReader __fileStreamReader = null;

    public LoadConfig(String fileName) {
        // Load file
        this.fileName = fileName;
        try {
            __fileStream = new File(fileName);
            __fileStreamReader = new FileReader(__fileStream);
            Reader __fileReader = new InputStreamReader(new FileInputStream(__fileStream), "utf-8");
            int ch = 0;
            StringBuffer sb = new StringBuffer();
            while ((ch = __fileReader.read()) != -1) {
                sb.append((char) ch);
            }
            __fileStreamReader.close();
            __fileReader.close();
            jsonData = sb.toString();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Load JSON File and dispatch the data
        JsonReader reader = Json.createReader(new StringReader(jsonData));
        JsonObject object = reader.readObject();
        reader.close();
        JsonObject jsonHost = object.getJsonObject("host");
        JsonObject jsonUpdate = object.getJsonObject("update");
        config_thread_count = object.getInt("thread_count");
        config_judge_name = object.getString("judge_name");
        config_ipAddress = new IPAddress(jsonHost.getString("address"));
        config_port = jsonHost.getInt("port");
        config_update_freq = jsonUpdate.getInt("freq");
        // Maybe error here -> getInt(i) means get the i-th index of the JSON Array
        for (int i = 0; i < config_update_freq; ++i)
            config_update_time.add((short) jsonUpdate.getJsonArray("time").getInt(i));

    }

    public static IPAddress getConfig_ipAddress() {
        return config_ipAddress;
    }

    public static int getConfig_port() {
        return config_port;
    }

    public static int getConfig_update_freq() {
        return config_update_freq;
    }

    public static ArrayList<Short> getConfig_update_time() {
        return config_update_time;
    }

    public static int getConfig_thread_count() {
        return config_thread_count;
    }

    public static String getConfig_judge_name() {
        return config_judge_name;
    }
}

package utility;



public class IPAddress {
    private short d1, d2, d3, d4;

    public IPAddress(String ipaddr){
        int cnt = 0;
        for(String sub: ipaddr.split(".")){
            if(cnt == 0) d1 = (short)Integer.parseInt(sub);
            if(cnt == 1) d2 = (short)Integer.parseInt(sub);
            if(cnt == 2) d3 = (short)Integer.parseInt(sub);
            if(cnt == 3) d4 = (short)Integer.parseInt(sub);
            cnt++;
        }
    }

    public IPAddress(int d1, int d2, int d3, int d4) {
        this.d1 = (short)d1;
        this.d2 = (short)d2;
        this.d3 = (short)d3;
        this.d4 = (short)d4;
    }

    @Override
    public String toString() {
        return d1 + "." + d2 + "." + d3 + "." + d4;
    }
}

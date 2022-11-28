package main.graphic;

import main.util.*;
import jssc.*;

public class Main {
	  public static void main(String[] args) throws Exception {
		  	String[] portNames = SerialPortList.getPortNames();
		  	for (int i = 0; i < portNames.length; i++){
			    System.out.println(portNames[i]);
			}
			SerialCommChannel channel = new SerialCommChannel(portNames[1],9600);
			System.out.println("Waiting Arduino for rebooting...");		
			Thread.sleep(4000);
			System.out.println("Ready.");	

			String waterLevel = channel.receiveMsg();
	        ChartFrame demo = new ChartFrame("Smart Bridge", "Water Level Chart", waterLevel);
		  	demo.pack();
	        demo.setVisible(true);
	        String msg;
	        Double wl = 100.0;
			while(true){
				//Thread.sleep(2000);
				msg = channel.receiveMsg();
				System.out.println(msg);
				if(msg.substring(0, 5).equals("LIGHT SYSTEM")) {
					System.out.println("LIGHTS: "+msg.substring(6));
				}else if(msg.substring(0, 5).equals("WATLV")) {
					System.out.println("WATER LEVEL: "+msg.substring(6));
				}else if(msg.substring(0, 5).equals("DISTA")) {
					demo.updateChart(String.valueOf(wl -  Math.min(Double.parseDouble(msg.substring(6)), 100.0) ));
				}
			}
	    }
}

package main.graphic;

import main.util.*;

public class Main {
	  public static void main(String[] args) throws Exception {
			SerialCommChannel channel = new SerialCommChannel(args[0],9600);
			System.out.println("Waiting Arduino for rebooting...");		
			Thread.sleep(4000);
			System.out.println("Ready.");	

			String waterLevel = channel.receiveMsg();
	        ChartFrame demo = new ChartFrame("Smart Bridge", "Water Level Chart", waterLevel);
		  	demo.pack();
	        demo.setVisible(true);
			while(true){
				Thread.sleep(2000);
				waterLevel = channel.receiveMsg();
				demo.updateChart(waterLevel);
			}
	    }
}

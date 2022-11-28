package main.graphic;

import java.sql.Timestamp;
import java.time.Instant;

import javax.swing.JFrame;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.DefaultXYDataset;
import org.jfree.data.xy.XYDataset;

public class ChartFrame extends JFrame {

	private static final long serialVersionUID = 1L;

    private DefaultXYDataset result = new DefaultXYDataset();
    private double data[][];
    private int counter;
    private Timestamp inst = Timestamp.from(Instant.now());

	public ChartFrame(String applicationTitle, String chartTitle, String waterlLevel) {
        super(applicationTitle);
        // based on the dataset we create the chart
        JFreeChart chart = createChart(createDataset(waterlLevel), chartTitle);
        // we put the chart into a panel
        ChartPanel chartPanel = new ChartPanel(chart);
        // default size
        chartPanel.setPreferredSize(new java.awt.Dimension(1200, 800));
        // add it to our application
        this.setContentPane(chartPanel);
    }

    public void updateChart(String waterLevel){
        double newData[][] = new double[this.data.length][counter+1];
        for(int i = 0; i < counter; i++){
            newData[0][i] = this.data[0][i];
            newData[1][i] = this.data[1][i];
        }
        newData[0][counter] = Timestamp.from(Instant.now()).getTime() - inst.getTime();
        newData[1][counter] = Double.parseDouble(waterLevel);
        this.result.removeSeries("Water Level (0m-100m) in ms");
        this.data = newData;
        this.result.addSeries("Water Level (0m-100m) in ms", data);
        counter++;
    }

	private XYDataset createDataset(String waterLevel) {
        this.data = new double[][]{{0}, {Double.parseDouble(waterLevel)}};
		this.result.addSeries("Water Level (0m-100m) in ms", data);
        counter = 0;
		return this.result;
	}

	private JFreeChart createChart(XYDataset dataset, String title) {

        JFreeChart chart = ChartFactory.createXYLineChart(
            title,                  // chart title
            "time", "water level",  //x and y axis name
            dataset                 // data
        );
        return chart;

    }
}

package main.graphic;

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

	public ChartFrame(String applicationTitle, String chartTitle, String waterlLevel) {
        super(applicationTitle);
        // based on the dataset we create the chart
        JFreeChart chart = createChart(createDataset(waterlLevel), chartTitle);
        // we put the chart into a panel
        ChartPanel chartPanel = new ChartPanel(chart);
        // default size
        chartPanel.setPreferredSize(new java.awt.Dimension(500, 270));
        // add it to our application
        this.setContentPane(chartPanel);
    }

    public void updateChart(String waterLevel){
        counter++;
        double newData[][] = new double[this.data.length][counter];
        for(int i = 0; i < counter - 1; i++){
            newData[0][i] = this.data[0][i];
            newData[1][i] = this.data[1][i];
        }
        newData[0][counter - 1] = counter + 1.0;
        newData[1][counter - 1] = Double.parseDouble(waterLevel);
        this.result.removeSeries("");
        this.data = newData;
        this.result.addSeries("", data);
    }

	private XYDataset createDataset(String waterLevel) {
        this.data = new double[][]{{0}, {Double.parseDouble(waterLevel)}};
		this.result.addSeries("", data);
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

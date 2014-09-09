package gmd;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

class DownloadData
{
	final long time;
	final long distance;
	
	final String desc1;
	final String desc2;
	
	DownloadData()
	{
		time = -1;
		distance = -1;
		desc1 = "Error";
		desc2 = "Error";
	}
	
	DownloadData(String time, String distance, String desc1, String desc2) {
		this.time = stringToDuration(time);
		this.distance = stringToDistance(distance);
		this.desc1 = desc1;
		this.desc2 = desc2;
	}
	
	static long stringToDuration(String time)
	{
		try (PrintStream ps = new PrintStream(new FileOutputStream ("log.txt", true)))
		{
			ps.println(time);
		} catch (FileNotFoundException e) {}
		return 0;
	}

	static long stringToDistance(String dist)
	{
		try (PrintStream ps = new PrintStream(new FileOutputStream ("log.txt", true)))
		{
			ps.println(dist);
		} catch (FileNotFoundException e) {}
		return 0;
	}
}

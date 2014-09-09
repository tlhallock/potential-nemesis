package gmd;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class DownloadData
{
	final double time;
	final double distance;
	
	final String desc1;
	final String desc2;
	
	boolean valid = true;
	
	static final Pattern MILES_PATTERN = Pattern.compile("([0-9.]*) miles");
	static final Pattern MINUTES_PATTERN = Pattern.compile("([0-9.]*) min");
	static final Pattern HOURS_PATTERN = Pattern.compile("([0-9]*) h ([0-9.]*) min");
	
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
	
	boolean isValid()
	{
		return valid;
	}
	
	double stringToDuration(String time)
	{
		try (PrintStream ps = new PrintStream(new FileOutputStream ("log.txt", true)))
		{
			ps.println(time);
		} catch (FileNotFoundException e) {}
		

		Matcher m = HOURS_PATTERN.matcher(time);
		if (m.matches())
		{
			double hours = new Double(m.group(1));
			double min = new Double(m.group(2));
			return hours * 60 * 60 + min * 60;
		}

		m = MINUTES_PATTERN.matcher(time);
		if (m.matches())
		{
			double min = new Double(m.group(1));
			return min * 60;
		}

		valid = false;
		System.out.println("Do not know how to parse: " + time);
		
		return 0;
	}

	double stringToDistance(String dist)
	{
		try (PrintStream ps = new PrintStream(new FileOutputStream ("log.txt", true)))
		{
			ps.println(dist);
		} catch (FileNotFoundException e) {}
		
		Matcher m = MILES_PATTERN.matcher(dist);
		if (m.matches())
		{
			return miles_to_meters(new Double(m.group(1)));
		}
		
		valid = false;
		System.out.println("Do not know how to parse: " + dist);
		
		return 0;
	}
	
	public String toString()
	{
		return "t=[" + time + "] d=[" + distance + "] d1=[" + desc1 + "] d2=[" + desc2 + "] v=[" + valid + "]";
	}
	
	static double miles_to_meters(double d)
	{
		return 1609.34 * d;
	}
}

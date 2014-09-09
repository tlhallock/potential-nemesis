package gmd;

import java.io.FileNotFoundException;
import java.io.PrintStream;

final class CostMatrix
{
	final Coord[] coords;
	final double[][] distances, durations;
	
	CostMatrix(Coord[] cs) { coords = cs; distances = new double[cs.length][cs.length]; durations = new double[cs.length][cs.length]; }
	
	void download()
	{
		for (int i = 0; i < coords.length; i++)
		{
			for (int j = 0; j < coords.length; j++)
			{
				if (i != j)
				{
					System.out.println(i + "/" + coords.length + ", " + j + "/" + coords.length);
					download(i, j);
				}
			}
		}
	}
	
	void download(int i, int j)
	{
		DownloadData downloadedSite = Downloader.rdownload(coords[i], coords[j]);
		distances[i][j] = downloadedSite.distance;
		durations[i][j] = downloadedSite.time;
		if (coords[i].desc == null && !downloadedSite.desc1.equals("Error"))
		{
			coords[i].desc = downloadedSite.desc1;
		}
		if (coords[j].desc == null && !downloadedSite.desc2.equals("Error"))
		{
			coords[j].desc = downloadedSite.desc2;
		}
	}
	
	void save(String filename) throws FileNotFoundException {
		try (PrintStream out = new PrintStream(filename))
		{
			out.println(coords.length);
			for (int i = 0; i < coords.length; i++)
			{
				out.println(i + "\t" + coords[i].x + "\t" + coords[i].y + "\t'" + coords[i].desc + "'");
			}
			
			for (int i = 0; i < coords.length; i++)
			{
				for (int j = 0; j < coords.length; j++)
				{
					String str = i + "\t" + j + "\t" + durations[i][j] + "\t" + distances[i][j];
					System.out.println(str);
					out.println(str);
				}
			}
		}
	}
}
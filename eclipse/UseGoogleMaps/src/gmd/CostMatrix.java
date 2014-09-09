package gmd;

final class CostMatrix
{
	final Coord[] coords;
	final long[][] distances, durations;
	
	CostMatrix(Coord[] cs) { coords = cs; distances = new long[cs.length][cs.length]; durations = new long[cs.length][cs.length]; }
	
	void download()
	{
		for (int i = 0; i < coords.length; i++)
		{
			for (int j = 0; j < coords.length; j++)
			{
				if (i != j)
				{
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
	
	void save(String filename)
	{
		for (int i = 0; i < coords.length; i++)
		{
			for (int j = 0; j < coords.length; j++)
			{
				System.out.println(i + ", " + j + "\t" + durations[i][j] + "\t" + distances[i][j]);
			}
		}
	}
}
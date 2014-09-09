package gmd;

import java.awt.MouseInfo;
import java.util.Timer;
import java.util.TimerTask;

public class Main
{
	static final boolean test = false;
	
	static Coord[] createCoords(int num)
	{
		Coord[] ret = new Coord[num];
		for (int i = 0; i < num; i++)
		{
			ret[i] = new Coord();
		}
		return ret;
	}
	
	public static void main(String[] args)
	{
		if (test)
		{
			new Timer().scheduleAtFixedRate(new TimerTask() {

				@Override
				public void run()
				{
					System.out.println(MouseInfo.getPointerInfo().getLocation());
				}}, 500, 500);
		}
		else
		{
			double timePerDownload = 20;
			double desiredTime = 30 * 60;
			int size = (int) Math.sqrt(2 * desiredTime / timePerDownload);
			System.out.println("Size = " + size);
			for (int i = 0;; i++)
			{
				CostMatrix c = new CostMatrix(createCoords(size));
				c.download();
				c.save("output." + System.currentTimeMillis() + "." + i + ".txt");
			}
		}
	}
}

package gmd;

import java.awt.AWTException;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.Robot;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

final class Downloader
{
	
//	static final Point loc1     = new Point(100, 160);
//	static final Point loc2     = new Point(100, 200);
//	static final Point search   = new Point(460, 124);
//	static final Point time     = new Point(381, 272);
//	static final Point distance = new Point(384, 304);

	static final Point loc1     = new Point(153, 201);
	static final Point loc2     = new Point(149, 240);
	static final Point search   = new Point(524, 159);
	static final Point time     = new Point(435, 330);
	static final Point distance = new Point(430, 354);
	
	
	static final Robot robot = createRobot();
	static Robot createRobot() {
		try
		{
			Robot r = new Robot();
			r.delay(10);
			return r;
		}
		catch (AWTException e)
		{
			e.printStackTrace();
			System.exit(-1);
			return null;
		}
	}
	
	static Point lastMouseInfo;
	static void moveDaMouse(Point p) throws InterruptedException
	{
		if (lastMouseInfo != null 
				&& !MouseInfo.getPointerInfo().getLocation().equals(lastMouseInfo))
		{
			System.out.println("Someone moved the mouse!!!!");
			System.exit(0);
		}
		
		robot.mouseMove(p.x, p.y);
		Thread.sleep(500);
		lastMouseInfo = MouseInfo.getPointerInfo().getLocation();
	}
	
	static DownloadData rdownload(Coord c1, Coord c2)
	{
		long s = System.currentTimeMillis();
		
		for (int i=0; i<3; i++)
		{
			try (PrintStream ps = new PrintStream(new FileOutputStream ("downloadedInfo.txt", true)))
			{
				String str = "Trying to download " + c1.x + "," + c1.y + "\t" + c2.x + "," + c2.y;
				ps.println(str);
				System.out.println(str);
			} catch (FileNotFoundException e) {}
			
			try 
			{
				type(loc1, c1.x + "," + c1.y);
				type(loc2, c2.x + "," + c2.y);
	
				robot.setAutoDelay(100);
				Thread.sleep(1000);
				moveDaMouse(search);
				robot.mousePress(MouseEvent.BUTTON1_MASK);
				robot.mouseRelease(MouseEvent.BUTTON1_MASK);
				
				// zoom animation
				Thread.sleep(2000);
	
				String desc1 = getStringAt(loc1);
				String desc2 = getStringAt(loc2);
				
				String distString =  getStringAt(distance);
				String timeString =  getStringAt(time);

				DownloadData ret = new DownloadData(timeString, distString, desc1, desc2);
				
				try (PrintStream ps = new PrintStream(new FileOutputStream ("downloadedInfo.txt", true)))
				{
					ps.println(ret);
					System.out.println(ret);
					ps.println("=============================================");
				} catch (FileNotFoundException e) {}
				System.out.println("t = " + (System.currentTimeMillis() - s));
				
				if (!ret.isValid())
				{
					continue;
				}
				return ret;
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
				continue;
			}
		}
		
		return new DownloadData();
	}
	
	static String getStringAt(Point l) throws InterruptedException
	{
		moveDaMouse(l);
		highlight();
		return get_selected_string();
	}
	
	static void highlight() throws InterruptedException
	{
		Thread.sleep(1000);
		robot.setAutoDelay(10);
		robot.mousePress(MouseEvent.BUTTON1_MASK);
		robot.mouseRelease(MouseEvent.BUTTON1_MASK);
		robot.mousePress(MouseEvent.BUTTON1_MASK);
		robot.mouseRelease(MouseEvent.BUTTON1_MASK);
		robot.mousePress(MouseEvent.BUTTON1_MASK);
		robot.mouseRelease(MouseEvent.BUTTON1_MASK);
	}
	
	public static void type(Point loc, String string) throws InterruptedException
	{
		moveDaMouse(loc);
		highlight();
		type(string);
	}
	
	public static void type(String string) throws InterruptedException
	{
		Thread.sleep(1000);
		robot.setAutoDelay(0);
		for (int i = 0; i < string.length(); i++)
		{
			int keyCode = KeyEvent.getExtendedKeyCodeForChar(string.charAt(i));
			robot.keyPress(keyCode);
			robot.keyRelease(keyCode);
		}
	}
	
	static String get_selected_string()
	{
	    robot.keyPress(KeyEvent.VK_CONTROL);
	    robot.keyPress(KeyEvent.VK_C);
	    robot.keyRelease(KeyEvent.VK_CONTROL);
	    robot.keyRelease(KeyEvent.VK_C);

	    Clipboard c = Toolkit.getDefaultToolkit().getSystemClipboard();
		Transferable t = c.getContents(null);
		if (t == null)
		{
			return null;
		}
		try
		{
			return (String) t.getTransferData(DataFlavor.stringFlavor);
		}
		catch (Exception e)
		{
	        e.printStackTrace();
	        return null;
	    }
	}
}

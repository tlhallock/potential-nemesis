package gmd;

import java.util.Random;

final class Coord
{
	static final Random random = new Random();
	private static final Coord lowerbound = new Coord(39.558185, -105.226243);
	private static final Coord upperbound = new Coord(40.211516, -104.745591);
	
	final double x, y;
	String desc;
	
	Coord(double x, double y) { this.x = x; this.y = y; }
	Coord() { this(next_uniform(lowerbound.x, upperbound.x), next_uniform(lowerbound.y, upperbound.y)); }
	
	private static double next_uniform(double l, double u) { return l + (u - l) * random.nextDouble(); }
}
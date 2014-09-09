package gmd;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Scrapts {

	static final Pattern distance = Pattern.compile("([0-9]*)");
	static final Pattern duration = Pattern.compile("([0-9]*)");
	
	private static long get_value(Pattern pattern, String string)
	{
		Matcher m = pattern.matcher(string);
		return m.find() ? new Long(m.group(1)) : -1;
	}
}

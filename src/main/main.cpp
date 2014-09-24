
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


void generate();
void simulate();
void verify();

int main(int argc, char **argv)
{
#if 0
	Current and next things I am working on:
		1. Finish writing the saveXml/loadXml
			rename saveXml -> save_xml
			combine everything under a single interface
		2. Implement the maximum number of containers at each staging area
		4. Finish implementing the genetic algorithm
			right now I am working on the breed function
			Almost all the stubs are empty...
		5. Add helpfull messages when Route.loadXml fails... almost all the logic for a validator should be there.
		6. This could use some unit tests :)
		7. Break off the main methods into: validate <city> <solution>, generate random city <out file>, solve methods <city> <outfile>
			Probably this will mean making a static .a file and compiling several main files against it.
			In the process, I should give this a real Makefile, instead of just using eclipse configs.
		8. Make the parameters also have a saveXml and loadXml method
			The Parameters class is passed around all the time, should this be static?
			Need to add types of distributions to this xml file too
		9. start profiling: I have some guesses why some of this is so slow...
			cache the get_time_taken()
			cache the already_services()
			5% of time is spent in shared_ptr<Action>
			5% of time is spent in get_distance
				I would like to use a distance table instead of calculate distances every the time
				This should be input into the algorithm (instead of x,y points? but then how would we plot it?)
		10. I should clean up the code, and maybe add comments.
			saveXml(bad parameter name)
			Action.get_points() is a bad name
		11. Should the spoke solution also spoke staging?
				maybe I should ensure staging areas are close to landfills
		12. Right now, in optimization utils, I do not consider paths that have have length more than two from a request (store->unstore->request)
		13. Add constraints to each request on which driver they can be attended by.
#endif

	srand(time(NULL));
	//srand(5000013);

	generate();
	simulate();
	verify();

	return 0;
}


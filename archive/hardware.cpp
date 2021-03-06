// WORKING VERSION OF ISR.CPP WITH ADDED LOG FILE WRITE FUNCTIONALITY

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <fstream>
using namespace std;



// What GPIO input are we using?
//	This is a wiringPi pin number

#define	BUTTON_PIN 22

static volatile int globalCounter = 0 ;
vector<int> intvector;
void myInterrupt (void)
{
	++globalCounter ;
}

int main (void)
{
	int myCounter = 0 ;

	if (wiringPiSetup () < 0)
	{
		fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
		return 1 ;
	}

	if (wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &myInterrupt) < 0)
	{
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
		return 1 ;
	}

	ofstream log_file;
	log_file.open("log_file.txt");

	for (;;)
	{
		log_file.open("log_file.txt" , ios::out|ios::app);
		printf ("Waiting ... ") ; fflush (stdout) ;
		while (myCounter == globalCounter){
			delay (100);
		}

		printf (" Done. counter: %5d\n", globalCounter) ;
		myCounter = globalCounter ;
		intvector.push_back(myCounter);
		log_file << (int) myCounter << " ";
		log_file.close();
		for (vector<int>::iterator z=intvector.begin(); z !=intvector.end(); ++ z)
    {
        cout << *z;
    }
	}

	return 0 ;
}
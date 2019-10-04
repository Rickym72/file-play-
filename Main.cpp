#include"tools.h"
#include"Run.h"
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;
using namespace RunNamespace;

typedef vector<Run> Runs;

void getData	( Runs &runs );
void mergeRuns	( Runs &runs );
void outputRun	( const Run &run );

int main(void)
{
	vector<Run> runs;
	getData		( runs );
	mergeRuns	( runs );
	outputRun	( runs[0] );

	//pause("Press ENTER to finish...");
	return 0;
}

void getData( Runs &runs )
{
	while (true)
	{
		ifstream dataStream;
		openIfStream( dataStream, "Enter name of file containing integer data: " );
		while (true)
		{
			int item;
			dataStream >> item;
			if ( dataStream.fail() ) break;
			runs.push_back( Run(item) );
		}
		if ( runs.size() > 0 ) break;
		cout << "No data in file - try again." << endl;
	}
}

void mergeRuns( Runs &runs )
{

	while ( runs.size() >  1)
	{
		Runs mergedRuns;

		for ( Runs::size_type index = 0 ; index+1 < runs.size() ; index += 2 )
			mergedRuns.push_back( runs[index] + runs[index+1] );

		if ( runs.size()%2 == 1)
			mergedRuns.push_back(runs[runs.size()-1]);

		runs = mergedRuns;
	}
}

void outputRun( const Run &run )
{
	ofstream sortedDataStream;
	openOfStream( sortedDataStream, "Enter name of file for sorted results: " );
	int lineCount = 0;
	for ( Run::size_type index = 0 ; index < run.size() ; ++index )
	{
		sortedDataStream << run[index] << ' ';
		if ( ++lineCount >= 10 )
		{
			sortedDataStream << endl;
			lineCount = 0;
		}
	}

}

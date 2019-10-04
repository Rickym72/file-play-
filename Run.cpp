#include"Run.h"
#include<assert.h>

namespace RunNamespace
{

	Run::Run(void) : local_size(0), data(new value_type[0]) {}

	Run::Run(value_type value) : local_size(1), data(new value_type[1]) { data[0] = value; }

	Run::Run( const Run &source ) : local_size(source.size())
	{
		if ( this == &source ) return;

		data = new value_type[source.size()];

		for ( size_type index = 0 ; index < size() ; ++index )
			data[index] = source.data[index];
	}

	Run::Run( const Run &mergeSourceA, const Run &mergeSourceB )
		: local_size(0),
			data( new value_type[mergeSourceA.local_size+mergeSourceB.local_size] )
	{
		Run::size_type firstUnusedIndexA = 0;
		Run::size_type firstUnusedIndexB = 0;
		while ( firstUnusedIndexA < mergeSourceA.local_size
				&& firstUnusedIndexB < mergeSourceB.local_size )
			insert( ( mergeSourceA[firstUnusedIndexA] < mergeSourceB[firstUnusedIndexB] )
								? mergeSourceA[firstUnusedIndexA++]
								: mergeSourceB[firstUnusedIndexB++]);
		while ( firstUnusedIndexA < mergeSourceA.local_size ) insert(mergeSourceA[firstUnusedIndexA++]);
		while ( firstUnusedIndexB < mergeSourceB.local_size ) insert(mergeSourceB[firstUnusedIndexB++]);
	}

	Run &Run::operator=( const Run &source )
	{
		if ( this == &source ) return *this;

		delete [] data;
		data = new value_type[local_size = source.local_size];
		for ( size_type index = 0 ; index < local_size ; ++index )
			data[index] = source[index];
		return *this;
	}

	Run operator+( const Run &mergeSource1, const Run &mergeSource2 )
	{
		return Run( mergeSource1, mergeSource2 );
	}

	Run::~Run(void) { delete [] data; }

	Run::size_type Run::size(void) const { return local_size; }

	Run::value_type Run::operator[](size_type index) const
	{
		assert( index < local_size );
		return data[index];
	}

	void Run::insert( value_type value )
	{
		data[local_size++] = value;
	}
}

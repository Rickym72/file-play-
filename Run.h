#ifndef RUN
#define RUN

namespace RunNamespace
{

	class Run
	{
	public:
		typedef size_t size_type;
		typedef int	value_type;

		Run(void);
		Run(int value);
		Run( const Run &source );
		Run( const Run &mergeSourceA, const Run &mergeSourceB );
		~Run(void);
		Run &operator=( const Run &source );
		friend Run operator+( const Run &mergeSourceA, const Run &mergeSourceB );
		size_type size(void) const;
		value_type operator[](size_type index) const;

	private:
		value_type *data;
		size_type local_size;
		void insert( value_type value );
	};

}

#endif

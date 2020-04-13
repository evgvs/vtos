int pow(int a , int b)
{
	int o = a;
	while ( b > 1 )
	{		
		o = o * a;
		b--;
	}
	if ( b == 0 )
	{
		return 1;
	}
	return o;
}

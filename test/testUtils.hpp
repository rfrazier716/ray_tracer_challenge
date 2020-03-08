template<class T>
inline void logVector(T vect)
{
	for (int j = 0; j < vect.length(); j++)
	{
		std::cout << vect[j] << " ";
	}
	std::cout << std::endl;
}
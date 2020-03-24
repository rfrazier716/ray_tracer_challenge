template<class T>
inline void logVector(T vect)
{
	std::cout << "<";
	for (int j = 0; j < vect.length(); j++)
	{
		std::cout << vect[j];
		char suffix = (j + 1) == vect.length() ? '>': ',';
		std::cout << suffix;
	}

	std::cout << std::endl;
}
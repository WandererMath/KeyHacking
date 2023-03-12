all: Me Victim

Me: Me.cpp
	g++ -o Me Me.cpp --static

Victim: Victim.cpp
	g++ -o Victim Victim.cpp

VictimR: Victim.cpp
	g++ -o Victim Victim.cpp --static
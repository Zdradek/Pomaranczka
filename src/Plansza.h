#ifndef plansza_H
#define plansza_H
class Plansza {
private:
	static const unsigned short board_height = 480, board_width = 640;
	static const unsigned long numberofelements = board_height * board_width;
public:
	void printPlansza(unsigned long *GRAPH);
};

#endif /* planszadron_H */

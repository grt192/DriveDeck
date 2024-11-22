void LCDsetup();

class Gui {
public:
Gui(char ID, int newX, int newY);
~Gui();
char letter;
int dir;
int maxdir;
int symbol;
int x;
int y;
void LCDloop(bool stopped, int counter);
};

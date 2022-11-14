class Player
{

    int score = 0;

public:
    Player();
    virtual void movepaddle() = 0;
    void updateScore();
};

class HumanPlayer : public Player
{

public:
    void movepaddle();
};

class PC : public Player
{

public:
    void movepaddle();
};
